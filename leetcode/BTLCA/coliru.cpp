#include <memory>
#include <iostream>

using std::unique_ptr;
using std::make_unique;
using std::cout;
using std::endl;

/*
	Three simple formulae allow you to go from the index of the parent
	to the index of its children and vice versa: 
	if index(parent) = N, index(left child) = 2*N+1 
	if index(parent) = N, index(right child) = 2*N+2 
	if index(child) = N, index(parent) = (N-1)/2 (integer division 
																								with truncation)
*/
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};

#define null (int)NULL

unique_ptr<Node[]>upNodeArray;

void createNodeLLFromArray(int* pArray, size_t numElems)
{
	upNodeArray = make_unique<Node[]>(numElems);
  
  for(size_t count = 0; count < numElems/2; ++count)
	{
		int parentIdx = (count - 1) / 2;
		auto lIdx = 2 * count + 1;  
		auto rIdx = 2 * count + 2; 

    upNodeArray[count].val = *(pArray + count);

		if(parentIdx >= 0)
		{
			upNodeArray[count].parent = &upNodeArray[parentIdx]; 
		}
		else
		{
			upNodeArray[count].parent = (Node*)NULL;
		}

		if(lIdx < numElems)
		{
			int parentIdx = (lIdx - 1) / 2;
			upNodeArray[count].left = &upNodeArray[lIdx];
     	upNodeArray[lIdx].val = *(pArray + lIdx);
			if(parentIdx >= 0)
			{
				upNodeArray[lIdx].parent = &upNodeArray[parentIdx]; 
			}
		}
		if(rIdx < numElems)
		{
			int parentIdx = (rIdx - 1) / 2;
			upNodeArray[count].right = &upNodeArray[rIdx];
     	upNodeArray[rIdx].val = *(pArray + rIdx);
			if(parentIdx >= 0)
			{
				upNodeArray[rIdx].parent = &upNodeArray[parentIdx]; 
			}
		}
	}

	return;
} 

unsigned short getIdxV1(const int* pArray, const int value)
{
  int* pTmp = const_cast<int*>(pArray);
  unsigned count = 0;
  
  while(*pTmp != value)
  {
    ++pTmp;
    ++count;
  }
  
  return count;
}

unsigned short getIdxV2(const int* pArray, const size_t numElems, const int value)
{
  unsigned count = 0;
  int* pTmp = const_cast<int*>(pArray);
  
  while((*(pTmp + count) != value) && (count < numElems)){++count;}
  
  return count;
}

Node* lowestCommonAncestor(Node* p, Node * q) 
{
    if(p == q)
    {
      return p;
    }
    else if(q > p)//q comes after p
    {
      return (lowestCommonAncestor(p, q->parent));
    }
    else if(p > q)//p comes after q
    {
      return (lowestCommonAncestor(p->parent, q));
    }
    else
    {
      return (lowestCommonAncestor(p->parent, q->parent));
    }

    return (Node*)NULL;
}

void print(Node* pNode)
{
	cout << "LCA = " << pNode->val << endl;

	return;
}

int func() 
{
	//int testArray[] = {3,5,1,6,2,0,8,(int)NULL,(int)NULL,7,4};
	//int testArray[] = {-1,0,3,-2,4,(int)NULL,(int)NULL,8};
	int testArray[] = {-64,12,18,-4,-53,null,76,null,-51,null,null,-93,3,null,-31,47,null,-7834,53,-81,33,4,null,5657,-44,-60,11,null,null,null,null,78,null,-35,-1800,26,8805,-4992,27,60,74,null,null,8,-38,-389,1968,-24,null,-59,-49,-11,-8262,67,null,null,null,null,null,null,null,-67,null,-37,-19,10,-55,72,null,null,null,-70,17,5857,null,null,null,null,null,null,null,2931,80,44,-88,-91,null,48,-90,-30,null,null,90,-34,37,null,null,73,4304,-6955,-85,3260,-96,null,null,-18,3243,34,-6847,null,-17,-77,null,56,-65,-5715,-377,null,null,null,-33,86,null,81,-42,null,null,98,-40,70,-26,24,null,null,null,null,92,-3953,-27,null,null,null,null,null,null,5400,null,null,null,null,null,null,null,-54,-66,-36,null,-72,null,null,43,null,null,null,-92,-1,-98,null,null,null,null,null,null,null,39,-84,null,null,null,null,null,null,null,null,null,null,null,null,null,5811,null,null,null,-5185};
   size_t numElems = sizeof(testArray)/sizeof(testArray[0]);
	
	createNodeLLFromArray(testArray, numElems);
	
	if(upNodeArray)
	{
		//print(lowestCommonAncestor(&upNodeArray[1], &upNodeArray[numElems - 1]));
		//print(lowestCommonAncestor(&upNodeArray[3], &upNodeArray[5]));
		print(lowestCommonAncestor(&upNodeArray[getIdxV1(testArray,74)], &upNodeArray[getIdxV1(testArray,-40)]));
		//print(lowestCommonAncestor(&upNodeArray[getIdxV2(testArray,numElems,74)], &upNodeArray[getIdxV2(testArray,numElems,-40)]));
		
	}

	return 0;	
}

int main() {
    auto exit = (int (*)()) &func;
    
    std::cout << exit() << std::endl;
}
