#include <bits/stdc++.h>
using namespace std;

class Process {
public:
    int id;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int priority;

    Process(int id, int bt, int priority) {
        this->id = id;
        this->bt = bt;
        this->priority = priority;
        this->ct = 0;
        this->tat = 0;
        this->wt = 0;
        this->rt = 0;
    }
};

void showInputChart(vector<Process>& processes) {
    cout << "\n+--------------+--------------+-----------+\n";
    cout << "|  Process ID  |  Burst Time  | Priority  |\n";
    cout << "+--------------+--------------+-----------+\n";
    for (int i = 0; i < processes.size(); i++) {
        cout << "|      P" << processes[i].id << setw(5) 
             << "      |   " << setw(6) << processes[i].bt 
             << "     |    " << setw(4) << processes[i].priority << "   |\n";
    }
    cout << "+--------------+--------------+-----------+\n";
}

void showGanttChart(vector<Process>& processes, vector<int>& times) {
    cout << "\nGantt Chart:\n";
    for (int i = 0; i < processes.size(); i++) {
        cout << "    P" << processes[i].id << "    ";
    }
    cout << "\n";
    for (int i = 0; i < times.size(); i++) {
        cout << times[i] << "        ";
    }
    cout << times.back() + processes.back().bt << "\n";
}

void showResultChart(vector<Process>& processes) {
    cout << "\n+------------+-----------------+-----------------+---------------+---------------+\n";
    cout << "| Process ID | Completion Time | Turnaround Time | Waiting Time  | Response Time |\n";
    cout << "+------------+-----------------+-----------------+---------------+---------------+\n";
    for (auto& process : processes) {
        cout << "|     P" << process.id << setw(4)
             << "     |     " << setw(6) << process.ct
             << "      |     " << setw(6) << process.tat
             << "      |   " << setw(6) << process.wt
             << "      |   " << setw(6) << process.rt << "      |\n";
    }
    cout << "+------------+-----------------+-----------------+---------------+---------------+\n";
}

int main() {
    cout << "Enter number of processes: ";
    int n;
    cin >> n;
    vector<Process> processes;
    cout << "Enter burst time and priority for each process:\n";
    for (int i = 1; i <= n; i++) {
        int bt, pr;
        cout << "P" << i << ": ";
        cin >> bt >> pr;
        processes.push_back(Process(i, bt, pr));
    }

    cout << "\nInput Processes in Tabular Format:";
    showInputChart(processes);

    sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2) {
        return p1.priority < p2.priority;
    });

    vector<int> times;
    int curr_time = 0;
    for (int i = 0; i < n; i++) {
        times.push_back(curr_time);
        processes[i].rt = curr_time;
        curr_time += processes[i].bt;
        processes[i].ct = curr_time;
        processes[i].tat = processes[i].ct;
        processes[i].wt = processes[i].tat - processes[i].bt;
    }

    showGanttChart(processes, times);

    sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2) {
        return p1.id < p2.id;
    });

    showResultChart(processes);

    double avg_wt = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += processes[i].wt;
    }
    cout << "Average waiting time: " << fixed << setprecision(2) << avg_wt / n << "\n";

    return 0;
}
