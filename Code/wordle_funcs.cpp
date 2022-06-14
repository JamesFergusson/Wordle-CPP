#include <string>
#include <vector>

std::vector<int> convert_word(std::string word){
	std::vector<int> word_int;
	int letter;
	for (char const &c: s){
		word_int.push_back((int)c);
	}
	return word_int;
}

std::string test_word(std::string guess, std::string answer){
/*  ************************************************
	Tests a guess word against an answer and generates
	a response string
	
	input:
	
	guess    :: A 5 letter string containing the guess word
	answer   :: A 5 letter string containing the solution word
	
	returns:
	
	response :: A 5 letter response string containing the information
			    wordle would return. in the string b=black
			    y=yellow, and g=green
	
	Note: The rules of wordle are not correct as stated on the site
	repeated letters are treated seperatly so:
	guess = 'shoot' and answer = 'bloat' will return:
	bbgbg not bbgyg as the second 'o' can't match with already matched 'o'
	in the answer.  This is also true for yellow matches.  
	To avoid this we must remove matched letters so they can't be matched again
	************************************************ */
	
	int i,j;
	
	// std::vector<int> guess_int = convert_word(guess);
	// std::vector<int> answer_int = convert_word(answer);
		
	// Set default to all black
	std::string response = "bbbbb";
	
	for(i=0;i<5;i++){
		// Check for green matches
		if(guess[i]==answer[i]){
			response[i] = 'g';
			// change to dummy values to exclude from future yellow searches
			guess[i] = '0';
			answer[i] = '1';
		}
	}
	
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			// Check for yellow matches
			if(guess[i]==answer[j]){
				response[i] = 'y';
			// change to dummy values to exclude from future yellow searches
				guess[i] = '0';
				answer[j] = '1';
			}
		}
	}
	
	
	return response;
}


std::vector<std::string> update_list(std::string guess, std::string response, std::vector<std::string> word_list){
/*  ************************************************
	Takes a list of words and removes all words which
	are not compatible with the guess and response
	
	input:
	
	guess     		:: A 5 letter string containing the guess word
	response		:: A 5 letter response string containing the information
					   wordle would return. in the string b=black
					   y=yellow, and g=green
	word_list		:: A vector of 5 letter strings for each word
	
	returns:
	
	word_list_new	:: returns a new word list which is the subset
					:: of 'word_list' which could be the solution
					:: given the ruess and response
	************************************************ */	
		
	std::vector<std::string> word_list_new;
	
	std::string word;
	
	for(auto &word : word_list){
		if(test_word(guess,word)==response){
			word_list_new.push_back(word);
		}
		
	}
	
	return word_list_new;
}




