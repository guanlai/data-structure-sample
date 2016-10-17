#include "map.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main(){
    Map<string, string> m1, m2;
    Map<string, string>::Iterator it1, it2, it3;
    
    string str[] = {"m", "l", "f", "e", "a",
        "c", "b", "d", "g", "k",
        "i", "h", "j", "n", "t",
        "s", "o", "q", "p", "r",
        "u", "y", "w", "v", "x" };
    
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
    cout << "output should be in alphabatic order" <<endl;
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
    assert( it1->key == "a" );
    
    cout << "------ test copy constructor and operator= ------" <<endl;
    Map<string, string> m3 = m1;
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
        string str3 = m2[str[i]];
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
        string str1 = (*it1).key;
        string str2 = it1 -> key;
        string str3 = m1[str[i]];
        
        assert( !str[ i ].compare( str1 ) );
        assert( !str[ i ].compare( str2 ) );
        assert( !str[ i ].compare( str3 ) );
    }
    
    
    Map<int, int> im1, im2;
    Map<int, int>::Iterator iit1, iit2, iit3;
    
    int istr[] = {22, 21, 15, 14, 10,
        12, 11, 13, 16, 20,
        18, 17, 19, 23, 29,
        28, 24, 26, 25, 27,
        30, 34, 32, 31, 33 };
    
    cout << "------ test insert and erase ------" <<endl;
    for( int i = 0; i<25; i++)
    {
        assert( im1.insert( istr[i], istr[i] ) == true);
        assert( im1.insert( istr[i], istr[i] ) == false);
        assert( im1.size() == i+1 );
        //cout << "now insert -- " << str[i] << endl;
        //cout << m1 << endl;
    }
    cout << "------ test rightThread and iterator ++ ------" <<endl;
    cout << "output should be in ascending order" <<endl;
    iit1 = im1.begin();
    while ( iit1 != im1.end() ) {
        cout << iit1 -> data << " ";
        iit1++;
    }
    cout << endl;
    for( int i = 0; i<25; i++)
    {
        //cout << m1 << endl;
        //cout << "now delete -- " << str[i] << endl;
        assert( im1.erase( istr[i] ) == true);
        assert( im1.erase( istr[i] ) == false);
        assert( im1.size() == 24 - i);
        iit1 = im1.begin();
        while ( iit1 != im1.end() ) {
            cout << iit1 -> data << " ";
            iit1++;
        }
        cout << endl;
    }
    
    cout << "------ test iterator ------" <<endl;
    for( int i = 0; i<25; i++)
    {
        assert( im1.insert( istr[i], istr[i] ) == true);
        assert( im1.insert( istr[i], istr[i] ) == false);
        assert( im2.insert( istr[i], istr[i] ) == true);
        assert( im2.insert( istr[i], istr[i] ) == false);
        assert( im1.size() == i+1 );
    }
    iit1 = im1.begin();
    iit2 = im2.begin();
    assert( iit1 != iit2 );
    iit2 = im1.begin();
    assert( iit1 == iit2 );
    assert( iit1->key == 10 );
    
    cout << "------ test copy constructor and operator= ------" <<endl;
    Map<int, int> im3 = im1;
    im2 = im1;
    
    for( int i = 0; i<25; i++)
    {
        assert( im3.erase( istr[i] ) == true);
        assert( im3.erase( istr[i] ) == false);
        assert( im3.size() == 24 - i);
        iit1 = im3.begin();
        //        while ( it1 != m3.end() ) {
        //            cout << it1 -> data << " ";
        //            it1++;
        //        }
        //        cout << endl;
    }
    
    for( int i = 0; i<25; i++)
    {
        assert( im2.erase( istr[i] ) == true);
        assert( im2.erase( istr[i] ) == false);
        assert( im2.size() == 24 - i);
        //        it1 = m2.begin();
        //        while ( it1 != m2.end() ) {
        //            cout << it1 -> data << " ";
        //            it1++;
        //        }
        //        cout << endl;
    }
    
    im3 = im1;
    im2 = im1;
    iit1 = im3.begin();
    iit2 = im2.begin();
    iit3 = im2.begin();
    while ( iit1 != im3.end() ) {
        assert( iit1 -> key == iit2 -> key );
        assert( (*iit1).key == iit2 -> key );
        assert( (*iit2).key == iit1 -> key );
        assert( iit1 != iit2 );
        assert( iit2 == iit3 );
        iit1++;
        iit2++;
        iit3++;
    }
    
    cout << "------ test insert by [] ------" <<endl;
    for( int i = 0; i<25; i++)
        assert( im2.erase( istr[i] ) == true);
    
    for( int i = 0; i < 25; i++ )
    {
        im2[ istr[ i ] ] = istr[ i ];
        assert( im2.size() == i + 1 );
        int istr3 = im2[istr[i]];
        assert( istr3 == istr[i] );
    }
    
    iit1 = im3.begin();
    iit2 = im2.begin();
    iit3 = im2.begin();
    while ( iit1 != im3.end() ) {
        assert( iit1 -> key == iit2 -> key );
        assert( (*iit1).key == iit2 -> key );
        assert( (*iit2).key == iit1 -> key );
        assert( iit1 != iit2 );
        assert( iit2 == iit3 );
        iit1++;
        iit2++;
        iit3++;
    }
    
    cout << "------ test find and access by [] ------" <<endl;
    
    for( int i = 0; i < 25; i++ )
    {
        iit1 = im1.find( istr[i] );
        int istr1 = (*iit1).key;
        int istr2 = iit1 -> key;
        int istr3 = im1[istr[i]];
        assert( istr1 == istr2 );
        assert( istr2 == istr3 );
    }

}
