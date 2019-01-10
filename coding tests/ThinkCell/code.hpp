#ifndef CODE_HPP
#define CODE_HPP
#include<assert.h>
#include<map>
#include<limits>
#include<map>
#include<utility>
#include<algorithm>
#include<iterator>
#include<type_traits>
#include<iostream>
using std::map;
using std::make_pair;
using std::pair;
using std::numeric_limits;
using std::equal_range;
using std::distance;
using std::next;
using std::cout;
using std::endl;

#define LINE (cout << "At line # " << __LINE__ << endl);
#define DBG_PRINT(...) (cout << __VA_ARGS__<< endl);

//caveats:
//the type K is copyable, assignable
//can be compared using < operator
//is bounded below with the lowest value
//being std::numeric_limits<K>::lowest()
//does not implement any other operations
//
//the type V is copyable, assignable
//can be compared using == operator
//does not implement any other operations
//
//each key-value-pair (k,v) in the m_map
//member means that the value v is associated
//to the interval from k (inclusive) to the next
//key (exclusive)
//the representation in m_map must be 
//canonical, that is, consecutive map 
//entries must not have the same value

enum class error{BAD_RANGE, INVALID_RANGE};

//function template to
//convert an enumeration
//class type to its corresponding
//integral type for the sake of
//printing

 template <typename Enumeration>
 auto as_integer(Enumeration const value)->typename std::               underlying_type<Enumeration>::type{
  
  return static_cast<typename std::underlying_type<Enumeration>::         type>(value);
  
  }


template<class K, class V>
class interval_map{

    friend void IntervalMapTest();

    private:

    map<K,V> m_map;

    private:
    bool did_assign;
    K did_replace;

    public:

    interval_map(V const&);

    public:

    void assign(K const& keyBegin, K const& keyEnd, V const& val);

    public:

    void replace(K const& key, V const& val);

    public:

    V const& operator [](K const& key) const;

    public:

    struct comp;

    public:
    void display(void);

};

template<class K, class V> struct interval_map<K,V>::comp{

    bool operator()(pair<K const&,V const&> p, V const& v) const{

        return(p.second < v);
    }

    bool operator()(V const& v, pair<K const&, V const&> p) const{

        return(v < p.second);

    }

};


template<class K, class V> interval_map<K,V>::interval_map(V const& val){

    m_map.insert(m_map.begin(), make_pair(numeric_limits<K>::lowest(), val));

    did_assign = 1;
    did_replace = numeric_limits<K>::lowest();

}

template<class K, class V> V const& interval_map<K,V>::operator [] (K const& key) const{

    return (--m_map.upper_bound(key))->second;
}

template<class K, class V> void interval_map<K,V>::assign(K const& keyBegin, K const& keyEnd, V const& val){

       //LINE
       //DBG_PRINT("keyBegin:" << keyBegin)
       //DBG_PRINT("keyEnd:" << keyEnd)


        if(
                keyBegin < 0 
          ){

            //LINE

                did_assign = 0;

                error e = error::BAD_RANGE;
                throw(e);

        }

       LINE

        auto begin = m_map.find(keyBegin); 

        if(begin == m_map.end()){

            LINE

            did_assign = 1;

            m_map.insert(make_pair(keyBegin,val));
        }
        else{

                LINE

                auto free = const_cast<K&>(keyBegin);
                bool flag = 1;

LOOP_4_FREE_POS:
                LINE

                do{

                    begin = m_map.find(++free);

                }while((flag = (begin != m_map.end() && free != keyEnd)));

                if(!flag){

                    LINE

                    if(free == keyEnd){

                        LINE

                        goto THROW_EXCEPTION;
                    }
                    else if(free == keyEnd - 1){

                        LINE

                        if(m_map[free -1] != val){

                            LINE

                            did_assign = 1;
                            
                            m_map.insert(make_pair(free,val));
                        }
                        else{

                                LINE

                                goto THROW_EXCEPTION;
                        }
                    }
                    else{

                            LINE

                            if((m_map[free -1] != val) && 
                                    (m_map[free + 1] != val)
                                    ){

                                        LINE
    
                                        did_assign = 1;

                                          m_map.insert(make_pair(free, val));
                                }
                                else{

                                        LINE

                                        goto LOOP_4_FREE_POS;
                                }
                        }

                    }

            }

        if(did_assign){

            LINE

            return;
        }

        LINE

        THROW_EXCEPTION:
                        error  e = error::INVALID_RANGE;
                        throw e;
    }

template<class K, class V> void interval_map<K,V>::replace(K const& key, V const& val){

    auto index = key;
    auto it = m_map.end();

    if(key == 0){

        LINE

        if(m_map[index + 1] != val){

            LINE

            did_replace = index;

            //m_map.insert(make_pair(key,val));

            it = m_map.find(index);

            it->second = val;
            
        }
        else{

                LINE

                error e = error::INVALID_RANGE;

                throw e;
        }

    }
    else if(key == next(m_map.end(), - 1)->first){

        LINE

        if(m_map[index - 1] != val){

            LINE

            did_replace = index;

            //m_map.insert(make_pair(key,val));

            it = m_map.find(index);

            it->second = val;

        }
        else{

                LINE

                error e = error::INVALID_RANGE;
                
                throw e;
        }
    }
    else{

            LINE

            if(
                    (m_map[index - 1] != val)
                                
                                &&

                    (m_map[index + 1] != val)
              ){

                    LINE
                    
                    //m_map.insert(make_pair(key,val));

                    it = m_map.find(index);

                    it->second = val;
            }
            else{

                    LINE

                    error e = error::INVALID_RANGE;

                    throw e; 
            }
    }



}


template<class K, class V> void interval_map<K,V>::display(){

    for(auto i : m_map){

        cout << i.first;

        cout << " ";

        cout << i.second;

        cout << endl;

    }

}

//friend function

void IntervalMapTest(){

    LINE

    interval_map<unsigned int, char> iMap('A');

    LINE
    
    iMap.assign(0,2,'B');

    LINE

    iMap.assign(0,3,'C');

    LINE

    iMap.assign(0,4,'D');

    LINE

    iMap.assign(0,5,'E');

    //LINE

    //iMap.assign(2,5,'C');

    LINE

    iMap.assign(2,6,'A');

    LINE

    iMap.assign(4,7,'F');

    //LINE

    //iMap.assign(1,5,'G');

    LINE

    iMap.replace(1, 'G');

    iMap.display();

    return;
}

#endif
