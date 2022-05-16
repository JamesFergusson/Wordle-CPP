#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "wordle_funcs.h"


	int main(){
		
		int i,j;
		std::ifstream datafile;
		datafile.open("./Data/words_all.txt", std::ios::in);
		
		std::string line;
		
		std::vector<std::string> word_list_all;
		
		if (datafile.is_open()){
			while(getline(datafile,line)){
				if (line.size()==5){
					word_list_all.push_back(line);
				}
				
			}
		}else{
			std::cout << "Error opening word file \n";
		}
		
		std::cout << word_list_all.size();
		std::cout << "\n";
		
		std::string response;
		
		response = test_word("tipsy","split");
		
		std::cout << response + "\n";
		
		bool test;
		
		test = check_word("split",response,"tipsy");
		
		std::cout << test;
		std::cout << "\n";
		
		std::vector<std::string> word_list_new;
		
		word_list_new = update_list("split",response,word_list_all);
		

	
		std::string word;
	
		for(auto & word : word_list_new){
			std::cout << word+"\n";
		}
		
		return 0;
	}