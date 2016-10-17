#include "map.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main(){
    Map<int, int> m1, m2;
    Map<int, int>::Iterator it1, it2, it3;
    
    int str[] = {22, 21, 15, 14, 10,
                12, 11, 13, 16, 20,
                18, 17, 19, 23, 29,
                28, 24, 26, 25, 27,
                30, 34, 32, 31, 33 };
    
    cout << "------ test insert and erase ------" <<endl;
    for( int i = 0; i<25; i++)
    {
        assert( m1.insert( str[i], str[i] ) == true);
        assert( m1.insert( str[i], str[i] ) == false);
        assert( m1.size() == i+1 );
        //cout << "now insert -- " << str[i] << endl;
        //cout << m1 << endl;
    }
    cout << "------ test rightThread and iterator ++ ------" <<endl;
    cout << "output should be in ascending order" <<endl;
    it1 = m1.begin();
    while ( it1 != m1.end() ) {
        cout << it1 -> data << " ";
        it1++;
    }
    cout << endl;
    for( int i = 0; i<25; i++)
    {
        //cout << m1 << endl;
        //cout << "now delete -- " << str[i] << endl;
        assert( m1.erase( str[i] ) == true);
        assert( m1.erase( str[i] ) == false);
        assert( m1.size() == 24 - i);
        it1 = m1.begin();
        while ( it1 != m1.end() ) {
            cout << it1 -> data << " ";
            it1++;
        }
        cout << endl;
    }

    cout << "------ test iterator ------" <<endl;
    for( int i = 0; i<25; i++)
    {
        assert( m1.insert( str[i], str[i] ) == true);
        assert( m1.insert( str[i], str[i] ) == false);
        assert( m2.insert( str[i], str[i] ) == true);
        assert( m2.insert( str[i], str[i] ) == false);
        assert( m1.size() == i+1 );
    }
    it1 = m1.begin();
    it2 = m2.begin();
    assert( it1 != it2 );
    it2 = m1.begin();
    assert( it1 == it2 );
    assert( it1->key == 10 );
    
    cout << "------ test copy constructor and operator= ------" <<endl;
    Map<int, int> m3 = m1;
    m2 = m1;
    
    for( int i = 0; i<25; i++)
    {
        assert( m3.erase( str[i] ) == true);
        assert( m3.erase( str[i] ) == false);
        assert( m3.size() == 24 - i);
        it1 = m3.begin();
        //        while ( it1 != m3.end() ) {
        //            cout << it1 -> data << " ";
        //            it1++;
        //        }
        //        cout << endl;
    }
    
    for( int i = 0; i<25; i++)
    {
        assert( m2.erase( str[i] ) == true);
        assert( m2.erase( str[i] ) == false);
        assert( m2.size() == 24 - i);
        //        it1 = m2.begin();
        //        while ( it1 != m2.end() ) {
        //            cout << it1 -> data << " ";
        //            it1++;
        //        }
        //        cout << endl;
    }
    
    m3 = m1;
    m2 = m1;
    it1 = m3.begin();
    it2 = m2.begin();
    it3 = m2.begin();
    while ( it1 != m3.end() ) {
        assert( it1 -> key == it2 -> key );
        assert( (*it1).key == it2 -> key );
        assert( (*it2).key == it1 -> key );
        assert( it1 != it2 );
        assert( it2 == it3 );
        it1++;
        it2++;
        it3++;
    }
    
    cout << "------ test insert by [] ------" <<endl;
    for( int i = 0; i<25; i++)
        assert( m2.erase( str[i] ) == true);
    
    for( int i = 0; i < 25; i++ )
    {
        m2[ str[ i ] ] = str[ i ];
        assert( m2.size() == i + 1 );
        int str3 = m2[str[i]];
        assert( str3 == str[i] );
    }
    
    it1 = m3.begin();
    it2 = m2.begin();
    it3 = m2.begin();
    while ( it1 != m3.end() ) {
        assert( it1 -> key == it2 -> key );
        assert( (*it1).key == it2 -> key );
        assert( (*it2).key == it1 -> key );
        assert( it1 != it2 );
        assert( it2 == it3 );
        it1++;
        it2++;
        it3++;
    }
    
    cout << "------ test find and access by [] ------" <<endl;
    
    for( int i = 0; i < 25; i++ )
    {
        it1 = m1.find( str[i] );
        int str1 = (*it1).key;
        int str2 = it1 -> key;
        int str3 = m1[str[i]];
        assert( str1 == str2 );
        assert( str2 == str3 );
    }
}
