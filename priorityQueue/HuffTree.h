/*
 CS515 Assignment 10
 File: HuffTree.h
 Name: Guanlai Li
 Section: 02
 Date: 11/19/2015
 Collaboration Declaration: worked out alone
 */
#ifndef HUFFTREE_H
#define HUFFTREE_H

#include <string>
using namespace std;

struct HuffNode{
    // default constructor
    HuffNode(HuffNode* l = 0, HuffNode* r = 0, int f = 0, char d = '\0', string str = "")
        : left(l), right(r), freq(f), data(d), code(str){}
    HuffNode * left, * right;  // two child node
    unsigned int freq; // freqency of the node
    char data;  // char value for leaf nodes; '\0' for internal nodes
    string code;  // Huffman code for leaf nodes; not assigned for internal nodes
    
    // do not change above code
    // you may add below here
    bool operator<=( HuffNode & rhs )
    {
        return freq <= rhs.freq;
    }
    
    bool operator>( HuffNode & rhs )
    {
        return freq > rhs.freq;
    }
};

class HuffTree{
public:
    // get Huffman code and return it as a string
    string getCode(char);
    
    // build Huffman tree from an array of characters
    // and and an array of their corresponding freqencys;
    // the size of both arrays is given
    void buildTree(char * chs, int * freqs, int size);
    //default constructor
    HuffTree();
    //copy constructor
    HuffTree( const HuffTree & );
    //destructor
    ~HuffTree();
    //deep copy
    HuffTree & operator=( const HuffTree & );
    
private:
    HuffNode * _root; // root of the Huffman tree
    // do not change above code
    // you may add below here


    void copyCode( HuffNode *&, HuffNode* );
    void destructCode( HuffNode * node );
    void readCode( HuffNode *, char, string&);
    void updateCode( HuffNode *, string );
    //bool HuffNode::operator<=( const HuffNode & rhs );
    //bool HuffNode::operator>( const HuffNode & rhs );
    void printTree( HuffNode * node );

};

#endif