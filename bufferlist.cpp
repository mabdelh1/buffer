#include "bufferlist.h"
#include "buffer.cpp"
    // **************************************
    // Implement the alternative constructor
    // **************************************
BufferList::BufferList(int minBufCapacity){

  //if stataement toguard against negative size  
  if(minBufCapacity < 1)
    m_minBufCapacity = DEFAULT_MIN_CAPACITY;
  else
    m_minBufCapacity = minBufCapacity;

  //create first buffer and assign the cursor to it
  Buffer*  firstBuffer = new Buffer(m_minBufCapacity);
  m_cursor = firstBuffer;
  m_cursor->m_next = firstBuffer;
  m_listSize = 1;
  
}
BufferList::~BufferList(){
    clear();
}

    // *****************************
    // Implement clear() function
    // *****************************
void BufferList::clear(){

  //Deallocate all memory
  Buffer* temp = m_cursor;
  int index = 0;

  while(m_listSize > index){
    m_cursor = temp;
    temp = temp -> m_next;
    m_cursor->clear();
    delete m_cursor;
    index++;
  }

  m_cursor = nullptr;
  
}


    // ****************************************************************************
    // Implement enqueue(...) function
    // we always insert at the back, that would be the cursor
    // if the current cursor is full we create a new node as cursor then we insert
    // ****************************************************************************
void BufferList::enqueue(const int& data) {

   Buffer* temp = m_cursor;
   
  try{
    temp->enqueue(data);
  }catch(const overflow_error& e) {
    if(temp->capacity() < (MAX_FACTOR * m_minBufCapacity)) {
      Buffer *anotherBuffer = new Buffer(temp->capacity() * INCREASE_FACTOR);
      anotherBuffer->m_next =  temp->m_next;
      temp->m_next = anotherBuffer;
      temp = temp->m_next;
      temp->enqueue(data);
      m_listSize = m_listSize + 1;
      m_cursor = temp; //added
	}
    else
      cout << "Max factor reached" << endl;
  }


}

    // *****************************
    // Implement dequeue() function
    // *****************************
int BufferList::dequeue() {

  int removedValue = -1;
  Buffer* temp = m_cursor->m_next;

  do{
    try{ //Attempt to dequeue, if performed succsessfully ignore catch
    removedValue = temp->dequeue();
    } catch(const underflow_error& e) { 
    if(m_cursor->m_next == m_cursor){
      throw underflow_error("This is the last node and its array is empty");
      return removedValue;
    }
    else {
    m_cursor->m_next = temp->m_next;
    temp->clear();
    delete temp;
    m_listSize = m_listSize - 1;
    temp = m_cursor->m_next;
  }
  }
  } while(removedValue == -1);


  return removedValue;
  
}


    // *******************************
    // Implement the copy constructor
    // *******************************
BufferList::BufferList(const BufferList & rhs){

  //clone rhs data
  m_listSize = rhs.m_listSize;
  m_minBufCapacity = rhs.m_minBufCapacity;
  
  if(m_minBufCapacity < 1)
    m_minBufCapacity = DEFAULT_MIN_CAPACITY;

Buffer *firstBuffer = new Buffer(*rhs.m_cursor);

  m_cursor = firstBuffer;
  m_cursor->m_next = firstBuffer;
  
  int index = 0;
  Buffer *temp = m_cursor;
  Buffer *tempCopy = rhs.m_cursor->m_next;
  
  while(index < m_listSize-1){
    Buffer* newBuffer = new Buffer(*tempCopy);
    temp->m_next = newBuffer;
    temp = temp->m_next;
    tempCopy = tempCopy->m_next;
    index++;    
  }

  temp->m_next = m_cursor;
 
}

    // ******************************
    // Implement assignment operator
    // ******************************
const BufferList & BufferList::operator=(const BufferList & rhs){

  //if statement to guard against self assignament
  if(this != &rhs)
    {
      clear(); //deallocate memory

      //clone data
  m_listSize = rhs.m_listSize;
  m_minBufCapacity = rhs.m_minBufCapacity;

  if(m_minBufCapacity < 1)
    m_minBufCapacity = DEFAULT_MIN_CAPACITY;

  Buffer *firstBuffer = new Buffer(*rhs.m_cursor);

  m_cursor = firstBuffer;
  m_cursor->m_next = firstBuffer;

  int index = 0;
  Buffer *temp = m_cursor;
  Buffer *tempCopy = rhs.m_cursor->m_next;

  while(index < m_listSize-1){
      Buffer* newBuffer = new Buffer(*tempCopy);
      temp->m_next = newBuffer;
    temp = temp->m_next;
    tempCopy = tempCopy->m_next;
    index++;
  }

  temp->m_next = m_cursor;
    }
      
 
  return *this;
}

void BufferList::dump(){
    Buffer* temp = m_cursor->m_next;
    for(int i=0;i<m_listSize;i++){
        temp->dump();
        temp = temp->m_next;
        cout << endl;
    }
    cout << endl;
}
