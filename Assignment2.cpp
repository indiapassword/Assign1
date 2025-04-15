#include<iostream>
#include <climits>

using namespace std;

class Process
{
    public:
        int processID;
        int arrivalTime;
        int burstTime;
        int waitingTime;
        int turnArroundTime;
        int completionTime;
        int priority;
        int remainingTime;
};
class Assignment2
{
    public:
        int n;
        Process* p = new Process[5];

        Assignment2(int a)
        {
            n = 5;
        }

        // Function to take input as process information
        void takeInput()
        {
            cout<< "Enter Process information :"<<endl;
            for(int i = 0; i < n ; i++)
            {
                cout<<"Process ID :";
                cin>>p[i].processID;

                cout<<"Arrival Time :";
                cin>>p[i].arrivalTime;

                cout<<"Burst Time :";
                cin>>p[i].burstTime;
                cout<<"-----------------------"<<endl;
            }
        }

        // Merge function supporting merge sort
        void merge(char s, int left, int mid, int right)
        {
            int n1 = mid - left + 1;
            int n2 = right - mid;

            Process* a = new Process[n1];
            Process* b = new Process[n2];

            for(int i = 0; i < n1; i++)
            {
                a[i] = p[i + left];
            }
            for(int i = 0; i < n2 ; i++)
            {
                b[i] = p[mid + 1 + i];
            }

            int i = 0;
            int j = 0;
            int k = left;
            
            // For sorting Arrival Time
            if(s == 'A')
            {   
                while(i < n1 && j < n2)
                {
                    if(a[i].arrivalTime < b[j].arrivalTime)
                    {
                        p[k] = a[i];
                        i++;
                        k++;
                    }
                    else
                    {
                        p[k] = b[j];
                        j++;
                        k++;
                    }
                    }
            }
            // For sorting Process ID
            else if(s == 'P')
            {
                while(i < n1 && j < n2)
                {
                    if(a[i].processID < b[j].processID)
                    {
                        p[k] = a[i];
                        i++;
                        k++;
                    }
                    else
                    {
                        p[k] = b[j];
                        
                        j++;
                        k++;
                    }
                }            
            }
            // For sorting Burst Time
            else if(s == 'B')
            {
                while(i < n1 && j < n2)
                {
                    if(a[i].burstTime < b[j].burstTime)
                    {
                        p[k] = a[i];                       
                        i++;
                        k++;
                    }
                    else
                    {
                        p[k] = b[j];                        
                        j++;
                        k++;
                    }
                }            
            }
            // For sorting Priority
            else if(s == 'R')
            {
                while(i < n1 && j < n2)
                {
                    if(a[i].priority < b[j].priority)
                    {
                        p[k] = a[i];
                        i++;
                        k++;
                    }
                    else
                    {
                        p[k] = b[j];    
                        j++;
                        k++;
                    }
                }            
            }

            while(i < n1)
            {
                p[k] = a[i];
                i++;
                k++;
            }
            while(j < n2)
            {
                p[k] = b[j];
                j++;
                k++;
            }      
        }

        // Sort function
        void sort(char s, int i, int j)
        {
            int mid = (i + j)/2;
            if(i < j)
            {
                sort(s, i, mid);
                sort(s, mid+1, j);
                merge(s, i, mid, j);
            }
        }    

        // Function to display the process information
        void display()
        {
            cout<<"Process ID"<<"\t"<<"Arrival Time"<<"\t"<<"Burst Time"<<"\t"<<"Waiting Time"<<"\t"<<"Completion Time"<<"\t"<<"Turnarround Time"<<"\t"<<endl;
            for(int i = 0; i< n;i++)
            {
                cout<<p[i].processID<<"\t\t\t"<<p[i].arrivalTime<<"\t\t\t\t"<<p[i].burstTime<<"\t\t\t"<<p[i].waitingTime<<"\t\t\t\t"<<p[i].completionTime<<"\t\t\t\t\t"<<p[i].turnArroundTime<<endl;
            }
        }

        // Function to schedule the processes
        void schedule(string t)     // t is the type of the scheduling method.
        {
            sort('A',0, n-1);       // First sort according to arrival time


            int i = 1;
            int j = i;

            // For FCFS
            if(t == "FCFS")
            {
                while(i < n)        // When arrival time is same then schedule according to process ID
                {
                    j = i;
                    while(i < n && p[i].arrivalTime == p[i-1].arrivalTime)
                    {
                        i++;
                    }
                    sort('P', j-1, i-1);
                    i++;
                }
            }
            // For SJF
            else if(t == "SJF")
            {
                while(i < n)        // When arrival time is same then sort according to burst time.
                {
                    j = i;
                    while(i < n && p[i].arrivalTime == p[i-1].arrivalTime)
                    {
                        i++;
                    }
                    sort('B', j-1, i-1);
                    i++;
                }

                // Sort according to process ID where arrival time and burst time is same
                while(i < n)
                {
                    j = i;
                    while(i < n && p[i].arrivalTime == p[i-1].arrivalTime && p[i].burstTime == p[i-1].burstTime)
                    {
                        i++;
                    }
                    sort('P', j-1, i-1);
                    i++;
                }
            }

            // For Priority - Non preemptive
            if(t == "Priority_NP")
            {
                cout<<"Enter the proirity values : ";
                for(int i = 0 ; i < n ; i++)
                {
                    cin>>p[i].priority;
                }
                for(int i = 1; i < n; i++)
                {
                    int j = i;
                    while(j < n && p[j].arrivalTime == p[j-1].arrivalTime) j++;
                    sort('R', i-1, j-1);
                }
            }
            // For Priority - Preemptive
            if(t == "Priority_P") // Preemptive Priority Scheduling
            {
                cout<<"Enter the priority values : ";
                for(int i = 0 ; i < n ; i++)
                {
                    cin>>p[i].priority;
                }           
                int completed = 0, currentTime = 0, minPriority = INT_MAX;
                int shortest = -1, finishTime;
                bool check = false;
                
                while(completed < n)
                {
                    for(int i = 0; i < n; i++)
                    {
                        if(p[i].arrivalTime <= currentTime && p[i].remainingTime > 0 && p[i].priority < minPriority)
                        {
                            minPriority = p[i].priority;
                            shortest = i;
                            check = true;
                        }
                    }
                    
                    if(!check)
                    {
                        currentTime++;
                        continue;
                    }
                    
                    p[shortest].remainingTime--;
                    minPriority = p[shortest].priority;
                    
                    if(p[shortest].remainingTime == 0)
                    {
                        completed++;
                        finishTime = currentTime + 1;
                        p[shortest].completionTime = finishTime;
                        p[shortest].turnArroundTime = finishTime - p[shortest].arrivalTime;
                        p[shortest].waitingTime = p[shortest].turnArroundTime - p[shortest].burstTime;
                        if(p[shortest].waitingTime < 0) p[shortest].waitingTime = 0;
                        minPriority = INT_MAX;
                    }
                    
                    currentTime++;
                }
            }
            display();

            // Calculate wating time, turnarround time and completion time.
            p[0].waitingTime = 0;
            p[0].completionTime = p[0].burstTime;
            p[0].turnArroundTime = p[0].completionTime - p[0].arrivalTime; 
            for(int i = 1; i < n; i++)
            {
                p[i].waitingTime = p[i-1].waitingTime + p[i-1].burstTime;
                p[i].completionTime = p[i].burstTime + p[i-1].completionTime;
                p[i].turnArroundTime = p[i].completionTime - p[i].arrivalTime;
            }

            display();

        }

        
};

int main()
{
    Assignment2 a(5);
    
    int s;
    
    while(1)
    {
        cout<<"Enter the scheduling Method : "<<endl;
        cout<<"1. FCFS"<<endl<<"2. SJF"<<endl<<"3. Exit"<<endl;
        cout<<"-----------------------"<<endl;
        cin>>s;
        cout<<"-----------------------"<<endl;
        switch(s)
        {
            case 1:
                a.takeInput();
                a.schedule("FCFS");
                continue;

            case 2:
                a.takeInput();
                a.schedule("SJF");
                continue;

            case 3:
                a.takeInput();
                a.schedule("Priority_NP");
                continue;
            
            case 4:
                return 0;

            default:
                cout<<"Invalid input."<<endl;
        }
    }


    return 0;

}