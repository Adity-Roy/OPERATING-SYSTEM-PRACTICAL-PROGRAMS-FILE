#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int absDiff(int a, int b) {
    return abs(a - b);
}

void fcfs(const vector<int>& req, int head) {
    int total = 0, cur = head;
    for (int x : req) {
        total += absDiff(cur, x);
        cur = x;
    }
    cout << "FCFS total head movement = " << total << '\n';
}

void sstf(const vector<int>& req, int head) {
    vector<bool> visited(req.size(), false);
    int total = 0, cur = head;
    for (int c = 0; c < (int)req.size(); c++) {
        int idx = -1, best = INT_MAX;
        for (int i = 0; i < (int)req.size(); i++)
            if (!visited[i] && absDiff(cur, req[i]) < best) {
                best = absDiff(cur, req[i]);
                idx = i;
            }
        visited[idx] = true;
        total += best;
        cur = req[idx];
    }
    cout << "SSTF total head movement = " << total << '\n';
}

void scan(vector<int> req, int head, int diskSize) {
    req.push_back(head);
    sort(req.begin(), req.end());
    int idx = lower_bound(req.begin(), req.end(), head) - req.begin();
    int total = 0, cur = head;
    for (int i = idx + 1; i < (int)req.size(); i++) {
        total += absDiff(cur, req[i]);
        cur = req[i];
    }
    total += absDiff(cur, diskSize - 1);
    cur = diskSize - 1;
    for (int i = idx - 1; i >= 0; i--) {
        total += absDiff(cur, req[i]);
        cur = req[i];
    }
    cout << "SCAN total head movement = " << total << '\n';
}

void cscan(vector<int> req, int head, int diskSize) {
    req.push_back(head);
    sort(req.begin(), req.end());
    int idx = lower_bound(req.begin(), req.end(), head) - req.begin();
    int total = 0, cur = head;
    for (int i = idx + 1; i < (int)req.size(); i++) {
        total += absDiff(cur, req[i]);
        cur = req[i];
    }
    total += absDiff(cur, diskSize - 1);
    total += diskSize - 1;
    cur = 0;
    for (int i = 0; i < idx; i++) {
        total += absDiff(cur, req[i]);
        cur = req[i];
    }
    cout << "C-SCAN total head movement = " << total << '\n';
}

int main() {
    int n, head, diskSize;
    cout << "Enter number of requests: ";
    cin >> n;
    vector<int> req(n);
    cout << "Enter the requests: ";
    for (int &x : req) cin >> x;
    cout << "Enter initial head position: ";
    cin >> head;
    cout << "Enter disk size (max cylinder + 1): ";
    cin >> diskSize;
    if (n <= 0 || diskSize <= 0 || head < 0 || head >= diskSize) {
        cout << "Invalid input\n";
        return 1;
    }
    fcfs(req, head);
    sstf(req, head);
    scan(req, head, diskSize);
    cscan(req, head, diskSize);
    return 0;
}