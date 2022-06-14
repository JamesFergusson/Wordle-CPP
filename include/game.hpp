#pragma once

#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring> 

const int WORD_LENGTH=5;

template <typename T>
class CGame{
public:    
    //we want to read the file in the constructor and force the class user to 
    //provide a filename, default constructor should not compile, so we delete it
    CGame() = delete;
    CGame(std::string data_filename);
    
    void play();
private:
    //the length of words is constant, no need to have a 2d dynamic array at all
    std::vector<std::array<T,WORD_LENGTH>> words;
    
    std::array<int,WORD_LENGTH> response;
    std::array<T,WORD_LENGTH> guess;
    
    void greet_and_init();  
    void print_word(int i);
};

//we read the file in the constructor

template<typename T> CGame<T>::CGame ( std::string data_filename ){
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
         //   so it's easier to just copy manucally
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
    
}

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
    
    //it's fairly difficult to provide a real safe user input, so it's better to just print
    //a warning with instructions;
    std::cout<<"WARNING: please type the word of exacly " <<WORD_LENGTH <<
    "low case latin symbols, otheriwse bad things will happen!" <<std::endl; 
    std::cout<<"Enter your guess now:"<<std::endl;
    std::cin.get(guess.data(), WORD_LENGTH);    
    
   
    
}

template<typename T> void CGame<T>::print_word ( int i ){
    for (size_t j=0; j<WORD_LENGTH;j++){
        std::cout<<words[i][j];
    }
}

