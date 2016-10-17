/*
 CS515 Assignment 10
 File: PQueue.cpp
 Name: Guanlai Li
 Section: 02
 Date: 11/19/2015
 Collaboration Declaration: worked out alone
 */

#include "PQueue.h"
#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

template< class T, int MAX_SIZE >
PQueue<T, MAX_SIZE>::PQueue()
{
    _size = 0;
}

template< class T, int MAX_SIZE >
PQueue<T, MAX_SIZE>::PQueue( T * items, int size )
{
    _size = size;
    if(_size > MAX_SIZE )
        _size = MAX_SIZE;
    for (int i = 0; i < _size; i++)
        _array[ i + 1 ] = items[ i ];
    buildHeap();
}

template< class T, int MAX_SIZE >
void PQueue<T, MAX_SIZE>::insert( T x ) // insert an item; duplicates are allowed.
{
    if( _size >= MAX_SIZE )
        return;
    _size++;
    _array[ _size ] = x;
    moveUp();
}

template< class T, int MAX_SIZE >
T PQueue<T, MAX_SIZE>::findMin() // return the smallest item from the queue
{
    return ( _size > 0 ) ? _array[ 1 ] : 0;
}

template< class T, int MAX_SIZE >
void PQueue<T, MAX_SIZE>::deleteMin() // remove the smallest item from the queue
{
    if( _size == 0 )
        return;
    _array[ 1 ] = _array[ _size ];
    _size--;
    moveDown( 1 );
}

template< class T, int MAX_SIZE >
bool PQueue<T, MAX_SIZE>::isEmpty() // test if the priority queue is logically empty
{
    return _size == 0;
}

template< class T, int MAX_SIZE >
int PQueue<T, MAX_SIZE>::size() // return queue size
{
    return _size;
}

template< class T, int MAX_SIZE >
void PQueue<T, MAX_SIZE>::buildHeap() // linear heap construction
{
    int cur = _size / 2;
    while ( cur > 0 ) {
        moveDown( cur );
        cur--;
    }
}

template< class T, int MAX_SIZE >
void PQueue<T, MAX_SIZE>::moveDown( int x ) // move down element at given index
{
    while ( x <= _size / 2 ) {
        if( * _array[ x ] <= * _array[ 2 * x ] &&
           ( 2 * x + 1 > _size ||
             * _array[ x ] <= * _array[ 2 * x + 1 ] ) )
            break;
        else if( * _array[ x ] > * _array[ 2 * x ] &&
                ( 2 * x + 1 > _size ||
                  * _array[ 2 * x ] <= * _array[ 2 * x + 1 ] ) )
        {
            T temp = _array[ 2 * x ];
            _array[ 2 * x ] = _array[ x ];
            _array[ x ] = temp;
            x *= 2;
        }
        else if( * _array[ x ] > * _array[ 2 * x + 1 ] &&
                2 * x + 1 <= _size &&
                * _array[ 2 * x ] > * _array[ 2 * x + 1 ] )
        {
            T temp = _array[ 2 * x + 1 ];
            _array[ 2 * x + 1 ] = _array[ x ];
            _array[ x ] = temp;
            x = 2 * x + 1;
        }
    }
}

template< class T, int MAX_SIZE >
void PQueue<T, MAX_SIZE>::moveUp() // move up the last element in the heap array
{
    int x = _size;
    while ( x / 2 > 0 ) {
        if( * _array[ x / 2 ] > * _array[ x ] )
        {
            T temp = _array[ x ];
            _array[ x ] = _array[ x / 2 ];
            _array[ x / 2 ] = temp;
            x /= 2;
        }
        else
            break;
    }
}



