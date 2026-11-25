#include <iostream>
#include <vector>
using namespace std;

const int MAXBLOCKS = 30;

void resetDisk(vector<int>& disk) {
    fill(disk.begin(), disk.end(), 0);
}

void contiguousAllocation() {
    vector<int> disk(MAXBLOCKS, 0);
    int nf;
    resetDisk(disk);
    cout << "\n--- Contiguous Allocation ---\n";
    cout << "Enter number of files: ";
    cin >> nf;
    for (int f = 0; f < nf; f++) {
        int start, len;
        cout << "File " << f + 1 << " - starting block, length: ";
        cin >> start >> len;
        bool ok = start >= 0 && len > 0 && start + len <= MAXBLOCKS;
        for (int i = start; ok && i < start + len; i++)
            if (disk[i] == 1) ok = false;
        if (!ok) {
            cout << "Allocation failed: blocks not free/out of range.\n";
            continue;
        }
        for (int i = start; i < start + len; i++) disk[i] = 1;
        cout << "File " << f + 1 << " allocated blocks "
             << start << " to " << start + len - 1 << '\n';
    }
}

void linkedAllocation() {
    vector<int> disk(MAXBLOCKS, 0);
    int nf;
    resetDisk(disk);
    cout << "\n--- Linked Allocation ---\n";
    cout << "Enter number of files: ";
    cin >> nf;
    for (int f = 0; f < nf; f++) {
        int len;
        cout << "File " << f + 1 << " - number of blocks: ";
        cin >> len;
        cout << "File " << f + 1 << " allocated blocks: ";
        int count = 0;
        for (int i = 0; i < MAXBLOCKS && count < len; i++) {
            if (disk[i] == 0) {
                disk[i] = 1;
                if (count > 0) cout << " -> ";
                cout << i;
                count++;
            }
        }
        cout << " -> (NULL)\n";
        if (count < len) cout << "Warning: disk full, could not allocate all blocks.\n";
    }
}

void indexedAllocation() {
    vector<int> disk(MAXBLOCKS, 0);
    int nf;
    resetDisk(disk);
    cout << "\n--- Indexed Allocation ---\n";
    cout << "Enter number of files: ";
    cin >> nf;
    for (int f = 0; f < nf; f++) {
        int len;
        cout << "File " << f + 1 << " - number of data blocks needed: ";
        cin >> len;
        int indexBlock = -1;
        for (int i = 0; i < MAXBLOCKS; i++)
            if (disk[i] == 0) {
                indexBlock = i;
                disk[i] = 1;
                break;
            }
        if (indexBlock == -1) {
            cout << "No free block available for index block.\n";
            continue;
        }
        cout << "File " << f + 1 << " - Index block: " << indexBlock
             << ", Data blocks: ";
        int count = 0;
        for (int i = 0; i < MAXBLOCKS && count < len; i++)
            if (disk[i] == 0) {
                disk[i] = 1;
                cout << i << " ";
                count++;
            }
        cout << '\n';
        if (count < len) cout << "Warning: disk full, could not allocate all data blocks.\n";
    }
}

int main() {
    int choice;
    cout << "Menu:\n1. Contiguous Allocation\n2. Linked Allocation\n3. Indexed Allocation\nEnter choice: ";
    cin >> choice;
    switch (choice) {
        case 1: contiguousAllocation(); break;
        case 2: linkedAllocation(); break;
        case 3: indexedAllocation(); break;
        default: cout << "Invalid choice\n";
    }
    return 0;
}