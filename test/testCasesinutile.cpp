//
// Created by Shuangrui CHEN on 27/11/2020.
//

#include "../src/kpSolverHeurDP.cpp"
#include "../src/kpSolverDP.cpp"
#include "../src/kpSolver.cpp"
#include "../src/kpSolverGreedy.cpp"


using namespace std;

int main() {
    string instanceFile = "./instances/kp_10000_1.in";
    ofstream outfile("./csv/testTauxInutil.csv", ios::out | ios::trunc);
    string sep = ",";

    KpSolverDP kpDP;
    kpDP.setMemoizedVersion(true);
    kpDP.setVerboseMode(false);

    outfile << "Taille" << sep << "TauxInutile" << endl;
    for (int i = 2; i < 600 ; i++) {
        kpDP.importInstance(instanceFile);
        kpDP.extractSubInstance(0, i);
        kpDP.solve();
        outfile << i << sep << kpDP.getTauxInutile() << endl;
        cout << "Taux de cases inutiles " << kpDP.getNbItems() << ": " << kpDP.getTauxInutile() << endl;
        kpDP.clearInstance();
    }

    outfile.close();
    return 0;

}
