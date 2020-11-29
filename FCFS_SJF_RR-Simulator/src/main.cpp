// Lecture : OS Term Project #2
// Name : Kwon Dong Young
// Student ID : 2016110307

#include "Application.h"

// Display command on screen and get a input from keyboard.
int GetCommand();

// Procedure for Scheduling Queues Program.
int main() {
    int         m_command;      // current command number
    Application app;            // Program application

    while(1) {
        m_command = GetCommand();

        switch(m_command) {
            case 1:     // 1 : FCFS scheduler
                app.Run(0);
                break;
            case 2:     // 2 : SJF scheduler
                app.Run(1);
                break;
            case 3:     // 3 : RR scheduler
                app.Run(2);
                break;
            case 0:     // 0 : Quit
                return 0;
            default:
                cout << "\tIllegal sellection...\n";
                break;
        }
    }
    return 0;
}

// Display command on screen and get a input from keyboard.
int GetCommand() {
    int command;
    cout << endl << endl;
    cout << "\t---ID -- Command ----- " << endl;
    cout << "\t   1 : FCFS Scheduler" << endl;
    cout << "\t   2 : SRTF Scheduler" << endl;
    cout << "\t   3 : RR Scheduler" << endl;
    cout << "\t   0 : Quit " << endl;

    cout << endl << "\t Choose a Command--> ";
    cin >> command;
    cout << endl;

    return command;
}