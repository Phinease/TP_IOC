//
// Created by Shuangrui CHEN on 07/03/2021.
//

#include "../src/kpSolver.cpp"
#include "../src/kpSolverGreedy.cpp"
#include "../src/kpSolverBB.cpp"
#include <chrono>
#include <string>

using namespace std;

ofstream outfile;
string seq = ",";

void printResultmodeBranching(KpSolverBB &kpBB, BranchingStrategies b) {
    kpBB.setBranchingStrategy(b);

    auto start = std::chrono::steady_clock::now();
    kpBB.solve();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    outfile << kpBB.getNbNodes() << seq << kpBB.getUpperBound() << seq
            << kpBB.getSolutionCost() << seq << kpBB.gap << seq << elapsed_seconds.count() << endl;

}

int main() {
    vector<string> files{
            "instances/kp_100_1.in",
            "instances/kp_100_2.in",
            "instances/kp_1000_1.in",
            "instances/kp_1000_2.in",
            "instances/kp_10000_1.in",
            "instances/kp_10000_1_0.1.in",
            "instances/kp_10000_1_0.01.in",
            "instances/kp_10000_1_0.02.in",
            "instances/kp_10000_1_0.03.in",
            "instances/kp_10000_1_0.04.in",
            "instances/kp_10000_1_0.05.in",
            "instances/kp_10000_2.in",
            "instances/kp_100000_1.in",
            "instances/kp_100000_2.in"
    };

    outfile = ofstream("csv/testSolution.csv", ios::out | ios::trunc);
    outfile << "File"
            //            << seq << "Nb Noeuds"
            << seq << "Upperbound" << seq
            << "Solution" << seq << "gap" << seq << "Time" << endl;

    for (auto &file : files) {
//        KpSolverBB kpBB;
//        kpBB.setVerboseMode(false);
//        kpBB.setNbMaxNodeBb(10000);
//        kpBB.setSizeDPheur(100);
//        kpBB.setWithPrimalHeuristics(false);
//        kpBB.setWithDPinitPrimalHeuristic(false);
//        kpBB.importInstance(file);
//
//        cout << file << ": " << endl;
//        kpBB.setWithPrimalHeuristics(true);
//        kpBB.setWithDPinitPrimalHeuristic(true);
//        outfile << file.substr(file.find_last_of('/') + 1) << seq;
//        printResultmodeBranching(kpBB, BestBound);
//        kpBB.clearInstance();

//        cout << file << endl;
//        outfile << file.substr(file.find_last_of('/') + 1) << seq;
//        KpSolverDP kpDP;
//        kpDP.setVerboseMode(false);
//        kpDP.setMemoizedVersion(true);
//        kpDP.importInstance(file);
//        auto start = std::chrono::steady_clock::now();
//        kpDP.solve();
//        auto end = std::chrono::steady_clock::now();
//        std::chrono::duration<double> elapsed_seconds = end - start;
//        outfile << kpDP.getUpperBound() << seq
//                << kpDP.getSolutionCost() << seq
//                << (floor(kpDP.getUpperBound()) - (double) kpDP.getSolutionCost()) / (double) kpDP.getSolutionCost()
//                << seq << elapsed_seconds.count() << endl;

        cout << file << endl;
        outfile << file.substr(file.find_last_of('/') + 1) << seq;
        KpSolverGreedy kpGreedy;
        kpGreedy.importInstance(file);
        auto start = std::chrono::steady_clock::now();
        kpGreedy.solve();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        outfile << kpGreedy.getUpperBound() << seq
                << kpGreedy.getSolutionCost() << seq
                << (floor(kpGreedy.getUpperBound()) - (double) kpGreedy.getSolutionCost()) / (double) kpGreedy.getSolutionCost() << seq
                << elapsed_seconds.count() << endl;
    }
    outfile.close();
    return 0;
}
