/**
 CS515 Assignment 9
 File: unorderedmap.cpp
 Name: Guanlai Li
 Section: 02
 Date: 11/10/2015
 Collaboration Declaration: worked out alone.
 */

// Below are the stubs for SOME methods
// Make sure all methods in unorderedmap.h are implemented

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::UnorderedMap(){
    tablesize = 101;  // initial table size
    entrysize = 0;
    array = new Entry[ tablesize ];
    for ( int i = 0; i < tablesize - 1; i++ )
    {
        array[ i ].next = &array[ i + 1 ];
        array[ i ].root = true;
    }
    array[ tablesize - 1 ].next = 0;
    array[ tablesize - 1 ].root = true;
}

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::~UnorderedMap(){
    for ( int i = 0; i < tablesize; i++ )
        freeNodes( array[ i ] );
    delete [] array;
}

template <typename KEY, typename T, typename H>
void UnorderedMap<KEY, T, H>::freeNodes( Entry & node )
{
    Entry * temp = node.next;
    while ( temp && !temp -> root ) {
        Entry * temp1 = temp;
        temp = temp -> next;
        delete temp1;
    }
    node.next = temp;
}

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::UnorderedMap(const UnorderedMap& rhs)
{
    tablesize = rhs.tablesize;  // initial table size
    entrysize = 0;
    array = new Entry[ tablesize ];
    for ( int i = 0; i < tablesize - 1; i++ )
    {
        array[ i ].next = &array[ i + 1 ];
        array[ i ].root = true;
    }
    array[ tablesize - 1 ].next = 0;
    array[ tablesize - 1 ].root = true;
    
    for ( int i = 0; i < tablesize; i++ ){
        Entry * node = rhs.array[ i ].next;
        while ( node && !node -> root ) {
            insert( node -> key, node -> data );
            node = node -> next;
        }
    }
}

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>& UnorderedMap<KEY, T, H>::operator=(const UnorderedMap& rhs)
{
    for ( int i = 0; i < tablesize; i++ )
        freeNodes( array[ i ] );
    delete [] array;

    tablesize = rhs.tablesize;  // initial table size
    entrysize = 0;
    
    array = new Entry[ tablesize ];
    for ( int i = 0; i < tablesize - 1; i++ )
    {
        array[ i ].next = &array[ i + 1 ];
        array[ i ].root = true;
    }
    array[ tablesize - 1 ].next = 0;
    array[ tablesize - 1 ].root = true;

    for ( int i = 0; i < tablesize; i++ ){
        Entry * node = rhs.array[ i ].next;
        while ( node && !node -> root ) {
            insert( node -> key, node -> data );
            node = node -> next;
        }
    }
    
    return * this;
}

template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::insert(const KEY & newkey, const T & data){
    std::size_t key = H()( newkey );
    key %= tablesize;
    Entry * target = array[ key ].next;
    while ( target && !target -> root ) {
        if ( target -> key == newkey )
            return false;
        else
            target = target -> next;
    }
    Entry * node = new Entry( newkey, data );
    node -> root = false;
    node -> next = array[ key ].next;
    array[ key ].next = node;
    entrysize++;
    
    if ( entrysize >= 2 * tablesize )
        rehash();
    return true;
}

template <typename KEY, typename T, typename H>
void UnorderedMap<KEY, T, H>::rehash( ){

    Entry * temp = array;
    int tsize = tablesize;
    tablesize = nextPrime( tablesize );
    entrysize = 0;
    array = new Entry[ tablesize ];
    for ( int i = 0; i < tablesize - 1; i++ )
    {
        array[ i ].next = &array[ i + 1 ];
        array[ i ].root = true;
    }
    array[ tablesize - 1 ].next = 0;
    array[ tablesize - 1 ].root = true;
    
    for ( int i = 0; i < tsize; i++ ){
        Entry * node = temp[ i ].next;
        while ( node && !node -> root ) {
            insert( node -> key, node -> data );
            node = node -> next;
        }
    }
    
    for ( int i = 0; i < tsize; i++ )
        freeNodes( temp[ i ] );
    delete [] temp;
}

template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::erase (const KEY& key )
{
    std::size_t pos = H()(key);
    pos %= tablesize;
    Entry * target = array[ pos ].next;
    Entry * prev = &array[ pos ];
    while ( target && !target -> root ) {
        if( target -> key == key )
        {
            prev -> next = target -> next;
            delete target;
            entrysize--;
            return true;
        }
        else
        {
            prev = target;
            target = target -> next;
        }
    }
    return false;
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::find( const KEY & x ) const{
    // stub code; need to implement !!!
    std::size_t key = H()(x);
    key %= tablesize;
    Entry * target = array[ key ].next;
    while ( target && !target -> root ) {
        if( target -> key == x )
            return Iterator( target );
        else
            target = target -> next;
    }
    return end();
}


template<typename KEY, typename T, typename H>
T& UnorderedMap<KEY, T, H>::operator[](const KEY & k){
    // stub code; need to implement !!!
    std::size_t key = H()( k );
    key %= tablesize;
    Entry * target = array[ key ].next;
    while ( target && !target -> root ) {
        if ( target -> key == k )
            return target -> data;
        else
            target = target -> next;
    }
    Entry * node = new Entry();
    node -> key = k;
    node -> root = false;
    node -> next = array[ key ].next;
    array[ key ].next = node;
    entrysize++;
    

    
    if ( entrysize < 2 * tablesize )
        return node -> data;
    
    rehash();
    key = H()( k );
    key %= tablesize;
    target = array[ key ].next;
    while ( target && !target -> root ) {
        if ( target -> key == k )
            return target -> data;
        else
            target = target -> next;
    }
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::Iterator::operator++(int){
    // stub code; need to implement !!!
    Entry * node = _cur -> next;
    while ( node && node -> root ) {
        node = node -> next;
    }
    _cur = node;
    return Iterator( _cur );
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::begin() const{
    // stub code; need to implement !!!
    Entry * node = & array[ 0 ];
    while ( node && node -> root ) {
        node = node -> next;
    }
    return Iterator( node );
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::end() const{
    // stub code; need to implement !!!
    return Iterator(0);
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Entry* UnorderedMap<KEY, T, H>::Iterator::operator->(){
    return _cur;
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Entry& UnorderedMap<KEY, T, H>::Iterator::operator*(){
    return *_cur;
}


template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::Iterator::operator!=(Iterator it){
    return _cur != it._cur;
}

template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::Iterator::operator==(Iterator it){
    return _cur == it._cur;
}

// Internal method to test if a positive number is prime (not efficient)
bool isPrime( int n ){
    if( n == 2 || n == 3 )
        return true;
    if( n == 1 || n % 2 == 0 )
        return false;
    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;
    return true;
}

// Internal method to return a prime number at least as large as n.
// Assumes n > 0.
int nextPrime( int n ){
    n *= 2;
    if( n % 2 == 0 )
        n++;
    for( ; !isPrime( n ); n += 2 )
        ;
    return n;
}

