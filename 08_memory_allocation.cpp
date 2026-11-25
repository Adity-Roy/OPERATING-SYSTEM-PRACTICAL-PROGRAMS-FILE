#include <iostream>
#include <vector>
using namespace std;

void display(string title, vector<int> allocation, vector<int> psize) {
    cout << "\n--- " << title << " ---\n";
    cout << "Process No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < (int)psize.size(); i++) {
        cout << "P" << i + 1 << "\t\t" << psize[i] << "\t\t";
        if (allocation[i] == -1) cout << "Not Allocated\n";
        else cout << "B" << allocation[i] + 1 << '\n';
    }
}

void firstFit(vector<int> bsize, vector<int> psize) {
    vector<int> allocation(psize.size(), -1);
    for (int i = 0; i < (int)psize.size(); i++)
        for (int j = 0; j < (int)bsize.size(); j++)
            if (bsize[j] >= psize[i]) {
                allocation[i] = j;
                bsize[j] -= psize[i];
                break;
            }
    display("First Fit", allocation, psize);
}

void bestFit(vector<int> bsize, vector<int> psize) {
    vector<int> allocation(psize.size(), -1);
    for (int i = 0; i < (int)psize.size(); i++) {
        int bestIdx = -1;
        for (int j = 0; j < (int)bsize.size(); j++)
            if (bsize[j] >= psize[i] &&
                (bestIdx == -1 || bsize[j] < bsize[bestIdx]))
                bestIdx = j;
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            bsize[bestIdx] -= psize[i];
        }
    }
    display("Best Fit", allocation, psize);
}

void worstFit(vector<int> bsize, vector<int> psize) {
    vector<int> allocation(psize.size(), -1);
    for (int i = 0; i < (int)psize.size(); i++) {
        int worstIdx = -1;
        for (int j = 0; j < (int)bsize.size(); j++)
            if (bsize[j] >= psize[i] &&
                (worstIdx == -1 || bsize[j] > bsize[worstIdx]))
                worstIdx = j;
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            bsize[worstIdx] -= psize[i];
        }
    }
    display("Worst Fit", allocation, psize);
}

int main() {
    int bn, pn;
    cout << "Enter number of memory blocks: ";
    cin >> bn;
    vector<int> bsize(bn);
    cout << "Enter sizes of blocks: ";
    for (int &x : bsize) cin >> x;
    cout << "Enter number of processes: ";
    cin >> pn;
    vector<int> psize(pn);
    cout << "Enter sizes of processes: ";
    for (int &x : psize) cin >> x;
    firstFit(bsize, psize);
    bestFit(bsize, psize);
    worstFit(bsize, psize);
    return 0;
}