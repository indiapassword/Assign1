#include<bits/stdc++.h>
using namespace std;

void firstFit(int bs[], int ps[], int m, int n) 
{
    int temp[m];    // To store the available memory in a block
    copy(bs, bs + m, temp);     // Copy values of bs[] into temp[]
    cout << "\nFirst Fit Allocation:\n";
    cout << "---------------------------------------------------\n";
    cout << "| Process No. | Process Size | Block No. | Fragment |\n";
    cout << "---------------------------------------------------\n";
    for (int i = 0; i < n; i++)     // To iterate through each process
    {
        int all = 0;
        for (int j = 0; j < m; j++)     // To check each block
        {
            if (temp[j] >= ps[i]) 
            {
                cout << "| " << setw(11) << i + 1 << " | " << setw(12) << ps[i] << " | " << setw(8) << j + 1 << " | " << setw(8) << temp[j] - ps[i] << " |\n";
                temp[j] -= ps[i];
                all = 1;
                break;
            }
        }
        // If the block is not allocated to any process
        if (all != 1)
            cout << "| " << setw(11) << i + 1 << " | " << setw(12) << ps[i] << " | " << setw(8) << "Not Allocated" << " | " << setw(8) << "No Change" << " |\n";
    }
    cout << "---------------------------------------------------\n";
}

void nextFit(int bs[], int ps[], int m, int n) 
{
    int temp[m];
    copy(bs, bs + m, temp);
    cout << "\nNext Fit Allocation:\n";
    cout << "---------------------------------------------------\n";
    cout << "| Process No. | Process Size | Block No. | Fragment |\n";
    cout << "---------------------------------------------------\n";
    int lastAllocated = 0;
    for (int i = 0; i < n; i++)        // To iterate through each process
    {
        int allocated = 0;
        int j = lastAllocated;
        int count = 0;      // To maintain count of number of blocks checked
        while(count != m)         // To iterate through blocks
        {
            if (temp[j] >= ps[i]) 
            {
                cout << "| " << setw(11) << i + 1 << " | " << setw(12) << ps[i] << " | " << setw(8) << j + 1 << " | " << setw(8) << temp[j] - ps[i] << " |\n";
                temp[j] -= ps[i];
                lastAllocated = j;
                allocated = 1;
                break;
            }
            j = (j + 1) % m;       // To wrap arround
            count++;
        }
        if (!allocated) {
            cout << "| " << setw(11) << i + 1 << " | " << setw(12) << ps[i] << " | " << setw(8) << "Not Allocated" << " | " << setw(8) << "No Change" << " |\n";
        }
    }
    cout << "---------------------------------------------------\n";
}

void bestFit(int bs[], int ps[], int m, int n) 
{
    int temp[m];
    copy(bs, bs + m, temp);
    cout << "\nBest Fit Allocation:\n";
    cout << "---------------------------------------------------\n";
    cout << "| Process No. | Process Size | Block No. | Fragment |\n";
    cout << "---------------------------------------------------\n";
    for (int i = 0; i < n; i++)         // For processes
    {
        int bestIdx = -1;
        for (int j = 0; j < m; j++)        // For blocks
        {
            // Fragmentation should be minimum, therefore check where available block memory is minimum
            if (temp[j] >= ps[i]) 
            {
                if (bestIdx == -1 || temp[j] < temp[bestIdx])
                    bestIdx = j;
            }
        }
        
        if (bestIdx != -1) 
        {
            cout << "| " << setw(11) << i + 1 << " | " << setw(12) << ps[i] << " | " << setw(8) << bestIdx + 1 << " | " << setw(8) << temp[bestIdx] - ps[i] << " |\n";
            temp[bestIdx] -= ps[i];
        } else 
        {
            cout << "| " << setw(11) << i + 1 << " | " << setw(12) << ps[i] << " | " << setw(8) << "Not Allocated" << " | " << setw(8) << "No Change" << " |\n";
        }
    }
    cout << "---------------------------------------------------\n";
}

void worstFit(int bs[], int ps[], int m, int n) 
{
    int temp[m];
    copy(bs, bs + m, temp);
    cout << "\nWorst Fit Allocation:\n";
    cout << "---------------------------------------------------\n";
    cout << "| Process No. | Process Size | Block No. | Fragment |\n";
    cout << "---------------------------------------------------\n";
    for (int i = 0; i < n; i++) 
    {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) 
        {
            if (temp[j] >= ps[i]) 
            {
                if (worstIdx == -1 || temp[j] > temp[worstIdx])     // Opposite to best fit
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) 
        {
            cout << "| " << setw(11) << i + 1 << " | " << setw(12) << ps[i] << " | " << setw(8) << worstIdx + 1 << " | " << setw(8) << temp[worstIdx] - ps[i] << " |\n";
            temp[worstIdx] -= ps[i];
        } else 
        {
            cout << "| " << setw(11) << i + 1 << " | " << setw(12) << ps[i] << " | " << setw(8) << "Not Allocated" << " | " << setw(8) << "No Change" << " |\n";
        }
    }
    cout << "---------------------------------------------------\n";
}

int main() 
{

    // bs[] = block sizes
    // ps[] = process sizes
    // m = number of blocks
    // n = number of processes

    int m, n;
    cout << "Enter the number of blocks: ";
    cin >> m;
    cout << "Enter the number of processes: ";
    cin >> n;
    int bs[m], ps[n];
    cout << "Enter the sizes of " << m << " blocks:\n";
    for (int i = 0; i < m; i++) 
    {
        cin >> bs[i];
    }
    cout << "Enter the sizes of " << n << " processes:\n";
    for (int i = 0; i < n; i++) 
    {
        cin >> ps[i];
    }
    firstFit(bs, ps, m, n);
    nextFit(bs, ps, m, n);
    bestFit(bs, ps, m, n);
    worstFit(bs, ps, m, n);
    return 0;
}