#include "buffer.h"

    // **************************************
    // Implement the alternative constructor
    // No need to set m_next to nullptr, 
    // it will be handled by linked list,
    // because it is used by linked list
    // **************************************
Buffer::Buffer(int capacity){

  //If-else statement to guard against negative size
  if(capacity < 0)
    m_capacity = 0;
  else {
  m_capacity = capacity;
  m_buffer = new int[m_capacity];
  }
  
  m_count = 0;
  m_start = 0;
  m_end = 0;
  m_next = nullptr;
  
}

    // ***********************************
    // Implement clear() function
    // No need to set m_next to nullptr, 
    // it will be handled by linked list,
    // because it is used by linked list
    // ***********************************
void Buffer::clear(){

  //deallocate array
    delete[] m_buffer;
  
  m_capacity = 0;
  m_count = 0;
  m_start = 0;
  m_end = 0;
  m_buffer = nullptr;

  
}

Buffer::~Buffer(){
    clear();
}

int Buffer::count(){return m_count;}

int Buffer::capacity(){return m_capacity;}

    // **************************
    // Implement full() function
    // **************************
bool Buffer::full(){
  
  bool isFull = false;

  //if amount of data is equal to capacity, array is full
  if(m_count == m_capacity)
    isFull = true;
  
  return isFull;
  
}

    // **************************
    // Implement empty() function
    // **************************
bool Buffer::empty(){

  bool isEmpty = false;

  if(m_count == 0){
    isEmpty = true;}

    return isEmpty;
}


    // ********************************
    // Implement enqueue(...) function
    // ********************************
void Buffer::enqueue(int data){

  //Only enquue if array is not full
  if(!full()){
    
    if(m_end == m_capacity)
      m_end = 0;
    
    m_buffer[m_end] = data;
    m_count = m_count + 1;
    m_end = m_end + 1;
  }
  else
    throw overflow_error("array is full");
  
  
}

    // *****************************
    // Implement dequeue() function
    // *****************************
int Buffer::dequeue(){

  //only dequeue if array is not empty
  if(!empty()) {
  int removedData = m_buffer[m_start];
  m_buffer[m_start] = 0;

  if(m_start == m_capacity-1)
    m_start = 0;
  else
    m_start = m_start + 1;

  
  m_count = m_count - 1;
  
  return removedData;
  }
  else
    throw underflow_error("array is empty");
  
}

    // *******************************
    // Implement the copy constructor
    // *******************************
Buffer::Buffer(const Buffer & rhs){

  m_capacity = rhs.m_capacity;

  if(m_capacity < 0)
    m_capacity = 0;
  else {
    //allocate memory if capacity is not 0
  m_buffer = new int[m_capacity];
  }
  //clone rhs data
  m_count = rhs.m_count;
  m_start = rhs.m_start;
  m_end = rhs.m_end;

  for(int i = 0; i < m_capacity; i++)
    m_buffer[i] = rhs.m_buffer[i];

  
}

    // ******************************
    // Implement assignment operator
    // ******************************
const Buffer & Buffer::operator=(const Buffer & rhs){

  //If statement to guard against self assignament
   if(this != &rhs)
    {

      delete [] m_buffer;
      
      m_capacity = rhs.m_capacity;

  if(m_capacity < 0)
    m_capacity = 0;
  else {
    //allocate array if capacity is not 0
  m_buffer = new int[m_capacity];
  }

  //clone rhs data
  m_count = rhs.m_count;
  m_start = rhs.m_start;
  m_end = rhs.m_end;

  for(int i = 0; i < m_capacity; i++)
    m_buffer[i] = rhs.m_buffer[i];
    }
  
    return *this;
}

void Buffer::dump(){
    int start = m_start;
    int end = m_end;
    int counter = 0;
    cout << "Buffer size: " << m_capacity << " : ";
    if (!empty()){
        while(counter < m_count){
            cout << m_buffer[start] << "[" << start << "]" << " ";
            start = (start + 1) % m_capacity;
            counter++;
        }
        cout << endl;
    }
    else cout << "Buffer is empty!" << endl;
}
