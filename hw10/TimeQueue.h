#ifndef __TIMEQ_H_
#define __TIMEQ_H_
//You can change/add to these #includes
#include <ctime>
#include <iostream>
#include <vector>
#include <cassert>

typedef int tq_hook; //Used to point to a location in the heap, fill in the "???"
//Forward declaration of Job class, do not remove this line, do not change.
class Job;
//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);
class TimeQueue{

private:
  std::vector<Job*> m_heap;
  // swapping elements up the heap to parents
  void percolate_up(int index);
  void percolate_down(int index);

public:
  TimeQueue() {}
  const Job* top() const;
  void push(Job*& entry );//adds job to queue
  Job* pop();//removes first job in queue
  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }
  //  A utility to print the contents of the heap.
  void printHeap(std::ostream & ostr );  
  void remove_from_index(int time_hook);//remove job from a specific index in queue
};


#endif
