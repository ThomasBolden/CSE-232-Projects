#include <iostream>
using std::cout; using std::cin; using std::endl;

#include <iomanip>

#include <string>
using std::string; using std::to_string; using std::stoi;

#include <vector>
using std::vector;

#include <algorithm>
using std::reverse; using std::transform; using std::count_if;

#include <cmath>
using std::pow;

#include <iterator>
using std::back_inserter;

// returns the lower case version of the input string s -- VERY trivial
string lower_case(string s){

    string temp_string = s;
    transform(temp_string.begin(), temp_string.end(), temp_string.begin(), tolower);
    return temp_string;

}

// brute force convert character to integer to binary
// could be better but Im hoping its not too inefficient for hackerrank
string to_binary(char c){

    if(isspace(c)){return "11011";} // hard coded bcus 
    int int_c = c - 'a';
    string binary_string = "";

    // 16  >> 8   >> 4   >> 2   >> 1
    // 2^4 >> 2^3 >> 2^2 >> 2^1 >> 2^0
    // could have used mods but idc at this point
    if((int_c - 16) >= 0){binary_string += '1';int_c -= 16;}
    else{binary_string += '0';}
    if((int_c - 8) >= 0){binary_string += '1';int_c -= 8;}
    else{binary_string += '0';}
    if((int_c - 4) >= 0){binary_string += '1';int_c -= 4;}
    else{binary_string += '0';}
    if((int_c - 2) >= 0){binary_string += '1';int_c -= 2;}
    else{binary_string += '0';}
    if((int_c - 1) >= 0){binary_string += '1';int_c -= 1;}
    else{binary_string += '0';}

    return binary_string;

}

// converts a binary bit string to the corresponding integer
int from_binary(string bit_str){

    int binary_int = 0;
    //cout << "bit_str: " << bit_str << endl;
    if(bit_str == "11011"){return 27;}
    for(int i = 0; i < 5; i++){
        //cout << "bit_str[" << i << "]: " << bit_str[i] << "\t";
        if(bit_str[i] == '1'){binary_int += pow(2,4-i);}
    }
    return binary_int;

}

// checks validity of args 
// original_text in which the secret message is encoded
// must be at least 5 times as long at the secret message
bool check_message(string original_text, string secret_message){

    int num_alpha_ot = 0;
    int num_alpha_sm = 0;
    for(auto ch : original_text){if(isalpha(ch)){num_alpha_ot++;}}
    for(auto ar : secret_message){if(isalpha(ar)){num_alpha_sm++;}}

    return (num_alpha_ot >= 5*num_alpha_sm);

}

// encodes the secret message in the original text
// there are a few variables here that I used for debugging and are 
// no longer necessary but I will leave them since it's late :)
string encode(string original_text, string secret_message){

    // converting input strings to lower case
    string ot_lower = lower_case(original_text);
    string sm_lower = lower_case(secret_message);
    
    bool b = check_message(ot_lower,sm_lower);

    if(!b){return "error";} // make sure encoding is possible!

    string encoded;

    string temp_bit, temp_str;
    int i, count;

    // gets confusing here so I will do my best to explain! lol
    for(auto ch : sm_lower){ // for each letter in the secret message including spaces

        temp_bit = to_binary(ch); // convert the letter to a bit string

        temp_str = ""; // temp string is us
        i = 0;
        count = 0;
        while(count < 5){ // count makes sure we are adding 5 alpha chars and not 5 chars
                          // because spaces can't be capitalized
            if(isalpha(ot_lower[i])){ // so long as original text is a letter here
                                      // capitalize if secret message bit string is '1'
                if(temp_bit[count] == '1'){encoded += toupper(ot_lower[i]);}
                else{encoded += ot_lower[i];}
                count += 1;
            }
            else{encoded += ot_lower[i];}
            i += 1;
        } 

        ot_lower.erase(0,i);

    }

    encoded += ot_lower;

    return encoded;

}

// decodes encoded message and returns secret message
string decode(string to_decode){

    string decoded = "";
    string temp_str;

    int alpha_index;

    int count = 0;
    for(auto ac : to_decode){
        if(isalpha(ac)){
            temp_str += ac;
        }
    }
    // temp_str is now string with all alphanum chars of to_decode

    string temp_5_str, temp_5_bit;

    while(temp_str.size() > 0){
        temp_5_str = temp_str.substr(0,5);
        temp_5_bit = "";
        for(auto te : temp_5_str){
            if(isupper(te)){temp_5_bit += '1';}
            else{temp_5_bit += '0';}
        }
        alpha_index = from_binary(temp_5_bit);
        decoded += "abcdefghijklmnopqrstuvwxyz  "[alpha_index]; // couldnt do better than this

        temp_str.erase(0,5);
    }

    return decoded;

}

int main (){

    char ch;
    string line;
    string bin_string;

    getline(cin, line);
    ch = line[0];
    bin_string = to_binary(ch);
    cout << bin_string << endl; // WORKS
    cout << from_binary(bin_string) << endl; // WORKS

    getline(cin,line);
    cout << lower_case(line) << endl; // WORKS
    
    string text, message;
    string encoded, decoded;
    getline (cin, text);
    getline (cin, message);

    encoded = encode(text, message);
    cout << encoded << endl; // WORKS
    if (encoded != "error"){
      decoded = decode(encoded);
      cout << decoded << endl; // WORKS
    }
    else
      cout << "" << endl;
  
}