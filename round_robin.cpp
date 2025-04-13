#include <bits/stdc++.h>
using namespace std;

class Process {
public:
    int id;
    int at; 
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int rem_bt;

    Process(int id, int at, int bt) {
        this->id = id;
        this->at = at;
        this->bt = bt;
        this->rem_bt = bt;
        this->ct = 0;
        this->tat = 0;
        this->wt = 0;
        this->rt = -1;
    }
};

void showInputChart(vector<Process>& processes) {
    cout << "\n+--------------+--------------+--------------+\n";
    cout << "|  Process ID  | Arrival Time |  Burst Time  |\n";
    cout << "+--------------+--------------+--------------+\n";
    for (auto& p : processes) {
        cout << "|     P" << p.id << setw(5)
             << "     |     " << setw(5) << p.at
             << "     |   " << setw(6) << p.bt << "     |\n";
    }
    cout << "+--------------+--------------+--------------+\n";
}

void showGanttChart(vector<int>& gantt_ids, vector<int>& gantt_times) {
    cout << "\n\nGantt Chart:\n\n";
    cout << " ";
    for (int i = 0; i < gantt_ids.size(); i++) {
        cout << "--------";
    }
    cout << "-\n|";
    for (int i = 0; i < gantt_ids.size(); i++) {
        cout << "  P" << setw(2) << gantt_ids[i] << "  |";
    }
    cout << "\n ";
    for (int i = 0; i < gantt_ids.size(); i++) {
        cout << "--------";
    }
    cout << "-\n";

    for (int i = 0; i < gantt_times.size(); i++) {
        cout << setw(2) << gantt_times[i] << "      ";
    }
}


void showResultChart(vector<Process>& processes) {
    cout << "\n+------------+--------------+-----------------+-----------------+---------------+---------------+\n";
    cout << "| Process ID | Arrival Time | Completion Time | Turnaround Time | Waiting Time  | Response Time |\n";
    cout << "+------------+--------------+-----------------+-----------------+---------------+---------------+\n";
    for (auto& p : processes) {
        cout << "|     P" << p.id << setw(4)
             << "     |     " << setw(5) << p.at
             << "     |     " << setw(6) << p.ct
             << "      |     " << setw(6) << p.tat
             << "      |   " << setw(6) << p.wt
             << "      |   " << setw(6) << p.rt << "      |\n";
    }
    cout << "+------------+--------------+-----------------+-----------------+---------------+---------------+\n";
}

int main() {
    cout << "Enter number of processes: ";
    int n;
    cin >> n;
    vector<Process> processes;
    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 1; i <= n; i++) {
        int at, bt;
        cout << "P" << i << ": ";
        cin >> at >> bt;
        processes.push_back(Process(i, at, bt));
    }

    int tq;
    cout << "Enter time quantum: ";
    cin >> tq;

    cout << "\nInput Processes in Tabular Format:";
    showInputChart(processes);

    sort(processes.begin(), processes.end(), [](Process& a, Process& b) {
        return a.at < b.at;
    });

    queue<int> q;
    vector<int> gantt_ids, gantt_times;
    vector<bool> inQueue(n, false);
    int curr_time = 0, completed = 0;

    q.push(0);
    inQueue[0] = true;
    curr_time = processes[0].at;

    while (!q.empty()) {
        int idx = q.front();
        q.pop();

        Process& p = processes[idx];
        if (p.rt == -1) p.rt = curr_time;

        gantt_ids.push_back(p.id);
        gantt_times.push_back(curr_time);

        int exec_time = min(tq, p.rem_bt);
        curr_time += exec_time;
        p.rem_bt -= exec_time;

        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && processes[i].at <= curr_time && processes[i].rem_bt > 0) {
                q.push(i);
                inQueue[i] = true;
            }
        }

        if (p.rem_bt > 0) {
            q.push(idx); 
        } else {
            p.ct = curr_time;
            p.tat = p.ct - p.at;
            p.wt = p.tat - p.bt;
            completed++;
        }

        if (q.empty() && completed < n) {
            for (int i = 0; i < n; i++) {
                if (!inQueue[i]) {
                    curr_time = max(curr_time, processes[i].at);
                    q.push(i);
                    inQueue[i] = true;
                    break;
                }
            }
        }
    }

    gantt_times.push_back(curr_time);
    showGanttChart(gantt_ids, gantt_times);

    sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2) {
        return p1.id < p2.id;
    });

    showResultChart(processes);

    double total_wt = 0;
    for (int i = 0; i < n; i++) {
        total_wt += processes[i].wt;
    }
    cout << "Average waiting time: " << fixed << setprecision(2) << total_wt / n << "\n";

    return 0;
}
