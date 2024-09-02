#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
struct Process {
    int pid;        
    int burstTime;  
    int waitTime;   
    int turnAroundTime; 
};

bool compareBurstTime(Process a, Process b) {
    return a.burstTime < b.burstTime;
}

void calculateTimes(vector<Process> &processes) {
    int n = processes.size();
    
    processes[0].waitTime = 0;
    processes[0].turnAroundTime = processes[0].burstTime;
    
    for (int i = 1; i < n; i++) {
        processes[i].waitTime = processes[i - 1].turnAroundTime;
        processes[i].turnAroundTime = processes[i].waitTime + processes[i].burstTime;
    }
}

void calculateAverageTimes(vector<Process> &processes) {
    int n = processes.size();
    double totalWaitTime = 0;
    double totalTurnAroundTime = 0;
    
    for (int i = 0; i < n; i++) {
        totalWaitTime += processes[i].waitTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
    }
    
    cout << "Average Waiting Time: " << (totalWaitTime / n) << endl;
    cout << "Average Turnaround Time: " << (totalTurnAroundTime / n) << endl;
}

void displayProcesses(vector<Process> &processes) {
    cout << "Process ID\tBurst Time\tWaiting Time\tTurnaround Time" << endl;
    for (const auto &process : processes) {
        cout << process.pid << "\t\t" << process.burstTime << "\t\t" 
             << process.waitTime << "\t\t" << process.turnAroundTime << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    
    vector<Process> processes(n);
    
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter burst time for process " << processes[i].pid << ": ";
        cin >> processes[i].burstTime;
    }
    
    sort(processes.begin(), processes.end(), compareBurstTime);
    
    calculateTimes(processes);
    
    displayProcesses(processes);
    
    calculateAverageTimes(processes);
    
    return 0;
}
