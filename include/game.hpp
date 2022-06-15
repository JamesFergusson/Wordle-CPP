#pragma once

#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

const int WORD_LENGTH=5;
const int MAX_STEPS=5;

template <typename T>
class CGame{
public:    
    //we want to read the file in the constructor and force the class user to 
    //provide a filename, default constructor should not compile, so we delete it
    CGame() = delete;
    CGame(const std::string& data_filename);
    
    void play();
private:
    //the length of words is constant, no need to have a 2d dynamic array at all
    std::vector<std::array<T,WORD_LENGTH>> words;
    std::vector<std::array<T,WORD_LENGTH>> words_sample;
    std::vector<int> scores;

    std::array<int,WORD_LENGTH> response;
    std::array<T,WORD_LENGTH> guess;
    int sample_size;
    
    void greet_and_init();  
    void ask_guess_and_response();
    void print_word(int i);
    void print_word(const std::array<T,WORD_LENGTH>& word);
    void print_words();
    void update_list();
    std::array<int,WORD_LENGTH> test_word_weird_rules (const std::array<T,WORD_LENGTH>& word);
    std::array<int,WORD_LENGTH> test_word (const std::array<T,WORD_LENGTH>& word);
    void create_words_sample();
    void calculate_scores_guesses();
    void calculate_scores_solutions();
    bool check_response();
    
};

//we read the file in the constructor

template<typename T> CGame<T>::CGame (const std::string& data_filename ){
    std::ifstream filevar;
	filevar.open(data_filename);
    
    //it is ok to use push back here, the data size is not that big,
    //but normally you just want to know the size in advance
    //(maybe manually input the number of lines)
    //reading the file twice might be just as bad as pushback
    std::array<T,WORD_LENGTH> temp;
    std::string temp_s;
    if (filevar.is_open()){
        std::cout<<"opened file"<<std::endl;
		while(std::getline(filevar,temp_s)){
         //   std::strcpy has problems with termination characters,
         //   so it's easier to just copy manually
            for (int k=0;k<temp_s.length();k++){temp[k]=temp_s[k];}
            words.push_back(temp);
		}
	}else{
        //in general, should print to standard error output
		std::cerr << "Error opening word file \n";
	}
    
    filevar.close();

}

template<typename T> void CGame<T>::play(){ 
    greet_and_init();
    
    int step_counter{2};
    while (step_counter<=MAX_STEPS){
        std::cout<<"this is STEP number "<<step_counter<<std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        update_list();
        std::cout<<"There are " <<words.size()<<" possible remaining guesses"<<std::endl;
		if(words.size()<20){
			print_words();
		}
		std::cout<<"Calculating next best guesses..."<<std::endl;
        
        create_words_sample();
        calculate_scores_guesses();
        
        std::cout<<"Calculating next best solutions..."<<std::endl;
        calculate_scores_solutions();
        
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
        std::cout << "Elapsed (in MILLISECONDS) time this step: " << duration.count() << std::endl;
        
        ask_guess_and_response();
        
        if(check_response()){
            break;
        }
        ++step_counter;
    }//while steps
    if(step_counter<=MAX_STEPS){
        std::cout<<"you won!"<<std::endl;
    }else{
        std::cout<<"you lost!"<<std::endl;
    }
    
}//play

template<typename T> void CGame<T>::greet_and_init(){
    printf("***************************************\n");
	printf("*                                     *\n");
	printf("*            Wordle Solver            *\n");
	printf("*                                     *\n");
	printf("***************************************\n");
    
    std::cout<< "total number of words: "<<words.size()<<std::endl;
    std::cout<<"first word is ";
    print_word(0);
    std::cout<<std::endl;
    
    //a horrible mess of printf and std::cout is because I was lazy to rewrite the given example
    std::cout<<"Select you first guess. Some suggestions are below." <<std::endl;
	printf("22430 - reais\n22616 - lares\n22830 - tares\n22844 - nares\n23054 - rales\n23302 - rates\n23432 - saner\n23744 - soare\n23816 - serai\n24382 - aeros\n\n");
    
    ask_guess_and_response();
    
}

template<typename T> void CGame<T>::print_word ( int i ){
    for (size_t j=0; j<WORD_LENGTH;j++){
        std::cout<<words[i][j];
    }
}

template<typename T> void CGame<T>::print_word ( const std::array<T, WORD_LENGTH>& word ) {
    for (size_t j=0; j<WORD_LENGTH;j++){
        std::cout<<word[j];
    }
}


/**
	Takes a list of words and removes all words which
	are not compatible with the guess and response.
**/
template<typename T> void CGame<T>::update_list() {
    std::vector<std::array<T,WORD_LENGTH>> temp_words;
    //we know the max length of the temp_words
    //ideally, we resize to it at the start of the program and never change,
    //but watch the "true" size through counters.
    //yet here we can reserve and push_back for easier coding
    //since the number of iterations is small, reallocations are not that bad in our case
    //having a local variable will mitigate the damage a bit
    temp_words.reserve(words.size());
    for (auto & word : words) {
        auto response_test=test_word_weird_rules (word);
        if (response_test==response){
            temp_words.push_back(word);
        }
    }//for 
    //in the end, temp_words need to become words
    words.resize(temp_words.size());
    words.swap(temp_words);
}//update_list

template<typename T> 
std::array<int,WORD_LENGTH> CGame<T>::test_word (const std::array<T, WORD_LENGTH>& word ) {
    std::array<int,WORD_LENGTH> response_test;
    response_test.fill(0);//reset the variable to "all black"
	for(int i=0;i<WORD_LENGTH;i++){
        if(guess[i]==word[i]){ //"green match"
            response_test[i] = 2;
        }else{
            for(int j=0;j<WORD_LENGTH;j++){
                if(guess[i]==word[j]){                
                    response_test[i] = 1;//"yellow match"
                    break;//found it, can stop
                }//if
            }//for inner loop
        }//if-else green case
	}//for
	return response_test;
}//test_word_weird_rules


template<typename T> 
std::array<int,WORD_LENGTH> CGame<T>::test_word_weird_rules(const std::array<T, WORD_LENGTH>& word ) {
    std::array<int,WORD_LENGTH> response_test;
    //if we passed by value, the copy of "word" would have been made automatically
    //however, as we also need a copy of guess this will become confusing
    //it's better to copy both manually
    std::array<T,WORD_LENGTH> guess2(guess);
    std::array<T,WORD_LENGTH> word2(word);
    response_test.fill(0);//reset the variable to "all black"
    
    for(int i=0;i<WORD_LENGTH;i++){
		// Check for green matches
		if(guess2[i]==word2[i]){
			response_test[i] = 2;
			guess2[i] = -2;
			word2[i] = -1;
		}
	}
	for(int i=0;i<WORD_LENGTH;i++){
		for(int j=0;j<WORD_LENGTH;j++){
			if(guess2[i]==word2[j]){
				response_test[i] = 1;
				guess2[i]=-2;
				word2[j]=-1;
			}
		}
	}
    
	return response_test;
}//test_word


template<typename T> void CGame<T>::print_words() {
    std::cout<<"[";
    for(int i=0;i<words.size();i++){
        print_word(i);
        std::cout<<" ";
    }//print_words
    std::cout<<"]"<<std::endl;
}//print_words

template<typename T> void CGame<T>::create_words_sample() {
    int test_unique{1};
        
    if (sample_size>words.size()){
        sample_size = words.size();
        words_sample=words;
    }else{
        std::vector<int> rand_list;
        rand_list.resize(sample_size);
        words_sample.resize(sample_size);
        //using the exact same approach as in c code here as we don't want to 
        //compare 2 completely different algorithms 
        //testing shuffle vs while loop is a different task in itself
        //IF you want shuffle though, DO NOT shuffle the word list, but rather an index array
        for(int i=0;i<sample_size;i++) {
            while(test_unique){
                test_unique = 0;
                int j = rand() % words.size();
                rand_list[i]=j;
                for(int k=0;k<i;k++){
                    if(j==rand_list[k]){
                        test_unique = 1;
                    }
                }//for
            }//while
            words_sample[i]=words[i];
            test_unique = 1;
        }//for
    }//if-else the list is bigger then sample
        
}//create sample

template<typename T> void CGame<T>::calculate_scores_guesses() {
    // score list to select best guesses
    // Method is to check for each guess word
    // and each possible answer from the sub sample
    // how many words would be compatible with the 
    // information gained from that guess
    std::array<T,WORD_LENGTH> potential_answer;
    std::array<T,WORD_LENGTH> word;
	std::array<int,WORD_LENGTH> response;
    std::array<int,WORD_LENGTH> response_test;
    scores.resize(words.size());
    for(int i=0;i<words.size();i++){
        int score{0};
        guess = words[i];
        for(int j=0;j<sample_size;j++){
            potential_answer = words_sample[j];
            response=test_word_weird_rules (potential_answer);
            for(int k=0;k<sample_size;k++){
                word = words_sample[k];
                response_test=test_word_weird_rules (word);
                if(response==response_test){
                    score += 1;
                }
            }
        }//for
        scores[i] = score;
    }//for 
    //now need to sort and print
    int smallest;
    int sml_index;
    for(int k=0;k<20;k++){
        sml_index=0;
        smallest = scores[0];
        for(int i=1;i<words.size();i++){
            if(smallest>scores[i]){
                smallest = scores[i];
                sml_index = i;
            }//if
        }//for
        std::cout<<scores[sml_index]<<" - ";
        print_word(sml_index);
        std::cout<<std::endl;
        scores[sml_index] = sample_size*sample_size;
    }//for
}//calculate_scores

//these 2 functions could be make into 1, but I ran out of time...
template<typename T> void CGame<T>::calculate_scores_solutions() {
   
    std::array<T,WORD_LENGTH> potential_answer;
    std::array<T,WORD_LENGTH> word;
	std::array<int,WORD_LENGTH> response;
    std::array<int,WORD_LENGTH> response_test;
    
    if(sample_size==words.size()){
    
    for(int i=0;i<sample_size;i++){
        int score{0};
        guess = words_sample[i];
        for(int j=0;j<sample_size;j++){
            potential_answer = words_sample[j];
            response=test_word_weird_rules (potential_answer);
            for(int k=0;k<sample_size;k++){
                word = words_sample[k];
                response_test=test_word_weird_rules (word);
                if(response==response_test){
                    score += 1;
                }
            }
        }//for
        scores[i] = score;
    }//for 
    //now need to sort and print
    int smallest;
    int sml_index;
    for(int k=0;k<20;k++){
        sml_index=0;
        smallest = scores[0];
        for(int i=1;i<words.size();i++){
            if(smallest>scores[i]){
                smallest = scores[i];
                sml_index = i;
            }//if
        }//for
        std::cout<<scores[sml_index]<<" - ";
        print_word(words_sample[sml_index]);
        std::cout<<std::endl;
        scores[sml_index] = sample_size*sample_size;
    }//for
    } 
}//calculate_scores solutions

template<typename T> 
void CGame<T>::ask_guess_and_response() {
     //it's fairly difficult to provide a real safe user input, so it's better to just print
    //a warning with instructions;
    std::cout<<"WARNING: please type the word of exactly " <<WORD_LENGTH <<
    " low-case latin symbols, otherwise bad things will happen!" <<std::endl; 
    std::cout<<"Enter your guess now:"<<std::endl;
    std::cin.get(guess.data(), WORD_LENGTH+1);  
    std::cout<<"you have entered "; 
    print_word(guess);
    //streams are weird - cin.get will leave trailing endline, if we don't clear it will crash
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    
    printf("\nWhat was the response? Enter a 5 letter sequence\n");
	printf("2=green 1=yellow 0=black\n");
	printf("An answer with a green square in position 2\n");
	printf("and a yellow one in position 5 you would type:\n");
	printf("02001:\n");
    printf("\nEnter response now:\n");
    
    std::array<T, WORD_LENGTH> temp;
    std::cin.get(temp.data(), WORD_LENGTH+1);
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    //need to convert that to ints
    for (int i=0;i<WORD_LENGTH;i++){
        response[i]=temp[i]-'0';
    }
    //debug
    std::cout<<"you have entered "; 
    for(int i=0;i<WORD_LENGTH;i++){
        std::cout<<response[i]<<" ";
    }
    std::cout<<std::endl;
}//ask_guess_and_response

template<typename T> 
bool CGame<T>::check_response() {
    bool result{true};
    for(int i=0;i<WORD_LENGTH;i++){
        if(response[i]!=2){
            result=false;
            break;
        }
    } 
    return result;
}//check_response


