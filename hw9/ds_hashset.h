#ifndef ds_hashset_h_
#define ds_hashset_h_
// The set class as a hash table instead of a binary search tree.  The
// primary external difference between ds_set and ds_hashset is that
// the iterators do not step through the hashset in any meaningful
// order.  It is just the order imposed by the hash function.
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
//#include "Movie.h"


// The ds_hashset is templated over both the type of key and the type
// of the hash function, a function object.
template < class KeyType, class HashFunc >
class ds_hashset {
private:
  typedef typename std::list<KeyType>::iterator hash_list_itr;

public:
  // =================================================================
  // THE ITERATOR CLASS
  // Defined as a nested class and thus is not separately templated.

  class iterator {
  public:
    friend class ds_hashset;   // allows access to private variables
  private:
    
    // ITERATOR REPRESENTATION
    ds_hashset* m_hs;          
    int m_index;               // current index in the hash table
    hash_list_itr m_list_itr;  // current iterator at the current index

  private:
    // private constructors for use by the ds_hashset only
    iterator(ds_hashset * hs) : m_hs(hs), m_index(-1) {}
    iterator(ds_hashset* hs, int index, hash_list_itr loc)
      : m_hs(hs), m_index(index), m_list_itr(loc) {}

  public:
    // Ordinary constructors & assignment operator
    iterator() : m_hs(0), m_index(-1)  {}
    iterator(iterator const& itr)
      : m_hs(itr.m_hs), m_index(itr.m_index), m_list_itr(itr.m_list_itr) {}
    iterator&  operator=(const iterator& old) {
      m_hs = old.m_hs;
      m_index = old.m_index; 
      m_list_itr = old.m_list_itr;
      return *this;
    }

    // The dereference operator need only worry about the current
    // list iterator, and does not need to check the current index.
    KeyType& operator*() const { return *m_list_itr; }

    // The comparison operators must account for the list iterators
    // being unassigned at the end.
    friend bool operator== (const iterator& lft, const iterator& rgt)
    { return lft.m_hs == rgt.m_hs && lft.m_index == rgt.m_index && 
	(lft.m_index == -1 || lft.m_list_itr == rgt.m_list_itr); }
    friend bool operator!= (const iterator& lft, const iterator& rgt)
    { return lft.m_hs != rgt.m_hs || lft.m_index != rgt.m_index || 
	(lft.m_index != -1 && lft.m_list_itr != rgt.m_list_itr); }
    // increment and decrement
    iterator& operator++() { 
      this->next();
      return *this;
    }
    iterator operator++(int) {
      iterator temp(*this);
      this->next();
      return temp;
    }
    iterator & operator--() { 
      this->prev();
      return *this;
    }
    iterator operator--(int) {
      iterator temp(*this);
      this->prev();
      return temp;
    }

  private:
    // Find the next entry in the table
    void next() {
      ++ m_list_itr;  // next item in the list

      // If we are at the end of this list
      if (m_list_itr == m_hs->m_table[m_index].end()) {
        // Find the next non-empty list in the table
        for (++m_index; 
             m_index < int(m_hs->m_table.size()) && m_hs->m_table[m_index].empty();
             ++m_index) {}
        
        // If one is found, assign the m_list_itr to the start
        if (m_index != int(m_hs->m_table.size()))
          m_list_itr = m_hs->m_table[m_index].begin();
        
        // Otherwise, we are at the end
        else
          m_index = -1;
      }
    }

    // Find the previous entry in the table
    void prev() {
      // If we aren't at the start of the current list, just decrement
      // the list iterator
      if (m_list_itr != m_hs->m_table[m_index].begin())
	m_list_itr -- ;

      else {
        // Otherwise, back down the table until the previous
        // non-empty list in the table is found
        for (--m_index; m_index >= 0 && m_hs->m_table[m_index].empty(); --m_index) {}

        // Go to the last entry in the list.
        m_list_itr = m_hs->m_table[m_index].begin();
        hash_list_itr p = m_list_itr; ++p;
        for (; p != m_hs->m_table[m_index].end(); ++p, ++m_list_itr) {}
      }
    }
  };
  // end of ITERATOR CLASS
  // =================================================================
private:
  // =================================================================
  // HASH SET REPRESENTATION
  std::vector< std::list<KeyType> > m_table;  // actual table
  HashFunc m_hash;                            // hash function
  unsigned int m_size;                        // number of keys
  float occupancy;

public:
  // =================================================================
  // HASH SET IMPLEMENTATION
  
  // Constructor for the table accepts the size of the table.  Default
  // constructor for the hash function object is implicitly used.
  ds_hashset(unsigned int init_size = 100):m_table(init_size),m_size(0),occupancy(0){}
  
  // Copy constructor just uses the member function copy constructors.
  ds_hashset(const ds_hashset<KeyType, HashFunc>& old) 
    : m_table(old.m_table), m_size(old.m_size), occupancy(old.occupancy) {}

  ~ds_hashset() {}

  //set the occupanxy of the table
  void setOccupancy(float o){occupancy = o;}
  unsigned int size() const { return m_size; }

  //function takes in the key(movie) and returns a string of all the
  //values of the movie put together
  std::string getHashstring(KeyType& key){
    std::string hash_string = "";
    std::vector<std::string> g = key.getGenres();
    std::vector<std::string> id = key.getActors();
    std::vector<std::string> r = key.getRoles();
    hash_string += key.getTitle() + key.getYear() + key.getMin();
    //check if the vector is empty
    if(g.size() == 0){
      hash_string += "0";
    }
    else{
     for(int i = 0; i < g.size(); i++){
       hash_string += g[i];//adds each genre to the string
     }
    }
    if(id.size() == 0){
      hash_string += "0";
    }
    else{
      for(int i = 0; i < id.size(); i++){
        hash_string += id[i];//adds each id to the string
      }
    }
    if(r.size() == 0){
      hash_string += "0";
    }
    else{
      for(int i = 0; i < r.size(); i++){
        hash_string += r[i];//adds each role to the string
      }
    }
    return hash_string;
  }

  // Insert the key if it is not already there.
  bool insert(KeyType & key) {
    float curr_occupancy;
    //calculates the current occupancy of the table and compare it to 
    //max it can be till it has to be resized
    curr_occupancy = float(m_size)/float(m_table.size());
    if(curr_occupancy > occupancy)
        //call resize_table with new size
       this->resize_table(2*m_table.size()+1);
    //hash string is gotten from the key of movies
    std::string hash_string = getHashstring(key);
    //gets the hash value from the hash function
    unsigned int hash_value = m_hash(hash_string); 
    unsigned int index = hash_value % m_table.size();
    //checks if anything is at that index
    if(m_table[index].size() == 0){
      //adds movie to the table and increases size
      m_table[index].push_front(key);
      this->m_size++;
      return true;
    }
    //if the index is already in the table and key matches the key at the index
    else if(key == m_table[index].front()){
      //adds movie to end of the list at the index
      m_table[index].push_back(key);
      return true;
    }
    //index is already in table, but key doesn't match(linear probing)
    else{
      int i = 1;
      while (true){
        //changes index
        index = (index + i) % m_table.size();
        //if something is at the new index and matches key of movie
        if(m_table[index].size() != 0 && m_table[index].front() == key){
          m_table[index].push_front(key);//add to list
          return false;
        }
        //empty spot, adds movie to table
        else if(m_table[index].size() == 0){
          m_table[index].push_front(key);
          this->m_size++;//increases size
          return true;
        } 
      }
    }
  }

  // Find the key, using hash function, indexing and list find
  std::list<KeyType> find( KeyType& key) {
    //get the hashstring of the movie
    std::string hash_string = getHashstring(key);
    unsigned int hash_value = m_hash(hash_string);
    unsigned int index = hash_value % m_table.size();//finds index in table
    //if key matches key at index in table
    if(key == m_table[index].front()){
      //returns the list at the index of the table
      return m_table[index];
    }
    //doesn't match, linear probe
    else {
      int i = 1;
      while (true){
        index = (index + i) % m_table.size();//change index
        //check if the key matches and there is a list at index
        if(m_table[index].size() != 0 && m_table[index].front() == key){
          return m_table[index];
        }
        else if(m_table[index].size() == 0) 
          break;
      }
    } 
    //return an empty list is there was no match
    std::list<KeyType> empty;
    return empty;
  }
  
  // Erase the key 
  int erase(const KeyType& key) {
    // Find the key and use the erase iterator function.
    iterator p = find(key);
    if (p == end())
      return 0;
    else {
      erase(p);
      return 1;
    }
  }

  // Erase at the iterator
  void erase(iterator p) {
    m_table[ p.m_index ].erase(p.m_list_itr);
  }

  // Find the first entry in the table and create an associated iterator
  iterator begin() {
    int index = 0;
    for(int i = 0; i < m_table.size(); i++){
      if(m_table[i].size() > 0){
        index = i;
        break;
      }
    }
    return iterator(this, 0, m_table[index].begin());
  }

  // Create an end iterator.
  iterator end() {
    iterator p(this);
    p.m_index = -1;
    return p;
  }
  
  //A public print utility.
  void print(std::ostream & ostr) {
    for (unsigned int i=0; i<m_table.size(); ++i) {
      ostr << i << ": ";
      for (hash_list_itr p = m_table[i].begin(); p != m_table[i].end(); ++p)
        ostr << ' ' << getHashstring(*p);
      ostr << std::endl;
    }
  }

private:
  // resize the table with the same values 
  void resize_table(unsigned int new_size) {
    // create a new vector
    std::vector<KeyType> movies;
    m_size = 0;//resets the size
    //goes trough the table
    for(int i = 0; i < m_table.size(); i++){
      //if the index is empty, continue through table
      if(m_table[i].size() == 0){
        continue;
      }
      //create iterator to go through list at index i of table
      typename std::list<KeyType>::iterator it = m_table[i].begin();
      for(; it != m_table[i].end(); it++){
        //adds the movie to the vector
        movies.push_back(*it);
      }
    }
    //creates a new table of the new size
    std::vector<std::list<KeyType> > new_table(new_size);
    m_table = new_table;//sets the table equal to the new table
    //goes through the movie vector
    for(int j = 0; j < movies.size(); j++){
      insert(movies[j]);//insert each movie into bigger table
    }
  }
};
#endif