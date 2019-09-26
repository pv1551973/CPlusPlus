#include <array>
#include <cstddef>
#include <tuple>
#include <functional>
#include <iostream>
#ifdef DBG
#include "debug.hpp"
#endif

using std::array;
using std::size_t;
using std::tuple;
using std::make_tuple;
using std::get;//std::get(std::tuple)
using std::function;
using std::cout;
using std::endl;

#define ARRAY_SZ 4

enum struct direction{forward=0,backward};

class comparator{
    public:
        comparator(array<size_t, ARRAY_SZ>&, array<size_t, ARRAY_SZ>&);
        ~comparator();
        int get_least_index (direction);
    private:
        //A[index], B[index]
        array<tuple<size_t, size_t>, ARRAY_SZ> a;
};

comparator::comparator(array<size_t, ARRAY_SZ>& r1, array<size_t, ARRAY_SZ>& r2){
    for(auto index = 0; index < ARRAY_SZ; ++index){
        a[index] = make_tuple(r1[index], r2[index]);
    }

}

comparator::~comparator(){}

int comparator::get_least_index(direction d){


    size_t diff = 0;
    size_t index = 0;
    auto min_index = -1;
    //for reverse traversal
    auto max_index = -1;

    //Note: in the following function object, that recursively
    //invokes itself, the adopted algorithm to find the minimum
    //index considers only the two adjacent index positions in
    //one recursion; this is based on the idea that if it is possible
    //to return to the starting point in all recursions, then effectively
    //it should be possible to return to the first starting point as a 
    //cumulative effect.

    //r_i stands for retrieve_index
    function<void()>r_i = [&](){
        switch(d){
            case direction::backward:
                goto BACKWARD;
                break;
            default:
                goto FORWARD;
                break;
        }
BACKWARD:
        {
            //need to cast index to int to control the recursion
            //the for loop invoking this function object
            //is itself controlled by means of identical logic
            auto k = static_cast<int>(index);
            if(k >= 0){
             auto t = a[index];
             auto a_i = get<0>(t);
             auto b_i = get<1>(t);
             if(a_i >= b_i){
                 diff = a_i - b_i;
                 if(k > 0){
                     auto t = a[index - 1];
                     auto a_inxt = get<0>(t);
                     auto b_inxt = get<1>(t);
                     if(a_inxt >= b_inxt){
                         diff += a_inxt - b_inxt;
                         if(diff >= b_inxt){
                             if(-1 == max_index || static_cast<int>(index) > max_index){
                                 max_index = static_cast<int>(index);
                             }
                             //decrement index by 2 here
                             //as we have already covered two indices
                             index -= 2;
                             return(r_i());
                         }
                         else{
                             //decrement index by 2 here
                             //as we have already covered two indices
                             index -= 2;
                             max_index = -1;
                             return;
                         }
                     }
                     else if(a_inxt + diff > b_inxt){
                         diff -= b_inxt - a_inxt;
                         if(diff >= b_inxt){
                             if(-1 == max_index || static_cast<int>(index) > max_index){
                                 max_index = index;
                             }
                             //decrement index by 2 here
                             //as we have already covered two indices
                             index -= 2;
                             return(r_i());
                         }
                         else{
                             //decrement index by 2 here
                             //as we have already covered two indices
                             index -= 2;
                             max_index = -1;
                             return;
                         }
                     }
                 }//end of if(k > 0)
                 else{
                     //at the last stop
                     //can't go any further
                     //at this point, we check whether
                     //this is the largest value for index
                     //(which should also imply the only value.
                     //since index == 0), which would allow 
                     //for complete circuit; if max_index had been
                     //updated previously, this should not be 
                     //the case
                     if(k > max_index){
                         max_index = k;
                     }
                     return;
                 }
             }//end of if(a_i >= b_i)
             else if(b_i > a_i){
                 //there are two possibilities:
                 //either index is equal to a.size() - 1 or 
                 //index is lesser
                 //Note that since we are traversing backward,
                 //a.size() - 1 value for index indicates the
                 //first slot visited
                 if(a.size() - 1 == index){
                     //can't get to the next station
                     //assume here that max_index would be -1
                     return;
                 }
                 else{
                     if(diff){
                         if(diff + a_i >= b_i){
                             diff -= b_i - a_i;
                             if(diff >= b_i){
                                 if(-1 == max_index || static_cast<int>(index) > max_index){
                                     max_index = index;
                                 }
                                 //decrement index by 2 here
                                 //as we have already covered two indices
                                 index -= 2;
                                 return(r_i());
                             }
                         }
                     }
                     else{
                         //decrement index by 2 here
                         //as we have already covered two indices
                         index -= 2;
                         max_index = -1;
                         return;
                     }
                 }
             }
            }//end of if(k >= 0)
            else{
                return;
            }
        }//end of label BACKWARD
FORWARD:
        {
            if(index < a.size()){
             auto t = a[index];
             auto a_i = get<0>(t);
             auto b_i = get<1>(t);
             if(a_i >= b_i){
                 diff = a_i - b_i;
                 if(index < a.size() - 1){
                     auto t = a[index + 1];
                     auto a_inxt = get<0>(t);
                     auto b_inxt = get<1>(t);
                     if(a_inxt >= b_inxt){
                         diff += a_inxt - b_inxt;
                         if(diff >= b_inxt){
                             if(-1 == min_index || static_cast<int>(index) < min_index){
                                 min_index = index;
                             }
                             ++index;
                             return(r_i());
                         }
                         else{
                             min_index = -1;
                             return;
                         }
                     }
                     else if(a_inxt + diff > b_inxt){
                         diff -= b_inxt - a_inxt;
                         if(diff >= b_inxt){
                             if(-1 == min_index || static_cast<int>(index) < min_index){
                                 min_index = index;
                             }
                             ++index;
                             return(r_i());
                         }
                         else{
                             min_index = -1;
                             return;
                         }
                     }
                 }//end of if(index < a.size() - 1)
                 else{
                     //at the last stop
                     //can't go any further
                     if(diff >= b_i){
                         return;
                     }
                     else{
                         min_index = -1;
                         return;
                     }
                 }
             }//end of if(a_i >= b_i)
             else if(b_i > a_i){
                 //there are two possibilities:
                 //either index is 0 or index is not 0
                 if(0 == index){
                     //can't get to the next station
                     //assume here that min_index would be -1
                     return;
                 }
                 else{
                     if(diff){
                         if(diff + a_i >= b_i){
                             diff -= b_i - a_i;
                             if(diff >= b_i){
                                 if(-1 == min_index || static_cast<int>(index) < min_index){
                                     min_index = index;
                                 }
                                 ++index;
                                 return(r_i());
                             }
                         }
                     }
                     else{
                         min_index = -1;
                         return;
                     }
                 }
             }
            }//end of if(index < a.size())
            else{
                return;
            }
        }//end of label FORWARD
    };

    switch(d){
        case direction::backward:
            {
                index = a.size() - 1;
                //we need to use an int variable
                //as the loop counter to exercise
                //control using a negative value
                int counter = index;
                //the for loop below has to be synchronized
                //with the recursive calls to the function object
                //above, which update the value of index;
                //hence, when control returns to the for loop,
                //we decrement index and then
                //populate counter with the updated value
                //of index
                for(; counter >=0; counter = static_cast<int>(--index)){
                 r_i();
                 if(-1 == max_index){continue;}
                }//end of for loop
            }
            break;
        default:
            {
             for(; index <= a.size() - 1; ++index){
             r_i();
             if(-1 == min_index){continue;}
             }//end of for loop
            }
            break;
    }

    return (d == direction::backward) ? (max_index) : (min_index); 
}

int main (void){

    array<size_t,ARRAY_SZ> A = {3,1,3,1};
    array<size_t,ARRAY_SZ> B = {4,2,2,1};
    direction d = direction::backward;
    //direction d = direction::forward;

    comparator c(A,B);

    auto result = c.get_least_index(d);

    cout << result << endl;

    return 0;
}
