#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isPresent(const vector<int>& frames, int page) {
    return find(frames.begin(), frames.end(), page) != frames.end();
}

void fifo(const vector<int>& ref, int nf) {
    vector<int> frames(nf, -1);
    int front = 0, faults = 0;
    for (int page : ref) {
        if (!isPresent(frames, page)) {
            frames[front] = page;
            front = (front + 1) % nf;
            faults++;
        }
    }
    cout << "FIFO Page Faults = " << faults << '\n';
}

void lru(const vector<int>& ref, int nf) {
    vector<int> frames, lastUsed;
    int faults = 0;
    for (int i = 0; i < (int)ref.size(); i++) {
        auto it = find(frames.begin(), frames.end(), ref[i]);
        if (it == frames.end()) {
            faults++;
            if ((int)frames.size() < nf) {
                frames.push_back(ref[i]);
                lastUsed.push_back(i);
            } else {
                int idx = min_element(lastUsed.begin(), lastUsed.end()) - lastUsed.begin();
                frames[idx] = ref[i];
                lastUsed[idx] = i;
            }
        } else {
            lastUsed[it - frames.begin()] = i;
        }
    }
    cout << "LRU Page Faults = " << faults << '\n';
}

void optimal(const vector<int>& ref, int nf) {
    vector<int> frames;
    int faults = 0;
    for (int i = 0; i < (int)ref.size(); i++) {
        if (isPresent(frames, ref[i])) continue;
        faults++;
        if ((int)frames.size() < nf) {
            frames.push_back(ref[i]);
            continue;
        }
        int replaceIdx = -1, farthest = -1;
        for (int j = 0; j < nf; j++) {
            int k;
            for (k = i + 1; k < (int)ref.size(); k++)
                if (frames[j] == ref[k]) break;
            if (k == (int)ref.size()) { replaceIdx = j; break; }
            if (k > farthest) { farthest = k; replaceIdx = j; }
        }
        frames[replaceIdx] = ref[i];
    }
    cout << "Optimal Page Faults = " << faults << '\n';
}

int main() {
    int n, nf;
    cout << "Enter number of pages in reference string: ";
    cin >> n;
    vector<int> ref(n);
    cout << "Enter the reference string: ";
    for (int &x : ref) cin >> x;
    cout << "Enter number of frames: ";
    cin >> nf;
    if (n <= 0 || nf <= 0) {
        cout << "Invalid input\n";
        return 1;
    }
    fifo(ref, nf);
    lru(ref, nf);
    optimal(ref, nf);
    return 0;
}