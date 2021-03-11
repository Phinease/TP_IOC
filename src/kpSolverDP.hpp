//********* kpSolver.hpp *********

#ifndef KPSOLVERDP_HPP
#define KPSOLVERDP_HPP

#include "kpSolver.hpp"

class KpSolverDP : public KpSolver {

private:

    //matrice de programmation dynamique
    int **matrixDP;

    //option pour appeler la memoisation
    bool memoizedVersion;
    //option pour appeler le mode verbeux du solveur, et afficher la matrice de programmation dynamique
    bool verboseMode;

    void solveIter();

    // construction itérative de la matrice de prog dynamique
    int solveMemoized(int i, int m);

    void backtrack();

    // construction et destruction de la matrice de prog dynamique
    void createMatrixDP();

    void deleteMatrixDP();

    //affichage de la matrice de prog dynamique
    void printMatrixDP();

    // construction de la première ligne de la matrice de prog dynamique (relative au premier objet)
    void fillFirstColumnDP();

    bool parallelizedVersion;

public:
    double gap;

    void solve();

    void setMemoizedVersion(bool memoizedVersion);

    void setVerboseMode(bool verbosemode);

    void setParallelizedVersion(bool parallelVersion);

    void solveIterParallel();

    void updateKpSolverDP(vector<int> &newWeights, vector<int> &newValues, int newBound);
};

#endif

