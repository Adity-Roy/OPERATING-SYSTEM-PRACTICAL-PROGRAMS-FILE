#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

struct Process {
    int pid, at, bt, pr, ct = 0, tat = 0, wt = 0, rem = 0;
};

void printResult(vector<Process> p) {
    double totalWT = 0, totalTAT = 0;
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto x : p) {
        cout << x.pid << '\t' << x.at << '\t' << x.bt << '\t'
             << x.ct << '\t' << x.tat << '\t' << x.wt << '\n';
        totalWT += x.wt;
        totalTAT += x.tat;
    }
    cout << "Average Waiting Time = " << totalWT / p.size() << '\n';
    cout << "Average Turnaround Time = " << totalTAT / p.size() << '\n';
}

void fcfs(vector<Process> p) {
    stable_sort(p.begin(), p.end(), [](Process a, Process b) { return a.at < b.at; });
    int time = 0;
    for (auto &x : p) {
        time = max(time, x.at);
        time += x.bt;
        x.ct = time;
        x.tat = x.ct - x.at;
        x.wt = x.tat - x.bt;
    }
    printResult(p);
}

void sjf(vector<Process> p) {
    int n = p.size(), completed = 0, time = 0;
    vector<bool> done(n, false);
    while (completed < n) {
        int idx = -1;
        for (int i = 0; i < n; i++)
            if (!done[i] && p[i].at <= time &&
                (idx == -1 || p[i].bt < p[idx].bt))
                idx = i;
        if (idx == -1) { time++; continue; }
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = time - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = true;
        completed++;
    }
    printResult(p);
}

void priorityScheduling(vector<Process> p) {
    int n = p.size(), completed = 0, time = 0;
    vector<bool> done(n, false);
    while (completed < n) {
        int idx = -1;
        for (int i = 0; i < n; i++)
            if (!done[i] && p[i].at <= time &&
                (idx == -1 || p[i].pr < p[idx].pr))
                idx = i;
        if (idx == -1) { time++; continue; }
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = time - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = true;
        completed++;
    }
    printResult(p);
}

void roundRobin(vector<Process> p, int quantum) {
    int n = p.size(), time = 0, completed = 0, next = 0;
    sort(p.begin(), p.end(), [](Process a, Process b) { return a.at < b.at; });
    queue<int> q;
    for (auto &x : p) x.rem = x.bt;

    while (completed < n) {
        if (q.empty()) {
            if (next < n) time = max(time, p[next].at);
            while (next < n && p[next].at <= time) q.push(next++);
        }
        int i = q.front();
        q.pop();
        int slice = min(quantum, p[i].rem);
        time += slice;
        p[i].rem -= slice;
        while (next < n && p[next].at <= time) q.push(next++);
        if (p[i].rem > 0) q.push(i);
        else {
            p[i].ct = time;
            p[i].tat = time - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            completed++;
        }
    }
    sort(p.begin(), p.end(), [](Process a, Process b) { return a.pid < b.pid; });
    printResult(p);
}

int main() {
    int n, choice, quantum;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Process " << i + 1 << " - Arrival Time, Burst Time, Priority: ";
        cin >> p[i].at >> p[i].bt >> p[i].pr;
    }
    cout << "\nMenu:\n1. FCFS\n2. SJF (Non-preemptive)\n3. Priority (Non-preemptive)\n4. Round Robin\nEnter choice: ";
    cin >> choice;
    if (choice == 1) fcfs(p);
    else if (choice == 2) sjf(p);
    else if (choice == 3) priorityScheduling(p);
    else if (choice == 4) {
        cout << "Enter time quantum: ";
        cin >> quantum;
        if (quantum > 0) roundRobin(p, quantum);
        else cout << "Invalid time quantum\n";
    } else cout << "Invalid choice\n";
    return 0;
}