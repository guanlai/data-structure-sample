// tests for rehash()

#include "unorderedmap.h"
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#define SIZE 5000

using namespace std;
int main(){
	UnorderedMap<string, int> m1;
	string str;
	for (int i = 0; i < SIZE; i++){
		stringstream ss;
		ss << i << ' ';
        ss >> str;
        m1.insert(str, i);
		assert(m1[str] == i);
		if (i%100 == 0)
		   cout << "table size at: " << i << " is "<< m1.tsize() << endl;
	}
	
	assert(m1.size() == SIZE);
	for (int i = 0; i < m1.size(); i++){
		stringstream ss;
		ss << i << ' ';
        ss >> str;
		assert(m1.find(str) != m1.end());
	}
}
