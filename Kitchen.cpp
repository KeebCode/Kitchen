#include "Kitchen.hpp"

Kitchen::Kitchen() : ArrayBag<Dish*>(), total_prep_time_(0), count_elaborate_(0) {
}
bool Kitchen::newOrder(Dish* new_dish)
{
    if (add(new_dish))
    {
        total_prep_time_ += new_dish->getPrepTime();
        //std::cout<< "Dish added: "<<new_dish.getName() << std::endl;
        //if the new dish has 5 or more ingredients AND takes an hour or more to prepare, increment count_elaborate_
        if (new_dish->getIngredients().size() >= 5 && new_dish->getPrepTime() >= 60)
        {
            //std::cout << "Elaborate dish added: "<<new_dish.getName() << std::endl;
            count_elaborate_++;
        }
        return true;
    }
    return false;
}
bool Kitchen::serveDish(Dish* dish_to_remove)
{
    if (getCurrentSize() == 0)
    {
        return false;
    }
    if (remove(dish_to_remove))
    {
        total_prep_time_ -= dish_to_remove->getPrepTime();
        if (dish_to_remove->getIngredients().size() >= 5 && dish_to_remove->getPrepTime() >= 60)
        {
            count_elaborate_--;
        }
        return true;
    }
    return false;
}
int Kitchen::getPrepTimeSum() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    return total_prep_time_;
}
int Kitchen::calculateAvgPrepTime() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    double total_prep_time_ = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        total_prep_time_ += items_[i]->getPrepTime();
    }
    total_prep_time_ = total_prep_time_ / getCurrentSize();
    // std::cout<< "Total prep time: "<<total_prep_time_ << std::endl;
    // std::cout<<"rounded: "<<round(total_prep_time_)<<std::endl;
    return round(total_prep_time_);
}
int Kitchen::elaborateDishCount() const
{
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return count_elaborate_;
}
double Kitchen::calculateElaboratePercentage() const
{
    // //Computes the percentage of vegetarian dishes in the kitchen rounded up to 2 decimal places.
    // double elaborate_dish = count_elaborate_;
    // std::cout << elaborate_dish << std::endl;
    // double total_dish = getCurrentSize();
    // std::cout << total_dish << std::endl;
    // double percentage = (elaborate_dish / total_dish) * 10000;
    // std::cout << percentage << std::endl;
    // percentage = round(percentage);
    // std::cout << percentage << std::endl;
    // percentage = percentage / 100;
    // std::cout << percentage << std::endl;
    // return percentage;
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return round(double(count_elaborate_) / double(getCurrentSize()) * 10000)/100;
    //return count_elaborate_ / getCurrentSize();
}
int Kitchen::tallyCuisineTypes(const std::string& cuisine_type) const{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if (items_[i]->getCuisineType() == cuisine_type)
        {
            count++;
        }
    }
    return count;
}
int Kitchen::releaseDishesBelowPrepTime(const int& prep_time)
{
    int count = 0;
    int num= getCurrentSize();
    for (int i = 0; i < num; i++)
    {
        if (items_[i]->getPrepTime() < prep_time)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}
int Kitchen::releaseDishesOfCuisineType(const std::string& cuisine_type)
{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if (items_[i]->getCuisineType() == cuisine_type)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}
void Kitchen::kitchenReport() const
{
    std::cout << "ITALIAN: " << tallyCuisineTypes("ITALIAN") << std::endl;
    std::cout << "MEXICAN: " << tallyCuisineTypes("MEXICAN") << std::endl;
    std::cout << "CHINESE: " << tallyCuisineTypes("CHINESE") << std::endl;
    std::cout << "INDIAN: " << tallyCuisineTypes("INDIAN") << std::endl;
    std::cout << "AMERICAN: " << tallyCuisineTypes("AMERICAN") << std::endl;
    std::cout << "FRENCH: " << tallyCuisineTypes("FRENCH") << std::endl;
    std::cout << "OTHER: " << tallyCuisineTypes("OTHER") << std::endl<<std::endl;
    std::cout << "AVERAGE PREP TIME: " << calculateAvgPrepTime() << std::endl;
    std::cout << "ELABORATE DISHES: " << calculateElaboratePercentage() << "%" << std::endl;
}

// Project 4 
/**
    * Parameterized constructor.
    * @param filename The name of the input CSV file containing dish information.
    * @pre The CSV file must be properly formatted.
    * @post Initializes the kitchen by reading dishes from the CSV file and storing them as `Dish*`.*/
//Kitchen::Kitchen(const std::string& filename):Kitchen(){}    
Kitchen::Kitchen(const std::string filename){
    std::ifstream file(filename);    
    std::string dishline;

    std::getline(file, dishline, '\n' ); // skip label line
    while(std::getline(file, dishline, '\n' )){
        std::stringstream line(dishline);
        std::string dishtype;
        std::getline(line, dishtype, ','); // APPETIZER, MAIN COURSE, OR DESSERT
        std::getline(line, dishline, '\n');
        Dish* adder;
        if(dishtype == "APPETIZER"){
            adder = parseAppetizer(dishline);
        }
        else if(dishtype == "MAINCOURSE"){
            adder = parseMainCourse(dishline);
        }
        else if(dishtype == "DESSERT"){
            adder = parseDessert(dishline);
        }
        else exit(1);
        newOrder(adder);
    }
}

/**
    helper function
    @param input input from csv string
    @brief This function's purpose is to turn the string into their matching enum.
    @return Returns the CuisineType enum
*/
Dish::CuisineType Kitchen::stringtoCuisine(std::string input){
    if(input == "ITALIAN"){
        return Dish::ITALIAN;
    }
    else if(input == "MEXICAN"){
        return Dish::MEXICAN;
    }
    else if(input == "CHINESE"){
        return Dish::CHINESE;
    }
    else if(input == "INDIAN"){
        return Dish::INDIAN;
    }
    else if(input == "AMERICAN"){
        return Dish::AMERICAN;
    }
    else if(input == "FRENCH"){
        return Dish::FRENCH;
    }
    else{
        return Dish::OTHER;
    }
}

/**
    helper function
    @param dishline reads the csv line
    @brief This function's purpose is to parse the line given from the csv and formats into a Appetizer 
    @return Returns the Appetizer dish
*/
Dish* Kitchen::parseAppetizer(std::string dishline){
    std::stringstream line(dishline);
    std::string token, dishtype, name, ingredients, preparationtime, price, cuisinetype, additionalattributes;
    std::vector<std::string> store;                 ///storing ingredients
    std::getline(line, name, ',');                  // Name of Dish
    std::getline(line, ingredients, ',');           // ingredients of the dish
    std::stringstream ingredientlist(ingredients); 
    while(std::getline(ingredientlist, token, ';')){ store.push_back(token); } // pushes ingredient list into vector store
    std::getline(line, preparationtime, ',');       //preptime of the dish
    std::getline(line, price, ',');                 //price of the dish
    std::getline(line, cuisinetype, ',');           //the cuisine of the dish

    // Appetizer Additional Attributes
    Appetizer::ServingStyle style;
    std::string spicy;
    bool vegetarian;

    std::getline(line, additionalattributes, ',');  //additional comments about the dish
    std::stringstream additionalattributeslist(additionalattributes);
    std::getline(additionalattributeslist, token, ';');

    if(token == "PLATED"){
        style = Appetizer::PLATED;
    }
    else if(token == "FAMILY_STYLE"){
        style = Appetizer::FAMILY_STYLE;
    }
    else if(token == "BUFFET"){
        style = Appetizer::BUFFET;
    }

    std::getline(additionalattributeslist, token, ';');
    spicy = token;

    std::getline(additionalattributeslist, token, ';');
    vegetarian = token == "true";
    
    // std::cerr << "Name: " << name << std::endl;
    // for(std::string x: store){
    //     std::cerr << "Ingredients: " << x << std::endl;
    // }
    // std::cerr << "Preptime: " << preparationtime << std::endl;
    // std::cerr << "Prince: " << price << std::endl;
    // std::cerr << "Cuisine: " << cuisinetype << std::endl;

    return new Appetizer(
        name, 
        store, 
        stoi(preparationtime), 
        stod(price), 
        stringtoCuisine(cuisinetype),
        style,
        stoi(spicy),
        vegetarian
    );
}

/**
    helper function
    @param dishline reads the csv line
    @brief This function's purpose is to parse the line given from the csv and formats into a MainCourse 
    @return Returns the MainCourse dish
*/
Dish* Kitchen::parseMainCourse(std::string dishline){
    std::stringstream line(dishline);
    std::string token, dishtype, name, ingredients, preparationtime, price, cuisinetype, additionalattributes;
    std::vector<std::string> store;                 ///storing ingredients
    std::getline(line, name, ',');                  // Name of Dish
    std::getline(line, ingredients, ',');           // ingredients of the dish
    std::stringstream ingredientlist(ingredients); 
    while(std::getline(ingredientlist, token, ';')){ store.push_back(token); } // pushes ingredient list into vector store
    std::getline(line, preparationtime, ',');       //preptime of the dish
    std::getline(line, price, ',');                 //price of the dish
    std::getline(line, cuisinetype, ',');           //the cuisine of the dish
    
    MainCourse::CookingMethod method;
    std::string protein;

    std::getline(line, token, ';'); //Cooking Type

    if(token == "GRILLED"){
        method = MainCourse::GRILLED;
    }
    else if(token == "BAKED"){
        method = MainCourse::BAKED;
    }
    else if(token == "BOILED"){
        method = MainCourse::BOILED;
    }
    else if(token == "FRIED"){
        method = MainCourse::FRIED;
    }
    else if(token == "STEAMED"){
        method = MainCourse::STEAMED;
    }
    else if(token == "RAW"){
        method = MainCourse::RAW;
    }
    else{
        method = MainCourse::GRILLED;
    }

    std::getline(line, protein, ';');                   //protein_type
    
    std::vector<MainCourse::SideDish> sidestore;        //sideDish

    std::string sidedishline;
    std::getline(line, sidedishline, ';');
    std::stringstream sidedishstream(sidedishline);
    
    std::string sidedishname, sidedishcat;


    MainCourse::SideDish side1;
    std::getline(sidedishstream,side1.name,':');
    std::getline(sidedishstream,sidedishcat,'|');
    side1.category = stringtoCategory(sidedishcat);
    sidestore.push_back(side1);

    MainCourse::SideDish side2;
    std::getline(sidedishstream,side2.name,':');
    std::getline(sidedishstream,sidedishcat,';');
    side2.category = stringtoCategory(sidedishcat);
    sidestore.push_back(side2);

    std::getline(line, token, ','); // Gluten_free
    
    // std::cerr << "Name: " << name << std::endl;
    // for(std::string x: store){
    //     std::cerr << "Ingredients: " << x << std::endl;
    // }
    // std::cerr << "Preptime: " << preparationtime << std::endl;
    // std::cerr << "Prince: " << price << std::endl;
    // std::cerr << "Cuisine: " << cuisinetype << std::endl;

    return new MainCourse(
        name,
        store,
        stoi(preparationtime), 
        stod(price),
        stringtoCuisine(cuisinetype),
        method,
        protein,
        sidestore,
        token == "true"
    );
}

MainCourse::Category Kitchen::stringtoCategory(std::string cat){
    if(cat == "GRAIN"){
        return MainCourse::Category::GRAIN;
    }
    else if(cat == "PASTA"){
        return MainCourse::Category::PASTA;
    }
    else if(cat == "LEGUME"){
        return MainCourse::Category::LEGUME;
    }
    else if(cat == "BREAD"){
        return MainCourse::Category::BREAD;
    }
    else if(cat == "SALAD"){
        return MainCourse::Category::SALAD;
    }
    else if(cat == "SOUP"){
        return MainCourse::Category::SOUP;
    }
    else if(cat == "STARCHES"){
        return MainCourse::Category::STARCHES;
    }
    else if(cat == "VEGETABLE"){
        return MainCourse::Category::VEGETABLE;
    }
    else{
        return MainCourse::Category::GRAIN;
    }
}

/**
    helper function
    @param dishline reads the csv line
    @brief This function's purpose is to parse the line given from the csv and formats into a Dessert 
    @return Returns the Dessert dish
*/
Dish* Kitchen::parseDessert(std::string dishline){
    std::stringstream line(dishline);
    std::string token, dishtype, name, ingredients, preparationtime, price, cuisinetype, additionalattributes;
    std::vector<std::string> store;                 ///storing ingredients
    std::getline(line, name, ',');                  // Name of Dish
    std::getline(line, ingredients, ',');           // ingredients of the dish
    std::stringstream ingredientlist(ingredients); 
    while(std::getline(ingredientlist, token, ';')){ store.push_back(token); } // pushes ingredient list into vector store
    std::getline(line, preparationtime, ',');       //preptime of the dish
    std::getline(line, price, ',');                 //price of the dish
    std::getline(line, cuisinetype, ',');           //the cuisine of the dish
    
    //Dessert Additional Attributes
    Dessert::FlavorProfile profile;
    std::string sweet;
    std::string nuts; 
    
    std::getline(line, additionalattributes, ',');  //additional comments about the dish
    std::stringstream additionalattributeslist(additionalattributes);
    std::getline(additionalattributeslist, token, ';'); // first token: Flavor Profile

    if(token == "SWEET"){
        profile = Dessert::SWEET;
    }
    else if(token == "BITTER"){
        profile = Dessert::BITTER;
    }
    else if(token == "SOUR"){
        profile = Dessert::SOUR;
    }
    else if(token == "SALTY"){
        profile = Dessert::SALTY;
    }
    else if(token == "UMAMI"){
        profile = Dessert::UMAMI;
    }

    std::getline(additionalattributeslist, sweet, ';');
    std::getline(additionalattributeslist, nuts, ';');
    
    // std::cerr << "Name: " << name << std::endl;
    // for(std::string x: store){
    //     std::cerr << "Ingredients: " << x << std::endl;
    // }
    // std::cerr << "Preptime: " << preparationtime << std::endl;
    // std::cerr << "Prince: " << price << std::endl;
    // std::cerr << "Cuisine: " << cuisinetype << std::endl;

    return new Dessert(
        name,
        store,
        stoi(preparationtime), 
        stod(price),
        stringtoCuisine(cuisinetype), 
        profile,
        stoi(sweet),
        nuts == "true"
    );
}

/**
    * Adjusts all dishes in the kitchen based on the specified dietary accommodation.
    * @param request A DietaryRequest structure specifying the dietary accommodations.
    * @post Calls the `dietaryAccommodations()` method on each dish in the kitchen to adjust them accordingly.*/
void Kitchen::dietaryAdjustment(const Dish::DietaryRequest& request){
    for(int i = 0; i < item_count_; i++){
        items_[i]->dietaryAccommodations(request);
    }
}

/**
    * Displays all dishes currently in the kitchen.
    * @post Calls the `display()` method of each dish.*/
void Kitchen::displayMenu() const{ 
    for(int i = 0; i < item_count_; i++){
        items_[i]->display();
    }
}

/**
    * Destructor.
    * @post Deallocates all dynamically allocated dishes to prevent memory leaks.*/
Kitchen::~Kitchen() {
    // while(!isEmpty()) {
    //     delete items_[0];
    // }
    clear();
}