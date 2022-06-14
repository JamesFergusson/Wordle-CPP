#ifndef WORDLE_FUNCS_H
#define WORDLE_FUNCS_H
	
	#include <string>
	
	std::string test_word(std::string answer, std::string guess);
	std::vector<std::string> update_list(std::string guess, std::string response, std::vector<std::string> word_list);
	
#endif