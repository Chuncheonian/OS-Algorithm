#pragma once
#include <iostream>
using namespace std;

#include "PCB.h"
#include "QueueLinkedList.h"

/**
 * application class for item management simply.
 */
class Application {
private:
	int						m_nCurCommand;		// current command number
	static int				m_pid;				// global variable for making PID into Primary Key.

	QueueLinkedList<PCB>	m_jobQue;			// 모든 Process를 저장하고 있는 Queue.
	QueueLinkedList<PCB>	m_readyQue;			// 실행 가능한 Process들이 CPU에 자원을 할당받기 위해 대기하는 Queue.
	QueueLinkedList<PCB>	m_waitingQue;		// I/O 장치에서 Process를 처리하는 동안 대기하는 Queue.
	QueueLinkedList<PCB>	m_runningQue;		// 실행 중인 Process를 저장하고 있는 Queue.

public:
	/**
	 * default constructor.
	 */
	Application() {
		m_nCurCommand = 0;
	}

	/**
	 * default destructor.
	 */
	~Application() {}
	
	/**
	 * @brief	Program driver.
	 * @pre	    program is started.
	 * @post	program is finished.
	 */
	void Run();

	/**
	 * @brief	Display command on screen and Get a input from keyboard.
	 * @pre     None.
	 * @post	None.
	 * @return	User's command.
	 */
	int GetCommand();

    /**
     * @brief   Add new Process into Job Queue.
     * @pre     Job Queue should be initialized.
     * @post    New Process is added into the Job Queue.
     */
    void AddProcess();

    /**
     * @brief   Display all processes in All Queues in screen.
     * @pre     None.
     * @post    None.
     */
    void DisplayStatus();

	/**
	 * @brief	Copy a process in Job Queue To in Ready Queue.
	 * @pre		At least one process in the JobQue must exist and
	 * 			There should not be the same process in the ReadyQue, RunningQue, or WaitingQue.
	 * @post	New State in PCB changes to Ready, and Copy a process in Job Queue To in Ready Queue.
	 */
	void MoveJobToReady();

	/**
	 * @brief	Move a process in Ready Queue To in Running Queue.
	 * @pre		At least one process in the ReadyQue must exist and
	 * 			Process in the RunningQue should not exist.
	 * @post	Ready State in PCB changes to Running, and Move a process in Ready Queue To in Running Queue.
	 */
	void MoveReadyToRun();

	/**
	 * @brief	Move a process in Running Queue To in Waiting Queue, and
	 * 			Execute MoveReadyToRun() If Process in ReadyQue exists.
	 * @pre		At least one process in the RunningQue must exist.
	 * @post	Running State in PCB changes to Waiting,
	 * 			Move a process in Job Queue To in Ready Queue, and
	 * 			Execute MoveReadyToRun() If Process in ReadyQue exists.
	 */
	void MoveRunToWait();

	/**
	 * @brief	Move a process in Waiting Queue To in Ready Queue.
	 * @pre		At least one process in the WaitingQue must exist.
	 * @post	Waiting State in PCB changes to Ready, and Move a process in Waiting Queue To in Ready Queue.
	 */
	void MoveWaitToReady();

	/**
	 * @brief	Termination a process in Running Queue.
	 * @pre		At least one process in the RunningQue must exist.
	 * @post	Running State in PCB changes to Terminated, and
	 * 			Delete the process in JobQue and RunningQue.
	 */
	void MoveRunToExit();

	/**
	 * @brief	Make empty all Queues.
	 * @pre     None.
	 * @post	Make empty list in this member.
	 */
	int MakeEmpty();
};