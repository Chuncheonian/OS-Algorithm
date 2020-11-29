// Lecture : OS Term Project #3
// Department : Computer Science and Engineering
// Name : Kwon Dong Young
// Student ID : 2016110307

#include <iostream>
using namespace std;

#define NUM_OF_PROCESS 5
#define NUM_OF_RESOURCE 4

struct Process {
    int maxResources[NUM_OF_RESOURCE];
    int allocResources[NUM_OF_RESOURCE];
    int needResources[NUM_OF_RESOURCE];
    bool finished = false;
};

int main() {
    for (int question = 1; question <= 2 ; question++) {
        struct Process Processes[NUM_OF_PROCESS];

        int reqResources[NUM_OF_RESOURCE];
        int completedProcesses[NUM_OF_PROCESS];
        int availableResources[NUM_OF_RESOURCE];
    
        availableResources[0] = 3;
        availableResources[1] = 2;
        availableResources[2] = 1;
        availableResources[3] = 1;

        Processes[0].maxResources[0] = 6;
        Processes[0].maxResources[1] = 0;
        Processes[0].maxResources[2] = 1;
        Processes[0].maxResources[3] = 2;

        Processes[1].maxResources[0] = 1;
        Processes[1].maxResources[1] = 7;
        Processes[1].maxResources[2] = 5;
        Processes[1].maxResources[3] = 0;

        Processes[2].maxResources[0] = 2;
        Processes[2].maxResources[1] = 3;
        Processes[2].maxResources[2] = 5;
        Processes[2].maxResources[3] = 6;

        Processes[3].maxResources[0] = 1;
        Processes[3].maxResources[1] = 6;
        Processes[3].maxResources[2] = 5;
        Processes[3].maxResources[3] = 3;

        Processes[4].maxResources[0] = 1;
        Processes[4].maxResources[1] = 6;
        Processes[4].maxResources[2] = 5;
        Processes[4].maxResources[3] = 6;

        Processes[0].allocResources[0] = 4;
        Processes[0].allocResources[1] = 0;
        Processes[0].allocResources[2] = 0;
        Processes[0].allocResources[3] = 1;

        Processes[1].allocResources[0] = 1;
        Processes[1].allocResources[1] = 1;
        Processes[1].allocResources[2] = 0;
        Processes[1].allocResources[3] = 0;

        Processes[2].allocResources[0] = 1;
        Processes[2].allocResources[1] = 2;
        Processes[2].allocResources[2] = 5;
        Processes[2].allocResources[3] = 4;

        Processes[3].allocResources[0] = 0;
        Processes[3].allocResources[1] = 6;
        Processes[3].allocResources[2] = 3;
        Processes[3].allocResources[3] = 3;

        Processes[4].allocResources[0] = 0;
        Processes[4].allocResources[1] = 2;
        Processes[4].allocResources[2] = 1;
        Processes[4].allocResources[3] = 2;

        // Need = MAX - Allocation
        for (int i = 0; i < NUM_OF_PROCESS; i++) {
            for (int j = 0; j < NUM_OF_RESOURCE; j++) {
                Processes[i].needResources[j] = Processes[i].maxResources[j] - Processes[i].allocResources[j];
            }
        }
    
        if (question == 2) {
            reqResources[0] = 1;
            reqResources[1] = 2;
            reqResources[2] = 0;
            reqResources[3] = 0;

            // Allocation >= Request
            for (int i = 0; i < NUM_OF_RESOURCE; i++) {
                if ((availableResources[i] - reqResources[i]) < 0) {
                    cout << "Not Allocation" << endl;
                    return 0;
                }
            }

            // Available = Available - Request
            availableResources[0] -= reqResources[0];
            availableResources[1] -= reqResources[1];
            availableResources[2] -= reqResources[2];
            availableResources[3] -= reqResources[3];

            // Allocation = Allocation + Request    
            Processes[4].allocResources[0] += reqResources[0];
            Processes[4].allocResources[1] += reqResources[1];
            Processes[4].allocResources[2] += reqResources[2];
            Processes[4].allocResources[3] += reqResources[3];

            // Need = Need - Request
            Processes[4].needResources[0] -= reqResources[0];
            Processes[4].needResources[1] -= reqResources[1];
            Processes[4].needResources[2] -= reqResources[2];
            Processes[4].needResources[3] -= reqResources[3];
        }
        
        bool finished = false;
        int turnCount = 0;

        while (!finished) {
            bool unsafeState = true;
            int completedCount = 0;
            for (int i = 0; i < NUM_OF_PROCESS; i++) {
                if (Processes[i].finished) {
                    completedCount++;
                    continue;
                }

                int possibleAlloc = 0;

                for (int j = 0; j < NUM_OF_RESOURCE; j++) {
                    if (availableResources[j] >= Processes[i].needResources[j]) {
                        possibleAlloc++;
                    }
                }
                if (possibleAlloc == NUM_OF_RESOURCE) {
                    for (int j = 0; j < NUM_OF_RESOURCE; j++) {
                        availableResources[j] += Processes[i].allocResources[j];
                        Processes[i].allocResources[j] = 0;
                    }
                    Processes[i].finished = true;
                    completedProcesses[turnCount] = i;
                    turnCount++;
                    unsafeState = false;
                }
            }

            if (completedCount == NUM_OF_PROCESS) {
                finished = true;
                break;
            }
            if (unsafeState) {
                cout << "Question" << question << " : System is Unsafe State" << endl;
                break;
            }
        }

        if (finished) {
            cout << "Question" << question << " : System is Safe State, ";
            cout << "Safe Sequence -> ";
            for (int i = 0; i < NUM_OF_PROCESS; i++) {
                cout << "P" << completedProcesses[i] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}