#ifndef KITCHEN_HPP
#define KITCHEN_HPP
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>

#include "ArrayBag.hpp"
#include "Dish.hpp"
#include "MainCourse.hpp"
#include "Appetizer.hpp"
#include "Dessert.hpp"

class Kitchen : public ArrayBag<Dish*> {
    public:
        Kitchen();
        bool newOrder(Dish* new_dish);
        bool serveDish(Dish* dish_to_remove);
        int getPrepTimeSum() const;
        int calculateAvgPrepTime() const;
        int elaborateDishCount() const;
        double calculateElaboratePercentage() const;
        int tallyCuisineTypes(const std::string& cuisine_type) const;
        int releaseDishesBelowPrepTime(const int& prep_time);
        int releaseDishesOfCuisineType(const std::string& cuisine_type);
        void kitchenReport() const;
        Kitchen(const std::string);
        //project 4
        //Kitchen(const std::string filename);
        void dietaryAdjustment(const Dish::DietaryRequest&);
        void displayMenu() const;
        ~Kitchen();

    private:
        int total_prep_time_;
        int count_elaborate_;
        //helper functions
        Dish::CuisineType stringtoCuisine(std::string);
        Dish* parseAppetizer(std::string);
        Dish* parseMainCourse(std::string);
        Dish* parseDessert(std::string);
        MainCourse::Category stringtoCategory(std::string cat);

};
#endif // KITCHEN_HPP