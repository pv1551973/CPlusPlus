
#ifndef BT_HPP
#define BT_HPP
#include "error.hpp"
#include<iostream>
#include<vector>
#include<string>
#include<memory>
#include<iterator>
#include<functional>
#include<cassert>
#include<cstddef>
using std::vector;
using std::string;
using std::to_string;
using std::shared_ptr;
using std::make_shared;
using std::next;
using std::distance;
using std::ptrdiff_t;
using std::function;
using std::cout;
using std::endl;

#define LINE (cout << "At line # " << __LINE__ << endl);
#define DBG_PRINT(...) (cout << __VA_ARGS__<< endl);

enum class traversal_order {PREORDER, INORDER, POSTORDER};

template<typename T1>
class node{
    public:
        using sp2node = class shared_ptr<node<T1>>;
        using r_sp2node = class shared_ptr<node<T1>>&;
        using r_const_sp2node = const class shared_ptr<node<T1>>&;
    public:
        static const shared_ptr<node<T1>> null_const_sp2node;
    public:
        node(T1&,r_const_sp2node rP = null_const_sp2node,r_const_sp2node rLC = null_const_sp2node,r_const_sp2node rRc = null_const_sp2node);
        ~node();
    public:
        void setParent(r_sp2node);
        void setLeftChild(r_sp2node);
        void setRightChild(r_sp2node);
    public:
        //overloaded methods
        void setParent();
        void setLeftChild();
        void setRightChild();
    public:
        void mark_as_root();
        //introduced in the context
        //of node addition
        void unmark_as_root();
    public:
        bool is_root();
        bool hasParent();
        bool hasLeftChild();
        bool hasRightChild();
    public:
        T1 const & getData();
        r_sp2node getParent();
        r_sp2node getLeftChild();
        r_sp2node getRightChild();
    public:
        void setData(T1 const&);
    public:
        node<T1>& getNode();
    private:
        T1 data;
        sp2node P;
        sp2node LC;
        sp2node RC;
        bool m_is_root;
};

template<typename T1, typename T2>
class tree{
    public:
        using sp2node_cont = vector<shared_ptr<node<T1>>>;
        using cnst_sp2node_cont = const vector<shared_ptr<node<T1>>>;
        using r_sp2node_cont = sp2node_cont&;
        using cnst_r_sp2node_cont = cnst_sp2node_cont&;
        using iter_sp2node_cont = typename vector<shared_ptr<node<T1>>>::iterator;
        using r_iter_sp2node_cont = typename vector<shared_ptr<node<T1>>>::iterator&;
        using rNode = node<T1>&;
        using crNode = const node<T1>&;
        //using type_null_const_sp2node = typename node<T1>::null_const_sp2Node;
    public:
        tree(T2 const&, size_t);
        ~tree();
    public:
        void traverse_tree(traversal_order);
        int getHeight();
        void addNode(T1&, int);
        void delNode(int);
    private:
        sp2node_cont hierarchy;
    private:
        void linkNodes();
        void renameNodes(iter_sp2node_cont);
};

//static member initialization

template<typename T1> const shared_ptr<node<T1>> node<T1>::null_const_sp2node = NULL;

//node related methods

template<typename T1> node<T1>::node(T1& rData, r_const_sp2node rP, r_const_sp2node rLC, r_const_sp2node rRC){

    data = rData;
    
    P = (rP ? rP : null_const_sp2node);
    assert(P == NULL);
    LC = (rLC ? rLC : null_const_sp2node);
    assert(LC == NULL);
    RC = (rRC ? rRC : null_const_sp2node);
    assert(RC == NULL);

    m_is_root = 0;
}

template<typename T1> node<T1>::~node(){ }

template<typename T1> void node<T1>::setParent(r_sp2node rP){

    P = rP;

    return;
}

template<typename T1> void node<T1>::setLeftChild(r_sp2node rLC){

    LC = rLC;

    return;
}

template<typename T1> void node<T1>::setRightChild(r_sp2node rRC){

    RC = rRC;

    return;
}

//overloaded methods

template<typename T1> void node<T1>::setParent(){

    P = null_const_sp2node;

    return;
}

template<typename T1> void node<T1>::setLeftChild(){

    LC = null_const_sp2node;

    return;
}

template<typename T1> void node<T1>::setRightChild(){

    RC = null_const_sp2node;

    return;
}

template<typename T1> void node<T1>::mark_as_root(){

    m_is_root = 1;

    return;
}

//introduced in the context of node addition
template<typename T1> void node<T1>::unmark_as_root(){

    m_is_root = 0;

    return;
}

template<typename T1> bool node<T1>::is_root(){

    return(m_is_root);
}

template<typename T1> bool node<T1>::hasParent(){

    return(P != null_const_sp2node);
}

template<typename T1> bool node<T1>::hasLeftChild(){

    return(LC != null_const_sp2node);
}

template<typename T1> bool node<T1>::hasRightChild(){

    return(RC != null_const_sp2node);
}

template<typename T1> T1 const & node<T1>::getData(){

    return(data);
}

template<typename T1> typename node<T1>::r_sp2node node<T1>::getParent(){

    return(P);
}

template<typename T1> typename node<T1>::r_sp2node node<T1>::getLeftChild(){

    return(LC);
}

template<typename T1> typename node<T1>::r_sp2node node<T1>::getRightChild(){

    return(RC);
}

template<typename T1> node<T1>& node<T1>::getNode(){

    return (*this);
}

template<typename T1> void node<T1>::setData(T1 const& crData){

    data = crData;
}

//tree related methods

template<typename T1, typename T2>tree<T1,T2>::tree(T2 const& cr_ofTypeT2, size_t size){

    for(auto count = 0; count < size; ++count){

        auto r_data_ofTypeT1 = cr_ofTypeT2[count]; 

        auto sp2node = make_shared<node<decltype(r_data_ofTypeT1)>>(r_data_ofTypeT1);
        hierarchy.push_back(sp2node);
    }

    linkNodes();
}

template<typename T1, typename T2> tree<T1,T2>::~tree(){}

template<typename T1, typename T2> void tree<T1,T2>::linkNodes(){

    //the following is the logic for
    //linking nodes:
    //1->2->3
    //2->4->5
    //3->6->7
    //4->8->9
    //5->10->11
    //6->12->13
    //7->14->15
    //8->16->17
    //9->18->19
    //10->20->21
    //11->22->23
    //12->24->25
    //and so on...
    
   auto count = 0;
   auto sz = hierarchy.size();
   auto limit = sz/2; 

   for(auto sp : hierarchy){

          //can't use a switch statement
          //here, as the comparisons used
          //do not involve complile time
          //constants
          if(count == limit){

                  goto EXIT;
          }
          else{
                  if(0 == count){

                      sp.get()->mark_as_root();
                      sp.get()->setParent();

                      sp.get()->setLeftChild(hierarchy[count + 1]);
                      hierarchy[count + 1].get()->setParent(sp);

                      sp.get()->setRightChild(hierarchy[count + 2]);
                      hierarchy[count + 2].get()->setParent(sp);

                      ++count;
                  }
                  else if(count > 0 && count < limit){

                          // a caveat for resetting a previous
                          // root node, in the case of adding
                          // a node at pos 0
                          sp.get()->unmark_as_root();

                          // the following logic works like this
                          // when count is 1, which corresponds
                          // to node 2, LC corresponds to
                          // ref2Cont[3], which is node 4, and RC
                          // corresponds to ref2Cont[4], which is
                          // node 5

                          auto lIdx = count * 2 + 1;
                          auto rIdx = count * 2 + 2;

                          //LINE
                          //DBG_PRINT("count:" << count)
                          //DBG_PRINT("lIdx:" << lIdx)
                          //DBG_PRINT("rIdx:" << rIdx)

                          if(lIdx < sz){
                              //LINE
                                sp.get()->setLeftChild(hierarchy[lIdx]);
                                hierarchy[lIdx].get()->setParent(sp);
                          }
                          else{
                                sp.get()->setLeftChild();
                          }
                          if(rIdx < sz){
                                sp.get()->setRightChild(hierarchy[rIdx]);
                                hierarchy[rIdx].get()->setParent(sp);
                          }
                          else{
                                sp.get()->setRightChild();
                          }

                          ++count;
                  }

            }

      }

      EXIT:
          return;
        
}

template<typename T1, typename T2> void tree<T1,T2>::traverse_tree(traversal_order D){

    switch(D){

        case traversal_order::PREORDER:
            {

                auto count = 0;
                auto limit = hierarchy.size()/2;

                //lambda definition

                //note the commmented out line below
                //the line had to be commented out
                //because of the fact that with the 
                //signature of the function object 
                //using a reference, the invocation
                //of std::next() within the function
                //object would not compile, as std::next()
                //would not be able to advance a reference
                //to an iterator, as a reference is constant
                //function<void(r_iter_sp2node_cont, r_iter_sp2node_cont)> print_preorder = [&] (r_iter_sp2node_cont begin, r_iter_sp2node_cont end){
                //
                function<void(iter_sp2node_cont, iter_sp2node_cont)> print_preorder = [&] (iter_sp2node_cont begin, iter_sp2node_cont end){


                    if(count  == limit){
                    //if(count > limit){

                        return;
                    }


                    cout << (*begin).get()->getData() << endl;

                    if((*begin).get()->is_root()){
                        
                        cout << "I am Root" << endl;
                    }
                    
                    if((*begin).get()->hasParent()){

                        cout << "My Parent is ";
                        cout << (*begin).get()->getParent().get()->getData();
                        cout << endl;
                    }

                    if((*begin).get()->hasLeftChild()){

                        cout << "My Left Child is ";
                        cout << (*begin).get()->getLeftChild().get()->getData();
                        cout << endl;
                    }
                    if((*begin).get()->hasRightChild()){

                        cout << "My Right Child is ";
                        cout << (*begin).get()->getRightChild().get()->getData();
                        cout << endl;
                    }

                    ++count;

                    print_preorder(next(begin), end);

                };//end definition of print_preorder

                print_preorder(hierarchy.begin(), hierarchy.end());

                break;
            }

        case traversal_order::INORDER:
            {
                //lambda

                function<void(rNode)>
                    print_inorder = [&](rNode rN){

                        if(rN.hasLeftChild()){

                            cout << "My Left Child: ";
                            cout << rN.getLeftChild().get()->getData();
                            cout << endl;
                        }

                        if(
                                rN.hasLeftChild() 
                                    //&&
                                    ||
                                rN.hasRightChild()
                        ){
                                cout << rN.getData() << endl;
                        }

                        if(rN.hasRightChild()){

                            cout << "My Right Child: ";
                            cout << rN.getRightChild().get()->getData();
                            cout << endl;
                        }

                        if(rN.hasLeftChild()){
                            print_inorder(rN.getLeftChild().get()->getNode());
                        }

                        if(rN.hasRightChild()){
                            print_inorder(rN.getRightChild().get()->getNode());
                        }
                    };

                   print_inorder((*hierarchy.begin()).get()->getNode());

                break;
            }
        case traversal_order::POSTORDER:
            {
                //lambda 

                function<void(rNode)>print_postorder = [&] (rNode rN){

                    if(rN.hasLeftChild()){
                        
                        cout << "My Left Child: ";
                        cout << rN.getLeftChild().get()->getData();
                        cout << endl;
                    }
                    if(rN.hasRightChild()){

                        cout << "My Right Child: ";
                        cout << rN.getRightChild().get()->getData();
                        cout << endl;
                    }
                    if(
                            rN.hasLeftChild()
                                 //&&
                                ||
                            rN.hasRightChild()
                      ){
                        cout << rN.getData() << endl;
                    }

                    if(rN.hasLeftChild()){

                        print_postorder(rN.getLeftChild().get()->getNode());
                    }
                            
                    if(rN.hasRightChild()){

                        print_postorder(rN.getRightChild().get()->getNode());
                    }
                };

                print_postorder((*hierarchy.begin()).get()->getNode());
                break;
            }

    }

    return;
}

template<typename T1, typename T2> int tree<T1,T2>::getHeight(){

    auto countL = 0;
    auto countR = 0;

    auto tmpSp2Node = *hierarchy.begin();
    auto pN = tmpSp2Node.get(); 

    while(pN){

        if(pN->hasLeftChild()){

                countL++;
                pN = pN->getLeftChild().get();
        }
        else{
                
            pN = NULL;
        }

    }

    pN = tmpSp2Node.get();

        while(pN){

            if(pN->hasRightChild()){
                
                countR++;
                pN = pN->getRightChild().get();
            }
            else{
                    pN = NULL;
            }

        }

        return( countL > countR ? countL : countR);
}

template<typename T1, typename T2> void tree<T1,T2>::addNode(T1& rData, int pos){

    if(pos < 0 || pos > hierarchy.size() - 1){

        error_code e(error_code::BAD_NODE_POS);
        throw e;
    }

    auto iter = hierarchy.begin();

    if(0 != pos){

        iter = next(iter,pos); 
    }

    auto tmpSp2Node = make_shared<node<T1>>(rData);

    //say if pos is 2, insert() would insert 
    //the element at index 1, since vector
    //indexing starts at 0
    iter = hierarchy.insert(iter,tmpSp2Node); 

    renameNodes(iter);
    linkNodes();

    return;
}

template<typename T1, typename T2> void tree<T1,T2>::delNode(int pos){

    if(pos < 0 || pos > hierarchy.size() -1){

        error_code e = error_code::BAD_NODE_POS;

        throw e;
    }

    auto iter = hierarchy.begin();

    next(iter,pos);

    iter = hierarchy.erase(iter);

    renameNodes(iter);
    linkNodes();

    return;
}

template<typename T1, typename T2> void tree<T1,T2>::renameNodes(iter_sp2node_cont Itr){

    auto diff = distance(hierarchy.begin(),Itr);

    while(Itr != hierarchy.end()){
        string s = "I am Node ";
            s += to_string(diff);
        (*Itr).get()->setData(s);

        ++Itr;
        
        if(Itr == hierarchy.end()){

            break;
        }
        else{
                diff = distance(hierarchy.begin(),Itr);
        }
    }

    return;
}


#endif
