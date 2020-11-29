#include "Application.h"

// Program driver.
void Application::Run() {
	while(1) {
		m_nCurCommand = GetCommand();

		switch(m_nCurCommand) {
		case 1:		// Add new Process inrto Job Queue.
			AddProcess();
			break;
		case 2:		// Display all Queue.
			DisplayStatus();
			break;
		case 3:		// Copy a process in Job Queue To in Ready Queue.
			MoveJobToReady();
			break;
		case 4:		// Move a process in Ready Queue To in Running Queue.
			MoveReadyToRun();
			break;
		case 5:		// Move a process in Running Queue To in Waiting Queue.
			MoveRunToWait();
			break;
		case 6:		// Move a process in Waiting Queue To in Ready Queue.
			MoveWaitToReady();
			break;
		case 7:		// Termination process in Running Queue.
			MoveRunToExit();
			break;
		case 8:		// Make empty all Queues.
			MakeEmpty();
			break;
		case 0:		// Quit.
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}


// Display command on screen and get a input from keyboard.
int Application::GetCommand() {
	int command;
	cout << endl << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : Add new Process" << endl;
	cout << "\t   2 : Display All Process Status" << endl;
	cout << "\t   3 : Copy JobQue to ReadyQue" << endl;
	cout << "\t   4 : Move ReadyQue to RunningQue" << endl;
	cout << "\t   5 : Move RunningQue to WaitingQue" << endl;
	cout << "\t   6 : Move WaitingQue to ReadyQue" << endl;
	cout << "\t   7 : Move RunningQue to Termination" << endl;
	cout << "\t   8 : Make empty all Process" << endl;
	cout << "\t   0 : Quit " << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}

// global variable allocate Initial Value.
int Application::m_pid = 0;

//  Add new Process into Job Queue.
void Application::AddProcess() {			// case 1
	PCB pcb;
	
	m_pid++;					// PID++
	pcb.SetRecord(m_pid, 1);	// PID and New State Allocate
	m_jobQue.EnQue(pcb);		// Add new process intoo the JobQue.

    DisplayStatus();			// Displat Status
}

// Display all records in the list in screen.
void Application::DisplayStatus() {			// case 2
	PCB pcb;

	cout << "\n\t<==All Process State==>" << endl;

	// Display Job Queue.
	m_jobQue.ResetList();	// Queue pointer initialized.
	cout << "\t--Current Job Que list--" << endl;
	cout << "\t";
	for (int i = 0; i < m_jobQue.GetLength(); i++) {
		m_jobQue.GetNextItem(pcb);
		cout << "PCB" << pcb.GetPID() << "("<< pcb.GetState() << "), ";
	}

	// Display Ready Queue.
	m_readyQue.ResetList();	// Queue pointer initialized.
	cout << "\n\t--Current Ready Que list--" << endl;
	cout << "\t";
	for (int i = 0; i < m_readyQue.GetLength(); i++) {
		m_readyQue.GetNextItem(pcb);
		cout << "PCB" << pcb.GetPID() << "("<< pcb.GetState() << "), ";
	}

	// Display Running Queue.
	m_runningQue.ResetList();	// Queue pointer initialized.
	cout << "\n\t--Current Running Que list--" << endl;
	cout << "\t";
	for (int i = 0; i < m_runningQue.GetLength(); i++) {
		m_runningQue.GetNextItem(pcb);
		cout << "PCB" << pcb.GetPID() << "("<< pcb.GetState() << "), ";
	}

	// Display Waiting Queue.
	m_waitingQue.ResetList();	// Queue pointer initialized.
	cout << "\n\t--Current Waiting Que list--" << endl;
	cout << "\t";
	for (int i = 0; i < m_waitingQue.GetLength(); i++) {
		m_waitingQue.GetNextItem(pcb);
		cout << "PCB" << pcb.GetPID() << "("<< pcb.GetState() << "), ";
	}

	cout << endl;
}

// Copy a process in Job Queue To in Ready Queue.
void Application::MoveJobToReady() {		// case 3
	DisplayStatus();
	
	PCB pcb;
	pcb.SetPIDFromKB();

	// If process in the JobQue don't exist.
	if (!m_jobQue.Get(pcb)) {
		cout << "\tNo Exist PCB in Job Que" << endl;
		return;
	}

	// If same process in the ReadyQue, RunningQue, or WaitingQue exist.
	if (m_readyQue.Get(pcb) || m_runningQue.Get(pcb) || m_waitingQue.Get(pcb)) {
		cout << "\tExist Same PCB in another Que" << endl;
		return;
	}

	pcb.SetState(4);		// State Change
	m_readyQue.EnQue(pcb);	// Add process into ReadyQue.

	DisplayStatus();		// Display Status.
}

// Move a process in Ready Queue To in Running Queue.
void Application::MoveReadyToRun() {		// case 4
	PCB pcb;

	// If process in the ReadyQue don't exist.
	if (!m_readyQue.GetLength()) {
		cout << "\tNo Exist PCB in Ready Que" << endl;
		return;
	}
	
	// If process in the ReadyQue exist.
	else {
		
		// If process in the RunningQue don't exist.
		if (!m_runningQue.GetLength()) {
			m_readyQue.ResetList();			// Queue pointer initialized.
			m_readyQue.GetNextItem(pcb); 	// Bring Information of process in ReadyQue
			m_readyQue.DeQue();				// Delete process in ReadyQue.
			pcb.SetState(2);				// State Change.
			m_runningQue.EnQue(pcb);		// Add process into RunningQue.

			DisplayStatus();				// Display Status.
		}

		// If process in the RunningQue exist.
		else
			cout << "\tExist PCB in Running Que" << endl;
	}
}

// Move a process in Running Queue To in Waiting Queue, and
// Execute MoveReadyToRun() If Process in ReadyQue exists.
void Application::MoveRunToWait() {			// case 5
	PCB pcb;

	// If process in the RunningQue don't exist.
	if (!m_runningQue.GetLength()) {
		cout << "\tNo Exist PCB in Running Que" << endl;
		return;
	}

	// If process in the RunningQue exist.
	m_runningQue.ResetList();		// Queue pointer initialized.
	m_runningQue.GetNextItem(pcb);	// Bring Information of process in RunningQue.
	m_runningQue.DeQue();			// Delete process in RunningQue.
	pcb.SetState(3);				// State Change
	m_waitingQue.EnQue(pcb);		// Add process into WaitingQue.

	// If Process in ReadyQue exists.
	if (m_readyQue.GetLength()) {
		MoveReadyToRun();
	}

	DisplayStatus();				// Display Status.
}

// Move a process in Waiting Queue To in Ready Queue.
void Application::MoveWaitToReady() {		// case 6
	PCB pcb;
	
	// If process in the WaitingQue don't exist.
	if (!m_waitingQue.GetLength()) {
		cout << "\tNo Exist PCB in Waiting Que" << endl;
		return;
	}

	// If process in the WaitingQue exist.
	m_waitingQue.ResetList();		// Queue pointer initialized.
	m_waitingQue.GetNextItem(pcb);	// Bring Information of process in WaitingQue.
	m_waitingQue.DeQue();			// Delete process in WaitingQue.
	pcb.SetState(4);				// State Change
	m_readyQue.EnQue(pcb);			// Add process into ReadyQue.

	DisplayStatus();				// Display Status.
}

// Termination a process in Running Queue.
void Application::MoveRunToExit() {			// case 7
	PCB pcb;

	// If process in the RunningQue don't exist.
	if (!m_runningQue.GetLength()) {
		cout << "\tNo Exist PCB in Running Que" << endl;
		return;
	}
	
	// If process in the RunningQue exist.
	m_runningQue.ResetList();		// Queue pointer initialized.
	m_runningQue.GetNextItem(pcb);	// Bring Information of process in RunningQue.
	m_runningQue.DeQue();			// Delete process in RunningQue.
	pcb.SetState(5);				// State Change.
	m_jobQue.Delete(pcb);			// Delete corresponding process in JobQue.

	DisplayStatus();				// Display Status.
}

// Make empty all Queues.
int Application::MakeEmpty() {				// case 8
	m_jobQue.MakeEmpty();		// Make empty Job Queue.
	m_readyQue.MakeEmpty();		// Make empty Ready Queue.
	m_runningQue.MakeEmpty();	// Make empty Running Queue.
	m_waitingQue.MakeEmpty();	// Make empty Waiting Queue.

	cout << "All Queues are now empty.";
	return 0;
}