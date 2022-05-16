#include <string>
#include <vector>


std::string test_word(std::string answer, std::string guess){
	
	int i,j;
	std::string response = "bbbbb";
	
	for(i=0;i<5;i++){
		if(guess[i]==answer[i]){
			response[i] = 'g';
		}else{
			for(j=0;j<5;j++){
				if(guess[i]==answer[j]){
					response[i] = 'y';
				}
			}
		}
	}
	
	
	return response;
}

bool check_word(std::string guess, std::string response, std::string word){
	
	int i,j;
	bool compatible = true;
	bool test;
	
	for(i=0;i<5;i++){
		if(response[i]=='g'){ 
			if(guess[i]!=word[i]){
				compatible = false;
			}
		}else if(response[i]=='y'){
			test = true;
			for(j=0;j<5;j++){
				if(guess[i]==word[j]){
					test = false;
				}
			}
			if (test){
				compatible = false;
			}
			if(guess[i]==word[i]){
				compatible = false;
			}
		}else{
			
		}
	}
	
	return compatible;
}

std::vector<std::string> update_list(std::string guess, std::string response, std::vector<std::string> word_list){
	
	std::vector<std::string> word_list_new;
	
	std::string word;
	
	for(auto & word : word_list){
		if(check_word(guess,response,word)){
			word_list_new.push_back(word);
		}
		
	}
	
	return word_list_new;
}