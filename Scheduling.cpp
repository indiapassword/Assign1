#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Process {
public:
    int processID, burstTime, waitingTime, turnAroundTime, arrivalTime, completionTime, remainingTime, priority;

    Process(int id, int bt, int at, int rt = 0, int pt = 0)
        : processID(id), burstTime(bt), arrivalTime(at), completionTime(0), waitingTime(0), 
          turnAroundTime(0), remainingTime(rt), priority(pt) {}
};

class FCFS {
private:
    vector<Process> processes;
    int n;
    float totalWaitingTime = 0.0, totalTurnAroundTime = 0.0;

public:
    void inputProcesses() {
        cout << "Enter the number of processes: ";
        cin >> n;

        processes.clear();
        cout << "\nEnter Arrival Time and Burst Time:\n";
        for (int i = 0; i < n; ++i) {
            int burstTime, arrivalTime;
            cout << "p-" << i + 1 << ": ";
            cin >> arrivalTime >> burstTime;
            processes.emplace_back(i + 1, burstTime, arrivalTime); // Add processes with arrival times and burst times
        }
    }
    
    void sortProcessesByArrivalTime() {
        // Sort the processes based on arrival time, then burst time (for tie breaking)
        sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
            return a.arrivalTime < b.arrivalTime;
        });
    }

    void calculateWaitingTime() {
        processes[0].waitingTime = 0;
        processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime; // Completion time for first process

        // For other processes, calculate waiting time and completion time
        for (int i = 1; i < n; ++i) {
            processes[i].waitingTime = processes[i - 1].completionTime - processes[i].arrivalTime;
            if (processes[i].waitingTime < 0) {
                processes[i].waitingTime = 0;
            }
            processes[i].completionTime = processes[i].arrivalTime + processes[i].waitingTime + processes[i].burstTime;
        }
    }

    void displayResults() {
        cout << "\nProcess ID    Arrival Time   Burst Time   Waiting Time    Turnaround Time    Completion Time\n";
        totalWaitingTime = 0.0;
        totalTurnAroundTime = 0.0;

        for (int i = 0; i < n; ++i) {
            processes[i].turnAroundTime = processes[i].burstTime + processes[i].waitingTime;
            cout << processes[i].processID << "\t\t" << processes[i].arrivalTime << "\t\t"
                 << processes[i].burstTime << "\t\t" << processes[i].waitingTime << "\t\t"
                 << processes[i].turnAroundTime << "\t\t" << processes[i].completionTime << "\n";

            totalWaitingTime += processes[i].waitingTime;
            totalTurnAroundTime += processes[i].turnAroundTime;
        }

        cout << "\nAverage Waiting Time: " << totalWaitingTime / n << endl;
        cout << "Average Turnaround Time: " << totalTurnAroundTime / n << endl;
    }
};

class SJF {
private:
    vector<Process> processes;
    int n;
    float totalWaitingTime = 0.0, totalTurnAroundTime = 0.0;

public:
    void inputProcesses() {
        cout << "Enter the number of processes: ";
        cin >> n;

        processes.clear();
        cout << "\nEnter Arrival Time and Burst Time:\n";
        for (int i = 0; i < n; ++i) {
            int burstTime, arrivalTime;
            cout << "p-" << i + 1 << ": ";
            cin >> arrivalTime >> burstTime;
            processes.emplace_back(i + 1, burstTime, arrivalTime); // Add processes with arrival times and burst times
        }
    }

    void sortProcessesByArrivalTime() {
        // Sort the processes based on arrival time, then burst time (for tie breaking)
        sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
            if (a.arrivalTime == b.arrivalTime)
                return a.burstTime < b.burstTime;
            return a.arrivalTime < b.arrivalTime;
        });
    }

    void calculateWaitingTime() {
        processes[0].waitingTime = 0;
        processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime; // Completion time for the first process

        // For other processes, calculate waiting time and completion time
        for (int i = 1; i < n; ++i) {
            // Wait for the process to arrive, if it hasn't yet
            if (processes[i].arrivalTime > processes[i - 1].completionTime) {
                processes[i].waitingTime = 0;
            } else {
                processes[i].waitingTime = processes[i - 1].completionTime - processes[i].arrivalTime;
            }
            processes[i].completionTime = processes[i].arrivalTime + processes[i].waitingTime + processes[i].burstTime;
        }
    }

    void displayResults() {
        cout << "\nProcess ID    Arrival Time   Burst Time   Waiting Time    Turnaround Time    Completion Time\n";
        totalWaitingTime = 0.0;
        totalTurnAroundTime = 0.0;

        for (int i = 0; i < n; ++i) {
            processes[i].turnAroundTime = processes[i].burstTime + processes[i].waitingTime;
            cout << processes[i].processID << "\t\t" << processes[i].arrivalTime << "\t\t"
                 << processes[i].burstTime << "\t\t" << processes[i].waitingTime << "\t\t"
                 << processes[i].turnAroundTime << "\t\t" << processes[i].completionTime << "\n";

            totalWaitingTime += processes[i].waitingTime;
            totalTurnAroundTime += processes[i].turnAroundTime;
        }

        cout << "\nAverage Waiting Time: " << totalWaitingTime / n << endl;
        cout << "Average Turnaround Time: " << totalTurnAroundTime / n << endl;
    }
};

class SJF_PRIMITIVE {
private:
    vector<Process> processes;
    int n ,completed=0 ,currentTime=0;
    float totalWaitingTime = 0.0, totalTurnAroundTime = 0.0;

public:
    void inputProcesses() {
        cout << "Enter the number of processes: ";
        cin >> n;

        processes.clear();
        cout << "\nEnter Arrival Time and Burst Time:\n";
        for (int i = 0; i < n; ++i) {
            int burstTime, arrivalTime ,remainingTime;
            cout << "p-" << i + 1 << ": ";
            cin >> arrivalTime >> burstTime;
            remainingTime = burstTime;
            processes.emplace_back(i + 1, burstTime, arrivalTime,remainingTime); // Add processes with arrival times and burst times
        }
    }

    void sortProcessesByArrivalTime() {
        // Sort the processes based on arrival time, then burst time (for tie breaking)
        sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
            if (a.arrivalTime == b.arrivalTime)
                return a.burstTime < b.burstTime;
            return a.arrivalTime < b.arrivalTime;
        });
    }

    void calculateWaitingTime() {
         while (completed < n) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && (idx == -1 || processes[i].remainingTime < processes[idx].remainingTime)) {
                idx = i;
            }
        }
        if (idx != -1) {
            processes[idx].remainingTime--;
            currentTime++;
            if (processes[idx].remainingTime == 0) {
                processes[idx].completionTime = currentTime;
                processes[idx].turnAroundTime = currentTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnAroundTime - processes[idx].burstTime;
                completed++;
            }
        } else {
            currentTime++;
        }
    }
    }
    


    void displayResults() {
        cout << "\nProcess ID    Arrival Time   Burst Time   Waiting Time    Turnaround Time    Completion Time\n";
        totalWaitingTime = 0.0;
        totalTurnAroundTime = 0.0;

        for (int i = 0; i < n; ++i) {
            processes[i].turnAroundTime = processes[i].burstTime + processes[i].waitingTime;
            cout << processes[i].processID << "\t\t" << processes[i].arrivalTime << "\t\t"
                 << processes[i].burstTime << "\t\t" << processes[i].waitingTime << "\t\t"
                 << processes[i].turnAroundTime << "\t\t" << processes[i].completionTime << "\n";

            totalWaitingTime += processes[i].waitingTime;
            totalTurnAroundTime += processes[i].turnAroundTime;
        }

        cout << "\nAverage Waiting Time: " << totalWaitingTime / n << endl;
        cout << "Average Turnaround Time: " << totalTurnAroundTime / n << endl;
    }
};

class Priority {
private:
    vector<Process> processes;
    int n;
    float totalWaitingTime = 0.0, totalTurnAroundTime = 0.0;

public:
    void inputProcesses() {
        cout << "Enter the number of processes: ";
        cin >> n;

        processes.clear();
        cout << "\nEnter Arrival Time , Burst Time and Priority:\n";
        for (int i = 0; i < n; ++i) {
            int burstTime, arrivalTime , priority;
            cout << "p-" << i + 1 << ": ";
            cin >> arrivalTime >> burstTime >> priority;
            processes.emplace_back(i + 1, burstTime, arrivalTime, 0 ,priority); 
        }
    }

     void scheduling() {
        vector<bool> isCompleted(n, false);
        int completed = 0, currentTime = 0;

        while (completed < n) {
            int idx = -1;
            int highestPriority = 99999;

            // Find process with highest priority that has arrived
            for (int i = 0; i < n; i++) {
                if (!isCompleted[i] && processes[i].arrivalTime <= currentTime) {
                    if (processes[i].priority < highestPriority) {
                        highestPriority = processes[i].priority;
                        idx = i;
                    }
                    // If priority is same, choose one with earlier arrival time
                    else if (processes[i].priority == highestPriority && processes[i].arrivalTime < processes[idx].arrivalTime) {
                        idx = i;
                    }
                }
            }

            if (idx == -1) { // No process is available at this time, so increase time
                currentTime++;
            } else {
                processes[idx].completionTime = currentTime + processes[idx].burstTime;
                processes[idx].turnAroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnAroundTime - processes[idx].burstTime;

                totalWaitingTime += processes[idx].waitingTime;
                totalTurnAroundTime += processes[idx].turnAroundTime;

                currentTime = processes[idx].completionTime;
                isCompleted[idx] = true;
                completed++;
            }
        }
    }

    void displayResults() {
        cout << "\nProcess ID    Arrival Time   Burst Time   Priority   Waiting Time    Turnaround Time    Completion Time\n";
        totalWaitingTime = 0.0;
        totalTurnAroundTime = 0.0;

        for (int i = 0; i < n; ++i) {
            processes[i].turnAroundTime = processes[i].burstTime + processes[i].waitingTime;
            cout << processes[i].processID << "\t\t" << processes[i].arrivalTime << "\t\t"
                 << processes[i].burstTime << "\t\t" << processes[i].priority << "\t\t" << processes[i].waitingTime << "\t\t"
                 << processes[i].turnAroundTime << "\t\t" << processes[i].completionTime << "\n";

            totalWaitingTime += processes[i].waitingTime;
            totalTurnAroundTime += processes[i].turnAroundTime;
        }

        cout << "\nAverage Waiting Time: " << totalWaitingTime / n << endl;
        cout << "Average Turnaround Time: " << totalTurnAroundTime / n << endl;
    }
};

class Round_Robin{
private:
    vector<Process> processes;
    int n ,completed=0 ,currentTime=0 , timeQuantum; 
    float totalWaitingTime = 0.0, totalTurnAroundTime = 0.0;

public:
    void inputProcesses() {
        cout << "Enter the number of processes: ";
        cin >> n;

        processes.clear();
        cout << "\nEnter Arrival Time and Burst Time:\n";
        for (int i = 0; i < n; ++i) {
            int burstTime, arrivalTime ,remainingTime;
            cout << "p-" << i + 1 << ": ";
            cin >> arrivalTime >> burstTime;
            remainingTime = burstTime;
            processes.emplace_back(i + 1, burstTime, arrivalTime,remainingTime); // Add processes with arrival times and burst times
        }
        
        cout << "Enter the time Quantum: ";
       cin>>timeQuantum;
        
    }

    void sortProcessesByArrivalTime() {
        // Sort the processes based on arrival time, then burst time (for tie breaking)
        sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
            if (a.arrivalTime == b.arrivalTime)
                return a.burstTime < b.burstTime;
            return a.arrivalTime < b.arrivalTime;
        });
    }

    void calculateWaitingTime() {
         while (completed < n) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && (idx == -1 || processes[i].remainingTime < processes[idx].remainingTime)) {
                idx = i;
            }
        }
        if (idx != -1) {
            processes[idx].remainingTime--;
            currentTime++;
            if (processes[idx].remainingTime == 0) {
                processes[idx].completionTime = currentTime;
                processes[idx].turnAroundTime = currentTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnAroundTime - processes[idx].burstTime;
                completed++;
            }
        } else {
            currentTime++;
        }
    }
    }
    


    void displayResults() {
        cout << "\nProcess ID    Arrival Time   Burst Time   Waiting Time    Turnaround Time    Completion Time\n";
        totalWaitingTime = 0.0;
        totalTurnAroundTime = 0.0;

        for (int i = 0; i < n; ++i) {
            processes[i].turnAroundTime = processes[i].burstTime + processes[i].waitingTime;
            cout << processes[i].processID << "\t\t" << processes[i].arrivalTime << "\t\t"
                 << processes[i].burstTime << "\t\t" << processes[i].waitingTime << "\t\t"
                 << processes[i].turnAroundTime << "\t\t" << processes[i].completionTime << "\n";

            totalWaitingTime += processes[i].waitingTime;
            totalTurnAroundTime += processes[i].turnAroundTime;
        }

        cout << "\nAverage Waiting Time: " << totalWaitingTime / n << endl;
        cout << "Average Turnaround Time: " << totalTurnAroundTime / n << endl;
    }
};


int main() {
    int choice;
    cout << "Enter the choice for Scheduling:\n";
    cout << "1. FCFS\n";
    cout << "2. SJF\n";
    cout << "3. SJF PRIMITIVE\n";
    cout << "4. Priority\n";
    cout << "5. Round Robin\n";
    cout << "Choice: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        FCFS fcfsScheduler;
        fcfsScheduler.inputProcesses();
        fcfsScheduler.sortProcessesByArrivalTime();
        fcfsScheduler.calculateWaitingTime();
        fcfsScheduler.displayResults();
        break;
    }
    case 2: {
        SJF sjfScheduler;
        sjfScheduler.inputProcesses();
        sjfScheduler.sortProcessesByArrivalTime(); // Sort processes by arrival time and burst time
        sjfScheduler.calculateWaitingTime();
        sjfScheduler.displayResults();
        break;
    }
    case 3: {
        SJF_PRIMITIVE sjfSchedulerPrimirtive;
        sjfSchedulerPrimirtive.inputProcesses();
        sjfSchedulerPrimirtive.sortProcessesByArrivalTime(); // Sort processes by arrival time and burst time
        sjfSchedulerPrimirtive.calculateWaitingTime();
        sjfSchedulerPrimirtive.displayResults();
        break;
    }
    case 4: {
        Priority priorityScheduler;
        priorityScheduler.inputProcesses();
        priorityScheduler.scheduling();
        priorityScheduler.displayResults();
        break;
    }
    case 5: {
    Round_Robin rrScheduler;
    rrScheduler.inputProcesses();
    rrScheduler.sortProcessesByArrivalTime();
    rrScheduler.calculateWaitingTime();
    rrScheduler.displayResults();
    break;
}
    
    
    default:
        cout << "Invalid choice! Please select 1 or 2.\n";
        break;
    }

    return 0;
}


