#include "readlevel.h"
#include "tfidf.h"
#include "stem.h"
#include "parse.h"
#include "except.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]){
	
	std::vector< vector<string> > allFileWords;
	std::vector< vector<int> > allFileCount;

	for(int i = 1; i < argc; i++){
		ifstream input_file(argv[i]);
		std::vector<string> words;
		std::vector<int> count;
		string temp_s;
		int temp_i;

		while (input_file >> temp_s >> temp_i) {
			if ((ispunct(temp_s[0]) && (temp_s[0] != '\''))){
                                //words1.push_back(curr);
                        }
                        else if (std::any_of(temp_s.begin(), temp_s.end(), ::isdigit) ||
                                (std::any_of(temp_s.begin(), temp_s.end(), ::isupper)) ||
                                (int(temp_s.length()) <= 2)){

                                words.push_back(temp_s);
				count.push_back(temp_i);
                        }
			else{
    				words.push_back(temp_s);
    				count.push_back(temp_i);
			}
		}
		allFileWords.push_back(words);
		allFileCount.push_back(count);
	}

	
        std::vector< vector<double> > totaltfidf = tfidf(allFileWords, allFileCount);
	double currtfidf;
        for(int i = 1; i < int(totaltfidf[0].size()); i++){
                currtfidf = totaltfidf[0][i];
                cout << currtfidf << " ";
                //cout << "File: " << fileNames[i] << " Sim: " << currtfidf << "\n";
        }
	cout << "\n";

        return 0;

}

