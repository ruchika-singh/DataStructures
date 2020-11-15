#include <iostream>
#include <vector>
#include "TimeQueue.h"
#include "Job.h"


//this function return the first thing in the queue
const Job* TimeQueue::top() const 
{
  assert( !m_heap.empty() );//makes sure the queue is not empty
  return m_heap[0]; 
}

//removes something from the queue at a specific index
void TimeQueue::remove_from_index(int index){
  //if the index is at the end of the queue just pop the last 
  //one 
  if(index == m_heap.size()-1){
    m_heap.pop_back();
  }
  else{
    //set the job at the back to replace the one you want to remove
    m_heap[index] = m_heap.back();
    m_heap.pop_back();//get rid of the extra job on the tail end
    //for everything in the queue after the removal, have to update their hooks
    for(int i = index+1; i < m_heap.size(); i++){
      m_heap[i]->time_hook = m_heap[i]->time_hook - 1;
    }
    //reset the hook to match its correct position in queue
    m_heap[index]->time_hook = index;
    //percolate down from the index that was changed to get it in the right order
    percolate_down(index);
    
  }
}

//function that adds a job to the back of the queue and puts it in the correct order
void TimeQueue::push(Job*& entry )
{
  //sets the pointer to point to the current queue
  entry->time_ptr = this;
  m_heap.push_back(entry);
  //set the hook to the correct position
  entry->time_hook = m_heap.size()-1;
  percolate_up(m_heap.size()-1);//percolate up from the job that was just added
}

//function that pops the first thing in the queue
Job* TimeQueue::pop() 
{
  assert( !m_heap.empty() );//checks if it is empty
  //have a temp value to hold the first thing in the queue
  Job* temp = m_heap[0]; 
  m_heap[0] = m_heap.back();//replace the first job with the last one
  //removes the job that was at m_heap[0]
  m_heap.pop_back();
  m_heap[0]->time_hook = 0;//reset hook
  percolate_down(0); 
  return temp;//return the job that was removed
}

//function that prints the Time queue 
void TimeQueue::printHeap( std::ostream & ostr )
{
	ostr << "TQ " << m_heap.size() << " jobs:" << std::endl;
	for ( unsigned int i=0; i<m_heap.size(); ++i )
  		ostr << "\t" << m_heap[i];
}


//function that finds the correct spot for the job passed in at index
void TimeQueue::percolate_up(int index){
    //checks validity
    if (index < 0 || index >= m_heap.size() || m_heap.size() == 1)
        return; 
    int parent = (index - 1) / 2; //finds the parent
    //go through queue
    while (parent >= 0) {
      //compares time of parent and index jobs
      if (m_heap[parent]->getTime() > m_heap[index]->getTime()) {
        //swaps the parent and index jobs if parent has a greater time than index
        Job* temp = m_heap[parent];
        int temphook = m_heap[parent]->time_hook;
        m_heap[parent] = m_heap[index];
        m_heap[index] = temp; 
        //resassign the hooks
        m_heap[parent]->time_hook = temphook;
        m_heap[index]->time_hook = m_heap[parent]->time_hook;
        index = parent;
        parent = (index - 1) / 2; 
      }
      else 
        break; 
    }
}

//function that goes down through queue from the index and finds the right
//spot for the job at the index passed in 
void TimeQueue::percolate_down(int index){
  //checks validity
    if (index < 0 || index >= m_heap.size() || m_heap.size() == 1)
        return;
    int left = (2 * index) + 1;
    int size = m_heap.size();
    int child;
    while (left < size) {
      int right = (2 * index) + 2;
      //checks if the right is greater in time than the left
      if (right < size && m_heap[right]->getTime() < m_heap[left]->getTime())
          child = right;//sets child for comparison
      else 
          child = left; 
        //compares the time of the index and child
      if (m_heap[index]->getTime() >= m_heap[child]->getTime()) {
        //swaps the index and child if index has a greater time
        Job* temp = m_heap[index]; 
        int temphook = m_heap[index]->time_hook;
        m_heap[index] = m_heap[child]; 
        m_heap[child] = temp;
        //reassigns the hooks after the swap
        m_heap[index]->time_hook = temphook;
        m_heap[child]->time_hook = m_heap[index]->time_hook;
        index = child; 
        left = (2*index)+1; 
      }
      else 
        break; 
    }
}
