
#include "bt.hpp"
#include<array>
#include<string>
#include<exception>
using std::array;
//using std::string;
//using std::to_string;
using std::exception;

#define LIMIT 25

int main(){

    try{

            array<string,LIMIT> A;
            auto count = 1;

            while(count <= A.size()){

                string s = "I am Node ";
                //s += to_string(count);
                s += to_string(count - 1);
                A[count - 1] = s;
                ++count;
            }

            tree<string, decltype(A)> a_tree(A,A.size());
            //a_tree.traverse_tree(traversal_order::PREORDER);
            //a_tree.traverse_tree(traversal_order::INORDER);
            //a_tree.traverse_tree(traversal_order::POSTORDER);
    
            //auto height = a_tree.getHeight();

            //cout <<"The height of the BT is " << height << endl;

            string s = "I am the Newly Inserted Node";

            //auto pos = a_tree.getHeight()/2;
            //auto pos = 1;
            auto pos = 7;
            //original pattern:
            //0->1->2
            //1->3->4
            //2->5->6
            //3->7->8
            //4->9->10
            //5->11->12
            //and so on...
            //expected output pattern:
            //0->n->1
            //n->2->3
            //1->4->5
            //2->6->7
            //3->8->9
            //4->10->11
            //5->12->13
            //and so on...

            //auto pos = 4;
            //original pattern:
            //0->1->2
            //1->3->4
            //2->5->6
            //3->7->8
            //4->9->10
            //5->11->12
            //and so on...
            //expected output pattern:
            //0->1->2
            //1->n->4
            //2->5->6
            //3->7->8
            //4->9->10
            //5->11->12
            //a_tree.addNode(s,pos);
            //pos = 4;
            //a_tree.addNode(s,pos);
            //pos = 9;
            a_tree.addNode(s,pos);

            pos = 1;
            a_tree.addNode(s,pos);

            pos = 13;
            a_tree.addNode(s,pos);
            
            pos = 0;
            a_tree.addNode(s,pos);

            pos = 5;
            a_tree.delNode(pos);

            pos = 0;
            a_tree.delNode(pos);

            //a_tree.traverse_tree(traversal_order::PREORDER);
            //a_tree.traverse_tree(traversal_order::INORDER);
            a_tree.traverse_tree(traversal_order::POSTORDER);
     }
     catch(error_code e){
         
         cout << "Exception error_code " << as_integer(e) << " caught" << endl;
     }
     catch(exception e){

         cout << "Standard Exception " << e.what() << " caught" << endl;
     }
     catch(...){

         cout << "Unknown exception caught" << endl;
     }

    return 0;
}
