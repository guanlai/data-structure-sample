#include "unorderedmap.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

int main(){
    UnorderedMap <int, string> m;
    for (int i = 1; i<25001; i++) {
        //cout << "now insert " << i << endl;
        assert(m.insert(i, "a") == true );
        //cout << "finish insert " << i << endl;
        assert(m.insert(i, "a") == false );
        assert(m.size()==i);
    }
    
    for (int i = 1; i<25001; i++) {
        //cout << "now insert " << i << endl;
        assert(m.erase(i) == true );
        //cout << "finish insert " << i << endl;
        assert(m.erase(i) == false );
        assert(m.size()==25000 - i);
    }
    //assert(m.size() == 4 );
    for (int i = 1; i<25001; i++) {
        m[i] = i;
        assert(m.size()==i);
    }
    UnorderedMap <int, string> m1 = m;
    UnorderedMap <int, string> m2;
    m2 = m;
    
    assert(m1.size()==25000);
    assert(m2.size()==25000);
    for (int i = 1; i<25001; i++) {
        m[i] = i;
        assert(m.size()==25000);

    }
    for (int i = 1; i<25001; i++) {
        assert(m1.erase(i) == true );
        assert(m1.erase(i) == false );
        assert(m1.size()==25000 - i);
    }
    for (int i = 1; i<25001; i++) {
        assert(m2.erase(i) == true );
        assert(m2.erase(i) == false );
        assert(m2.size()==25000 - i);
    }
    cout << "------ start iterator test ------" << endl;
    UnorderedMap <int, string>::Iterator it = m.begin();
    
    while ( it != m.end() ) {
        cout << it -> key << endl;
        it++;
    }
    cout << "------ end iterator test ------" << endl;
}
