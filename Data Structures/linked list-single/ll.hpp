#ifndef LL_HPP
#define LL_HPP
#include<iostream>
#include<memory>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::make_shared;
template <class T> 
class LNode{
public:
LNode(T&,shared_ptr<LNode<T>> = NULL);
~LNode();
shared_ptr<LNode<T>> getNext(void);
void setNext(shared_ptr<LNode<T>>);
T& getData(void);
void empty(void);
private:
T& data;
shared_ptr<LNode<T>> pNext;
};

template <class T, class C>
class List{
public:
List(int,C&);
~List();
void insert(int,T&);
void remove(int);
shared_ptr<LNode<T>> operator[](int);
void display(void);
int getNumElems();
private:
shared_ptr<LNode<T>> head;
shared_ptr<LNode<T>> tail;
};

template <class T> LNode<T>::LNode(T& rData, shared_ptr<LNode<T>> pN):data(rData), pNext(pN){ }

template <class T> LNode<T>::~LNode(){pNext = NULL;}

template <class T> shared_ptr<LNode<T>> LNode<T>::getNext(void){return pNext;}

template <class T> void LNode<T>::setNext(shared_ptr<LNode<T>> pN){pNext = pN;}

template <class T> void LNode<T>::empty(void){delete this;} 

template <class T> T& LNode<T>::getData(void){return data;}

template <class T, class C> List<T,C>::List(int n, C& rData){
shared_ptr<LNode<T>> prev = NULL;
for(auto i = 0; i < n; ++i){
if(0 == i){
head = make_shared<LNode<T>>(rData[i]);
prev = head;
#ifdef DBG
cout << "head data: " << head->getData() << endl;
cout << "head next: " << head->getNext() << endl;
#endif
}
else{
tail = make_shared<LNode<T>>(rData[i]);
prev->setNext(tail);
#ifdef DBG
cout << "previous next: " << prev->getNext() << endl;
#endif
tail->setNext(NULL);
#ifdef DBG
cout << "tail data: " << tail->getData() << endl;
if(1 == i){
cout << "head next: " << head->getNext() << endl;
}
#endif
prev = tail;
if(i + 1 < n)
tail = tail->getNext();;
}
}
}

template <class T, class C> List<T,C>:: ~List(){
head = tail = NULL;
}

template <class T, class C> void List<T,C>::insert(int pos, T& rData){
shared_ptr<LNode<T>> pN = (*this)[pos];
shared_ptr<LNode<T>> pTmpN = pN->getNext();
shared_ptr<LNode<T>> pNuN = make_shared<LNode<T>>(rData,pTmpN);
pN->setNext(pNuN);
return;
}

template <class T, class C> void List<T,C>::remove(int pos){
shared_ptr<LNode<T>> pN1 = (*this)[pos];
shared_ptr<LNode<T>> pN2 = (*this)[pos-1];
pN2->setNext(pN1->getNext());
//pN1->empty();
pN1->setNext(NULL);
return;
}

template <class T, class C> shared_ptr<LNode<T>> List<T,C>::operator[](int pos){
shared_ptr<LNode<T>> pTmpN = head;
auto i = 0;
while(i++ < pos){
pTmpN = pTmpN->getNext(); 
}
return pTmpN;
}

template <class T, class C> void List<T,C>::display(void){
shared_ptr<LNode<T>> pTmpN = head;
do{
cout << pTmpN->getData() << endl;
 }while((pTmpN = pTmpN->getNext()));
return;
}

template<class T, class C> int List<T, C>::getNumElems(){
shared_ptr<LNode<T>> pTmpN = head;
auto count = 0;
while(pTmpN){
++count;
pTmpN = pTmpN->getNext();
}
return count;
}
#endif
