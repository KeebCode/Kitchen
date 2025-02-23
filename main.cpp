#include <string> 
#include <iostream>
#include "RecipeBook.hpp"

int main(){
    RecipeBook test1("debug.csv");
    //test1.clear();
    // RecipeBook RecipeBook("debug.csv");
    
    // srand(time(0));
    // Recipe test0;
    // for(int i = 0; i < 10; i++){
    //     test0.name_ = "Recipe " + std::to_string(i+1);
    //     test0.difficulty_level_ = rand()%5+1;
    //     // test0.mastered_ = rand()%20 > 10;
    //     test0.mastered_ = 0;
    //     test1.addRecipe(test0);
    // }
    
    test1.preorderDisplay();
    test1.balance();
    // test1.calculateMasteryPoints("Recipe 3");
    //std::cout << "Calculate: " << test1.calculateMasteryPoints("name5") << "\n";
}
