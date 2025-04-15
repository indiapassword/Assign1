#include<iostream>
#include<vector>
using namespace std;

class Process
{
    public: 
        int processID;
        int allocatedResources[3];
        int max[3];
};
class BankersAlgorithm
{
    public:
        int n;
        Process *p;
        int totalResources[3];
    
        BankersAlgorithm(int a, int *r)
        {
            n = a;
            p = new Process[n];
            for(int i = 0 ; i < 3 ; i++)
            {
                totalResources[i] = r[i];
            }
        }

        void takeInput()
        {
            cout<<"Enter process information."<<endl;

            for(int i = 0 ; i < n ; i++)
            {
                cout<<"Process "<<i+1<<": "<<endl;
                cout<<"Allocated Resources : ";
                for(int j = 0 ; j < 3 ; j++)
                {
                    cin>>p[i].allocatedResources[j];
                }
                cout<<"Maximum Resources : ";
                for(int j = 0 ; j < 3 ; j++)
                {
                    cin>>p[i].max[j];
                }
            }
        }
        void algo()
        {
            // Calculate initial available resources
            int available[3] = {0,0,0};

            for(int i = 0 ; i < n; i++)
            {
                for(int j = 0 ; j < 3 ; j++)
                {
                    available[j] += p[i].allocatedResources[j];
                }
            }
            for(int i = 0 ; i < 3 ; i++)
            {
                available[i] = totalResources[i] - available[i]; 
            }

            // Calculate need
            int need[n][3];

            for(int i = 0 ; i < n ; i++)        // For each process
            {
                for(int j = 0 ;  j < 3 ; j++)       // For each resource in a process
                {
                    need[i][j] = p[i].max[j] - p[i].allocatedResources[j];      // need = max - allocated
                }
            }

            // Implement algorithm
            vector<int> v;      // To maintain safe sequence

            bool visited[n];
            for(int i = 0 ; i < n ; i++)
            {
                visited[i] = false;
            }

            int count = n;
            int i = 0;
            int cycles = 0;
            bool progress = false;
            while(count > 0)
            {
                progress = false;
                if(visited[i] == false)
                {
                    for(int j = 0 ; j < 3 ; j++)
                    {
                        if(need[i][j] > available[j])       // If need > available then do not allocate
                        {
                            goto label_name;        // To skip following steps
                        }
                    }

                    v.push_back(i+1);
                    visited[i] = true;
                    for(int j = 0 ; j < 3 ; j++)
                    {
                        need[i][j] = 0;
                    }

                    // Update available
                    for(int j = 0 ; j < 3 ; j++)
                    {
                        available[j] = available[j] + p[i].allocatedResources[j];       // The resourses are released after process completion
                    }

                    count--;
                    progress = true;
                    cycles = 0;
                
                }
                label_name:
                i = (i + 1) % n;
                cycles++; // Count iterations**
                if(cycles >= n && !progress) // If no progress in one full cycle, exit**
                {
                    cout << "No safe sequence exists!" << endl;
                    return;
                }
                
            }

            cout<<"The safe sequence is : ";
            for(int i = 0 ; i < n; i++)
            {
                cout<<v[i]<<"\t";
            }
        }
};
int main()
{
    int a[3];
    int n;
    cout<<"Enter number of processes : ";
    cin>>n;
    cout<<"Enter the total number of resources(A, B, C) : ";
    for(int i = 0 ; i < 3 ; i++)
    {
        cin>>a[i];
    }
    BankersAlgorithm b(n, a);
    b.takeInput();
    cout<<"----------------------------------"<<endl;
    b.algo();
    return 0;

}