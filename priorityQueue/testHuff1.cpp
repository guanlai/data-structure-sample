#include "HuffTree.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main(){
    HuffTree h;
    HuffTree h4;

    char c[5] = {'e', 'f', 'd', 'a', 'g'};
    int f[5] = {12, 4, 2, 3, 1};
    h.buildTree(c,f,5);
    
    HuffTree h1(h);
    HuffTree h2;
    HuffTree h3;

    h2 = h1;
    h3 = h;

    cout << "------h------" << endl;
    cout << h.getCode('e') << endl;
    cout << h.getCode('f') << endl;
    cout << h.getCode('a') << endl;
    cout << h.getCode('g') << endl;
    cout << h.getCode('d') << endl;
    cout << "------h1------" << endl;
    cout << h1.getCode('e') << endl;
    cout << h1.getCode('f') << endl;
    cout << h1.getCode('a') << endl;
    cout << h1.getCode('g') << endl;
    cout << h1.getCode('d') << endl;
    cout << "------h2------" << endl;
    cout << h2.getCode('e') << endl;
    cout << h2.getCode('f') << endl;
    cout << h2.getCode('a') << endl;
    cout << h2.getCode('g') << endl;
    cout << h2.getCode('d') << endl;
    cout << "------h3------" << endl;
    cout << h3.getCode('e') << endl;
    cout << h3.getCode('f') << endl;
    cout << h3.getCode('a') << endl;
    cout << h3.getCode('g') << endl;
    cout << h3.getCode('d') << endl;
}

