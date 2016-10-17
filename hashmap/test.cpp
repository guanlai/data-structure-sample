// Below are the stubs for SOME methods
// Make sure all methods in unorderedmap.h are implemented

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::UnorderedMap(){

}

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::~UnorderedMap(){

}

template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::insert(const KEY & newkey, const T & data){
	std::size_t key = H()(newkey); 
	return true;
}

template <typename KEY, typename T, typename H>
void UnorderedMap<KEY, T, H>::rehash( ){

}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::find( const KEY & x ) const{
	// stub code; need to implement !!!
	return end(); 
}


template<typename KEY, typename T, typename H>
T& UnorderedMap<KEY, T, H>::operator[](const KEY & k){
	// stub code; need to implement !!!
	static T tmp;
	return tmp;
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::Iterator::operator++(int){
	// stub code; need to implement !!!
	return Iterator(NULL);
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::begin() const{
	// stub code; need to implement !!!
	return Iterator(NULL);
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::end() const{
	// stub code; need to implement !!!
	return Iterator(NULL);
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Entry* UnorderedMap<KEY, T, H>::Iterator::operator->(){
	return _cur;
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Entry& UnorderedMap<KEY, T, H>::Iterator::operator*(){
	return *_cur;
}


template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::Iterator::operator!=(Iterator it){
	return _cur != it._cur;
}

template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::Iterator::operator==(Iterator it){
	return _cur == it._cur;
}

// Internal method to test if a positive number is prime (not efficient)
bool isPrime( int n ){
	if( n == 2 || n == 3 )
		return true;
	if( n == 1 || n % 2 == 0 )
		return false;
	for( int i = 3; i * i <= n; i += 2 )
		if( n % i == 0 )
			return false;
	return true;
}

// Internal method to return a prime number at least as large as n.
// Assumes n > 0.
int nextPrime( int n ){
	if( n % 2 == 0 )
		n++;
	for( ; !isPrime( n ); n += 2 )
		;
	return n;
}

