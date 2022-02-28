#include "bufferlist.cpp"
#include <ctime>

class Tester{                                                                                       
    public:
  bool testBufferCopyConstructor(const Buffer& buffer);
  bool BufferEnqueueDequeue(Buffer& buffer, int dataCount);
  bool BufEnqueueFullDequeueEmpty(int size, bool fullTest);
  bool testBufferlistCopyConstructor(const BufferList& bufferlist);
  bool BufferListEnqueueDequeue(BufferList& bufferList, int dataCount);
  bool BufferAssignmentOperator(int size);
  bool BufferListDequeueEmpty();
  void BufListEnqueuePerformance(int numTrials, int N);
};

int main() {
    Tester tester;
    int bufferSize = 500;
    int minBufSize = 25;
    cout << "                      ***Testing Buffer Class***" << endl << endl;
    {
      Buffer buffer(bufferSize);
        //test deep copy, object with many members
      for(int i = 0; i < bufferSize; i++)
	buffer.enqueue(i);
      
        cout << "Test case, Copy Constructor: same members, same size, different pointers (deep copy):" << endl;
        if (tester.testBufferCopyConstructor(buffer)) cout << "Copy constructor passed!" << endl << endl;
	else cout << "Copy constructor failed!" << endl << endl;;
    }
    {
      Buffer buffer2(bufferSize);
      //test inserting and removing data in normal cases
      cout << "Test case, Normal Buffer Operations: Enqueue & Dequeue" << endl;
      if (tester.BufferEnqueueDequeue(buffer2, bufferSize)) cout << "Normal Operations passed!" << endl << endl;
      else cout << "Normal operations failed!" << endl << endl;
    }
    {
      Buffer buffer3(1);
      //Test enqueu & dequeue on buffer with size of 1
      cout << "Test case, Edge Case: Size 1 buffer" << endl;
      if(tester.BufferEnqueueDequeue(buffer3, 1)) cout << "Edge Case Passed!" << endl << endl;
      else cout << "Edge Case Failed!" << endl << endl;

    }
    {
      //Perform tests on full and empty buffers
      cout << "Test case, Adding to Full Buffer" << endl;
      if(tester.BufEnqueueFullDequeueEmpty(bufferSize, true)) cout << "Adding to Full Buffer Test passed!" << endl << endl;
      else cout << "Adding to Full Buffer Test failed!" << endl << endl;

      cout << "Test case, Removing from Empty Buffer" << endl;
      if(tester.BufEnqueueFullDequeueEmpty(bufferSize, false)) cout << "Removing from Empty Buffer Test passed!" << endl << endl;
      else cout	<< "Removing from Empty Buffer Test failed!" << endl << endl;
    }
    cout << "                      ***Testing Bufferlist Class***" << endl << endl;
    {
      //Test bufferlist copy constructor
      BufferList bufferList(minBufSize);

      for(int c = 0; c < minBufSize; c++)
	bufferList.enqueue(c);

      cout << "Test case, Copy Constructor, normal cases: same members, same size, different pointers (deep copy):" << endl;
      if (tester.testBufferlistCopyConstructor(bufferList)) cout << "Copy constructor passed!" << endl << endl;
      else cout << "Copy constructor failed!" << endl << endl;
     
    }
    {
      BufferList bufferList2(1);
      bufferList2.enqueue(60);
      cout << "Test case, Copy Constructor, edge cases: same members, same size, different pointers (deep copy):" << endl;
      if (tester.testBufferlistCopyConstructor(bufferList2)) cout << "Copy constructor passed!" << endl << endl;
      else cout << "Copy constructor failed!" << endl << endl;
    }
    {
      BufferList bufferList3(minBufSize*2);
      //test inserting and removing data in normal cases                                                                                                                  
      cout << "Test case, Normal BufferList Operations: Enqueue & Dequeue" << endl;
      if (tester.BufferListEnqueueDequeue(bufferList3, 500)) cout << "Normal Operations passed!" << endl << endl;
      else cout << "Normal operations failed!" << endl << endl;
    }
    {
      cout << "Test case, Assignment Operator" << endl;
      if (tester.BufferAssignmentOperator(5)) cout << "Assignment Operator passed!" << endl << endl;
      else cout << "Assignment Operator failed!" << endl << endl;
    }
    {
      cout << "Test case, Remove from Empty Buffer List" << endl;
      if (tester.BufferListDequeueEmpty()) cout << "Remove from Empty Buffer List passed!" << endl << endl;
      else cout << "Remove from Empty Buffer List failed!" << endl << endl;
    }
    {
        //Measuring the efficiency of insertion functionality 
        cout << "\nMeasuring the efficiency of insertion functionality:" << endl;
        int M = 5;//number of trials
        int N = 10000;//original input size      
        tester.BufListEnqueuePerformance(M, N);  
     }
    return 0;
}

bool Tester::testBufferCopyConstructor(const Buffer& buffer){

  Buffer copy(buffer);
int counter = 0;
int start = buffer.m_start;
    //the case of empty object                                                                                                                                                                      
if (buffer.m_capacity == 0 && copy.m_capacity == 0) return true;
    //the case that sizes are the same and the table pointers are not the same                                                                                              
 else{
   
   if (buffer.m_capacity == copy.m_capacity && buffer.m_buffer != copy.m_buffer){
     
      if(buffer.m_start == copy.m_start && buffer.m_end == copy.m_end && buffer.m_count == copy.m_count){
	while(counter < buffer.m_count){
                if (buffer.m_buffer[start] != copy.m_buffer[start])                                                                                     
                    return false;

		start = (start + 1) % buffer.m_capacity;
            counter++;
            }
      }
      else return false;
     }
   else return false;

 }
   
 return true;
 
}

bool Tester::BufferEnqueueDequeue(Buffer& buffer, int dataCount){

  for(int i = 0; i < dataCount; i++)
    buffer.enqueue(i);

  int removedData = 0;
  for(int c = 0; c < dataCount; c++){
        removedData = buffer.dequeue();

      if(removedData != c)
    return false;
  }

  return true;

}

bool Tester::BufferListEnqueueDequeue(BufferList& bufferList, int dataCount){

  for(int i = 0; i < dataCount; i++)
    bufferList.enqueue(i);

  int removedData = 0;
  for(int c = 0; c < dataCount; c++){
        removedData = bufferList.dequeue();

      if(removedData != c)
    return false;
  }

  return true;

}

bool Tester::BufEnqueueFullDequeueEmpty(int size, bool fullTest) {

  Buffer test(size);

  for(int i = 0; i < size; i++)
    test.enqueue(i);

  if(fullTest){

     try{
        //trying to insert in a full buffer
        test.enqueue(size+1);
    }
    catch(overflow_error &e){
        //the exception that we expect 
        return true;
    }
    catch(...){
        //any other exception, this case is not acceptable
        return false;
    }
    //no exception thrown, this case is not acceptable
    return false;
  }
  else {
    for(int i = 0; i < size; i++)
      test.dequeue();
    try{
        //trying to remove from empty buffer
      test.dequeue();
    }
    catch(underflow_error &e){
	//the exception that we expect 
	return true;
    }
    catch(...){
	//any other exception, this case is not acceptable                          
	return false;
    }
    //no exception thrown, this case is not acceptable                           
    return false;
  }

}

bool Tester::testBufferlistCopyConstructor(const BufferList& bufferlist){
   BufferList copy(bufferlist);
  
  if(bufferlist.m_minBufCapacity == 0 && copy.m_minBufCapacity == 0)
    return true;
  else {
    if(bufferlist.m_listSize == copy.m_listSize && copy.m_minBufCapacity == bufferlist.m_minBufCapacity) {
      if(bufferlist.m_cursor == copy.m_cursor)
	return false;
      else {
	Buffer* temp = bufferlist.m_cursor;
	Buffer* temp2 = copy.m_cursor;
	int index = 0;

	while(bufferlist.m_listSize > index){
	  if(!testBufferCopyConstructor(*temp) ||
	        temp == temp2)
      	    return false;
	  temp = temp -> m_next;
	    temp2 = temp2 -> m_next;
	  index++;
	}
      }

    }
    else return false;
  }
    return true;

  }

bool Tester::BufferAssignmentOperator(int size){
  BufferList bufferlist(size);

  for(int i = 0; i < size*3; i++)
    bufferlist.enqueue(i);

  BufferList copy = bufferlist;

  for(int i = 0; i < size*3; i++)
    bufferlist.dequeue();
  
  for(int c = 0; c < size*3; c++){
    if(c != copy.dequeue())
      return false;                                                                                                                    
  }

  return true;

}

bool Tester::BufferListDequeueEmpty() {

  BufferList bufferlist(1);

  bufferlist.enqueue(3);
  bufferlist.dequeue();

  try{
        //trying to remove from empty buffer list 
      bufferlist.dequeue();
    }
    catch(underflow_error &e){
        //the exception that we expect
        return true;
    }
    catch(...){
        //any other exception, this case is not acceptable       
        return false;
    }
    //no exception thrown, this case is not acceptable
    return false;
  
}

void Tester::BufListEnqueuePerformance(int numTrials, int N){

 const int a = 2;//scaling factor for input size                                                                                                                       
    double T = 0.0;//to store running times                                                 
    clock_t start, stop;//stores the clock ticks while running the program    
    for (int k=0;k<numTrials-1;k++)
    {
      BufferList bufferList(N/5);
        start = clock();
        for(int i=0; i<N; i++)
	  bufferList.enqueue(i);//the algorithm to be analyzed for efficiency
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took                                      
        cout << "Inserting " << N * N << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
        N = N * a;//increase the input size by the scaling factor                                                                             
    }

}
