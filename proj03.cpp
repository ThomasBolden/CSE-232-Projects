/*

Author:		Thomas Bolden
Project:	Project 03
Date:		September 26, 2016
Section:	001

*/

#include <iostream>
#include <iomanip>
#include <cmath>

using std::cout; using std::cin; using std::endl;


// funtion takes a long and returns the sum of its unique divisors
long sum_divisors(long num){

	long sum = 0;

	//for(int i = 1; i <= num/; i++){
	for(int i = 1; i <= sqrt(num); i++){ // checks integers below the square root so no repeats
										 // mainly here for small time save
		if((num % i) == 0){ // if input long is multiple of current index, then add to sum
			sum += i;
			if((num / i) != i){sum += num/i;} // check so square roots only get added once
		}

	}
	
	return sum;

}

// function taking an int k and a long and returns whether or not the long is k-perfect
// for n to be k-perfect, (k*n == sum_divisors(n)) must be true
bool is_k_perfect(int k, long num){

	bool b = false; // initializing a boolean 

	if(num == 0){return b;} // 0 is not perfect, but would pass following test
							// so hard exclusion here prevents that

	long k_times_num = k*num; 

	if(k_times_num == sum_divisors(num)){b = true;} // if num is k-perfect, set the
													// boolean to true and return it

	return b;

}

// function to check whether the number in range [first, last] are k-perfect
void check_range(int k, int first, int last){

	bool b = false;
	for(int i = first; i <= last; i++){ // loop through every number 
										// between first and last
		b = is_k_perfect(k,i);
		if(b == true){
			cout << i << " ";
		}
	}

}

int main (){

    long first, last, num, k;

    cin >> num;
    cout << sum_divisors(num) << endl;

    cin >> k;
    cout << std::boolalpha << is_k_perfect(k,num) << endl;

    cin >> first >> last;
    check_range(k,first,last);
    cout << endl;

    return 0;

}