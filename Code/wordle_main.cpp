#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include "wordle_funcs.h"

struct wordscore{
	int score;
	std::string word;
	
	bool operator < (const wordscore& str) const
	{
		return (score < str.score);
	}
	
};
	
auto rng = std::mt19937{};

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
	
	
	// Start actual code
	
	std::string guess;
	std::string response;
	
	std::cout << "***************************************\n";
	std::cout << "*                                     *\n";
	std::cout << "*            Wordle Solver            *\n";
	std::cout << "*                                     *\n";
	std::cout << "***************************************\n";
		
	std::cout << "Select you first guess. Some suggestions are below.\n";
	std::cout << "[aloes\tsoare\taeros\taeons\tlares]\n\n";
	std::cout << "Enter your guess now:\n";
	
	std::cin >> guess;
	
	while(guess.size()!=5){
		std::cout << "\nGuesses must be 5 letters\n";
		std::cout << "Enter your guess now:\n";
		std::cin >> guess;
	}

	std::cout << "\nWhat was the response? Enter a 5 letter sequence\n";
	std::cout << "g=green y=yellow b=black\n";
	std::cout << "An answer with a green square in position 2\n";
	std::cout << "and a yellow one in position 5 you would type:\n";
	std::cout << "bgbby:\n";
	std::cout << "\nEnter response now:\n";

	std::cin >> response;

	while(response.size()!=5){
		std::cout << "\nResponses must be 5 letters\n";
		std::cout << "Enter response now:\n";
		std::cin >> response;
	}
	
	std::vector<std::string> word_list_new;
	
	word_list_new = word_list_all;
	
	while(response!="ggggg"){

		word_list_new = update_list(guess,response,word_list_new);
		
		std::cout << "\nThere are ";
		std::cout << word_list_new.size();
		std::cout << " possible remaining guesses\n";
		if(word_list_new.size()<20){
			std::cout << "[";
			for(auto & word : word_list_new){
				std::cout << word;
				std::cout << "\t";
			}
			std::cout << "]\n";
		}
		std::cout << "Calculating next best guesses...\n";
		
		int score;
		std::shuffle(word_list_new.begin(), word_list_new.end(), rng);
	
		int sample = 100;
		
		std::vector<std::string> word_list_sml;
			
		if(word_list_new.size()>sample){
			for(i=0;i<sample;i++){
				word_list_sml.push_back(word_list_new[i]);
			}
		}else{
			word_list_sml = word_list_new;
		}
		
		std::vector<wordscore> scored_list;
		wordscore tmp;

		for(auto & guess : word_list_all){
			score = 0;
			for(auto & answer : word_list_sml){
				response = test_word(guess,answer);
				for(auto & word : word_list_sml){
					score += check_word(guess,response,word);
				}	
			}
			tmp.score = score/sample;
			tmp.word = guess;
			scored_list.push_back(tmp);
		}
	
		std::sort(scored_list.begin(),scored_list.end());

		std::cout << "The top ten guesses are:\n";
		std::cout << "[";
		for(i=0;i<10;i++){
			std::cout << scored_list[i].word;
			std::cout << "\t";
		}
		std::cout << "]\n";
		
		std::cout << "\nEnter your guess now:\n";
		std::cin >> guess;
	
		while(guess.size()!=5){
			std::cout << "\nGuesses must be 5 letters\n";
			std::cout << "Enter your guess now:\n";
			std::cin >> guess;
		}

		std::cout << "\nEnter response now:\n";
		std::cin >> response;

		while(response.size()!=5){
			std::cout << "\nResponses must be 5 letters\n";
			std::cout << "Enter response now:\n";
			std::cin >> response;
		}
	}
	
	std::cout << "Yay! You won!!\n";
	
	return 0;
}