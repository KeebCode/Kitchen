/**
 * @file StationManager.cpp
 * @brief This file contains the implementation of the StationManager class, which represents a cooking station in the kitchen
 * 
 * The StationManager class includes methods to manage a station.
 * @date Due: 12/2
 * @author Weini Li
 */
#include "StationManager.hpp"
#include <iostream>

// Default Constructor
StationManager::StationManager() {
    // Initializes an empty station manager
    dish_queue_ = std::queue<Dish*>();
    backup_ingredients_ = std::vector<Ingredient>();
}


// Adds a new station to the station manager
bool StationManager::addStation(KitchenStation* station) {
    return insert(item_count_, station);
}

// Removes a station from the station manager by name
bool StationManager::removeStation(const std::string& station_name) {
    for (int i = 0; i < item_count_; ++i) {
        if (getEntry(i)->getName() == station_name) {
            return remove(i);
        }
    }
    return false;
}

// Finds a station in the station manager by name
KitchenStation* StationManager::findStation(const std::string& station_name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == station_name) {
            return searchptr->getItem();
        }
        searchptr = searchptr->getNext();
    }
    return nullptr;
}

// Moves a specified station to the front of the station manager list
bool StationManager::moveStationToFront(const std::string& station_name) {
    // First, make sure the station exists
    if (findStation(station_name) == nullptr) {
        return false;
    }
    
    // If it's already at the front, return true
    if (getHeadNode()->getItem()->getName() == station_name) {
        return true;
    }

    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == station_name) {
            // Make a copy of the station
            KitchenStation* station = searchptr->getItem();
            
            // Remove the station from its current position
            int pos = getStationIndex(searchptr->getItem()->getName());
            remove(pos);
            
            // Insert the station at the front
            insert(0, station);
            
            return true;  // Exit after moving the station
        }
        
        searchptr = searchptr->getNext();  // Move to the next node
    }
    
    return false;
}


int StationManager::getStationIndex(const std::string& name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    int index = 0;
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == name) {
            return index;
        }
        searchptr = searchptr->getNext();
        index++;
    }
    return -1;
}

// Merges the dishes and ingredients of two specified stations
bool StationManager::mergeStations(const std::string& station_name1, const std::string& station_name2) {
    KitchenStation* station1 = findStation(station_name1);
    KitchenStation* station2 = findStation(station_name2);
    if (station1 && station2) {
        // take all the dishes from station2 and add them to station1
        for (Dish* dish : station2->getDishes()) {
            station1->assignDishToStation(dish);
        }
        // take all the ingredients from station2 and add them to station1
        for (Ingredient ingredient : station2->getIngredientsStock()) {
            station1->replenishStationIngredients(ingredient);
        }
        // remove station2 from the list
        removeStation(station_name2);
        return true;
    }
    return false;
}

// Assigns a dish to a specific station
bool StationManager::assignDishToStation(const std::string& station_name, Dish* dish) {
    KitchenStation* station = findStation(station_name);
    if (station) {
        return station->assignDishToStation(dish);
    }
    return false;
}

// Replenishes an ingredient at a specific station
bool StationManager::replenishIngredientAtStation(const std::string& station_name, const Ingredient& ingredient) {
    KitchenStation* station = findStation(station_name);
    if (station) {
        station->replenishStationIngredients(ingredient);
        return true;
    }
    return false;
}

// Checks if any station in the station manager can complete an order for a specific dish
bool StationManager::canCompleteOrder(const std::string& dish_name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->canCompleteOrder(dish_name)) {
            return true;
        }
        searchptr = searchptr->getNext();
    }
    return false;
}

// Prepares a dish at a specific station if possible
bool StationManager::prepareDishAtStation(const std::string& station_name, const std::string& dish_name) {
    KitchenStation* station = findStation(station_name);
    if (station && station->canCompleteOrder(dish_name)) {
        return station->prepareDish(dish_name);
    }
    return false;
}

//project 6
/**
* Retrieves the current dish preparation queue.
* @return A copy of the queue containing pointers to Dish objects.
* @post: The dish preparation queue is returned unchanged.*/
std::queue<Dish*> StationManager::getDishQueue(){
    return dish_queue_;
}

/**
* Retrieves the list of backup ingredients.
* @return A vector containing Ingredient objects representing backup supplies.
* @post: The list of backup ingredients is returned unchanged.*/
std::vector<Ingredient> StationManager::getBackupIngredients(){
    return backup_ingredients_;
}

/**
* Sets the current dish preparation queue.
* @param dish_queue A queue containing pointers to Dish objects.
* @pre: The dish_queue contains valid pointers to dynamically allocated Dish objects.
* @post: The dish preparation queue is replaced with the provided queue. */
void StationManager::setDishQueue(const std::queue<Dish*> &dish_queue){
    dish_queue_ = dish_queue;
}

/**
* Sets the backup ingredients list.
* @param backup_ingredients A vector of Ingredient objects representing backup supplies.
* @pre: The backup_ingredients vector contains valid Ingredient objects.
* @post: The list of backup ingredients is replaced with the provided vector.*/
void StationManager::setBackupIngredients(const std::vector<Ingredient> &backup_ingredients){
    backup_ingredients_ = backup_ingredients;
}

/**
* Adds a dish to the preparation queue without dietary accommodations.
* @param dish A pointer to a dynamically allocated Dish object.
* @pre: The dish pointer is not null.
* @post: The dish is added to the end of the queue.*/
void StationManager::addDishToQueue(Dish* dish){
    if(dish != nullptr){
        dish_queue_.push(dish); 
    }
}

/**
* Adds a dish to the preparation queue with dietary accommodations.
* @param dish A pointer to a dynamically allocated Dish object.
* @param request A DietaryRequest object specifying dietary accommodations.
* @pre: The dish pointer is not null.
* @post: The dish is adjusted for dietary accommodations and added to the end of the queue.*/
void StationManager::addDishToQueue(Dish* dish,const Dish::DietaryRequest &request){
    if(dish != nullptr){
        dish->dietaryAccommodations(request);
        dish_queue_.push(dish);
    }
}

/**
* Prepares the next dish in the queue if possible.
* @pre: The dish queue is not empty.
* @post: The dish is processed and removed from the queue.
* If the dish cannot be prepared, it stays in the queue
* @return: True if the dish was prepared successfully; false otherwise.*/
bool StationManager::prepareNextDish(){
    if(dish_queue_.size() <= 0){
        return false;
    }
    Node<KitchenStation*>* ks = getHeadNode();
    Dish* disptr = getDishQueue().front();
    std::string dishName = disptr->getName();
    while(ks != nullptr){
        if(ks->getItem()->canCompleteOrder(dishName)){
            ks->getItem()->prepareDish(dishName);
            dish_queue_.front() = nullptr;
            delete dish_queue_.front();
            dish_queue_.pop();
            return true;
        }
        ks = ks->getNext();
    }
    return false;
}

/**
* Displays all dishes in the preparation queue.
* @pre: None.
* @post: Outputs the names of the dishes in the queue in order (each name is on its own line).*/
void StationManager::displayDishQueue(){
    std::queue<Dish*> copy = dish_queue_;
    while(!copy.empty()){
        std::cout<< copy.front()->getName() << "\n";
        copy.pop();
    }
}

/**
* Clears all dishes from the preparation queue.
* @pre: None.
* @post: The dish queue is emptied and all allocated memory is freed.*/
void StationManager::clearDishQueue(){
    while(!dish_queue_.empty()){
        dish_queue_.front() = nullptr;
        delete dish_queue_.front();
        dish_queue_.pop();
    }
}

/**
* Replenishes a specific ingredient at a given station from the backup ingredients stock by a specified quantity.
* @param station_name A string representing the name of the station.
* @param ingredient_name A string representing the name of the ingredient to replenish.
* @param quantity An integer representing the amount to replenish.
* @pre None.
* @post If the ingredient is found in the backup ingredients stock and has
sufficient quantity, it is added to the station's ingredient stock by the
specified amount, and the function returns true.
* The quantity of the ingredient in the backup stock is decreased by the specified amount.
* If the ingredient in backup stock is depleted (quantity becomes zero), it is removed from the backup stock.
* If the ingredient does not have sufficient quantity in backup
    stock, or the ingredient or station is not found, returns false.
* @return True if the ingredient was replenished from backup; false otherwise.*/
bool StationManager::replenishStationIngredientFromBackup(std::string station_name, std::string ingredient_name, int quantity){
    KitchenStation *station = findStation(station_name);
    if(station == nullptr) return false;//Finds station name. If cannot find, ingredient cannot be added

    bool check = false;
    for(size_t i = 0; i < backup_ingredients_.size(); i++){ //search for ingredient
        if(backup_ingredients_[i].name == ingredient_name && backup_ingredients_[i].quantity >= quantity){
            check = true;
            backup_ingredients_[i].quantity -= quantity;
            if(backup_ingredients_[i].quantity == 0){
                backup_ingredients_.erase(backup_ingredients_.begin() + i);
            }
        }
    }
    if(check == false){
        return false; // ingredient was not found in backup storage
    } 

    //Assume backup ingredient was found and already removed from backup_ingredients_
    Ingredient replenish;
    replenish.name = ingredient_name;
    replenish.quantity = quantity;
    station->replenishStationIngredients(replenish);
    return true;
}

/**
* Sets the backup ingredients stock with the provided list of ingredients.
 * @param ingredients A vector of Ingredient objects to set as the backup stock.
 * @pre None.
 * @post The backup_ingredients_ vector is replaced with the provided ingredients.
 * @return True if the ingredients were added; false otherwise.*/
bool StationManager::addBackupIngredients(std::vector<Ingredient> ingredients){
    backup_ingredients_ = ingredients;
    return true;
}

/**
* Adds a single ingredient to the backup ingredients stock.
* @param ingredient An Ingredient object to add to the backup stock.
* @pre None.
* @post If the ingredient already exists in the backup stock, its quantity is increased by the ingredient's quantity.
* If the ingredient does not exist, it is added to the backup stock.
* @return True if the ingredient was added; false otherwise.*/
bool StationManager::addBackupIngredient(Ingredient ingredient){
    if(ingredient.quantity <= 0) return false; //whats the edge case to be false?
    for(size_t i=0;i<backup_ingredients_.size();i++){
        if(backup_ingredients_[i].name == ingredient.name){
            backup_ingredients_[i].quantity += ingredient.quantity;
            return true;
        }
    }
    backup_ingredients_.push_back(ingredient);
    return true;
}

/**
* Empties the backup ingredients vector
* @post The backup_ingredients_ private member variable is empty.*/
void StationManager::clearBackupIngredients(){
    backup_ingredients_ = std::vector<Ingredient>();
}

/**
* Processes all dishes in the queue and displays detailed results.
* @pre: None.
* @post: All dishes are processed, and detailed information is displayed
        (as per the format in the specifications), including station replenishments
        and preparation results.
* If a dish cannot be prepared even after replenishing ingredients, it
    stays in the queue in its original order...
* i.e. if multiple dishes cannot be prepared, they will remain in the queue in the same order.*/
void StationManager::processAllDishes(){
    // if(dish_queue_.empty()) return; //checks if queue is empty

    // Node<KitchenStation*>* ks = getHeadNode();
    // if(ks == nullptr) return; //if there are no more nodes
        
    // std::queue<Dish*> incompleteDishes;
    
    // do{
    //     Dish* dish = getDishQueue().front();
    //     std::vector<Ingredient> dishIng = dish->getIngredients();
    //     bool dishCompleted =  false;
    //     std::cout  << "PREPARING DISH: " << dish->getName() << std::endl;
    //     while(!(ks == nullptr || dishCompleted)){//If there are no more kitchen stations to check or a dish is completed, stop traversing the KitchenStation Nodes
    //         std::vector<Dish*> ksDishes = ks->getItem()->getDishes();
            
    //         for(size_t i = 0; i < ksDishes.size(); i++){
    //             if(ksDishes[i]->getName() != dish->getName()) continue;

    //             //Matching Dish in KitchenStation is found
    //             std::cout << ks->getItem()->getName() << " attempting to prepare " << dish->getName() << "..." << std::endl;

    //             if(ks->getItem()->canCompleteOrder(dish->getName())){//Complete on first try
    //                 ks->getItem()->prepareDish(dish->getName());
    //                 dish_queue_.pop();
    //                 dishCompleted = true;
    //                 break;
    //             }

    //             //Attempting backup
    //             std::cout << ks->getItem()->getName() << ": Insufficient ingredients. Replacing ingredients...\n";
    //             if(canCompleteWithBackup(ks->getItem(),dish)){
    //                 std::cout << ks->getItem()->getName() << ": Ingredients Replenished.\n";
    //                 prepareDishWithBackup(ks->getItem(),dish);
    //                 dishCompleted = true;
    //                 break;
    //             }
    //             incompleteDishes.push(dish_queue_.front());
    //             dish_queue_.pop();
    //         }
    //     }
    //     if(!dishCompleted){
    //         incompleteDishes.push(dish_queue_.front());
    //         dish_queue_.pop();
    //     }
    // }while (!dish_queue_.empty());
    // dish_queue_ = incompleteDishes;
    // std::cout << "\n\nAll dishees have been processed.";
}

//helper function
// bool StationManager::canCompleteWithBackup(KitchenStation* ks, Dish* dish){
//     for(size_t i = 0; i < dish->getIngredients().size(); i++){
//         for(size_t j = 0; j < ks->getIngredientsStock().size(); j++){
//             if(dish->getIngredients()[i].name == ks->getIngredientsStock()[j].name){
//                 bool ingredientFound = false;
//                 if(dish->getIngredients()[i].required_quantity < ks->getIngredientsStock()[j].quantity){// If There is enough in Kitchen Stock. continue
//                     break;
//                 }
//                 else{
//                     for(size_t k = 0; k < backup_ingredients_.size(); k++){
//                         if(dish->getIngredients()[i].name == backup_ingredients_[k].name){
//                             if(dish->getIngredients()[i].required_quantity < ks->getIngredientsStock()[j].quantity + backup_ingredients_[k].quantity){  // If the required quantity is less than the quantity and backup's quantity combined
//                                 ingredientFound = true;
//                                 break;
//                             }
//                             else return false;
//                         }

//                     }
//                 }
//                 if(ingredientFound) break;
//             }
//         }
//     }
//     return true;
// }

//helper function 
// bool StationManager::prepareDishWithBackup(KitchenStation* ks, Dish* dish){
//     for(size_t i= 0; i < dish->getIngredients().size(); i++){
//         for(size_t j = 0; j < ks->getIngredientsStock().size(); j++){
//             bool backupFound = false;
//             if(dish->getIngredients()[i].name == ks->getIngredientsStock()[j].name){
//                 if(dish->getIngredients()[i].required_quantity < ks->getIngredientsStock()[j].quantity){
//                     ks->getIngredientsStock()[j].quantity -= dish->getIngredients()[i].required_quantity;
//                     break;
//                 }
//                 for(size_t k = 0; k < backup_ingredients_.size(); k++){
//                     if(dish->getIngredients()[i].name == backup_ingredients_[k].name){
//                         if(dish->getIngredients()[i].required_quantity < ks->getIngredientsStock()[j].quantity + backup_ingredients_[k].quantity){
//                             replenishStationIngredientFromBackup(ks->getName(),dish->getIngredients()[i].name,dish->getIngredients()[i].required_quantity - ks->getIngredientsStock()[k].quantity);
//                             ks->removeIngredient(dish->getIngredients()[i].name);
//                             backupFound = true;
//                             break;
//                         } else return false;
//                     }
//                 }
//             }
//             if(backupFound) break;
//         }
//     }
//     return true;
// }