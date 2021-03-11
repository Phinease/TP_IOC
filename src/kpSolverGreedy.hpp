//********* kpSolverGreedy.hpp *********

#ifndef KPSOLVERGREEDY_HPP
#define KPSOLVERGREEDY_HPP

#include "kpSolver.hpp"

class KpSolverGreedy : public KpSolver {


public:
    void solveLowerBound();

    void solveUpperBound();

    //solve() appelle les deux calculs de bornes precedents, encadre l'optimum avec une complexité en temps O(n log n)
    void solve();


};


#endif
