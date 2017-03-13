#include <iostream>
using std::cout; using std::cin; using std::endl;
using std::ostream;

#include <string>
using std::string; using std::isalpha; using std::to_string;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <algorithm>
using std::transform; using std::copy; using std::sort;

#include <utility>
using std::pair;

#include <iterator>
using std::ostream_iterator;

#include <sstream>
using std::istringstream; using std::ostringstream;

// reads in a word (string) to 'process'. returns (a string) the 
// lowercase version of word with non-alphabetical chars removed from 
// beggining and end (keeps internals for contractions and possesives)
string process_word(string s){

	string lc_s = s;
	string return_s = "";
	transform(lc_s.begin(), lc_s.end(), lc_s.begin(), tolower);
	//int len = lc_s.size();
	while((not isalpha(lc_s[lc_s.size()-1])) && (lc_s.size() > 0)){
		lc_s.pop_back();
	} // checks last char of word
	  // this needed to happen first
	  // b/c if first char is removed,
	  // last index would be different
	if(not isalpha(lc_s[0])){lc_s.erase(0,1);} // checks first char of word
	return lc_s;

}

// takes in a line of text and a vector string
// fills in the vector string with words in the line
// each word is space delimited, so that is how the line is split
void process_line(string line, vector<string>& v){

    string temp_str = "";
    for(auto ar : line){
        temp_str += ar;
        if(ar == ' '){
            v.push_back(process_word(temp_str));
            temp_str = "";
        }
    }
    v.push_back(process_word(temp_str));
	return;

}

// func
// map.insert({key,value})
// unigram is a single word
// bigram is an ordered pair of words (does not ignore carriage returns)
// for bigrams, the order of the words does not matter! 
void read_file(map<string,long>& bi, map<string,long>& uni){

	string l;
	while(getline(cin,l)){
    	if (l.empty()){
    		getline(cin,l);
    		if(l.empty()){break;} // to account for extra indent between paragraphs
    	}
    	vector<string> words;
    	process_line(l,words); // fill 'words' with words in line
    	
    	for(int i = 0; i<words.size(); i++){if(words[i] == ""){words.erase(words.begin()+i);}}
    	// ^ for loop to remove empty strings from the vector of words
    	// because for some reason (& only on hackerrank, not my computer)
    	// the first test case was adding an empty string

    	for(auto w : words){uni[w] += 1;} // default behavior should add if nonexistant
    	
    	if(words.size() >= 1){	
	    	for(int i = 1; i < words.size(); i++){
	    		vector<string> temp_pair; 		 // temporary vector of strings that gets filled with
	    		temp_pair.push_back(words[i]);	 // pairs of strings and sorted so that the order of the 
	    		temp_pair.push_back(words[i-1]); // strings does not matter (ie. "hi mom" == "mom hi")
	    		sort(temp_pair.begin(), temp_pair.end());
	    		bi[temp_pair[0]+' '+temp_pair[1]] += 1; // adds pairs of words to bigram map
	    	}
    	}
	}

	return;

}

// reports a string of five numbers which are (in order):
//		1 - from the text, the number of times there was a bigram "word1 word2"
//		2 - unigrams of word1 exculing bigrams
//		3 -	unigrams of word2 excluding bigrams
//		4 - the number of unique bigrams in the text
//		5 - the number of unique unigrams in the text 
string report_counts(const map<string,long>& bi,
					 const map<string,long>& uni,
					 string word1, string word2){

	string counts;

	// put word1 and word2 in alphabetical order (like the rest of the keys)
	// and use as a key for the order-independent bigram containing word1 and word2
	vector<string> temp_vec_str;
	temp_vec_str.push_back(word1);
	temp_vec_str.push_back(word2);
	sort(temp_vec_str.begin(), temp_vec_str.end());
	string temp_key = temp_vec_str[0]+' '+temp_vec_str[1];
	counts += to_string(bi.at(temp_key)) + ' '; // 1

	long word1uni, word2uni, word1word2bi;

	// the if/else statements are making sure the word1 and word2 are in the unigram map
	// and if they are not, then artificially making their value 0
	if(uni.find(word1) != uni.end()){word1uni = uni.at(word1);}
	else{word1uni = 0;}
	if(bi.find(temp_key) != bi.end()){word1word2bi = bi.at(temp_key);}
	else{word1word2bi = 0;}
	counts += to_string(word1uni - word1word2bi) + ' '; // 2

	if(uni.find(word2) != uni.end()){word2uni = uni.at(word2);}
	else{word2uni = 0;}
	counts += to_string(word2uni - word1word2bi) + ' '; // 3

	counts += to_string(bi.size()) + ' '; // 4

	counts += to_string(uni.size()); // 5

	return counts;

}

int main (){

	map<string,long> bigrams;
	map<string, long> unigrams;
	string word1, word2, line;
	cin >> word1 >> word2; // get the two words
	getline(cin,line); // clear the \n at end of first line
  
	read_file(bigrams, unigrams); // read the lines and process

	cout << report_counts(bigrams, unigrams, word1, word2)
    	<< endl;

    return 0;
}