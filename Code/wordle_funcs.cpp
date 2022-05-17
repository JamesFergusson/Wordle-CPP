#include <string>
#include <vector>


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
	************************************************ */
	
	int i,j;
	
	// Set default to all black
	std::string response = "bbbbb";
	
	for(i=0;i<5;i++){
		// Check for green matches
		if(guess[i]==answer[i]){
			response[i] = 'g';
		}else{
			for(j=0;j<5;j++){
				// Check for yellow matches being careful to avoid green clashes
				if(guess[i]==answer[j] && guess[j]!=answer[j]){
					response[i] = 'y';
				}
			}
		}
	}
	
	
	return response;
}

bool check_word(std::string guess, std::string response, std::string word){
/*  ************************************************
	Takes a guess word and a response and checks
	is a given word could be a solution
	
	input:
	
	guess    :: A 5 letter string containing the guess word
	response :: A 5 letter response string containing the information
			    wordle would return. in the string b=black
			    y=yellow, and g=green
	word     :: A 5 letter string containing the possible solution word
	
	returns:
	
	bool     :: returns 1 if the word could be a solution and
			 :: 0 if the word could not be a solution
	************************************************ */	
	int i,j;
	bool test;
	bool compatible;
	
	if(test_word(guess,word)==response){
		compatible = true;
	}else{
		compatible = false;
	}
	
	return compatible;
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
	
	for(auto & word : word_list){
		if(check_word(guess,response,word)){
			word_list_new.push_back(word);
		}
		
	}
	
	return word_list_new;
}




