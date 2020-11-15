#ifndef __URGENTQ_H_
#define __URGENTQ_H_
//You can change/add to these #includes
#include <ctime>
#include <iostream>
#include <vector>
#include <cassert>

typedef int uq_hook; //Used to point to a location in the heap, fill in the "???"

//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class UrgentQueue{

private:
  std::vector<Job*> m_heap;
  // swapping elements up the heap to parents
  void percolate_up(int index);
  void percolate_down(int index);
public:
  UrgentQueue() {}
  const Job* top() const;
  void push(Job*& entry );//adds a job to queue
  Job* pop();//removes first thing from queue
  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }
  //  A utility to print the contents of the heap.
  void printHeap(std::ostream & ostr );  
  void remove_from_index(int urgent_hook);//removes job from a specific location in queue
};

#endif
