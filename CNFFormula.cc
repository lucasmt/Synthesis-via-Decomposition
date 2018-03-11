#include "CNFFormula.hpp"
#include "Map.hpp"

#include <numeric>

using std::iota;

/** CNFClause **/

CNFClause::CNFClause() {}

CNFClause::CNFClause(BLit lit)
{
  _lits = { lit };
}

CNFClause::CNFClause(BLit l1, BLit l2)
{
  _lits = { l1, l2 };
}

CNFClause& CNFClause::operator|=(BLit lit)
{
  _lits.push_back(lit);

  return *this;
}

CNFClause& CNFClause::operator|=(const CNFClause& other)
{
  _lits.insert(_lits.end(), other._lits.begin(), other._lits.end());

  return *this;
}

CNFClause CNFClause::operator|(const CNFClause& other) const
{
  CNFClause newClause(*this);

  newClause |= other;

  return newClause;
}

CNFClause CNFClause::atLeastOne(const Set<BVar>& vars)
{
  CNFClause clause;

  for (BVar var : vars)
    clause |= var;

  return clause;
}

CNFClause CNFClause::projection(const Set<BVar>& vars) const
{
  CNFClause newClause;

  /* Add literal to new clause only if its variable appears in vars */
  for (BLit lit : _lits)
    if (vars.find(abs(lit)) != vars.end())
      newClause |= lit;

  return newClause;
}

/** CNFFormula **/

CNFFormula::CNFFormula() {}

CNFFormula& CNFFormula::operator&=(const CNFClause& clause)
{
  _clauses.push_back(clause);

  return *this;
}

CNFFormula& CNFFormula::operator&=(const CNFFormula& other)
{
  _clauses.insert(_clauses.end(),
		  other._clauses.begin(),
		  other._clauses.end());

  return *this;
}

CNFFormula CNFFormula::operator&(const CNFFormula& other) const
{
  CNFFormula cnf(*this);

  cnf &= other;

  return cnf;
}

CNFClause& CNFFormula::operator[](size_t i)
{
  return _clauses[i];
}

const CNFClause& CNFFormula::operator[](size_t i) const
{
  return _clauses[i];
}

const Vector<CNFClause>& CNFFormula::clauses() const
{
  return _clauses;
}

CNFFormula CNFFormula::projection(const Set<BVar>& vars) const
{
  CNFFormula newCNF;

  for (const CNFClause& clause : _clauses)
    newCNF &= clause.projection(vars);

  return newCNF;
}

Graph<size_t> CNFFormula::dependencyGraph() const
{
  /* Initialize a graph with one vertex for every clause */
  Vector<size_t> range(_clauses.size());
  iota(range.begin(), range.end(), 0);
  Graph<size_t> g(range);

  /* Collects for every variable the indices of the clauses where it appears */
  Map<BVar, Set<size_t>> appearances;

  for (size_t i = 0; i < _clauses.size(); i++)
    for (const BLit& lit : _clauses[i])
      appearances[abs(lit)].insert(i);

  /* Add an edge for each pair of clauses that share a variable */
  for (const auto& entry : appearances)
    for (size_t i : entry.second)
      for (size_t j : entry.second)
      {
	g.addEdge(i, j);
	g.addEdge(j, i);
      }

  return g;
}
