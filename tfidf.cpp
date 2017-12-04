#include "tfidf.h"
#include "stem.h"
#include "parse.h"
#include "except.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <math.h>



std::vector< std::vector<double> > tfidf(std::vector< std::vector<string> > words, 
		std::vector< std::vector<int> > count){



	/*for(int i = 0; i < int(words[0].size()); i++){
		cout << words[0][i] << " " << count[0][i] << "\n";
	}*/



	double n;
	double tf;
	double idf;
	double wtfidf;
	double N = words.size();
	//cout << N << "\n";
	std::vector< std::vector<double> > tfidf;
	//tfidf.resize(words.size());
	for(int i = 0; i < (int)words.size(); i++){
		//cout << words[i].size() << "\n";
		std::vector<double> temp;
		for(int j = 0; j < (int)words[i].size(); j++){
			n = (double)numDocs(words[i][j], words);
			//cout << n << "\n";
			tf = count[i][j];
			//cout << "tf " << tf << "\n";
			idf = log10((N/n));
			//cout << N/n << "\n";
			//cout << "idf " << idf << "\n";
			wtfidf = tf*idf;
			//cout << wtfidf << "\n";
			temp.push_back(wtfidf);
		}
		tfidf.push_back(temp);
	}
	//cout << tfidf.size() << "\n";
	return totaltfidf(words, tfidf);
}



std::vector< std::vector<double> > totaltfidf(std::vector< std::vector<string> > words,
		std::vector< std::vector<double> > wtfidf){
	
	std::vector< std::vector<double> > total;
	//total.resize(words.size());
	//int tottfidf;
	//Compare every document with every other document
	//for(int i = 0; i < (int)words.size(); i++){
		std::vector<double> temp;
                for(int j = 0; j < (int)words.size(); j++){
			temp.push_back(doctfidf(words[0], words[j], wtfidf[0], wtfidf[j]));
		}
		total.push_back(temp);
	//}
	//cout << total.size() << "\n";
	return total;
}



double doctfidf(std::vector<string> doc1, std::vector<string> doc2, 
		std::vector<double> wtfidf1, std::vector<double> wtfidf2){

	double total = 0;
	for(int i = 0; i < (int)doc1.size(); i++){
		for(int j = 0; j < (int)doc2.size(); j++){
			//If word is in both documents multiply tfidf scores and add to total
			if(doc1[i].compare(doc2[j]) == 0){
				total += (wtfidf1[i] * wtfidf2[j]);
				//cout << doc1[i] << ": " << wtfidf1[i] << " * " << wtfidf2[j] << " = " << total << "\n";
				break;
			}
		}
	}

	//cout << total << "\n";
	return total;

}



int numDocs(string word, std::vector< std::vector<string> > words){
	int docs = 0;
	for(int i = 0; i < (int)words.size(); i++){
                if(std::find(words[i].begin(), words[i].end(), word) != words[i].end()) {
			docs++;
		}
        }
	//cout << word << ": " << docs << " docs\n";
	return docs;
}
