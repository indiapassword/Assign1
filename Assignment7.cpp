#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Assignment7
{
public:
    int *pageReference;
    int n;
    int *pageFrame;
    int frameSize;

    Assignment7()
    {
        cout << "Enter page frame size : ";
        cin >> frameSize;
        pageFrame = new int[frameSize];

        cout << "Enter number of page peferences : ";
        cin >> n;
        pageReference = new int[n];
        for (int i = 0; i < frameSize; i++)
        {
            pageFrame[i] = -1;
        }

        cout << "Enter page references : ";
        for (int i = 0; i < n; i++)
        {
            cin >> pageReference[i];
        }
    }

    void FCFS()
    {
        int end = 0;
        int hit = 0;
        int miss = 0;

        bool isHit;

        for (int i = 0; i < n; i++)
        {
            isHit = false;
            for (int j = 0; j < frameSize; j++)
            {
                if (pageFrame[j] == pageReference[i])
                {
                    hit++;
                    isHit = true;
                    break;
                }
            }

            if (!isHit)
            {
                pageFrame[end] = pageReference[i];
                miss++;
                end = (end + 1) % frameSize;
            }

            for (int k = 0; k < frameSize; k++)
            {
                cout << pageFrame[k] << "\t";
            }
            if (isHit)
            {
                cout << "Hit" << endl;
            }
            else
            {
                cout << "Miss" << endl;
            }
        }
        cout << "Total Hit : " << hit << endl;
        cout << "Total Miss : " << miss;
    }

    void LRU()
    {
        int hit = 0;
        int miss = 0;

        bool isHit;

        vector<int> v;    // To store the sequence of page references used (First element is the least resently used element)
        for (int i = 0; i < frameSize; i++)
        {
            v.push_back(-1);
        }

        map<int, int> m;
        m[-1] = 0;      // To store the index of the page reference in pageFrame array

        for (int i = 0; i < n; i++)
        {
            isHit = false;
            for (int j = 0; j < frameSize; j++)
            {
                if (pageFrame[j] == pageReference[i])
                {
                    hit++;
                    isHit = true;

                    // Find the page reference in the vector --> delete it --> append it to last
                    for (auto it = v.begin(); it != v.end(); it++)
                    {
                        if (*it == pageReference[i])
                        {
                            v.erase(it);
                            break;
                        }
                    }
                    v.push_back(pageReference[i]);

                    break;
                }
            }

            // Replace it with the element which is at the begining of the vector
            if (!isHit)
            {
                pageFrame[m[*v.begin()]] = pageReference[i];
                v.push_back(pageReference[i]);
                m[pageReference[i]] = m[*v.begin()];
                if (*v.begin() == -1)       // If the page frame in empty
                {
                    m[*v.begin()]++;
                }
                v.erase(v.begin());

                miss++;
            }

            for (int k = 0; k < frameSize; k++)
            {
                cout << pageFrame[k] << "\t";
            }
            if (isHit)
            {
                cout << "Hit" << endl;
            }
            else
            {
                cout << "Miss" << endl;
            }
        }
        cout << "Total Hit : " << hit << endl;
        cout << "Total Miss : " << miss;
    }

    void optimal()
    {
        int hit = 0;
        int miss = 0;

        for (int i = 0; i < n; i++)
        {
            bool isHit = false;

            // Check if the page is already in the frame
            for (int j = 0; j < frameSize; j++)
            {
                if (pageFrame[j] == pageReference[i])
                {
                    hit++;
                    isHit = true;
                    break;
                }
            }

            // If it's a miss, replace a page
            if (!isHit)
            {
                int indexToReplace = -1;
                int farthest = i + 1;

                // Find an empty frame slot first
                for (int j = 0; j < frameSize; j++)
                {
                    if (pageFrame[j] == -1)
                    {
                        indexToReplace = j;
                        break;
                    }
                }

                // If no empty slot found, find the page used farthest in future
                if (indexToReplace == -1)
                {
                    int maxDistance = -1;
                    for (int j = 0; j < frameSize; j++)
                    {
                        int k;
                        for (k = i + 1; k < n; k++)
                        {
                            if (pageReference[k] == pageFrame[j])
                                break;
                        }

                        if (k == n) // This page is never used again
                        {
                            indexToReplace = j;
                            break;
                        }
                        else if (k - i > maxDistance)
                        {
                            maxDistance = k - i;
                            indexToReplace = j;
                        }
                    }
                }

                // Replace the page
                pageFrame[indexToReplace] = pageReference[i];
                miss++;
            }

            // Print current frame
            for (int k = 0; k < frameSize; k++)
            {
                cout << pageFrame[k] << "\t";
            }
            if (isHit)
            {
                cout << "Hit" << endl;
            }
            else
            {
                cout << "Miss" << endl;
            }
        }

        cout << "Total Hit : " << hit << endl;
        cout << "Total Miss : " << miss << endl;
    }
};
int main()
{
    Assignment7 a;

    cout << "\n=== First-Come-First-Serve (FCFS) Algorithm ===\n";
    // Reset pageFrame to -1 before each algorithm
    for (int i = 0; i < a.frameSize; i++)
    {
        a.pageFrame[i] = -1;
    }
    a.FCFS();

    cout << "\n\n=== Least Recently Used (LRU) Algorithm ===\n";
    for (int i = 0; i < a.frameSize; i++)
    {
        a.pageFrame[i] = -1;
    }
    a.LRU();

    cout << "\n\n=== Optimal Page Replacement Algorithm ===\n";
    for (int i = 0; i < a.frameSize; i++)
    {
        a.pageFrame[i] = -1;
    }
    a.optimal();

    return 0;
}
