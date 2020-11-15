#include <iostream>
#include <vector>
#include "UrgentQueue.h"
#include "Job.h"

UrgentQueue::UrgentQueue(std::vector<Job*> const& values)
{
	this->m_heap = values;
	int n = this->m_heap.size();
	for(int c = (n-1)/2; c >= 0; c--){
	  percolate_down(c);
	}
}

const Job* UrgentQueue::top() const 
{
	assert( !m_heap.empty() );
	return m_heap[0]; 
}

void UrgentQueue::remove_from_index(int urgent_hook){
	if(urgent_hook == m_heap.size()-1){
		m_heap.pop_back();
	}
	else{
		m_heap[urgent_hook] = m_heap.back();
		m_heap.pop_back();
		m_heap[urgent_hook]->urgent_hook = urgent_hook;
		percolate_down(urgent_hook);
		
		
		for(int i = urgent_hook+1; i < m_heap.size(); i++){
			m_heap[i]->urgent_hook = m_heap[i]->urgent_hook-1;
		}
	}
	// m_heap.pop_back();
	// m_heap[urgent_hook]->urgent_hook = urgent_hook;
}

void UrgentQueue::push(Job*& entry )
  {
  	entry->priority_ptr = this;
    m_heap.push_back(entry);
    percolate_up(m_heap.size()-1);
    entry->urgent_hook = m_heap.size()-1; 
  }

Job* UrgentQueue::pop() 
{
	assert( !m_heap.empty() );
	m_heap[0] = m_heap.back();
	Job* temp = m_heap[0]; 
	m_heap.pop_back(); 
	percolate_down(0); 
	return temp;
}

bool UrgentQueue::check_heap( const std::vector<Job*>& heap )
	{
	int size = heap.size(); 
	int left, right; 
	if (size <= 1)
	  return true; 
	for (int c = 0; c < size; c++) {
	  left = (2*c)+1; 
	  right = left+1; 
	  //value must be less than or equal to value of both children 
	  if ((left < size && heap[c] >= heap[left]) || 
	    (right < size && heap[c] >= heap[right]))
	      return false; 
	}
	return true;
}

void UrgentQueue::printHeap( std::ostream & ostr )
{
	ostr << "UQ " << m_heap.size() << " jobs:" <<std::endl;
	for ( unsigned int i=0; i<m_heap.size(); ++i )
  		ostr << "\t" << m_heap[i];
  	if(m_heap.size() > 0){
  		ostr << std::endl;
  	}
}

void UrgentQueue::percolate_up(int index){
    if (index < 0 || index >= m_heap.size() || m_heap.size() == 1)
        return; 
    int parent = (index - 1) / 2; 
    while (parent >= 0) {
      if (m_heap[parent]->getPriority() < m_heap[index]->getPriority()) {
          Job* temp = m_heap[parent];
          m_heap[parent] = m_heap[index];
          m_heap[index] = temp; 
          //resassign the hooks
          m_heap[parent]->urgent_hook = m_heap[index]->urgent_hook;
          m_heap[index]->urgent_hook = temp->urgent_hook;
          index = parent;
          parent = (index - 1) / 2; 
      }
      else 
        break; 
    }
}

void UrgentQueue::percolate_down(int index){
    if (index < 0 || index >= m_heap.size() || m_heap.size() == 1)
        return;
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;
    int size = m_heap.size();
    int child; 
    while (left < size) {
      if (right < size && m_heap[right]->getPriority() > m_heap[left]->getPriority())
          child = right;
      else 
          child = left; 
      if (m_heap[index]->getPriority() <= m_heap[child]->getPriority()) {
        Job* temp = m_heap[index]; 
        m_heap[index] = m_heap[child]; 
        m_heap[child] = temp;
        m_heap[index]->urgent_hook = m_heap[child]->urgent_hook;
        m_heap[child]->urgent_hook = temp->urgent_hook;
        index = child; 
        left = (2*index)+1; 
        right = left+1; 
      }
      else 
        break; 
    }
}