/*

Author:		Thomas Bolden
Project:	Project 01
Date:		September 12, 2016
Section:	001

*/

#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <cmath>

// Functions to convert between radians and degrees
// These functions use the relationship:
// degrees/radians = 180/pi

double convert_to_radians(double dangle){
	double rangle = dangle * M_PI / 180.0;
	return rangle;
}
double convert_to_degrees(double rangle){
	double dangle = rangle * 180.0 / M_PI;
	return dangle;
}

int main(){
	double sidea, angleA, sideb, angleB, sidec, angleC; // initializing variables
	std::cin >> sideb >> angleA >> sidec; // reading in SAS (b, A, c)
	                                      // can be from a file or command line

	angleA = convert_to_radians(angleA); // because cos & sin needs radians
	sidea = std::sqrt(sideb*sideb + sidec*sidec - 2.0*sideb*sidec*cos(angleA));

	// following if/else is because law of sines needs the smaller side for some reason
	if (sideb < sidec){
		angleB = asin(sin(angleA)*sideb/sidea);
		angleC = M_PI- angleA - angleB;
	}
	else{
		angleC = asin(sin(angleA)*sidec/sidea);
		angleB = M_PI - angleA - angleC;
	}

	angleA = convert_to_degrees(angleA);
	angleB = convert_to_degrees(angleB);
	angleC = convert_to_degrees(angleC);

	std::cout << std::fixed << std::setprecision(2) << sidea << std::endl;
	std::cout << std::fixed << std::setprecision(2) << angleB << std::endl;
	std::cout << std::fixed << std::setprecision(2) << angleC << std::endl;

	return 0;
}