#include "PCB.h"

// Set Process ID(PID) from keyboard.
void PCB::SetPIDFromKB() {
	cout << "\tEnter PID : ";
	cin >> m_pid;
}

// Set Process State from keyboard.
void PCB::SetStateFromKB() {
	cout << "\tEnter State(1. new, 2. running, 3. waiting, 4.ready, 5. terminated) : ";
	cin >> m_state;
}

// Set Process record from keyboard.
void PCB::SetRecordFromKB() {
	SetPIDFromKB();
	SetStateFromKB();
}

// Read a record from file.
int PCB::ReadDataFromFile(ifstream& fin) {
	fin >> m_pid;
	fin >> m_state;

	return 1;
};

// Write a record into file.
int PCB::WriteDataToFile(ofstream& fout) {
	fout << m_pid << " ";
	fout << m_state;
	return 1;
}

// Compare two PCB by PID.
bool PCB::operator>(PCB& item) {
	return (this->GetPID() > item.GetPID());
}	// return 1 if this.m_pid > data.m_pid, 0 if not.

// Compare two PCB by PID.
bool PCB::operator<(PCB& item) {
	return (this->GetPID() < item.GetPID());
}	// return 1 if this.m_pid < data.m_pid, 0 if not.

// Compare two PCB by PID.
bool PCB::operator==(PCB& item) {
	return (this->GetPID() == item.GetPID());
}	// return 1 if this.m_pid == data.m_pid, 0 if not.