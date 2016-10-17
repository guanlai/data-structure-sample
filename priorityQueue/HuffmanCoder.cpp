/*
 CS515 Assignment 10
 File: HuffmanCoder.cpp
 Name: Guanlai Li
 Section: 02
 Date: 11/19/2015
 Collaboration Declaration: worked out alone
 */
#include "HuffTree.h"
#include <iostream>
#include <fstream>
#include <iomanip> 
#include <string>
#include <cassert>
#include <ctype.h>
using namespace std;

int main( int argc, char ** argv )
{
    if( argc != 2 )
    {
        cout << "wrong number of arguments" << endl;
        return 0;
    }
    //initialize the freq table
    int freq[26];
    char table[26];
    for ( int i = 0; i < 26; i++) {
        freq[ i ] = 0;
        table[ i ] = 'a' + i;
    }
    
    ifstream f( argv[1] );
    if ( f.fail() )
    {
        cout << "Error opening file" << endl;
        return 1;
    }
    
    char c;
    int countAll = 0;
    int countSyb = 0;
    while ( f.get( c ) ) {
        countAll++;
        if (isalpha( c )) {
            c = tolower( c );
            freq[ c - 'a' ]++;
        }
        else
            countSyb++;
    }
    f.close();
    
    HuffTree h;
    h.buildTree( table, freq, 26 );

    int aftComp = 0;
    for ( int i = 0; i < 26; i++ )
        aftComp += freq[ i ] * h.getCode( table[ i ] ).length();
    
    cout << "original bits: " << 8*countAll << endl;
    cout << "bits after compression: " << aftComp + 8*countSyb << endl;
    cout << "compression rate: " << setprecision(4);
    cout << 100 - 100.*(aftComp + 8*countSyb)/(8.*countAll);
    cout << "%"<< endl;
}