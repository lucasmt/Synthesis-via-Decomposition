#pragma once

#include "CNFFormula.hpp"
#include "Set.hpp"
#include "Vector.hpp"

#include <functional>

/**
 * Second component of the CNF decomposition:
 * (z_1 -> Y_1) /\ (z_2 -> Y_2) /\ ... /\ (z_n -> Y_n)
 */
class MSSSpec
{
	Vector<BVar> _indicatorVars; /**< z_1, z_2, ..., z_n */
	Set<BVar> _outputVars; /**< y_1, y_2, ..., y_k */
	CNFFormula _outputCNF; /**< Y_1 /\ Y_2 /\ ... /\ Y_n */

public:

	MSSSpec(Vector<BVar> indicatorVars, Set<BVar> outputVars, CNFFormula outputCNF);

	const Vector<BVar>& indicatorVars() const;
	const Set<BVar>& outputVars() const;
	const CNFFormula& outputCNF() const;

	BVar maxVar() const;

	/**
	 * Iterates over clauses, executing the visitor function for each.
	 * Example: For a clause of the form (z -> (l_1 | ... | l_k)),
	 * the inputs given to the visitor would be (z, (l_1, ..., l_k)).
	 */  
	void forEach(std::function<void(BVar, const CNFClause&)> visitor) const;
};
