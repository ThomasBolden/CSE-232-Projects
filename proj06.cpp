/*

Author:		Thomas Bolden
Project:	Project 06
Date:		October 24, 2016
Section:	001

*/

#include <iostream>
using std::cin; using std::cout; using std::getline; using std::endl;

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <cstdlib>
#include <algorithm>
using std::find;

const bool dead = false; // I guess I didn't really need these but 
const bool alive = true; // they could be useful to understand code

int m; // these need to be available globally because referenced in
int n; // check_cell() but declared in main()

// 1 is alive, 0 is dead
bool check_cell(vector<string> b, int i, int j){
	if(b[i % m][j % n] == '#'){return alive;} // modulo to support toroidal board
	else{return dead;}
}

//	there are eight neighbors to check, and its done in this order:
//				1 2 3
//				8 0 4
//				7 6 5
int add_neighbors(vector<string> b, int i, int j){
	if(i == 0){i = m;} // because can't get negative index
	if(j == 0){j = n;} // of a vector (or string I think?)
	int living_cells = 0;
	if(check_cell(b,i-1,j-1)){living_cells += 1;}
	if(check_cell(b,i-1,j)){living_cells += 1;}
	if(check_cell(b,i-1,j+1)){living_cells += 1;}
	if(check_cell(b,i,j+1)){living_cells += 1;}
	if(check_cell(b,i+1,j+1)){living_cells += 1;}
	if(check_cell(b,i+1,j)){living_cells += 1;}
	if(check_cell(b,i+1,j-1)){living_cells += 1;}
	if(check_cell(b,i,j-1)){living_cells += 1;}
	return living_cells;
}

// loops through array to find all living cells
int count_living_cells(vector<string> b){
	int living_total = 0;
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			if(b[i][j] == '#'){living_total += 1;}
		}
	}
	return living_total;
}

// takes a board and updates it for the next generation
vector<string> next_gen(vector<string> old_board, vector<int> br, vector<int> sr){
	vector<string> next_board = old_board;
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			int n = add_neighbors(old_board, i, j);
			if((find(br.begin(), br.end(), n) != br.end()) && (old_board[i][j] == '.')){
				next_board[i][j] = '#';
			}// ^ a cell is born
			else if((find(sr.begin(), sr.end(), n) != sr.end()) && (old_board[i][j] == '#')){
				next_board[i][j] = '#';
			}// ^ a cell survives
			else{
				next_board[i][j] = '.';
			}// ^ a cell dies
		}
	}
	return next_board;
}

//
//	Conway's Game of life with custom rules
//	
//	Input:	B##/S## <- 	a string; representing the rules of the game.
//						a string of integers following 'B' and before '/'
//						representing the exact number of neighbors a cell
//						needs to be born
//						a string of integers following 'S'
//						represent the exact number of neighbors a cell
//						needs to survive / not die
//
//			iter 	<-	an integer; the number of iterations/ generations the
//						game will progress through before terminating
//
//			m, n    <-	two integers; the dimensions of the board (rows, columns)
//
//			strings <-	m strings; the board layout. 
//						'#' is a living cell, '.' is a dead cell
//
//	Output:	cells 	<-	the total number of living cells remaining at 
//						the end of game
//
int main(){

	string rules; // Input: B##/S## 
				  // neighbors to birth new cell / neighbors for survival

	//int cell_birth, cell_death;
	int iterations, rows, columns;

	getline(cin, rules); // extract two numbers from this string
	cin >> iterations; // no manipulations needed
	cin >> rows >> columns; // no manipulations needed
	m = rows;
	n = columns;

    vector<string> board;		// the board is declared as a vector
						  		// of strings -- an m x n martix.
						  		// board[i % m][j % n] returns the element
						  		// in the i-th row and j-th column

	vector<string> updated;		// board used to replace current board

	string b_i; // string is a row

	// fills up the initial board
	for(int i = 0; i < rows; i++){
		cin >> b_i;
        board.push_back(b_i);
		b_i = "";
	}

	// a couple of vectors for the rules
	vector<int> birth_rules;
    vector<int> survive_rules;

    // fill the vectors with appropriate stuff
	int s = rules.find('S');
	for(auto ch : rules.substr(1,s-2)){
		birth_rules.push_back(ch - '0');
	}
    rules.erase(0,s+1);
    for(auto ar : rules){
        survive_rules.push_back(ar - '0');
    }

	// for loop that runs the game for specified number of iterations
	for(int iter = 0; iter < iterations; iter++){
		updated = next_gen(board, birth_rules, survive_rules);
		board = updated;
		/* // un-comment for board display. used for debug but not required output
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				cout << board[i][j];
			}
			cout << "\t";
			for(int j = 0; j < n; j++){
				cout << add_neighbors(board, i, j);
			}
			cout << endl;
		}
		*/
	}

	// and if its all working correctly this should be the correct output:
	cout << count_living_cells(board) << endl;	

	return 0;

}