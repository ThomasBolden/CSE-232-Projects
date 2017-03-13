#include <iostream>
using std::cout; using std::cin; using std::endl;
using std::ostream;

#include <vector>
using std::vector;

#include <string>
using std::string; using std::stod; using std::stol; using std::to_string;

#include <map>
using std::map; 

#include <utility>
using std::pair;

#include <iterator>
using std::ostream_iterator; using std::back_inserter; using std::prev;

#include <sstream>
using std::ostringstream; using std::istringstream;

#include <algorithm>
using std::copy; using std::transform; using std::reverse; using std::plus;

#include <cmath>
using std::abs;

#include <limits>

//  Since there are a great deal of members in this class, I will explain
//  them all here. Specific lines that need comments will still have them.
// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//
//  Polynomial Class
//      .
//      .
//  
//  private:
//      long    highest_power_      this is one higher than the highest power
//                                  term of the polynomial, ie the size of the 
//                                  vector containing the coefficients
//      vector  coefficients_       a vector of longs containing the coefficients
//                                  in front of each polynomial term
//      map     values_             a map from double->double that maps x-values
//                                  to their corresponding y-values by plugging 
//                                  the x-value into the polynomial
//
//  public:
//      void    set_table           makes the map by evaluating the polynomial
//      void    process_string      turns the input string into a polynomial
//      double  eval                there are three things this function does:
//                                      if the value passed is already a key
//                                      in the map, return its value
//                                      else if it is in the range [x0,x1],
//                                      return the interpolated value
//                                      else evaluate the polynomial at val
//      double  full_eval           returns exact value of the polynomial at the 
//                                  double passd
//      string  dump_table          prints the map
//      friend  <<                  overloads the << operator to print the polynomial
//      friend  +                   overloads the + operator to add the vectors of 
//                                  two polynomials together and create a new polynomial
//                                  from that result
//
// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

const string x_to_the = "x**"; // this is pointless but w/e

class Polynomial{
private:
    long highest_power_;
    vector<long> coefficients_;
    map<double, double> values_;

public:
    Polynomial()=default;
    Polynomial(string s, long samp=10, double x0=0.0, double x1=1.0);
    Polynomial(vector<long>& v, long samp=10, double x0=0.0, double x1=1.0);
    void set_table(size_t samples, double x0, double x1);
    void process_string(string s, char delim=' ');
    double eval(double);
    double full_eval(double);
    string dump_table();
    friend ostream& operator<<(ostream&, const Polynomial& p);
    friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
};

// DONE
Polynomial::Polynomial(string s, long samp, double x0, double x1){
    // process string to get polynomial coefficients and highest power
    process_string(s);
    // take samp samples on interval [x0, x1] and fill map with them
    set_table(samp, x0, x1);
}

// DONE
Polynomial::Polynomial(vector<long>& v, long samp, double x0, double x1){
    coefficients_ = v;
    highest_power_ = coefficients_.size();
    //set_table(samp, x0, x1);
}

// DONE
void Polynomial::set_table(size_t samples, double x0, double x1){
    values_.clear();
    double dx = (x1 - x0) / (samples - 1);
    //cout << "dx: " << dx;
    for(double xcurr = x0; xcurr <= x1; xcurr += dx){ // loops over interval
        values_[xcurr] = 0.0;
        for(long i = 0; i <= highest_power_; i += 1){
            values_[xcurr] += coefficients_[i]*pow(xcurr,i);
        }
    }
}

// DONE
void Polynomial::process_string(string s, char delim){
    string temp_coeff;
    for(auto ch : s){
        if(ch != delim){
            temp_coeff += ch;
        }
        else{
            coefficients_.push_back(stol(temp_coeff));
            temp_coeff = "";
        }
    }
    coefficients_.push_back(stol(temp_coeff));
    reverse(coefficients_.begin(), coefficients_.end());
    highest_power_ = coefficients_.size();
}

// DONE
double Polynomial::eval(double val){
    if      (values_.find(val) != values_.end()){
        return values_[val];
    }
    // linear interpolation below.
    // equation is: y = y0 + (x-x0)*((y1-y0)/(x1-x0))
    else if (val >= values_.begin()->first && val <= values_.rbegin()->first){
        double ya, yb, xa, xb;
        auto itr1 = values_.lower_bound(val); // first key bigger than val
        auto itr0 = prev(itr1,1); // key before the one above
        ya = itr1->second;
        yb = itr0->second;
        xa = itr1->first;
        xb = itr0->first;
        return ya + (val - xa) * ((yb - ya) / (xb - xa));
    }
    else{
        return full_eval(val);
    }
}

// DONE ?
double Polynomial::full_eval(double val){
    double value = 0.0;
    for(long i = 0; i <= highest_power_; i += 1){
        value += coefficients_[i]*pow(val,i);
    }
    return value;
}

// DONE
string Polynomial::dump_table(){
    string table;
    for (const auto &p : values_) {
        table += "[" + to_string(p.first) + "] = " + to_string(p.second) + '\n';
    }
    return table;
}

// DONE
ostream& operator << (ostream& os, const Polynomial& p){
    string polynom;
    vector<long> coef = p.coefficients_;
    reverse(coef.begin(), coef.end());
    polynom += to_string(coef[0]) + x_to_the + to_string(p.highest_power_ - 1);
    for(long j = 1; j < p.highest_power_; j++){
        if(coef[j] > 0){
            polynom += " + ";
            polynom += to_string(coef[j]);
            if(j < p.highest_power_ - 2){
                polynom += x_to_the + to_string(p.highest_power_-1-j);
            }
            else{
                polynom += "x";
            }
        }
        else if(coef[j] < 0){
            polynom += " - ";
            polynom += to_string(abs(coef[j]));
            if(j < p.highest_power_ - 2){
                polynom += x_to_the + to_string(p.highest_power_-1-j);
            }
            else{
                polynom += "x";
            }
        }
    }
    polynom.pop_back();
    os << polynom;
    return os;
}

// DONE
Polynomial operator + (const Polynomial& p1, const Polynomial& p2){
    vector<long> return_poly_vec = p1.coefficients_;
    for(long place = 0; place < p2.highest_power_; place++){
        return_poly_vec[place] += p2.coefficients_[place];
    }
    Polynomial return_poly(return_poly_vec);
    return return_poly;
}

int main(){
    size_t samples;
    double x0, x1, test_val;
    string poly;

    cin >> samples >> x0 >> x1 >> test_val;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    getline(cin, poly);
    Polynomial p1(poly, samples, x0, x1);
    // cout << p1.dump_table() << endl;
    cout << p1 << endl;
    cout << p1.eval(test_val) << endl;
    cout << p1.full_eval(test_val) << endl;
    cout << p1.eval(x1) << endl;
    cout << p1.eval(x1 + 1) << endl;

    getline(cin, poly);
    Polynomial p2(poly, samples, x0, x1);
    Polynomial p = p1 + p2;
    p.set_table(samples, x0, x1);
    // cout << p.dump_table() << endl;
    cout << p << endl;  
    cout << p.eval(test_val) << endl;
    cout << p.full_eval(test_val) << endl;
    cout << p.eval(x0) << endl;
    cout << p.eval(x0 - 1) << endl;
}