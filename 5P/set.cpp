/*
 CS515 Assignment 5
 File: set.cpp
 Name: Guanlai Li
 Section: 02
 Date: 10/13/2015
 Collaboration Declaration: worked out alone.
 */

#include "set.h"

// common code for copy constructor and assignment
void Set::copyCode(const Set & v)
{
    _head = new Elem();
    _tail = new Elem();
    _head -> prev = 0;
    _head -> next = _tail;
    _tail -> prev = _head;
    _tail -> next = 0;
    _size = 0;
    
    Iterator it = v.begin();
    while ( it != v.end() )
    {
        insert( *it );
        it++;
    }
}

// common code for deallocation
void Set::destructCode()
{
    Iterator it = begin();
    while ( it != end() )
    {
        ELEMENT_TYPE x = *it;
        it++;
        erase( x );
    }
    _size = 0;
}

// output set elements
ostream& Set::dump(ostream& out, const Set &v)
{
    if( v.size() == 0 )
        return out;
    Iterator it = v.begin();
    while ( it != v.end() )
    {
        out << *it << " ";
        it++;
    }
    return out;
}


// construct a null iterator
Set::Iterator::Iterator()
{
    _cur = 0;
}

// construct an iterator given pointer to Elem
Set::Iterator::Iterator( Elem * cur )
{
    _cur = cur;
}

// overloaded dereference operator
ELEMENT_TYPE& Set::Iterator::operator*()
{
    return _cur -> info;
}

// overloaded post-increment operator
Set::Iterator Set::Iterator::operator++(int)
{
    _cur = _cur -> next;
    return *this;
}

// overloaded post-decrement operator
Set::Iterator Set::Iterator::operator--(int)
{
    _cur = _cur -> prev;
    return *this;
}

// overloaded equality operator
bool Set::Iterator::operator==(Iterator it)
{
    return _cur == it._cur;
}

// overloaded inequality operator
bool Set::Iterator::operator!=(Iterator it)
{
    return _cur != it._cur;
}

// construct a null iterator
Set::Reverse_Iterator::Reverse_Iterator()
{
    _cur = 0;
}

// construct an iterator given pointer to Elem
Set::Reverse_Iterator::Reverse_Iterator(Elem *cur)
{
    _cur = cur;
}

// overloaded dereference operator
ELEMENT_TYPE& Set::Reverse_Iterator::operator*()
{
    return _cur -> info;
}

// overloaded post-increment operator
Set::Reverse_Iterator Set::Reverse_Iterator::operator++(int)
{
    _cur = _cur -> prev;
    return *this;
}

// overloaded post-decrement operator
Set::Reverse_Iterator Set::Reverse_Iterator::operator--(int)
{
    _cur = _cur -> next;
    return *this;
}

// overloaded equality operator
bool Set::Reverse_Iterator::operator==(Reverse_Iterator it)
{
    return _cur == it._cur;
}

// overloaded inequality operator
bool Set::Reverse_Iterator::operator!=(Reverse_Iterator it)
{
    return _cur != it._cur;
}



// constructs empty set
Set::Set()
{
    _head = new Elem();
    _tail = new Elem();
    _head -> prev = 0;
    _head -> next = _tail;
    _tail -> prev = _head;
    _tail -> next = 0;
    _size = 0;
}

// Constructs a container with as many elements as the range [first,last),
// with each element constructed from its corresponding element in that range.
Set::Set(ELEMENT_TYPE* first, ELEMENT_TYPE* last)
{
    _head = new Elem();
    _tail = new Elem();
    _head -> prev = 0;
    _head -> next = _tail;
    _tail -> prev = _head;
    _tail -> next = 0;
    _size = 0;
    
    ELEMENT_TYPE * temp = first;
    while ( temp != last )
        insert( *temp++ );
}

// copy constructor
Set::Set(const Set &rhs)
{
    copyCode( rhs );
}

// destructor
Set::~Set()
{
    destructCode();
    delete _head;
    delete _tail;
    _head = 0;
    _tail = 0;
}

// assignment operator
Set& Set::operator=( const Set &rhs )
{
    if( this == & rhs )
        return *this;
    destructCode();
    delete _head;
    delete _tail;
    copyCode( rhs );
    return * this;
}

// insert an element
void Set::insert(ELEMENT_TYPE x )
{
    Elem * temp = _head -> next;
    ELEMENT_TYPE y = temp -> info;
    while ( temp != _tail )
    {
        if( y.compare( x ) == 0 )
            return;
        if( y.compare( x ) > 0 )
        {
            Elem * node = new Elem();
            node -> info = x;
            node -> prev = temp -> prev;
            node -> next = temp;
            node -> prev -> next = node;
            node -> next -> prev = node;
            _size++;
            return;
        }
        temp = temp -> next;
        y = temp -> info;
    }
    Elem * node = new Elem();
    _tail -> info = x;
    node -> prev = _tail;
    node -> next = 0;
    _tail -> next = node;
    _tail = node;
    _size++;
}

// remove an element from the set
void Set::erase(ELEMENT_TYPE x )
{
    Elem * temp = _head -> next;
    ELEMENT_TYPE y = temp -> info;
    while ( temp != _tail )
    {
        if( y.compare( x ) == 0 )
        {
            temp -> prev -> next = temp -> next;
            temp -> next -> prev = temp -> prev;
            delete temp;
            _size--;
            return;
        }
        temp = temp -> next;
        y = temp -> info;
    }
}

// remove all elements from set
void Set::clear()
{
    destructCode();
}

// return size of the set
int Set::size() const
{
    return _size;
}

// return an iterator to the element if val is found, or set::end() otherwise.
Set::Iterator Set::find(ELEMENT_TYPE x ) const
{
    Iterator it = begin();
    while ( it != end() )
    {
        if( (*it).compare( x ) == 0 )
            break;
        it++;
    }
    return it;
}

// return an iterator pointing at the begining of the list
Set::Iterator Set::begin() const
{
    return Iterator( _head -> next );
}

// return an iterator pointing at one element beyond the end of list
Set::Iterator Set::end() const
{
    return Iterator( _tail );
}

// return an reverse iterator pointing at the reverse beginning of the list
Set::Reverse_Iterator Set::rbegin() const
{
    return Reverse_Iterator( _tail -> prev );
}

// return an reverse iterator pointing at one element beyond the beginning of list
Set::Reverse_Iterator Set::rend() const
{
    return Reverse_Iterator( _head );
}

// friend top level function for output all list elements
// elements are output as a single white space delimited
ostream& operator<< (ostream& out , Set& s )
{
    s.dump( out, s );
    return out;
}

// set join and intersect
Set operator&(const Set& s1, const Set& s2 )
{
    Set s;
    Set::Iterator it = s1.begin();
    while ( it != s1.end() )
    {
        if( s2.find( *it ) != s2.end() )
            s.insert( *it );
        it++;
    }
    return s;
}

Set operator|(const Set& s1, const Set& s2 )
{
    Set s = s1;
    Set::Iterator it = s2.begin();
    while ( it != s2.end() )
    {
        s.insert( *it );
        it++;
    }
    return s;
}

// set difference
Set operator-(const Set& s1, const Set& s2 )
{
    Set s = s1;
    Set::Iterator it = s2.begin();
    while ( it != s2.end() )
    {
        if( s1.find( *it ) != s2.end() )
            s.erase( *it );
        it++;
    }
    return s;
}
// set equality
bool operator==(const Set& s1, const Set& s2)
{
    if( s1.size() != s2.size() )
        return false;
    Set::Iterator it = s1.begin();
    while ( it != s1.end() )
    {
        if( s2.find( *it ) == s2.end() )
            return false;
        it++;
    }
    return true;
}