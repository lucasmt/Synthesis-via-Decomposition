/* DF 4.4.2018.
 * This class is designed to verify the list of MSS that we get from Algorithm.hpp. 
 * Given a list L ={<M1,a1>,.....<Mn,an>} of tuples where each Mi is an MSS and ai is a corresponding assigment, we would like to verify that this list is indeed a solution for our synthesis problem.
 * Our general synthesis algorithm works as follows:
 * 
0) Assume F(x,y) is our input formula, F1(x) is the x part and F2(x) is the y part.
1) Given an input c to x, let F1^f(c) be the false clauses of F1(c).
2) Find an MSS s from our list L that contains F1^f(c).
3) Find in our list the matching assignment d for y that corresponds to the MSS s
4) Return s.

Now in this class we need to verify this algorithm. For this we need to verify the list L and to verify step 2 of the algorithm.

* Verify step 2 of the algorithm looks easy (algorithmically).

* To verify the list L of MSS we need to do the following:
 
1) We need to make sure that for every input c for x, F1^f(c) is contained in an mss from L.

2) We need to verify that our list works: namely that if <s,d> is an <MSS,assignment for y> in our list
then that d satisfies all the clauses in s.


We present several methods for (1) and a simple method for (2).

*/

#include "Verifier.hpp"
#include <iostream>
using std::cout;
using std::endl;



Verifier::Verifier(Vector<Set<BVar>> mssList,CNFSpec spec) : f(spec)  //This notation means that f is initiallized with spec, without first initializing empty f.
{
    this->mssList = mssList;
   // this->f = spec;                 //This would not work since CNFSpec does not have an empty constructor
    printf("Verifier Generated\n");
}

Verifier::~Verifier(){}

bool Verifier::VerifyList()
{
    printf("Verifying list\n");
    
     for (const Set<BVar>& mss : this->mssList)
      {
	

	Set<BVar> indicatorAssignment = setDifference(mss, f.outputVars());
	print(indicatorAssignment, "z");

	cout << " |-> Output assignment: ";

	Set<BVar> outputAssignment = setDifference(mss, indicatorAssignment);
	print(outputAssignment, "y");

	cout << endl;
      }
    return true;
}

//bool VerifyInputCover();

//bool RandomVerifyInputCover();