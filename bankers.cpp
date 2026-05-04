bool isSafe(vector<int> processes, vector<int> avail,
            vector<vector<int>> max,
            vector<vector<int>> allot,
            int P, int R) {

    vector<vector<int>> need(P, vector<int>(R));
    vector<bool> finish(P, false);
    vector<int> safeSeq(P);
    vector<int> work = avail;

    // Calculate Need
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];

    // Print Need matrix
    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }

    int count = 0;

    while (count < P) {
        bool found = false;

        for (int p = 0; p < P; p++) {
            if (!finish[p]) {

                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += allot[p][k];

                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "\nSystem is NOT SAFE\n";
            return false;
        }
    }

    cout << "\nSystem is SAFE\nSafe sequence: ";
    for (int i = 0; i < P; i++)
        cout << "P" << safeSeq[i] << " ";

    cout << endl;

    return true;
}