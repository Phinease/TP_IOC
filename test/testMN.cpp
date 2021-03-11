#include "../src/kpSolver.cpp"
#include "../src/kpSolverDP.cpp"

#include <chrono>

using namespace std;

int main() {
    bool verboseMode = false;
    const char *instanceFile = "instances/kp_10000_1.in";

    ofstream outfile = ofstream("csv/testSolution.csv", ios::out | ios::trunc);
    string seq = ",";
    KpSolverDP kp;
    kp.setMemoizedVersion(false);
    kp.importInstance(instanceFile);
    kp.setVerboseMode(verboseMode);

    for (int i = 100; i < 1000; ++i) {
        kp.
    }

    cout << "Dynamic Programming iterative version  :" << endl << endl;
    auto start1 = std::chrono::steady_clock::now();
    kp.solve();
    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end1 - start1;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;

    kp.printKnapsackSolution(verboseMode);
    kp.clearInstance();

    kp.importInstance(instanceFile);
    kp.setVerboseMode(verboseMode);

//    cout << endl << "Dynamic Programming memoized version :" << endl << endl;
//    kp.setMemoizedVersion(true);
//    auto start2 = std::chrono::steady_clock::now();
//    kp.solve();
//    auto end2 = std::chrono::steady_clock::now();
//    elapsed_seconds = end2 - start2;
//    std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
//
//    kp.printKnapsackSolution(verboseMode);
//    kp.clearInstance();
//
//    kp.importInstance(instanceFile);
//    kp.setVerboseMode(verboseMode);
//
//    cout << endl << "Dynamic Programming parallelized version :" << endl << endl;
//    kp.setMemoizedVersion(false);
//    kp.setParallelizedVersion(true);
//    auto start3 = std::chrono::steady_clock::now();
//    kp.solve();
//    auto end3 = std::chrono::steady_clock::now();
//    elapsed_seconds = end3 - start3;
//    std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
//
//    kp.printKnapsackSolution(verboseMode);

    return 0;
}
