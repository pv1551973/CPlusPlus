#ifndef CODE_HPP
#define CODE_HPP
#include <memory>
#include <iostream>

using std::shared_ptr;
using std::make_shared;

using std::cout;
using std::endl;

#define DBG_TRACE (cout << "At line " << __LINE__ << endl);

//forward declarations
template<typename X>class list;
template<typename X> shared_ptr<X> get_node_handle(list<X>&, size_t, bool);

template<typename T>
class node{
	private:
		T& data;
		shared_ptr<node<T>> next;
	private:
		void set_data(T&);
	public:
		node(T&);
		~node();
	public:
		T& get_data(void);
		shared_ptr<node<T>> get_next (void);
		void set_next(shared_ptr<node<T>>);
};

template<typename X>
class list{
	private:
		shared_ptr<X> head;
		list(shared_ptr<X>);
	public:
		shared_ptr<X> get_head(void);
        void set_head(shared_ptr<X>);
	public:
        list();
		~list();
    public:
        size_t size (void)const;
        shared_ptr<X> operator[] (size_t) const;
        size_t remove (size_t);
        void reverse (void);
};

template<typename T>
node<T>::node(T& _data):data(_data){
	this->next = NULL;
}
template<typename T>
node<T>::~node(){
}

template<typename T>
void node<T>::set_next(shared_ptr<node<T>> next){
	this->next = next;

    return;
}
template<typename T>
shared_ptr<node<T>> node<T>::get_next(void){
	return(this->next);
}
template<typename T>
T& node<T>::get_data(void){
	return(this->data);
}

template<typename X>
list<X>::list(){
    this->head = NULL;
}

template<typename X>
list<X>::~list(){
}

template<typename X>
shared_ptr<X> list<X>::get_head(void){
	return(this->head);
}

template<typename X>
void list<X>::set_head(shared_ptr<X> head){
	this->head = head;
    
    return;
}

template<typename X>
size_t list<X>::size (void)const{
    auto h = this->head;
    auto count = 0;

    while(h->get_next()){
        ++count;
        h = h->get_next();
    }
    if(h && !h->get_next()){
        ++count;
    }

    return count;
}

template<typename X>
shared_ptr<X> list<X>::operator[] (size_t idx) const{

    if(idx >= this->size()){
        return NULL;
    }

    auto h = this->head;
    size_t count = 0;

    while(h && count < idx){
        ++count;
        h = h->get_next();
    }

    return h;
}

//get_node_handle() implementation
template<typename X>
shared_ptr<X> get_node_handle(list<X>& rList, size_t idx, bool is_first_final_invocation){
    static size_t size = 0;
    //handle for the new head 
    static shared_ptr<X> phead = NULL;

    if(is_first_final_invocation && idx){//idx is not 0; first invocation
        //retrieve the size of the list and store it in
        //the static variable
        size = rList.size();
        goto RETURN;
    }
    else if(is_first_final_invocation && !idx){//idx is 0; final invocation
        return phead;
    }
    else{
        goto RETURN;
    }

RETURN:
    if(idx > size - 1){
        //a temporary work around
        //need to replace with code
        //to throw an exception
        return NULL;
    }

    auto h = rList.get_head();
    size_t count = 0;

    while(count < idx){
       h = h->get_next();
       ++count;
    }

    if(is_first_final_invocation && idx){
        //first invocation; save the handle for the new
        //head
        phead = h;
    }

    return h;
}

template<typename X>
size_t list<X>::remove(size_t idx){

    if(idx >= this->size()){
        //a workaround; need to 
        //replace with exception
        return (this->size());
    }
    else{

         if(0 == idx){
         auto h = (*this)[idx];
         auto nxt = h->get_next();
         this->set_head(nxt);
         h.reset();
        }
        else{
         auto h = (*this)[idx - 1];
         auto nxt = h->get_next()->get_next();
         h->get_next().reset();
         h->set_next(nxt);
        }

        return (this->size());
   }
}

template<typename X>
void list<X>::reverse(void){
    size_t i = 0;
    size_t j = 0;
    size_t sz = size();
    i = sz - 1;
    j = i - 1;

    do{
        if(i == sz - 1){
            get_node_handle(*this, i, true)->set_next(get_node_handle(*this, j, false));
        }
        get_node_handle(*this, i, false)->set_next(get_node_handle(*this, j, false));
        i = j;
        j = i - 1;
     }while(i != 0);

    get_node_handle(*this, i, false)->set_next(NULL);
    set_head(get_node_handle(*this, i, true));

    return;
}
#endif
