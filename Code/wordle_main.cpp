#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "wordle_funcs.h"

using namespace std;


	int main(){
		
		ifstream datafile;
		datafile.open("./Data/words_all.txt", ios::in);
		
		string line;
		
		std::vector<string> word_list_all;
		
		if (datafile.is_open()){
			while(getline(datafile,line)){
				if (line.size()==5){
					word_list_all.push_back(line);
				}
				
			}
		}else{
			cout << "Error opening word file";
		}
		
		cout << word_list_all.size()+'\n';
		
		return 0;
	}