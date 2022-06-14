#include <iostream>
#include <vector>
#include <game.hpp>

int main(){
  std::cout<< "test" <<std::endl;
  
  CGame<char> game("./Data/words_all.txt");
  game.play();


}
