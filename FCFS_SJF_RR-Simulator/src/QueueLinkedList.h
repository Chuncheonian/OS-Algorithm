#pragma once
#include <iostream>
using namespace std;

/**
 * Structure for NodeType to use in Linked structure.
 */
template <typename T>
struct NodeType {
	T			data;		// A data for each node.
	NodeType*	next;		// A node pointer to point succeed node.
};

/**
 * Queue_Linked_List Class.
 */
template <typename T>
class QueueLinkedList {
private:
	NodeType<T>*	m_pFront;		// Pointer for pointing a first node.
	NodeType<T>*	m_pRear;		// Pointer for pointing a last node.
	NodeType<T>*	m_pCurPointer;	// Node pointer for pointing current node to use iteration.
	int				m_nLength;		// Number of node in the list.

public:
	/**
	 * default constructor.
	 */
	QueueLinkedList();     

	/**
	 * destructor.
	 */
	~QueueLinkedList();   
	
	/**
	 * @brief	Initialize list to empty state.
	 * @pre		None.
	 * @post	List is empty.
	 */
	void MakeEmpty();

	bool isEmpty();

	/**
	 * @brief	Get number of elements in the list.
	 * @pre		None.
	 * @post	Function value = number of elements in list.
	 * @return	Number of elements in this list.
	 */
	int GetLength() const;

	/**
	 * @brief	Add item into appropriate spot of this list.
	 * @pre		List is not full. item is not in list. 
	 * @post	Item is inserted in this list.
	 * @return	1 if this function works well, otherwise 0.
	 */
	int EnQue(T& _item);

	/**
	 * @brief	Delete item from this list.
	 * @pre		List is not empty. the item exists in list.
	 * @post	Item is deleted from this list.
	 * @return	1 if this function works well, otherwise 0.
	 */
	int DeQue();

	/**
	 * @brief   Delete existing a record.
	 * @pre     template T should be initialized.
	 * @post    Delete the record into the queue and m_nLength--.
	 * @param   item    The record to want to delete.
	 * @return  return 1 if the item to be deleted is in the queue,
	 *          oterwise return 0.
	 */
	int Delete(T _item);
	
	/**
	 * @brief	Change value of item which is in this list.
	 * @pre		List is not empty. the item exists in list.
	 * @post	Item's value is changed.
	 * @return	1 if this function works well, otherwise 0.
	 */
	int Replace(T& _item);

	/**
	 * @brief	Retrieve list element whose key matches item's key (if present).
	 * @pre		Key member of item is initialized.
	 * @post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	 * @return	1 if any element's primary key matches with item's, otherwise 0.
	 */
	int Get(T& _item);

	/**
	 * @brief	Initialize current pointer for an iteration through the list.
	 * @pre		None.
	 * @post	Current pointer is prior to list. current pointer has been initialized.
	 */
	void ResetList();

	/**
	 * @brief	Get the next element in list.
	 * @pre		Current pointer is defined. Element at current pointer is not last in list.
	 * @post	Current pointer is updated to next position. item is a copy of element at current pointer.
	 */
	void GetNextItem(T& _item);

    void GetNextItem();

	// Operation Overloading.
	void operator= (QueueLinkedList& _item);
};


// Class constructor
template <typename T>
QueueLinkedList<T>::QueueLinkedList() {
	m_nLength = 0;
	m_pFront = nullptr;
	m_pRear = nullptr;
	m_pCurPointer = nullptr;
}

// Class destructor
template <typename T>
QueueLinkedList<T>::~QueueLinkedList() {
	//리스트내의 모든 node 제거
	MakeEmpty();
}

// Initialize list to empty state.
template <typename T>
void QueueLinkedList<T>::MakeEmpty() {
// Post: List is empty; all items have been deallocated.
	// 리스트내의 모든 노드 제거 하고 리스트의 length를 초기화
	NodeType<T>* tempPtr = m_pFront;
	
	while (m_pFront != nullptr)	{
		tempPtr = m_pFront;
		m_pFront = m_pFront->next;
		delete tempPtr;
	}

	m_nLength = 0;
	m_pRear = nullptr;
}

template <typename T>
bool QueueLinkedList<T>::isEmpty(){
	if (m_nLength <= 0)
		return true;
	else
		return false;
}

// Get number of elements in the list.
template <typename T>
int QueueLinkedList<T>::GetLength() const {
	return m_nLength;
}

// Add item into this list.
template <typename T>
int QueueLinkedList<T>::EnQue(T& _item) {
	
	NodeType<T>* node = new NodeType<T>; // 리스트에 추가할 새로운 node 객체 선언

	// node 객체에 입력받은 데이터 설정 및 초기화
	node->data = _item;
	node->next = nullptr;

	// list 에 node 가 존재하지 않는 경우
	if (!m_nLength) {
		m_pFront = node;
		m_pRear = node;
	}

	// list 에 node 가 하나 이상 존재하는 경우
	else {
        ResetList();
        for (int i = 0; i < m_nLength; i++) {
            GetNextItem();
        }
        
        m_pCurPointer->next = node;
		m_pRear = node;
	}
	m_nLength++;

	return 1;
}

// Delete item from this list.
template <typename T>
int QueueLinkedList<T>::DeQue() {
	NodeType<T>* tempPtr = nullptr;	// 변수 선언

	tempPtr = m_pFront;
	
	m_pFront = m_pFront->next;

	delete tempPtr;
	m_nLength--;
	return 1;
}

// Delete item from this list.
template <typename T>
int QueueLinkedList<T>::Delete(T _item) {
	NodeType<T>* pre = nullptr;	// 변수 선언
	
	m_pCurPointer = m_pFront;
	
	//리스트의 끝까지 찾는다.
	while (m_pCurPointer != nullptr) {
		if (_item == m_pCurPointer->data) {
			// 처음 노드를 삭제할 경우
			if (pre == nullptr) {
				m_pFront = m_pCurPointer->next;
				delete m_pCurPointer;
				m_pCurPointer = m_pFront;
			}
			else { // 처음 이후의 노드를 삭제할 경우
				pre->next = m_pCurPointer->next;
				delete m_pCurPointer;
				m_pCurPointer = pre->next;

				// 지금 지운 것이 마지막 노드일 경우
				if (m_pCurPointer == nullptr) {
					m_pRear = pre;
				}
			}

			m_nLength--;
			// 제일 먼저 나오는 하나만 지움
			return true;
		}
		else {
			pre = m_pCurPointer;
			m_pCurPointer = m_pCurPointer->next;
		}
	}
	// 찾지 못했으므로 false를 리턴
	return false;
}


// Change value of item which is in this list.
template <typename T>
int QueueLinkedList<T>::Replace(T& _item) {
	bool moreToSearch, found;
	NodeType<T>* location;	// 변수 선언

	location = m_pFront;
	found = false;
	moreToSearch = (location != nullptr);	// 변수 초기화
	
	while (moreToSearch && !found) {	// 리스트의 끝이 아니면서 아직 찾지 않았으면 반복한다.
		if (_item == location->data) {
			found = true;
			location->data = _item;
		}	// 일치하는 항목을 찾았을 때 found의 값을 변경해주고 리스트의 항목에 item을 복사해준다.
		else {
			location = location->next;
			moreToSearch = (location != nullptr);
		}	// 찾지 못했을 때 다음 항목으로 location을 옮기고 그 값이 nullptr이면 리스트의 끝이므로 moreToSearch의 값을 변경해준다.
	}

	if(found)
		return 1;
	else
		return 0;	//수정에 성공하면 1, 그렇지 못하면 0을 리턴한다.
}

// Retrieve list element whose key matches item's key (if present).
template <typename T>
int QueueLinkedList<T>::Get(T& _item) {
	bool moreToSearch, found;
	NodeType<T>* location;	//변수 선언

	location = m_pFront;
	found = false;
	moreToSearch = (location != nullptr);	//변수 초기화
	
	while (moreToSearch && !found) {	//리스트의 끝이 아니면서 아직 찾지 않았으면 반복한다.
		if (_item == location->data) {
			found = true;
			_item = location->data;
		}	//일치하는 항목을 찾았을 때 found의 값을 변경해주고 item에 해당 항목을 복사해준다.
		else {
			location = location->next;
			moreToSearch = (location != nullptr);
		}	//찾지 못했을 때 다음 항목으로 location을 옮기고 그 값이 nullptr이면 리스트의 끝이므로 moreToSearch의 값을 변경해준다.
	}

	if(found)
		return 1;
	else
		return 0;	//찾으면 1, 그렇지 못하면 0을 리턴한다.
}

// Initializes current pointer for an iteration through the list.
template <typename T>
void QueueLinkedList<T>::ResetList() {
	// current pointer 초기화
	m_pCurPointer = nullptr;
}

// Gets the next element in list.
template <typename T>
void QueueLinkedList<T>::GetNextItem(T& _item) {
	// current pointer 이 nullptr이라면 처음 node를 가리킴.
	if (m_pCurPointer == nullptr)
		m_pCurPointer = m_pFront;
	
	//current position 을 다음 노드로 이동
	else
		m_pCurPointer = m_pCurPointer->next;

	//item 에 current position 의 info 를 삽입
	_item = m_pCurPointer->data;
}

// Gets the next element in list.
template <typename T>
void QueueLinkedList<T>::GetNextItem() {
	// current pointer 이 nullptr이라면 처음 node를 가리킴.
	if (m_pCurPointer == nullptr)
		m_pCurPointer = m_pFront;
	
	//current position 을 다음 노드로 이동
	else
		m_pCurPointer = m_pCurPointer->next;
}

// Operator Overloading.
template<typename T>
void QueueLinkedList<T>::operator=(QueueLinkedList& _item) {
    MakeEmpty();
    int len = _item.GetLength();
    _item.ResetList();

    for(int i = 0; i < len; i++) {
        T item;
        _item.GetNextItem(item);
        Add(item);
    }
}
