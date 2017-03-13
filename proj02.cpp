/*

Author:		Thomas Bolden
Project:	Project 02
Date:		September 19, 2016
Section:	001

*/

#include <iostream>
#include <iomanip>
#include <cmath>

/*
Function to calculate the GL series estimating pi
The Gregory-Leibniz series is: 
		\pi = 4 \sum_{n=0}^\infty \frac{(-1)^n}{2n+1}
*/
void calc_GL_pi(float epsilon){

	long iter = 0;
	double GL_pi = 0.0;
	double GL_pi_0 = epsilon;

	// self explanitory, but do until the term is less than epsilon
	// also check to make sure epsilon isnt zero because it would break
	while((std::fabs(GL_pi_0) >= epsilon) && (epsilon != 0.0)){

		GL_pi_0 = 4.0*std::pow(-1.0, iter) / (2.0*iter + 1.0);
		GL_pi += GL_pi_0;
		iter++;

	}

	std::cout << std::fixed << std::setprecision(12) << GL_pi;
	std::cout << " " << iter << std::endl;

}

/*
The Nilakantha series is: 
		\pi = 3 + 4 \sum_{n=0}^\infty \frac{(-1)^n}{(2n+2)(2n+3)(2n+4)}
*/
void calc_N_pi(float epsilon) {

	long iter = 0;
	double N_pi = 0.0;
	double N_pi_0 = epsilon;

	while((std::fabs(N_pi_0) >= epsilon) && (epsilon != 0.0)){
		
		N_pi_0 = 4.0*std::pow(-1.0, iter)/((2.0*iter + 2.0)*(2.0*iter + 3.0)*(2.0*iter + 4.0));
		N_pi += N_pi_0;
		iter++;

	}

	if(epsilon != 0){N_pi += 3;}

	std::cout << std::fixed << std::setprecision(12) << N_pi;
	std::cout << " " << iter << std::endl;

}

int main(){

	float epsilon;

	std::cin >> epsilon;

	calc_GL_pi(epsilon);
	calc_N_pi(epsilon);

	return 0;

}