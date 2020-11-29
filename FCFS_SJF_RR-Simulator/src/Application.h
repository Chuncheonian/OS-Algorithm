#pragma once
#include <iostream>
#include <time.h>
using namespace std;

#include "PCB.h"
#include "QueueLinkedList.h"

/**
 * application class for item management simply.
 */
class Application {
    private:
        QueueLinkedList<PCB*>    m_readyQueue;      // ReadyQueue

    public:
        /**
         * default constructor.
         */
        Application() {}

        /**
         * default destructor.
         */
        ~Application() {}

        /**
         * @brief   Program driver.
         * @pre     program is started.
         * @post    program is finished.
         */
        void Run(int _scheduler);

        // FCFS Scheduler
        PCB* FCFS(PCB* cpu);

        // SJF Scheduler
        PCB* SJF(PCB *cpu);

        // RR Scheduler
        PCB* RR(PCB *cpu);
};
