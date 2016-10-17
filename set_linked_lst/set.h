// a set implemented with sorted doubly linked list with dummy header and tail nodes. 
// the set supports two iterators for set traversal. 
// set type is typedef as string 


#ifndef SET_H
#define SET_H
#include <iostream>
#include <string>

using namespace std;
typedef string ELEMENT_TYPE;  // a set for string elements

class Set{
private:
    struct Elem {
        ELEMENT_TYPE info;
        Elem *prev, *next;
    };
    
    // dummy header and tail nodes
    Elem *_head, *_tail;
    
    int _size;
    
    // common code for copy constructor and assignment
    void copyCode(const Set & v);
    
    // common code for deallocation
    void destructCode();
    
    // output set elements
    ostream& dump(ostream& out, const Set &v);
    
public:
    class Iterator{
    public:
    	// construct a null iterator
        Iterator(); 
        
        // construct an iterator given pointer to Elem 
        explicit Iterator(Elem *cur); 
        
        // overloaded dereference operator
        ELEMENT_TYPE& operator*();
        
        // overloaded post-increment operator
        Iterator operator++(int); 
        
        // overloaded post-decrement operator
        Iterator operator--(int);
        
        // overloaded equality operator
        bool operator==(Iterator it);
        
        // overloaded inequality operator
        bool operator!=(Iterator it);
        
    private:
        Elem* _cur;
    };
    
    class Reverse_Iterator{
    public:
    	// construct a null iterator
        Reverse_Iterator(); 
        
        // construct an iterator given pointer to Elem 
        explicit Reverse_Iterator(Elem *cur); 
        
        // overloaded dereference operator
        ELEMENT_TYPE& operator*();
        
        // overloaded post-increment operator
        Reverse_Iterator operator++(int); 
        
        // overloaded post-decrement operator
        Reverse_Iterator operator--(int);
        
        // overloaded equality operator
        bool operator==(Reverse_Iterator it);
        
        // overloaded inequality operator
        bool operator!=(Reverse_Iterator it);
        
    private:
        Elem* _cur;
    };
    
    
    // constructs empty set
    Set();
    
    // Constructs a container with as many elements as the range [first,last), 
    // with each element constructed from its corresponding element in that range.
    Set(ELEMENT_TYPE* first, ELEMENT_TYPE* last);
    
    // copy constructor
    Set(const Set &rhs);
    
    // destructor
    ~Set();
    
    // assignment operator
    Set& operator=(const Set &rhs);
    
    // insert an element
    void insert(ELEMENT_TYPE);
    
    // remove an element from the set
    void erase(ELEMENT_TYPE);
    
    // remove all elements from set
    void clear();
    
    // return size of the set
    int size() const; 
    
    // return an iterator to the element if val is found, or set::end() otherwise.
    Iterator find(ELEMENT_TYPE) const;
    
    // return an iterator pointing at the begining of the list
    Iterator begin() const;
    
    // return an iterator pointing at one element beyond the end of list
    Iterator end() const;
    
    // return an reverse iterator pointing at the reverse beginning of the list
    Reverse_Iterator rbegin() const;
    
    // return an reverse iterator pointing at one element beyond the beginning of list
    Reverse_Iterator rend() const;
    
    // friend top level function for output all list elements
    // elements are output as a single white space delimited 
    friend ostream& operator<< (ostream&, Set&);
};

// set join and intersect
Set operator&(const Set&, const Set&);
Set operator|(const Set&, const Set&);

// set difference 
Set operator-(const Set&, const Set&);
// set equality
bool operator==(const Set& s1, const Set& s2);

#endif
