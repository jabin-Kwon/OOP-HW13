#include <iostream>
#include <Windows.h> // Sleep( )
#include <vector>
#include <fstream>

using namespace std;

int main() {
    int NI = 10, NO = 10; // Initial values set to 10
    int itime = 0, T = 1, lost = 0, ni, no, high = 0, sum = 0; // Initialize variables
    float average = 0;
    int capacity = 100;
    int NofPackets[120] = { 0 }; // Initialize array to store number of packets

    ofstream xx; // Create an output file stream
    xx.open("aa.txt");
    if (!xx) {
        cout << "Can't open file" << endl;
        return 666;
    }

    vector<int> queue;

    while (itime < 120) {
        itime += T;

        Sleep(T * 1000); // Sleep for 1 second
        cout << "Elapsed time[sec] = " << itime << endl; // Record time

        // Input
        ni = rand() % NI;
        cout << "ni: " << ni << endl;

        if (capacity < queue.size() + ni) { // If overflow occurs
            lost += queue.size() + ni - capacity; // Accumulate lost packets
            ni = capacity - queue.size(); // Adjust ni to fit capacity
            cout << "Overflow" << endl;
        }

        for (int i = 0; i < ni; i++) {
            queue.push_back(rand() % 20);
            cout << queue[queue.size() - 1] << " in " << queue.size() << endl;
        }
        cout << endl;

        // Output
        no = rand() % NO;
        cout << "no: " << no << endl;

        for (int i = 0; i < no && !queue.empty(); i++) {
            int ii = queue[0];
            cout << ii << " out " << queue.size() << endl;
            queue.erase(queue.begin());
        }
        cout << endl;
        NofPackets[itime - 1] = queue.size();
        cout << "NofPackets: " << NofPackets[itime - 1] << endl << endl;

        if (high < NofPackets[itime - 1]) { // Update the highest value
            high = NofPackets[itime - 1];
        }

        sum += NofPackets[itime - 1]; // Accumulate the total number of packets
    } // End of while loop

    average = static_cast<float>(sum) / itime; // Calculate the average

    int j = 0;
    for (int a : NofPackets) {
        j++;
        xx << j << " " << a << endl; // Write to the file
    }

    cout << "Highest: " << high << " Average: " << average << endl;

    xx.close();

    return 123;
}
