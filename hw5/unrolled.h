#ifndef dslist_h_
#define dslist_h_
// A simplified implementation of the STL list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.
#include <cassert>
#include <iostream>
const int NUM_ELEMENTS_PER_NODE = 6;
// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
  Node() : num_elements(0),next_(NULL), prev_(NULL) {}
  Node(const T& v) : num_elements(1), next_(NULL), prev_(NULL) {elements[0] = v;}

  // REPRESENTATION
  T elements[NUM_ELEMENTS_PER_NODE]; //array of elements in each node
  Node<T>* next_;
  Node<T>* prev_;
  int num_elements;//holds number of elements in each array
};

// A "forward declaration" of this class is needed
template <class T> class UnrolledLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  list_iterator(Node<T>* p=NULL) : ptr_(p), offset(0) {}
  // NOTE: the implicit compiler definitions of the copy constructor,
  // assignment operator, and destructor are correct for this class
  // dereferencing operator gives access to the value at the pointer
  T& operator*()  { return ptr_->elements[offset];  }
  // increment & decrement operators
  list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
    if(offset != ptr_->num_elements-1){
      offset++;//goes through all elements in array
    }
    else{
      ptr_ = ptr_->next_;//pointer moved to next node
      offset = 0;
    }
    return *this;
  }
  list_iterator<T> operator++(int) { // post-increment, e.g., iter++
    list_iterator<T> temp(*this);
    if(offset != ptr_->num_elements-1){
      offset++;
    }
    else{
      ptr_ = ptr_->next_;
      offset = 0;
    }
    return temp;
  }
  list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
    if(offset < 0){
      ptr_ = ptr_->prev_;//pointer moved to previous node
      offset = NUM_ELEMENTS_PER_NODE;
    }
    else{
      offset--;//goes backwards through array
    }
    return *this;
  }
  list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
    list_iterator<T> temp(*this);
    if(offset < 0){
      ptr_ = ptr_->prev_;
      offset = NUM_ELEMENTS_PER_NODE;
    } 
    else{
      offset--;
    }
    return temp;
  }
  // the dslist class needs access to the private ptr_ member variable
  friend class UnrolledLL<T>;
  // Comparions operators are straightforward
  //also added offset comparisons
  bool operator==(const list_iterator<T>& r) const {
    return ptr_ == r.ptr_ || offset == r.offset; }
  bool operator!=(const list_iterator<T>& r) const {
    return ptr_ != r.ptr_ || offset != r.offset;}

private:
  // REPRESENTATION
  Node<T>* ptr_;    // ptr to node in the list
  int offset; //element in Node array
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class UnrolledLL {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}
  UnrolledLL(const UnrolledLL<T>& old) { copy_list(old); }
  UnrolledLL& operator= (const UnrolledLL<T>& old);
  ~UnrolledLL() { destroy_list(); }

  typedef list_iterator<T> iterator;

  // simple accessors & modifiers
  unsigned int size();
  bool empty() const { return head_ == NULL; }
  void clear() { destroy_list(); }

  // read/write access to contents
   const T& front() const { return head_->elements[0];  }
   T& front() { return head_->elements[0]; }
   const T& back() const { return tail_->elements[tail_->num_elements-1]; }
   T& back() { return tail_->elements[tail_->num_elements -1]; }

  // modify the linked list structure
  void push_front(const T& e);
  void pop_front();
  void push_back(const T& e);
  void pop_back();

  iterator erase(iterator itr);
  iterator insert(iterator itr, const T& e);
  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(NULL); }
  void print(std::ostream& output);

private:
  // private helper functions
  void copy_list(const UnrolledLL<T>& old);
  void destroy_list();

  //REPRESENTATION
  Node<T>* head_;
  Node<T>* tail_;
  unsigned int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
  // check for self-assignment
  if (&old != this) {
    destroy_list();
    copy_list(old);
  }
  return *this;
}
template <class T>
//includes all elements in each node 
unsigned int UnrolledLL<T>::size() {
  Node<T>* temp;
  temp = head_;
  int size = 0;
  while(temp != NULL){
    size += temp->num_elements;
    temp = temp->next_;
  }
  return size; 
}
//function that puts a new number in the front of the list
//unless its full, then it creates a new node with the new 
//value
template <class T>
void UnrolledLL<T>::push_front(const T& v) {
  //if the node is not full
  if(head_->num_elements != NUM_ELEMENTS_PER_NODE){
    for(int i = head_->num_elements - 1; i >= 0; i--)
      head_->elements[i+1] = head_->elements[i];//pushes all nums back
    head_->elements[0] = v;//adds new val to front
    head_->num_elements++;//increases size of array
  }
  //if the node is full
  else{
    //creates a new node
    Node<T>* newp = new Node<T>(v);
    // special case: initially empty list
    if (!tail_) {
      head_ = tail_ = newp;
    } 
    else{
      head_->prev_ = newp;
      newp->next_ = head_;
      newp->prev_ = NULL;
      head_ = newp;
    }
    ++size_;//increase size of list
  }
}
//function deletes the first value in the front of the list
//and if its the only one in the array, the whole node is deleted
template <class T> void UnrolledLL<T>::pop_front() {
  //if the array has more than one values
  if(head_->num_elements > 1){
    for(int i = 0; i < head_->num_elements-1; i++)
      head_->elements[i] = head_->elements[i+1];//pushes them forward
    head_->num_elements--;
  }
  //if there is only one thing in the list, delete whole list
  else if(head_== tail_ && head_->num_elements==1){
    delete head_;
    head_ = NULL;
    tail_ = NULL;
  }
  //if the array has one value, delete the node
  else if(head_->num_elements == 1){
    Node<T>* temp;
    temp = head_->next_;
    delete head_;
    //change where the head is pointing 
    head_ = temp;
    head_->prev_ = NULL;
  }
  else{
    std::cerr<<"List is not long enough to pop_front"<<std::endl;
  }
  --size_;//decreases size of list
}
//function adds a value to the end of the list and if the node is 
//full adds a new node with val
template <class T>
void UnrolledLL<T>::push_back(const T& v) {
  //if array has space at end
  if (tail_ && tail_->num_elements < NUM_ELEMENTS_PER_NODE){
    tail_->elements[tail_->num_elements] = v;
    tail_->num_elements++;
  }
  //if array is full: makes new Node
  else{
    Node<T>* newp = new Node<T>(v);
    // special case: initially empty list
    if (!tail_) {
      head_ = tail_ = newp;
    } else {
      //changes tail to point to new node
      newp->prev_ = tail_;
      tail_->next_ = newp;
      tail_ = newp;
      tail_->elements[0] = v;
    }
    ++size_;
  }
}
//function deletes the last element in the last node, but if 
//its the last one in the array deletes the last node
template <class T>
void UnrolledLL<T>::pop_back() {
  //if the tail has more than one element 
  if(tail_ && tail_->num_elements != 1){
    tail_->elements[tail_->num_elements] = 0;
    tail_->num_elements--;
  }
  //if there is one thing in the list, delete it
  else if(head_== tail_ && size_ == 1){
    delete head_;
    head_ = NULL;
    tail_ = NULL;
  }
  //node is deleted and tail ptr is moved
  else{
    Node<T>* temp;
    temp = tail_->prev_;
    delete tail_;
    tail_ = temp;
    tail_->next_ = NULL;
  }
  --size_;
}
//function prints out each node is the list with its 
//elements in the array
template <class T>
void UnrolledLL<T>::print(std::ostream& output) {
  output<<"UnrolledLL, size: "<<size()<<"\n";
  Node<T>* temp;
  temp = head_;
  while(temp != NULL){
    output<< "node: [" << temp->num_elements << "]";
    //walk through the list 
    for(int i = 0; i < temp->num_elements; i++ ){
      output<< " " << temp->elements[i];
    }
    temp = temp->next_;
    output<<"\n";
  }
}
// do these lists look the same (length & contents)?
template <class T>
bool operator== (UnrolledLL<T>& left, UnrolledLL<T>& right) {
  if (left.size() != right.size()) return false;
  typename UnrolledLL<T>::iterator left_itr = left.begin();
  typename UnrolledLL<T>::iterator right_itr = right.begin();
  // walk over both lists, looking for a mismatched value
  while (left_itr != left.end()) {
    if (*left_itr != *right_itr) return false;
    left_itr++; right_itr++;
  }
  return true;
}
// do these lists look the different(length & contents)?
template <class T>
bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right){ return !(left==right); }
template <class T>
//erases the value that the iterator points to in the list
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
  assert (size_ > 0);
  --size_;
  itr.ptr_-> num_elements--;//decreases number of elements 
  if(itr.ptr_->num_elements <1){
     iterator result(itr.ptr_->next_);
    // One node left in the list.
    if (itr.ptr_ == head_ && head_ == tail_) {
      head_ = tail_ = 0;
    }
    // Removing the head in a list with at least two nodes
    else if (itr.ptr_ == head_) {
      head_ = head_->next_;
      head_->prev_ = 0;
    }
    // Removing the tail in a list with at least two nodes
    else if (itr.ptr_ == tail_) {
      tail_ = tail_->prev_;
      tail_->next_ = 0;
    }
    // Normal remove
    else {
      itr.ptr_->prev_->next_ = itr.ptr_->next_;
      itr.ptr_->next_->prev_ = itr.ptr_->prev_;
    }
    delete itr.ptr_;
    return result;
  }
  //if there are multiple elements, can just be deleted
  else{
    //if the element to be deleted is the last one in the array
    if(itr.ptr_->num_elements <= itr.offset){
      itr.offset = itr.ptr_ -> num_elements-1;
    }
    else{
      for(int i = itr.offset; i < itr.ptr_->num_elements; i++){
        itr.ptr_->elements[i] = itr.ptr_->elements[i+1];
      }
    }
    return itr;
  }
}
//function inserts a value where the itr is pointing in the list 
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {
  ++size_ ;
  //if there is space in the array for it to be added
  if(itr.ptr_->num_elements != NUM_ELEMENTS_PER_NODE){
    for(int i = itr.ptr_->num_elements - 1; i >= itr.offset; i--){
      itr.ptr_->elements[i+1] = itr.ptr_->elements[i];//moves everything over
    }
    itr.ptr_->elements[itr.offset] = v;//inserts value
    itr.ptr_->num_elements++;
    return iterator(itr);
  } 
  //if the array in the node is full, split it where it is pointing
  else { 
    itr.ptr_->num_elements++;
    Node<T>* newp = new Node<T>();
    //how many vals have to be put in new node
    int end = NUM_ELEMENTS_PER_NODE - itr.offset;
    //adds new values to new node
    for(int j = 0; j < end; j++){
      itr.ptr_->num_elements--;
      newp->elements[j] = itr.ptr_->elements[j+itr.offset];
      newp->num_elements++;
    }
    //adds the value to where itr is pointing
    *itr = v;
    //readjust pointers
    Node<T>* temp = itr.ptr_->next_;
    itr.ptr_->next_ = newp;
    newp->prev_ = itr.ptr_;
    newp->next_ = temp;
    newp->prev_->next_ = newp;
    return iterator(newp);
  }
}
//copies a list
template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old) {
  size_ = old.size_;
  // Handle the special case of an empty list.
  if (size_ == 0) {
    head_ = tail_ = 0;
    return;
  }
  // Create a new head node.
  head_ = new Node<T>(old.head_->elements[NUM_ELEMENTS_PER_NODE]);
  // tail_ will point to the last node created and therefore will move
  // down the new list as it is built
  tail_ = head_;
  // old_p will point to the next node to be copied in the old list
  Node<T>* old_p = old.head_->next_;
  // copy the remainder of the old list, one node at a time
  while (old_p) {
    tail_->next_ = new Node<T>(old_p->value_);
    tail_->next_->prev_ = tail_;
    tail_ = tail_->next_;
    old_p = old_p->next_;
  }
}
//deletes the entire list AKA all nodes in list
template <class T>
void UnrolledLL<T>::destroy_list() {
  Node<T>* curr;
  curr = head_;
  while(curr != NULL){
    Node<T>* temp;
    temp = curr->next_;
    delete curr;
    curr = temp;
    size_--;
  }
  head_ = tail_ = NULL;
}

#endif