#ifndef CODE_HPP
#define CODE_HPP

#include <array>
#include <memory>
#include <cstddef>

#ifdef DBG
#include <iostream>
#include "debug.hpp"
#include <algorithm>

using std::cout;
using std::endl;
using std::for_each;
#endif

using std::array;
using std::shared_ptr;
using std::make_shared;

template <typename T1>
class node{
public:
   node(T1&);
   ~node();
public:
   const T1& get_data ();
   shared_ptr<node<T1>>& get_next ();
private:
   T1& data;
   shared_ptr<node<T1>> next;
};
template<typename T1,typename T2>
class list{
public:
   list(T2&);
   ~list();
public:
   const node<T1>& get_middle_node (void);
private:
  shared_ptr<node<T1>> head;
  shared_ptr<node<T1>> tail;
  size_t sz;
};

template<typename T1> node<T1>::node(T1& r):data(r){
   //https://en.cppreference.com/w/cpp/types/NULL
   //A null pointer constant may be implicitly converted to any pointer type; such conversion results in the null pointer value of that type.
   next = NULL;
}

template<typename T1> node<T1>::~node(){
}

template<typename T1> const T1& node<T1>::get_data(){
   return data;
}

template<typename T1> shared_ptr<node<T1>>& node<T1>::get_next(){
   return next;
}

template<typename T1,typename T2> list<T1,T2>::list(T2& r){
#ifdef DBG
     PRNT_LN_NUM
#endif

   auto it = r.begin();
   //shared_ptr& operator=( const shared_ptr& r ) noexcept;
   //Replaces the managed object with the one managed by r.
   //If *this already owns an object and it is the last shared_ptr owning it, 
   //and r is not the same as *this, the object is destroyed through the owned deleter.
   //
   //Due to the above, temp is required to ensure continuity of linkage between successive nodes.
   shared_ptr<node<T1>>temp; 

   while(it != r.end()){
      if(it == r.begin()){
         head = make_shared<node<T1>>(*it);
         head->get_next() = tail;
      }
      else{
         if(it == r.begin() + 1){
            tail = make_shared<node<T1>>(*it);
            temp = tail;
            head->get_next() = temp;
            tail = tail->get_next();
         }
         else{
            tail = make_shared<node<T1>>(*it);
            temp->get_next() = tail;
            temp = tail;
            tail = tail->get_next();
         }
      }
      ++it;
   }
   //https://en.cppreference.com/w/cpp/types/NULL
   //A null pointer constant may be implicitly converted to any pointer type; such conversion results in the null pointer value of that type.
   tail = NULL;
   sz = r.size();
#ifdef DBG
     PRNT_LN_NUM
#endif
}

template<typename T1,typename T2> list<T1,T2>::~list(){
}

template<typename T1,typename T2> const node<T1>& list<T1,T2>::get_middle_node(void){

   auto index = 0;
   auto count = 0;

   if(sz % 2){index = sz/2;}
   else{index = sz/2 + 1;}

   auto temp = head;

   while(temp){
     if(count == index){break;}
     temp = temp->get_next();
     ++count;
   }
   return *temp;
}

#endif
