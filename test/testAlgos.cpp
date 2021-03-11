#include "../src/kpSolver.cpp"
#include "../src/kpSolverGreedy.cpp"
#include "../src/kpSolverBB.cpp"
#include <chrono>
#include <string>

using namespace std;

int main() {
    ofstream outfile;
    string seq = ",";
    bool verboseMode = false;
    const char *instanceFile = "instances/kp_100000_1.in";
    outfile = ofstream("csv/testAlgos.csv", ios::out | ios::trunc);
    outfile << "Nb Instance" << seq << "Glouton" << seq << "Heur" << seq << "DP"
            << seq << "BB - Heur - BestBound" << endl;

    for (int i = 0; i < 80; ++i) {
        cout << endl << "[0, " << 100 + i * 100 << "]: " << endl;
        outfile << 100 + i * 100 << seq;

        KpSolverGreedy kpGreedy;
        kpGreedy.importInstance(instanceFile);
        kpGreedy.extractSubInstance(0, 100 + 100 * i);
        auto start = std::chrono::steady_clock::now();
        kpGreedy.solve();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        outfile << elapsed_seconds.count() << seq;

        KpSolverHeurDP kpHeurDP;
        kpHeurDP.importInstance(instanceFile);
        kpHeurDP.extractSubInstance(0, 100 + 100 * i);
        kpHeurDP.setNeighborhood(100, 100);
        start = std::chrono::steady_clock::now();
        kpHeurDP.solve();
        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;
        outfile << elapsed_seconds.count() << seq;

        KpSolverDP kpDP;
        kpDP.setMemoizedVersion(false);
        kpDP.setVerboseMode(verboseMode);
        kpDP.importInstance(instanceFile);
        kpDP.extractSubInstance(0, 100 + 100 * i);
        start = std::chrono::steady_clock::now();
        kpDP.solve();
        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;
        outfile << elapsed_seconds.count() << seq;

        KpSolverBB kpBB;
        kpBB.setVerboseMode(verboseMode);
        kpBB.setNbMaxNodeBb(10000);
        kpBB.setSizeDPheur(100);
        kpBB.setWithPrimalHeuristics(true);
        kpBB.setWithDPinitPrimalHeuristic(false);
        kpBB.importInstance(instanceFile);
        kpBB.extractSubInstance(0, 100 + i * 100);
        start = std::chrono::steady_clock::now();
        kpBB.solve();
        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;
        outfile << elapsed_seconds.count() << endl;
    }

    outfile.close();
    return 0;
}