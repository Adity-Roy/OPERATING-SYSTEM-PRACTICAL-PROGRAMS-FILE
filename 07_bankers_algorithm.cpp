#include <iostream>
#include <vector>
using namespace std;

const int P = 5, R = 3;
int available[R], maximum[P][R], allocation[P][R], need[P][R];

void calculateNeed() {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];
}

bool isSafe(int safeSeq[]) {
    int work[R], finish[P] = {0};
    for (int j = 0; j < R; j++) work[j] = available[j];
    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < R; j++)
                    if (need[i][j] > work[j]) break;
                if (j == R) {
                    for (int k = 0; k < R; k++) work[k] += allocation[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (!found) return false;
    }
    return true;
}

bool requestResources(int pid, int request[]) {
    for (int j = 0; j < R; j++) {
        if (request[j] > need[pid][j]) {
            cout << "Error: process has exceeded its maximum claim.\n";
            return false;
        }
        if (request[j] > available[j]) {
            cout << "Request denied: not enough resources available.\n";
            return false;
        }
    }

    for (int j = 0; j < R; j++) {
        available[j] -= request[j];
        allocation[pid][j] += request[j];
        need[pid][j] -= request[j];
    }

    int safeSeq[P];
    if (isSafe(safeSeq)) {
        cout << "Request can be granted safely.\n";
        return true;
    }

    for (int j = 0; j < R; j++) {
        available[j] += request[j];
        allocation[pid][j] -= request[j];
        need[pid][j] += request[j];
    }
    cout << "Request denied: would lead to an unsafe state.\n";
    return false;
}

int main() {
    cout << "Enter available resources of each type (" << R << " types): ";
    for (int j = 0; j < R; j++) cin >> available[j];

    cout << "Enter Maximum matrix (" << P << " processes x " << R << " resources):\n";
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++) cin >> maximum[i][j];

    cout << "Enter Allocation matrix:\n";
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++) cin >> allocation[i][j];

    calculateNeed();
    int safeSeq[P];
    if (isSafe(safeSeq)) {
        cout << "System is in a SAFE state.\nSafe sequence: ";
        for (int i = 0; i < P; i++) cout << "P" << safeSeq[i] << " ";
        cout << '\n';
    } else {
        cout << "System is in an UNSAFE state.\n";
    }

    int pid, request[R];
    cout << "\nEnter process number requesting resources (0 to " << P - 1 << "): ";
    cin >> pid;
    cout << "Enter request vector (" << R << " values): ";
    for (int j = 0; j < R; j++) cin >> request[j];
    if (pid >= 0 && pid < P) requestResources(pid, request);
    else cout << "Invalid process number.\n";
    return 0;
}