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
    outfile << kpBB.getNbNodes() << seq;
}


int main() {
    bool verboseMode = false;
    const char *instanceFile = "instances/kp_100000_1.in";
    outfile = ofstream("csv/testComplexiteNBNoeud.csv", ios::out | ios::trunc);
    outfile << "Nb Instance" << seq
            << "BestBound, DFS10,DFS01, BFS,Random" << seq
            << "Heur - BestBound,Heur - DFS10,Heur - FS01,Heur - BFS,Heur - Random" << seq
            << "DP - BestBound" << endl;

    for (int i = 0; i < 80; ++i) {
        KpSolverBB kpBB;
        kpBB.setVerboseMode(verboseMode);
        kpBB.setNbMaxNodeBb(10000);
        kpBB.setSizeDPheur(100);
        kpBB.setWithPrimalHeuristics(false);
        kpBB.setWithDPinitPrimalHeuristic(false);
        kpBB.importInstance(instanceFile);
        kpBB.extractSubInstance(0, 100 + i * 100);
        outfile << 100 + i * 100 << seq;

        cout << endl << "[0, " << 100 + i * 100 << "]: " << endl << endl;
        cout << endl << "Resultats sans heuristique gloutonne:" << endl;
        for (BranchingStrategies modeBranch = BranchingStrategies::BestBound;
             modeBranch != BranchingStrategies::End; ++modeBranch) {
            cout << printModeBranching(modeBranch) << ": ";
            printResultmodeBranching(kpBB, modeBranch);
        }

        cout << endl << "Resultats avec heuristique gloutonne:" << endl << endl;
        kpBB.setWithPrimalHeuristics(true);
        for (BranchingStrategies modeBranch = BranchingStrategies::BestBound;
             modeBranch != BranchingStrategies::End; ++modeBranch) {
            cout << printModeBranching(modeBranch) << ": ";
            printResultmodeBranching(kpBB, modeBranch);
        }

//        cout << endl << "Resultats avec heuristique prog dyanmqiue:" << endl << endl;
//        kpBB.setWithDPinitPrimalHeuristic(true);
//        printResultmodeBranching(kpBB, BestBound);

        outfile << endl;
    }

    return 0;
}