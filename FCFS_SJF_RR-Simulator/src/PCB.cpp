#include "PCB.h"

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
