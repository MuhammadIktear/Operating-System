#include<bits/stdc++.h>
using namespace std;
class Process{
    public:
    int id;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    Process(int id,int bt){
        this->id=id;
        this->bt=bt;
        this->ct=0;
        this->tat=0;
        this->wt=0;
        this->rt=0;
    }
};

void showInputChart(vector<Process>& processes) {
    cout << "\n+--------------+--------------+\n";
    cout << "|  Process ID  |  Burst Time  |\n";
    cout << "+--------------+--------------+\n";

    for (int i = 0; i < processes.size(); i++) {
        cout << "|      P" << processes[i].id << setw(5) 
             << "      |   " << setw(6) << processes[i].bt << "     |\n";
    }

    cout << "+--------------+--------------+\n";
}
void showGanttChart(vector<Process>&processes,vector<int>&times){
    cout<<"\n Gantt Chart: \n";
    for(int i=0;i<processes.size();i++){
        cout<<"    P"<<processes[i].id<<"    ";
    }
    cout<<"\n";
    for(int i=0;i<times.size();i++){
        cout<<times[i]<<"        ";
    }
    cout<<times.back()+processes.back().bt<<"\n";
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
int main(){
    cout<<"Enter number of process: ";
    int n;
    cin>>n;
    cout<<"Enter burst time for all process: \n";
    vector<Process>processes;
    for(int i=1;i<=n;i++){
        int bt;
        cin>>bt;
        processes.push_back(Process(i,bt));
    }
    cout << "\nInput Processes in Tabular Format:";
    showInputChart(processes);
    sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2) {
        return p1.bt < p2.bt;
    });
    vector<int>times;
    int curr_time=0;
    for(int i=0;i<n;i++){
        times.push_back(curr_time);
        processes[i].rt=curr_time;
        curr_time+=processes[i].bt;
        processes[i].ct=curr_time;
        processes[i].tat=processes[i].ct;
        processes[i].wt=processes[i].tat-processes[i].bt;
    }
    showGanttChart(processes,times);
    sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2) {
        return p1.id < p2.id;
    });    
    showResultChart(processes);
    double sum=0;
    for(int i=0;i<n;i++){
        sum+=processes[i].wt;
    }
    cout<<"Average waiting time: "<<sum/n<<"\n";
}