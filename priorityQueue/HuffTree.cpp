/*
 CS515 Assignment 10
 File: HuffTree.cpp
 Name: Guanlai Li
 Section: 02
 Date: 11/19/2015
 Collaboration Declaration: worked out alone
 */
#include "HuffTree.h"
#include "PQueue.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

//constructor
HuffTree::HuffTree()
{
    _root = new HuffNode;
}

//copy constructor
HuffTree::HuffTree( const HuffTree & rhs )
{
    _root = new HuffNode;
    copyCode( _root -> left, rhs._root -> left );
}

//deep copy
HuffTree & HuffTree::operator=( const HuffTree & rhs )
{
    destructCode( _root -> left );
    _root -> left = 0;
    copyCode( _root -> left, rhs._root -> left );
    return *this;
}

//destructor
HuffTree::~HuffTree()
{
    if( _root -> left )
        destructCode( _root -> left );
    delete _root;
}

// common copy code for deep copy a tree
void HuffTree::copyCode( HuffNode *& newRoot, HuffNode* origRoot){
    if ( origRoot == 0 )
        newRoot = 0;
    else{
        newRoot = new HuffNode(0, 0, origRoot -> freq,
                               origRoot -> data, origRoot -> code );
        copyCode( newRoot -> left, origRoot -> left);
        copyCode( newRoot -> right, origRoot -> right);
    }
}

//helper function for distructor
void HuffTree::destructCode( HuffNode * node )
{
    if ( node == 0 )
        return;
    
    if( node -> left )
        destructCode( node -> left );
    if( node -> right )
        destructCode( node -> right );
    delete node;
}

void HuffTree::printTree( HuffNode * node )
{
    if ( node == 0 )
        return;
    
    if( node -> left )
        printTree( node -> left );
    if( node -> right )
        printTree( node -> right );
    cout << node -> freq << endl;
}

// get Huffman code and return it as a string
string HuffTree::getCode( char c )
{
    string ret = "";
    readCode( _root -> left, c ,ret);
    return ret;
}

void HuffTree::readCode( HuffNode * node, char c , string& in_string )
{
    if( node == 0 )
        return;
    
    if( node -> left )
        readCode( node -> left, c, in_string );
    if(node->right)
        readCode( node -> right, c ,in_string );
    
    if( node -> data == c )
        in_string = node -> code;
}

// build Huffman tree from an array of characters
// and and an array of their corresponding freqencys;
// the size of both arrays is given
void HuffTree::buildTree(char * chs, int * freqs, int size)
{
    destructCode( _root -> left );
    _root -> left = 0;
    
    if( size == 0 )
        return;

    HuffNode * nodeArray[ size ];
    for( int i = 0; i < size; i++ )
        nodeArray[i] = new HuffNode( 0, 0, freqs[ i ], chs[ i ], "" );
    
    PQueue< HuffNode*, 200 > p( nodeArray, size );
    
    while ( p.size() > 1 ) {
        HuffNode * temp1 = p.findMin();
        p.deleteMin();
        HuffNode * temp2 = p.findMin();
        p.deleteMin();
        HuffNode * node = new HuffNode( temp1, temp2, temp1 -> freq + temp2 -> freq, '\0', "" );
        p.insert( node );
    }
    //update _root pointer
    _root -> left = p.findMin();
    HuffNode * temp = _root -> left;
    
    //update code
    string key = "";
    if( size > 1 )
        updateCode( _root -> left, key );
    else
        _root -> left -> code = key + '0';
}

void HuffTree::updateCode( HuffNode * node, string key )
{
    if( node -> left )
        updateCode( node -> left, key + '0' );
    
    if( node -> right )
        updateCode( node -> right, key + '1' );
    
    if( node -> data != '\0' )
        node -> code = key;
}
