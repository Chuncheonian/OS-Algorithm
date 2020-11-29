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
        int     m_pid;          // Process PID. (Primary Key)
        int     m_state;        // process state (1. new, 2. runnung, 3. waiting, 4. ready, 5. terminated)
                                // new          -> Process가 처음으로 생성되는 상태
                                // running      -> Process 실행 상태
                                // waiting      -> Process가 실행 도중에 특수한 이벤트를 만나 대기하는 상태
                                // ready        -> Process가 CPU의 자원을 받기 위해서 실행 할 준비가 된 상태
                                // terminated   -> Process가 끝날 때 보여주는 상태
        int     m_arrivalTime;  // ReadyQueue에 도착하는 시간
        int     m_endTime;      // 끝나는 시간
        int     m_burstTime;    // 수행 시간
        int     m_serviceTime;  // 수행한 시간
    public:

        /**
        * default constructor.
        */
		PCB() {
			m_pid = 0;
			m_state = 0;
			m_serviceTime = 0;
		}

		/**
		 * destructor.
		 */
		~PCB()	{}

		int getArrivalTime(){
			return m_arrivalTime;
		}

		int getBurstTime(){
			return m_burstTime;
		}

		int getServiceTime(){
			return m_serviceTime;
		}

		int getEndTime() {
			return m_endTime;
		}

		void exec(int currentTime,PCB* cpu){
			cout << currentTime-1 <<" - " << currentTime << "ms - current Process : Process" << cpu->GetPID()+1 << endl;
			m_serviceTime++;
		}

		void setEndTime(int _endTime){
			m_endTime = _endTime;
		}

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
		void SetPID(int _pid) { m_pid = _pid; }

		/**
		 * @brief	Set Process State.
		 * @pre	    None.
		 * @post	Process State is set.
		 * @param	_state	Process State
		 */
		void SetState(int _state) { m_state = _state; }

		/**
		 * @brief	Set Process record.
		 * @pre	    None.
		 * @post	Process record is set.
		 * @param	_pid		Process ID(PID).
		 * @param	_state		Process name.
		 */
		void SetRecord(int _pid, int _arrivalTime, int _burstTime){

			m_pid= _pid;
			m_arrivalTime = _arrivalTime;
			m_burstTime = _burstTime;
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
