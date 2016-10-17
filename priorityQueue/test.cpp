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
    _size = 0;
}

//copy constructor
HuffTree::HuffTree( const HuffTree & rhs )
{
    if( rhs._root -> left )
    {
        _root = new HuffNode;
        copyCode( _root -> left, rhs._root -> left );
        _size = rhs._size;
    }
    else
    {
        _root = new HuffNode;
        _size = 0;
    }
}

//deep copy
HuffTree & HuffTree::operator=( const HuffTree & rhs )
{
    destructCode( _root -> left );
    _root -> left = 0;
    copyCode( _root -> left, rhs._root -> left );
    _size = rhs._size;
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
                    origRoot -> data, origRoot -> code, origRoot -> rightMost );
        copyCode( newRoot -> left, origRoot -> left);
        copyCode( newRoot -> right, origRoot -> right);
    }
}

//helper function for distructor
void HuffTree::destructCode( HuffNode * node )
{
    if ( _size == 0 )
        return;

    if( node -> left )
        destructCode( node -> left );
    if( node -> right )
        destructCode( node -> right );
    delete node;
}

// get Huffman code and return it as a string
string HuffTree::getCode( char c )
{
    return ( _size == 0 ) ? "" : readCode( _root, c );
}

string HuffTree::readCode( HuffNode * node, char c )
{

    if( node -> left )
        readCode( node -> left, c );
    if( node -> right )
        readCode( node -> right, c );
    if( node -> data == c )
        return node -> code;
    if( node -> data != c && node -> rightMost )
        return "";
}

// build Huffman tree from an array of characters
// and and an array of their corresponding freqencys;
// the size of both arrays is given
void HuffTree::buildTree(char * chs, int * freqs, int size)
{
    if( size == 0 )
        return;
    
    HuffNode ** nodeArray[ size ];
    for( int i = 0; i < size; i++ )
        node[i] = new HuffNode( 0, 0, freqs[ i ], chs[ i ], false );
    
    PQueue< HuffNode*, size > p( nodeArray, size );
    
    while ( p.size() > 1 ) {
        HuffNode * temp1 = p.findMin();
        p.deleteMin();
        HuffNode * temp2 = p.findMin();
        p.deleteMin();
        HuffNode * node = new HuffNode( temp1, temp2, temp1 -> freq + temp2 -> freq, '\0', "", false );
        p.insert( node );
    }
    
    assert( p.size() == 1 );
    _root -> left = p.findMin();
    
    HuffNode * temp = _root -> left;
    while ( temp -> right ) {
        temp = temp -> right;
    }
    temp -> rightMost = true;
    
    string key = "";
    updateCode( _root, key );
}

HuffNode * HuffTree::updateCode( HuffNode * node, string key )
{
    if( node -> left )
    {
        key += '0';
        updateCode( node -> left, key );
    }
    
    if( node -> right )
    {
        key += '1';
        updateCode( node -> right, key );
    }
    
    if( node -> data != '\0' )
        node -> code = key;
}

bool HuffNode::operator<=( const HuffNode & rhs )
{
    return freq <= rhs.freq;
}

bool HuffNode::operator>( const HuffNode & rhs )
{
    return freq > rhs.freq;
}
