/*

Author:		Thomas Bolden
Project:	Project 04
Date:		October 3, 2016
Section:	001

*/

#include <iostream>
#include <iomanip>
#include <string>
//#include <cstdlib>
#include <algorithm>
#include <cmath>

using std::cout; using std::cin; using std::endl; using std::boolalpha;
using std::string; using std::to_string; using std::stol; 
using std::reverse;

// basic function that takes a long and returns the long reversed
long rev_num(long n){

	string s = to_string(n); // string.h function that converts long to string
	reverse(s.begin(), s.end()); // algorithm.h function that reverses a string

	return stol(s); // string.h function that converts string to long

}

// func that calls rev_num to check if a long is the same forward and reversed
bool is_palindrome(long n){

	if(n == rev_num(n)){return true;}
	else{return false;}

}

// function taking 
bool check_args(long limit, long &first, long &second){

	if(second > first){
		long temporary_first = first;
		first = second;
		second = temporary_first;
	}// swap first & second to make sure first <= second

	if((limit < 1) || (first < 1)){return false;} // logical or in cpp is ||
	else{return true;}

}

bool check_lychrel(long n, long limit){

	long i = 0;
	while(i < limit){
		if(is_palindrome(n)){return false;}
		else{n += rev_num(n);}
		i++;
	}
	return true;

}

// I REALLY DO NOT UNDERSTAND WHY THIS IS NOT WORKING !!!!!!
// this really makes sense to me but the last line output is always 0 0 0
// which seems to imply me for loop is not activating but it should since 
// it does not depend on any conditions to be true or false
long check_range(long start, long end, long limit, long &natural_cnt, long &pal_cnt){

	long lychrel_count = 0;
	for(long i = start; i <= end; i++){
		cout << i << endl;
		if(is_palindrome(i)){natural_cnt = natural_cnt + 1;}
		if(check_lychrel(i,limit)){pal_cnt = pal_cnt + 1;}
		else{lychrel_count = lychrel_count + 1;}
	}
	return lychrel_count;

}

int main(){

	cout << boolalpha;

    long num, limit, start, end;
    long natural_cnt=0, pal_cnt=0, lychrel_cnt = 0;
        
    cin >> num;
    cout << rev_num(num)<<endl;

    cin >> num;
    cout << is_palindrome(num)<<endl;

    cin >> num >> limit;
    cout << check_lychrel(num,limit)<< endl;

    cin >> start >> end >> limit;

    if (check_args(limit, start, end)){    
      lychrel_cnt = check_range(start, end, limit, natural_cnt, pal_cnt);
      cout << lychrel_cnt << " " << natural_cnt << " " << pal_cnt << endl;
    }
    else cout << "error" << endl;

	return 0;

}