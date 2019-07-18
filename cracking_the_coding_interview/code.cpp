#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <cstdlib>
using std::vector;
using std::array;
using std::for_each;
using std::rand;
using std::cout;
using std::endl;

#define NUM_COLS 4
#define NUM_ROWS 3

#define MINVAL 0
#define MAXVAL 25

#define DBG_TRACE cout << "At line " << __LINE__ << endl;

vector<array<int,NUM_COLS>>matrix(NUM_ROWS);
void set_matrix(vector<array<int,NUM_COLS>>&);
void set_random_col2Zero(vector<array<int,NUM_COLS>>&);
void reset_matrix(vector<array<int,NUM_COLS>>&);
void display_matrix(vector<array<int,NUM_COLS>>&);

int main(void){

	set_matrix(matrix);
	display_matrix(matrix);

	set_random_col2Zero(matrix);
	display_matrix(matrix);

	reset_matrix(matrix);
	display_matrix(matrix);

	return 0;
}

void set_matrix(vector<array<int,NUM_COLS>>& matrix){

	for_each(matrix.begin(), matrix.end(), [](array<int, NUM_COLS>& a){ 
			for(size_t i = 0; i < a.max_size(); ++i){
				a[i] = 	MINVAL + ( rand() % ( MAXVAL - MINVAL + 1 ) );
			}
		}
		);
	return;
}

void set_random_col2Zero(vector<array<int,NUM_COLS>>& matrix){
	auto row_col_min = 0;
	auto col_max = 3;
	auto row_max = 2;

	auto row = row_col_min + ( rand() % ( row_max - row_col_min + 1 ) );
	auto col = row_col_min + ( rand() % ( col_max - row_col_min + 1 ) ); 

	matrix[row][col] = 0;

	return;
}

void reset_matrix(vector<array<int,NUM_COLS>>& matrix)
{
	struct index{
		int row;
		int col;
	}idx;
	vector<index>v_idx;
	auto count = 0;
	for_each(matrix.begin(), matrix.end(), [&](array<int, NUM_COLS>& a){
			for(size_t i = 0; i < a.max_size(); ++i){
				if(0 == a[i]){
					idx.row = count;
					idx.col = i;
					v_idx.push_back(idx);
				}
			}
			
			++count;
		}
		);

	for(auto idx : v_idx){
		DBG_TRACE
		auto iter = matrix.begin();
		auto row = 0;
		while(iter != matrix.end()){
			if(row == idx.row){
				(*iter).fill(0);

			}
			else{
				auto col = 0;
				auto a_iter = (*iter).begin();//array_iter
				while(col != idx.col){
					++a_iter;
					++col;
				}
				*a_iter = 0;
			}
			++row;
			++iter;
		}
	}
	return;
}

void display_matrix(vector<array<int,NUM_COLS>>& matrix){

	auto row = 0;
	for(auto a : matrix){
		cout <<  "row " << row << endl;
		cout << "------------------" << endl;
		for(auto i : a){
			cout << i << " ";
		}
		cout << endl;
		++row;
	}
	return;
}
