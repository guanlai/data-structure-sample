/*
 CS515 Assignment 7
 File: map.cpp
 Name: Guanlai Li
 Section: 02
 Date: 10/24/2015
 Collaboration Declaration: worked out alone
 */

// A generic Map implemented with threaded BST
// BST is not balanced

#include <map>
template <typename KEY, typename T>
Map<KEY, T>::Map(){
    // create a dummy root node
    _root = new Elem;
    _root->left = _root; // empty tree
    _root->right = 0;
    _root->rightThread = false;
    _size = 0;
    
}

// copy constructor
template <typename KEY, typename T>
Map<KEY, T>::Map(const Map<KEY,T> &v){
    // if empty tree
    if (v._root == v._root->left){
        _root = new Elem;
        _root->left = _root; // empty tree
        _root->right = 0;
        _size = 0;
    } else {
        _root = new Elem;
        _root->left = _root;
        _root->right = 0;
        copyCode(_root->left, v._root->left); // to deep copy the tree without dummy nodes
        copyThread(_root, v._root); // to copy the threading; must pass dummy nodes to complete the threads
        _size = v._size;
    }
}

// destructor
template <typename KEY, typename T>
Map<KEY, T>::~Map()
{
    destructCode( _root -> left );
    delete _root;
    _root = 0;
    _size = 0;
}

// common code for deallocation
template <typename KEY, typename T>
void Map<KEY, T>::destructCode(Elem *& p)
{
    if( size() == 0 )
        return;
    
    if( p -> left )
        destructCode( p -> left );
    if ( p -> right && !p -> rightThread )
        destructCode( p -> right );

    delete p;
}

// assignment operator
template <typename KEY, typename T>
Map<KEY, T>& Map<KEY, T>::operator=(const Map &rhs)
{
    destructCode(_root -> left);
    _size = 0;
    if (rhs._root == rhs._root->left )
        return *this;
    copyCode(_root->left, rhs._root->left);
    copyThread(_root, rhs._root);
    _size = rhs._size;
}


// construct a key-element map to rethread the new tree
// the map contains all nodes key values and their corresonding elem node address
// for furture lookup in setting up threads
template <typename KEY, typename T>
void Map<KEY, T>::addToMap(Elem* root, map<KEY, Elem*> &keyElemMap){
    if (root) {
        keyElemMap[root->key] = root;
        addToMap(root->left, keyElemMap);
        if (!root->rightThread)
            addToMap(root->right, keyElemMap);
    }
}

// common copy code for thread copying
template <typename KEY, typename T>
void Map<KEY, T>::copyThread(Elem* &newRoot, Elem* origRoot){
    // construct the key-element map for new and orig tree
    map<KEY, Elem*> newKeyElemMap;
    map<KEY, Elem*> origKeyElemMap;
    addToMap(newRoot->left, newKeyElemMap);
    addToMap(origRoot->left, origKeyElemMap);
    
    // start at the last element in the tree, which threads to root
    typename std::map<KEY, Elem*>::reverse_iterator it = origKeyElemMap.rbegin();
    newKeyElemMap[it->first] -> rightThread = true;
    newKeyElemMap[it->first] -> right = newRoot;
    
    // then thread the rest of the tree backwardly
    it++;
    while(it != origKeyElemMap.rend()){
        if (it->second->rightThread){
            newKeyElemMap[it->first] -> rightThread = true;
            newKeyElemMap[it->first] -> right = newKeyElemMap[ origKeyElemMap[it->first]->right->key ];
        }
        it++;
    }
}

// common copy code for deep copy a tree without copying threads
template <typename KEY, typename T>
void Map<KEY,T>::copyCode(Elem* &newRoot, Elem* origRoot){
    if (origRoot == 0)
        newRoot = 0;
    else{
        newRoot = new Elem;
        newRoot->key = origRoot->key;
        newRoot->data = origRoot->data;
        newRoot->rightThread = origRoot->rightThread;
        copyCode(newRoot->left, origRoot->left);
        if (!origRoot->rightThread)
            copyCode(newRoot->right, origRoot->right);
    }
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::begin() const {
    // return the left most (smallest) tree node
    Elem * node = _root -> left;
    while ( node -> left && node != _root )
        node = node -> left;
    return Iterator( node );
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::end() const {
    // return the dummy root node
    return Iterator( _root );
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::Iterator::operator++(int){
    // fill in here
    if( !_cur -> right )
        return Iterator( _cur );
    Elem * node = _cur -> right;
    while ( (node -> left) && (node -> left -> key > _cur -> key) )
    {
        node = node -> left;
    }
    _cur = node;
    return Iterator( _cur );
}

template <typename KEY, typename T>
typename Map<KEY, T>::Elem& Map<KEY, T>::Iterator::operator*(){
    // fill in here
    return *_cur;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Elem* Map<KEY, T>::Iterator::operator->(){
    // fill in here
    return _cur;
}

template <typename KEY, typename T>
bool Map<KEY, T>::Iterator::operator==(Iterator it)
{
    return _cur == it._cur;
}

template <typename KEY, typename T>
bool Map<KEY, T>::Iterator::operator!=(Iterator it)
{
    return _cur != it._cur;
}

template <typename KEY, typename T>
bool Map<KEY, T>::insert(Elem *& root, const KEY &key, const T &data, Elem *lastLeft)
{
    if( root == _root || root == 0 )
    {
        root = new Elem;
        root -> key = key;
        root -> data = data;
        root -> left = 0;
        root -> rightThread = true;
        root -> right = lastLeft;
        _size++;
        return true;
    }
    else if( key == root -> key )
        return false;
    else if( key < root -> key )
        insert( root -> left, key, data, root );
    else if( !root -> rightThread )
        insert( root -> right, key, data, lastLeft );
    else
    {
        root -> rightThread = false;
        root ->right = new Elem;
        root ->right -> key = key;
        root ->right -> data = data;
        root ->right -> left = 0;
        root ->right -> rightThread = true;
        root ->right -> right = lastLeft;
        _size++;
        return true;
    }
}

template <typename KEY, typename T>
bool Map<KEY, T>::insert(KEY key, T data )
{
    return( insert( _root -> left, key, data, _root ) );
}

template <typename KEY, typename T>
bool Map<KEY, T>::erase(KEY key)
{
    if( size() == 0 )
        return false;
    
    Elem * node = _root -> left;
    Elem * parent = _root;
    
    while ( node )
    {
        if( key < node -> key )
        {
            parent = node;
            node = node -> left;
        }
        else if( key > node -> key && !node -> rightThread)
        {
            parent = node;
            node = node -> right;
        }
        else if( key > node -> key && node -> rightThread )
            return false;
        else if( key == node -> key )
        {
            if( !node -> left && node -> rightThread )
            {//no child
                if( node == parent -> left )
                    parent -> left = 0;
                else
                {
                    parent -> right = node -> right;
                    parent -> rightThread = true;
                }
            }
            else if( node -> left && node -> rightThread )
            {//left child
                if( node == parent -> left )
                    parent -> left = node -> left;
                else
                    parent -> right = node -> left;
                Elem * temp = node -> left;
                while( temp -> right && !temp -> rightThread )
                    temp = temp -> right;
                temp -> right = node -> right;
            }
            else if ( !node -> left && !node -> rightThread )
            {//right child
                if( node == parent -> left )
                    parent -> left = node -> right;
                else
                    parent -> right = node -> right;
            }
            else if( node -> left && !node -> rightThread )
            {//two children
                Elem * temp = node -> right;
                //cout << "two children, node to delete is " << node -> key;
                //cout << ", node to move is " << temp -> key << endl;
                if(!temp -> left)
                {
                    //cout << temp -> key << " does not have left child" << endl;
                    node -> key = temp -> key;
                    node -> data = temp -> data;
                    node -> right = temp -> right;
                    node -> rightThread = temp -> rightThread;
                    node = temp;
                    //cout << "now node is " << node -> key << endl;
                    //cout << "now node right is " << node -> right -> key << endl;
                }
                else
                {
                    while(temp -> left)
                    {
                        parent = temp;
                        temp = temp -> left;
                    }
                    node -> key = temp -> key;
                    node -> data = temp -> data;
                    node = temp;
                    if( node -> rightThread )
                        parent -> left = 0;
                    else
                        parent -> left = node -> right;
                }
            }
            delete node;
            _size--;
            if( _size == 0 )
            {
                _root -> left = _root;
                _root -> rightThread = false;
                _root -> right = 0;
            }
            return true;
        }
    }
    
    return false;
    
}

template <typename KEY, typename T>
int Map<KEY, T>::size() const{
    return _size;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::find(KEY key) const
{
    Elem * node = _root -> left;
    while ( node && node != _root )
    {
        if( key == node -> key )
            return Iterator( node );
        else if( key > node -> key )
        {
            if( node -> rightThread )
                break;
            else
                node = node -> right;
        }
        else if( key < node -> key )
            node = node -> left;
    }
    return end();
}

template <typename KEY, typename T>
T& Map<KEY, T>::operator[](KEY key)
{
    Elem * node = _root -> left;
    Elem * parent = _root;
    while ( node && node != _root )
    {
        if( key == node -> key )
            return node -> data;
        else if( key > node -> key )
        {
            if( node -> rightThread )
                break;
            else
            {
                parent = node;
                node = node -> right;
            }
        }
        else if( key < node -> key )
        {
            parent = node;
            node = node -> left;
        }
    }
    Elem * newNode = new Elem;
    newNode -> key = key;
    newNode -> left = 0;
    _size++;
    
    if( node && node != _root )
    {
        newNode -> rightThread = true;
        newNode -> right = node -> right;
        node -> right = newNode;
        node -> rightThread = false;
        return newNode -> data;
    }
    
    if( parent == _root || key < parent -> key )
    {
        parent -> left = newNode;
        newNode -> rightThread = true;
        newNode -> right = parent;
        return newNode -> data;
    }
    
}

// output the structure of tree. The tree is output as "lying down"
// in which _root is the LEFT most Elem.
template <typename KEY, typename T>
void Map<KEY, T>::printTree(ostream& out, int level, Elem *p) const{
    int i;
    if (p) {
        if (p->right && !p->rightThread)
            printTree(out, level+1,p->right);
        for(i=0;i<level;i++) {
            out << "\t";
        }
        out << p->key << " " << p->data << '\n';
        printTree(out, level+1,p->left);
    }
}

// outputs information in tree in inorder traversal order
template <typename KEY, typename T>
ostream& Map<KEY, T>::dump(ostream& out) const{
    if ( _root == _root->left) {// tree empty
        return out;
    }
    printTree(out, 0, _root->left); // print tree structure
    return out;
}


// outputs using overloaded << operator
template<typename KEY, typename T>
ostream& operator<< (ostream& out, const Map<KEY, T>& v){
    v.dump(out);
    return out;
}
