#include "Application.h"
#include "QueueLinkedList.h"
#define NPROC    6
#define Quantum  3

#define _FCFS     0
#define _SJF      1
#define _RR       2

// Program driver.
void Application::Run(int _scheduler) {
    PCB process[NPROC];

    process[0].SetRecord(0,0,10);
    process[1].SetRecord(1,3,12);
    process[2].SetRecord(2,7,4);
    process[3].SetRecord(3,10,6);
    process[4].SetRecord(4,14,8);
    process[5].SetRecord(5,15,7);

    PCB *cpu = nullptr;
    int currentTime = 0;
    int nextForkTime = 0;;
    int numProc = 0;
    int qTime = 0; // QuantumTime
    int scheduler = _scheduler; // 0: FCFS, 1:SJF, 2:RR

    cout << "Scheduler : ";
    switch (scheduler) {
    case _FCFS :
        cout << "FCFS " << endl << endl;
        break;
    case _SJF:
        cout << "SRTF " << endl << endl;
        break;
    case _RR :
        cout << "RR " << endl << endl;
        break;
    }

    cpu = &process[numProc++];
    nextForkTime = process[numProc].getArrivalTime();
    while(1){
        currentTime++;
        qTime++;
        if(cpu != nullptr){
            cpu->exec(currentTime,cpu);
        }
        
        // prcoess Create
        if(currentTime == nextForkTime){
            PCB* ptr = &process[numProc++];
            m_readyQueue.EnQue(ptr);

            if(numProc < NPROC){
                nextForkTime = process[numProc].getArrivalTime();
            }
        }

        // all process is done;
        if(numProc >= NPROC && m_readyQueue.isEmpty() && cpu == nullptr){
            break; 
        }

        // process Terminate
        if (cpu->getServiceTime() == cpu->getBurstTime()){
            cpu->setEndTime(currentTime);
        }

        // schedule
        switch(scheduler){
            case _FCFS:
                // schedule해야하는 상황일 때 scheduler를 호출.
                cpu = FCFS(cpu);
                break;
            case _SJF:
                // 프로세스가 아직 끝나지 않으면 다시 큐에 넣어서 다시 스케쥴링 해준다
                if(cpu->getServiceTime() != cpu->getBurstTime()){
                    m_readyQueue.EnQue(cpu);
                }
                cpu = SJF(cpu);
                break;
            case _RR:
                // Quantum Time이 끝났는지와 프로세스가 끝나는지를 점검하며 라운드로빈을 진행한다.
                if(qTime == Quantum || cpu->getServiceTime() == cpu->getBurstTime()){
                    qTime = 0;

                    if(cpu->getServiceTime() != cpu->getBurstTime()){
                        m_readyQueue.EnQue(cpu);
                    }

                    cpu = RR(cpu);
                }
                break;
        }
    }

    // 평균 waiting Time 출력
    double sum = 0;
    for (int i = 0; i < NPROC; i++) {
        int waitingTime = process[i].getEndTime() - process[i].getArrivalTime() - process[i].getBurstTime();
        sum += waitingTime;
    }

    cout << "Average Waiting Time : " << sum / NPROC << endl;
    cout << "=============================================" << endl;
}

PCB* Application::FCFS(PCB* cpu){
    if (cpu->getServiceTime() == cpu->getBurstTime()){
        if (!m_readyQueue.isEmpty()){
            PCB* temp;
            m_readyQueue.ResetList();
            m_readyQueue.GetNextItem(temp);
            m_readyQueue.DeQue();
            return temp;
        }
        else {
            return nullptr;
        }
    }
    else {
        return cpu;
    }
}

PCB* Application::SJF(PCB *cpu){
    if (m_readyQueue.isEmpty()) {
        return nullptr;
    }

    // 맨처음꺼낸값을 최솟값이라고 가정하고 계산
    PCB* temp = nullptr;
    m_readyQueue.ResetList();
    m_readyQueue.GetNextItem(temp);
    PCB* minProc = temp;
    int minValue = minProc->getBurstTime() - minProc->getServiceTime();

    // 큐에서 하나씩 꺼내서 검사
    /// 하나 꺼냈었으니까 index는 1부터 계산
    for(int i = 1; i < m_readyQueue.GetLength();i++){
        m_readyQueue.GetNextItem(temp);
        int tempRemain = temp->getBurstTime() - temp->getServiceTime(); 
        if(tempRemain <= minValue){
            minProc = temp;
            minValue = tempRemain;
        }
    }
    m_readyQueue.Delete(minProc);
    
    return minProc;
}

PCB* Application::RR(PCB *cpu){
    if (m_readyQueue.isEmpty()){
        return nullptr;
    }

    PCB* temp;
    m_readyQueue.ResetList();
    m_readyQueue.GetNextItem(temp);
    m_readyQueue.DeQue();
    return temp;
}