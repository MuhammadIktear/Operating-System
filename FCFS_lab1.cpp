#include <bits/stdc++.h>
using namespace std;

class Process {
public:
    int id;
    int at;
    int bt;
    int tat;
    int wt;
    int rt; 
    Process(int id, int at, int bt) {
        this->id = id; 
        this->at = at; 
        this->bt = bt; 
        this->tat = 0; 
        this->wt = 0;
        this->rt = 0;
    }
};

bool compareArrival(Process& p1, Process& p2) {
    return p1.at < p2.at;
}

// Display input chart
void showInputChart(vector<Process>& processes) {
    cout << "\n--------------------------------------------------\n";
    cout << "| Process ID | Arrival Time | Burst Time        |\n";
    cout << "--------------------------------------------------\n";
    for (auto& process : processes) {
        cout << "|     P" << process.id << "      |      " << process.at 
        << "       |       " << process.bt << "         |\n";
    }
    cout << "--------------------------------------------------\n";
}

// Display Gantt Chart
void showGanttChart(vector<Process>& processes, vector<int>& startTimes) {
    cout << "\nGantt Chart:\n\n";
    for (auto& process : processes) {
        cout << "   P" << process.id << "   ";
    }
    cout << "\n";

    // Print timeline
    for (int time : startTimes) {
        cout << time <<"       ";
    }
    cout << startTimes.back() + processes.back().bt << "\n";
}

// Display result chart
void showResultChart(vector<Process>& processes) {
    cout << "\n-----------------------------------------------------------------------------\n";
    cout << "| Process ID | Turnaround Time | Waiting Time | Response Time               |\n";
    cout << "-----------------------------------------------------------------------------\n";
    for (auto& process : processes) {
        cout << "|     P" << process.id << "      |      " << process.tat 
             << "         |      " << process.wt 
             << "         |      " << process.rt << "                |\n";
    }
    cout << "-----------------------------------------------------------------------------\n";
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes;
    cout << "\nEnter the Arrival Time and Burst Time for each process (in tabular format):\n";
    cout << "-------------------------------------------------\n";
    cout << "| Process ID | Arrival Time | Burst Time       |\n";
    cout << "-------------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        int at, bt;
        cout << "|     P" << (i + 1) << "      |      ";
        cin >> at >> bt;
        processes.emplace_back(i + 1, at, bt);
    }

    cout << "\nInput Processes in Tabular Format:";
    showInputChart(processes);

    // Sort processes by arrival time for FCFS
    sort(processes.begin(), processes.end(), compareArrival);

    // Calculate
    vector<int> startTimes;
    int currentTime = 0;
    for (auto& process : processes) {
        if (currentTime < process.at) {
            currentTime = process.at; 
        }
        startTimes.push_back(currentTime); 

        process.rt = currentTime - process.at; // Response Time
        currentTime += process.bt; 

        process.tat = currentTime - process.at; // Turnaround Time
        process.wt = process.tat - process.bt;  // Waiting Time
    }

    // Display Gantt Chart
    showGanttChart(processes, startTimes);

    // Display result chart
    showResultChart(processes);

    return 0;
}
