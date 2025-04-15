#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Assignment8
{
public:
    vector<int> requests;
    int head;
    int n;
    int diskSize;

    Assignment8()
    {
        cout << "Enter total number of disk requests: ";
        cin >> n;
        requests.resize(n);

        cout << "Enter disk requests: ";
        for (int i = 0; i < n; i++)
        {
            cin >> requests[i];
        }

        cout << "Enter initial head position: ";
        cin >> head;

        cout << "Enter total disk size (e.g., 200): ";
        cin >> diskSize;
    }

    void FIFO()
    {
        int seekCount = 0;
        int current = head;
        cout << "\nFIFO Order: " << current << " ";

        for (int i = 0; i < n; i++)
        {
            seekCount += abs(requests[i] - current);
            current = requests[i];
            cout << "-> " << current << " ";
        }

        cout << "\nTotal Seek Operations (FIFO): " << seekCount << endl;
    }

    void SSTF()
    {
        vector<int> temp = requests;
        int current = head;
        int seekCount = 0;
        cout << "\nSSTF Order: " << current << " ";

        vector<bool> visited(n, false);     // Declare vector of size n and initialize all the elements as false

        for (int i = 0; i < n; i++)
        {
            int minDist = INT_MAX;
            int pos = -1;

            // To find the minimum seek count
            for (int j = 0; j < n; j++)
            {
                if (!visited[j] && abs(temp[j] - current) < minDist)
                {
                    minDist = abs(temp[j] - current);
                    pos = j;    // Update the index which gives minimum seek count
                }
            }

            seekCount += minDist;
            current = temp[pos];
            visited[pos] = true;

            cout << "-> " << current << " ";
        }

        cout << "\nTotal Seek Operations (SSTF): " << seekCount << endl;
    }

    void SCAN()
    {
        vector<int> temp = requests;
        temp.push_back(head);
        temp.push_back(0); // assuming SCAN moves towards 0 first
        sort(temp.begin(), temp.end());

        int index;
        for(index = 0 ; index < n+2 ; index++)  // (n+2) because we added 2 extra elements in temp
        {
            if(temp[index] == head)
            {
                break;
            }
        }
        int seekCount = 0;
        int current = head;
        cout << "\nSCAN Order: "<<head<<" ";
        
        // Moving towards 0 first
        for(int i = index-1 ; i >= 0 ; i--)     
        {
            seekCount += abs(current - temp[i]);
            current = temp[i];
            cout<<"-> "<<current<<" ";
        }
        
        // Moving towards end
        for(int i = index + 1 ; i < n+2 ; i++)
        {
            seekCount += abs(current - temp[i]);
            current = temp[i];
            cout<<"-> "<<current<<" ";
        }        

        cout << "\nTotal Seek Operations (SCAN): " << seekCount << endl;
    }

    void CSCAN()
    {
        vector<int> temp = requests;
        temp.push_back(head);
        temp.push_back(0);
        temp.push_back(diskSize - 1);
        sort(temp.begin(), temp.end());

        int index;
        for(index = 0 ; index < (n+3) ; index++)    // (n+3) because we added 3 extra elements in temp
        {
            if(temp[index] == head)
            {
                break;
            }
        }
        int seekCount = 0;

        cout << "\nC-SCAN Order: "<<head<<" ";
        int i = (index + 1) % (n+3);
        int current = temp[index];
        while(i != index)
        {
            seekCount += abs(current - temp[i]);
            current = temp[i];
            cout<<"-> "<<current<<" ";
            i = (i + 1)%(n+3);      // To wrap arround
        }

        cout << "\nTotal Seek Operations (C-SCAN): " << seekCount << endl;
    }
};

int main()
{
    Assignment8 a;
    cout << endl
         << "-----------------------------------------------------------------------" << endl;

    cout << "\nRunning FIFO...\n";
    a.FIFO();
    cout << endl
         << "-----------------------------------------------------------------------";

    cout << "\n\nRunning SSTF...\n";
    a.SSTF();
    cout << endl
         << "-----------------------------------------------------------------------";
    cout << "\n\nRunning SCAN...\n";
    a.SCAN();
    cout << endl
         << "-----------------------------------------------------------------------";
    cout << "\n\nRunning C-SCAN...\n";
    a.CSCAN();
    cout << endl
         << "-----------------------------------------------------------------------";
    return 0;
}
