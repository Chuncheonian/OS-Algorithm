#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * item information class.
 */
class PCB{
protected:
	int		m_pid;			// Process PID. (Primary Key)
	int		m_state;		// process state (1. new, 2. runnung, 3. waiting, 4. ready, 5. terminated)
							// new			-> Process가 처음으로 생성되는 상태
							// running		-> Process 실행 상태
							// waiting		-> Process가 실행 도중에 특수한 이벤트를 만나 대기하는 상태
							// ready		-> Process가 CPU의 자원을 받기 위해서 실행 할 준비가 된 상태
							// terminated	-> Process가 끝날 때 보여주는 상태
	PCB*	m_pointer;		// Next PCB Pointer.
public:
	/**
	* default constructor.
	*/
	PCB() {
		m_pid = 0;
		m_state = 0;
		m_pointer = nullptr;
	}

	/**
	 * destructor.
	 */
	~PCB()	{}

	/**
	 * @brief	Get Process ID(PID).
	 * @pre		Process ID(PID) is set.
	 * @post	None.
	 * @return	Process ID(PID).
	 */
	int GetPID() { return m_pid; }

	/**
	 * @brief	Get Process State.
	 * @pre		Process State is set.
	 * @post	None.
	 * @return	Process State.
	 */
	int GetState() { return m_state; }

	/**
	 * @brief	Get Pointer.
	 * @pre		Pointer is set.
	 * @post	None.
	 * @return	Pointer.
	 */
	PCB* GetPointer() { return m_pointer; }

	/**
	 * @brief	Set Process ID(PID).
	 * @pre	    None.
	 * @post    Process ID(PID) is set.
	 * @param	_pid	Process ID(PID).
	 */
	void SetPID(int _pid) { m_pid = _pid; }
	
	/**
	 * @brief	Set Process State.
	 * @pre	    None.
	 * @post	Process State is set.
	 * @param	_state	Process State
	 */
	void SetState(int _state) { m_state = _state; }
	
	/**
	 * @brief	Set Pointer.
	 * @pre	    None.
	 * @post	Pointer is set.
	 * @param	_pointer	Pointer.
	 */
	void SetPointer(PCB* _pointer) { m_pointer = _pointer; }

	/**
	 * @brief	Set Process record.
	 * @pre	    None.
	 * @post	Process record is set.
	 * @param	_pid		Process ID(PID).
	 * @param	_state		Process name.
	 */
	void SetRecord(int _pid, int _state) {
		SetPID(_pid);
		SetState(_state);
	}

	/**
	 * @brief	Display Process ID(PID) on screen.
	 * @pre	    Process ID(PID) is set.
	 * @post	Process ID(PID) is on screen.
	 */
	void DisplayPIDOnScreen() { cout << "\tPID : " << m_pid; }

	/**
	 * @brief	Display Process State on screen.
	 * @pre	    Process State is set.
	 * @post	Process State is on screen.
	 */
	void DisplayStateOnScreen() { cout << "\tState(1. new, 2. running, 3. waiting, 4.ready, 5. terminated) : " << m_state; }

	/**
	 * @brief	Display a Process record on screen.
	 * @pre	    Process record is set.
	 * @post	Process record is on screen.
	 */
	void DisplayRecordOnScreen() {
		DisplayPIDOnScreen();
		DisplayStateOnScreen();
	   cout << endl;
	}

	/**
	 * @brief	Set Process ID(PID) from keyboard.
	 * @pre	    None.
	 * @post	Process ID(PID) is set.
	 */
	void SetPIDFromKB();

	/**
	 * brief	Set Process State from keyboard.
	 * @pre	    None.
	 * @post	Process State is set.
	 */
	void SetStateFromKB();
	
	/**
	 * @brief	Set Process record from keyboard.
	 * @pre	    None.
	 * @post	Process record is set.
	 */
	void SetRecordFromKB();

	/**
	 * @brief	Read a record from file.
	 * @pre	    the target file is opened.
	 * @post	Process record is set.
	 * @param	fin     file descriptor.
	 * @return	return 1 if this function works well, otherwise 0.
	 */
	int ReadDataFromFile(ifstream& fin);

	/**
	 * @brief	Write a record into file.
	 * @pre	    the target file is opened. And the list should be initialized.
	 * @post	the target file is included the new Process record.
	 * @param	fout	file descriptor.
	 * @return	return 1 if this function works well, otherwise 0.
	 */
	int WriteDataToFile(ofstream& fout);
	
	/**
	 * @brief	Compare two process by PID.
	 * @pre	    Two process should be initialized.
	 * @param	item	target item for comparing.
	 * @return	return 1 if this.m_pid > data.m_pid, 0 if not.
	 */
	bool operator>(PCB& item);

	/**
	 * @brief	Compare two process by PID.
	 * @pre	    two process should be initialized.
	 * @param	item	target item for comparing.
	 * @return	return 1 if this.m_pid > data.m_pid, 0 if not.
	 */
	bool operator<(PCB& item);

	/**
	 * @brief	Compare two process by PID.
	 * @pre	    two process should be initialized.
	 * @param	item	target item for comparing.
	 * @return	return 1 if this.m_pid == data.m_pid, 0 if not.
	 */
	bool operator==(PCB& item);

	/**
	 * @brief	Print record.
	 * @pre		PCB class should be initialized.
	 * @post	content record is on screen.
	 * @param	cout	ostream instance
	 * @param	_item	target PCB for printing.
	 */
	friend ostream& operator<<(ostream& cout, const PCB& _item) {
		cout << "\t[ PID: " << _item.m_pid;
		cout << ", State(1. new, 2. running, 3. waiting, 4.ready, 5. terminated): " << _item.m_state << " ]";

		return cout;
	}

	/**
	 * @brief	Input record.
	 * @pre		none.
	 * @post	content record is initialized.
	 * @param	cin	    istream instance
	 * @param	_item	target PCB for Input.
	 */
	friend istream& operator>>(istream& cin, PCB& _item) {
		cout << "\n\tEnter PID: ";
		cin >> _item.m_pid;
		cout << "\tEnter Process state: ";
		cin >> _item.m_state;

		return cin;
	}
};