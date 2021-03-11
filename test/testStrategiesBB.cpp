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

BranchingStrategies &operator++(BranchingStrategies &e) {
    if (e == BranchingStrategies::End) {
        throw std::out_of_range("for E& operator ++ (E&)");
    }
    e = BranchingStrategies(static_cast<std::underlying_type<BranchingStrategies>::type>(e) + 1);
    return e;
}

string printModeBranching(BranchingStrategies b) {
    switch (b) {
        case BestBound:
            return "BestBound";
        case BFS:
            return "BFS";
        case DFS10:
            return "DFS10";
        case DFS01:
            return "DFS01";
        case Random:
            return "Random";
        case End:
            return "";
    }
}

void printResultmodeBranching(KpSolverBB &kpBB, BranchingStrategies b) {
    kpBB.setBranchingStrategy(b);

    auto start = std::chrono::steady_clock::now();
    kpBB.solve();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    outfile << printModeBranching(b) << seq << elapsed_seconds.count()
            << seq << kpBB.getNbNodes() << seq << kpBB.gap << endl;
}

int main() {
    vector<string> files{
            "instances/kp_100_2.in",
            "instances/kp_1000_2.in",
            "instances/kp_10000_2.in",
            "instances/kp_100000_2.in"
    };

    outfile = ofstream("csv/testStrategiesBB.csv", ios::out | ios::trunc);
    outfile << "File" << seq << "Algo" << seq << "Strategy" << seq
            << "Time" << seq << "Nb Noeuds" << seq << "gap" << endl;

    for (auto &file : files) {
        KpSolverGreedy kpGreedy;
        KpSolverBB kpBB;
        kpBB.setVerboseMode(false);
        kpBB.setNbMaxNodeBb(10000);
        kpBB.setSizeDPheur(100);
        kpBB.setWithPrimalHeuristics(false);
        kpBB.setWithDPinitPrimalHeuristic(false);

        cout << file << ": " << endl;
        kpGreedy.importInstance(file);
        auto start = std::chrono::steady_clock::now();
        kpGreedy.solve();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        outfile << file.substr(file.find_last_of('/') + 1) << seq << "Greedy" << seq << ""
                << seq << elapsed_seconds.count() << seq << "" <<endl;

        kpBB.importInstance(file);
        cout << "Mode sans heuristique: " << endl;
        for (BranchingStrategies modeBranch = BranchingStrategies::BestBound;
             modeBranch != BranchingStrategies::End; ++modeBranch) {
            cout << printModeBranching(modeBranch) << ": " << endl;
            outfile << file.substr(file.find_last_of('/') + 1) << seq << "B&B" << seq;
            printResultmodeBranching(kpBB, modeBranch);
            cout << "-------------------------------------" << endl;
        }

        cout << "Mode avec heuristique: " << endl;
        kpBB.setWithPrimalHeuristics(true);
        for (BranchingStrategies modeBranch = BranchingStrategies::BestBound;
             modeBranch != BranchingStrategies::End; ++modeBranch) {
            cout << printModeBranching(modeBranch) << ": " << endl;
            outfile << file.substr(file.find_last_of('/') + 1) << seq << "B&B - Heur" << seq;
            printResultmodeBranching(kpBB, modeBranch);
            cout << "-------------------------------------" << endl;
        }

        cout << "Mode avec heuristique DP: " << endl;
        kpBB.setWithDPinitPrimalHeuristic(true);
        for (BranchingStrategies modeBranch = BranchingStrategies::BestBound;
             modeBranch != BranchingStrategies::End; ++modeBranch) {
            cout << printModeBranching(modeBranch) << ": " << endl;
            outfile << file.substr(file.find_last_of('/') + 1) << seq << "B&B - HeurDP" << seq;
            printResultmodeBranching(kpBB, modeBranch);
            cout << "-------------------------------------" << endl;
        }

        kpGreedy.clearInstance();
        kpBB.clearInstance();
    }
    outfile.close();
    return 0;
}
