#include <iostream>
#include "Dish.hpp"
#include "Appetizer.hpp"
#include "MainCourse.hpp"
#include "Dessert.hpp"
//fist project main test
// int main(){
//     Dish Dish0;
//     Dish0 = Dish();
//     Dish0.setPrepTime(30);
//     Dish0.setPrice(9.99);
//     Dish0.display();
//     std::cout<<'\n';

//     Dish DishTest;
//     DishTest = Dish();
//     std::vector<std::string> random = {"Pasta", "Eggs", "Pancetta", "Parmesan", "Pepper"};
//     Dish::CuisineType rann = Dish::ITALIAN; //calling an enum
//     DishTest = Dish("test", random, 20, 10.00, rann);
//     DishTest.setName("Pasta Carbonara");
//     DishTest.getName();
//     //vector<std::string> setRan{"rice"};
//     DishTest.setIngredients(random);
//     DishTest.getIngredients();
//     DishTest.setPrepTime(20);
//     DishTest.getPrepTime();
//     DishTest.setPrice(12.50);
//     DishTest.getPrice();
//     // Dish::CuisineType anotherOne = Dish::ITALIAN;
//     // DishTest.setCuisineType(anotherOne);
//     DishTest.setCuisineType(Dish::ITALIAN);
//     DishTest.getCuisineType();
//     DishTest.display();
// }

//second project main test
int main(){
    Appetizer Appetizer0;
    Appetizer0 = Appetizer();
    Appetizer0.setPrepTime(0);
    Appetizer0.setPrice(0.00);
    Appetizer0.setCuisineType(Dish::OTHER);
    Appetizer0.getCuisineType();
    Appetizer0.setSpicinessLevel(7);
    Appetizer0.getSpicinessLevel();
    Appetizer0.setServingStyle(Appetizer::FAMILY_STYLE);
    Appetizer0.getServingStyle();
    Appetizer0.setVegetarian(true);
    Appetizer0.isVegetarian();
    Appetizer0.displayAppetizer();
    std::cout<<'\n';

    MainCourse MainCourse0;
    MainCourse0 = MainCourse();
    std::vector<std::string> random = {"Chicken", "Olive Oil", "Garlic", "Rosemary"};
    //MainCourse::CuisineType rann = MainCourse::AMERICAN; //calling an enum
    MainCourse::SideDish sideDish0 = {"Mash Potatoes",MainCourse::STARCHES};
    MainCourse::SideDish sideDish1 = {"Green Beans", MainCourse::VEGETABLE};
    std::vector<MainCourse::SideDish> sideDishTest = {sideDish0, sideDish1};
    MainCourse0 = MainCourse("Grilled Chicken", random, 30, 18.99, Dish::CuisineType::AMERICAN, MainCourse::CookingMethod::GRILLED, "Chicken", sideDishTest, true);
    MainCourse0.setName("Grilled Chicken");
    MainCourse0.getName();
    MainCourse0.setIngredients(random);
    MainCourse0.getIngredients();
    MainCourse0.setPrepTime(30);
    MainCourse0.getPrepTime();
    MainCourse0.setPrice(18.99);
    MainCourse0.getPrice();
    MainCourse0.setCookingMethod(MainCourse::GRILLED);
    MainCourse0.getCookingMethod();
    MainCourse0.setProteinType("Chicken");
    MainCourse0.getProteinType();
    // MainCourse0.addSideDish({"Mash Potatoes",MainCourse::STARCHES});
    //MainCourse0.addSideDish({"Green Beans", MainCourse::VEGETABLE});
    MainCourse0.getSideDishes();
    MainCourse0.setGlutenFree(true);
    MainCourse0.isGlutenFree();
    MainCourse0.displayMainCourse();
    std::cout<<'\n';

    Dessert Dessert0;
    Dessert0 = Dessert();
    std::vector<std::string> DessertRandom = {"Flour", "Sugar", "Cocoa Powder", "Eggs"};
    Dessert0 = Dessert("Chocolate Cake", DessertRandom, 45, 7.99, Dish::CuisineType::FRENCH, Dessert::FlavorProfile::SWEET, 9, false);
    Dessert0.setName("Chocolate Cake");
    Dessert0.getName();
    Dessert0.setIngredients(DessertRandom);
    Dessert0.getIngredients();
    Dessert0.setPrepTime(45);
    Dessert0.getPrepTime();
    Dessert0.setPrice(7.99);
    Dessert0.getPrice();
    Dessert0.setCuisineType(Dessert::FRENCH);
    Dessert0.getCuisineType();
    Dessert0.setFlavorProfile(Dessert::SWEET);
    Dessert0.getFlavorProfile();
    Dessert0.setSweetnessLevel(9);
    Dessert0.getSweetnessLevel();
    Dessert0.setContainsNuts(false);
    Dessert0.containsNuts();
    Dessert0.displayDessert();
}
