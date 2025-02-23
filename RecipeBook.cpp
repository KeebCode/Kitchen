/**
 * @file RecipeBook.cpp
 * @brief This file contains the implementation of the RecipeBook class, which represents a RecipeBook in the Recipe.
 * 
 * The RecipeBook class includes methods to manage a Recipe.
 * @date Due: 12/16
 * @author Weini Li
 */
#include "RecipeBook.hpp"

/**
* Default constructor.
* @post: Initializes name_ and description_ to empty strings, difficulty_level_ to 0, and mastered_ to false.*/
Recipe::Recipe(){
    name_ = "";
    description_ = "";
    difficulty_level_ = 0;
    mastered_ = false;
}

/**
* Parameterized Constructor.
* @param name The name of the recipe. Operator Overloads
    Implement the following operators based on difficulty_level_ :
* @param difficulty_level The difficulty level of the recipe.
* @param description A brief description of the recipe.
* @param mastered Indicates whether the recipe has been mastered (default is false).
* @post: Initializes the Recipe with the provided values.*/
Recipe::Recipe(std::string name, int difficulty_level, std::string description, bool mastered){
    name_ = name;
    difficulty_level_ = difficulty_level;
    description_ = description; 
    mastered_ = mastered;
}

/**
* Equality operator.
* @param other A const reference to another Recipe.
* @return True if name_ is equal to other's name_; false otherwise.*/
bool Recipe::operator==(const Recipe& other){ return name_ == other.name_; }

/**
* Less-than operator.
* @param other A const reference to another Recipe.
* @return True if  if name_ is lexicographically greater than other's name_; false otherwise. */
bool Recipe::operator<(const Recipe& other){ return name_  < other.name_; }


/**
* Greater-than operator.
* @param other A const reference to another Recipe.
* @return True if name_ is lexicographically greater than other's name_; false otherwise.*/
bool Recipe::operator>(const Recipe& other){ return name_ > other.name_; }


/**
* Default Constructor.
* @post: Initializes an empty RecipeBook.*/
RecipeBook::RecipeBook():BinarySearchTree(){}

/**
* Parameterized Constructor.
* @param filename A const reference to a string representing the name of a CSV file.
* @post: The RecipeBook is populated with Recipes from the CSV file.
* The file format is as follows:
* name,difficulty_level,description,mastered
* Ignore the first line. Each subsequent line represents a Recipe to be added to the RecipeBook.*/
RecipeBook::RecipeBook(const std::string& filename){
    std::ifstream file(filename);
    std::string name,difficulty,desc,mastery;

    std::getline(file, name, '\n');// Skips first line

    while(std::getline(file, name, ',')){
        if(findRecipe(name) != nullptr){
            getline(file, name, '\n');
            continue;
        } 
        std::getline(file, difficulty, ',');
        std::getline(file, desc, ',');
        std::getline(file, mastery, '\n');

        add(Recipe(name, stoi(difficulty), desc, mastery == "1"));

    }


}

/** Task 3
* Finds a Recipe in the tree by name.
* @param name A const reference to the name.
* @return A pointer to the node containing the Recipe with the given difficulty level, or nullptr if not found.*/
std::shared_ptr<BinaryNode<Recipe>> RecipeBook::findRecipe(const std::string& name){
    if(isEmpty()) return nullptr;
    Recipe temp(name,0,"",0);
    return findRecipeHelper(getRoot(),temp);
}

/**
      @param subtree_ptr a pointer to the subtree to be searched
      @param target a reference to the item to be found
      @return a helper pointer to the node containing the target, nullptr if not found**/
std::shared_ptr<BinaryNode<Recipe>> RecipeBook::findRecipeHelper(std::shared_ptr<BinaryNode<Recipe>> subtree_ptr, Recipe& target){
    // Uses a binary search
  if (subtree_ptr == nullptr) return subtree_ptr; // Not found
  if ((subtree_ptr->getItem() == target)) return subtree_ptr; // Found
  if (subtree_ptr->getItem() > target) return findRecipeHelper(subtree_ptr->getLeftChildPtr(), target); // Search left subtree
  return findRecipeHelper(subtree_ptr->getRightChildPtr(), target);
}

/** Task 4
* Adds a Recipe to the tree.
* @param recipe A const reference to a Recipe object.
* @pre: The Recipe does not already exist in the tree (based on name).
* @post: The Recipe is added to the tree in BST order (based on difficult level).
* @return: True if the Recipe was successfully added; false if a Recipe with the same name already exists.*/
bool RecipeBook::addRecipe(const Recipe recipe){
    if(findRecipe(recipe.name_)) return false;
    add(recipe);
    return true;
}

/** Task 5
* Removes a Recipe from the tree by name.
* @param name A const reference to a string representing the name of the Recipe.
* @post: If found, the Recipe is removed from the tree.
* @return: True if the Recipe was successfully removed; false otherwise.*/
bool RecipeBook::removeRecipe(const std::string& name){
    Recipe temp(name,0,"",0);
    return remove(temp);
}

/** Task 6
* Clears all Recipes from the tree.
* @post: The tree is emptied, and all nodes are deallocated.*/
void RecipeBook::clear(){
    while(!isEmpty()){
        Recipe temp(getRoot().get()->getItem().name_,0,"",0);
        remove(temp);
    }
}

/** Task 7
* Calculates the number of mastery points needed to master a Recipe.
* @param name A const reference to a string representing the name of the
Recipe.
* @note: For a Recipe to be mastered, all Recipes with lower difficulty
levels must also be mastered.
* @return: An integer representing the number of mastery points needed, or
-1 if the Recipe is not found. If the recipe is already mastered, return 0.
* Note: Mastery points are calculated as the number of unmastered Recipes in
the tree with a lower difficulty level than the given Recipe. Add one if the
Recipe is not mastered.*/
int RecipeBook::calculateMasteryPoints(const std::string &name){
    std::shared_ptr<BinaryNode<Recipe>> temp = findRecipe(name);
    int counter;
    if(temp == nullptr) return -1;
    if(temp->getItem().mastered_ == 1) return 0;
    if(temp->getItem().mastered_ == 0) counter = 1;
    counter += calculateMasteryPointsHelper(getRoot(),temp->getItem().difficulty_level_);
    return counter;
}

/**
 @param node a pointer to the subtree to be searched
 @param difficulty a integer of difficulty level.
 @return a integer of all unmastered Recipe at a specify difficulty level.*/
int RecipeBook::calculateMasteryPointsHelper(std::shared_ptr<BinaryNode<Recipe>> node, int difficulty){
    int count = 0;
    if(node == nullptr) return 0;//Base Case
    //If mastered, don't need points, If not mastered, check difficulty
    //If level is below  difficulty and is not mastered, add one
    if(node->getItem().mastered_ == 0 && node->getItem().difficulty_level_ < difficulty){
        count++;
    }   
    count += calculateMasteryPointsHelper(node->getLeftChildPtr(),difficulty); //Continue traversing BT Left Child
    count += calculateMasteryPointsHelper(node->getRightChildPtr(),difficulty); // Right Child
    return count;
}

/** Task 8
    * Balances the tree.
    * @post: The tree is balanced such that for any node, the heights of its
        left and right subtrees differ by no more than 1.
    * @note: You may implement this by performing an inorder traversal to get sorted Recipes and rebuilding the tree.*/
void RecipeBook::balance(){
    std::vector<Recipe> num;
    InOrder(getRoot(), num); 
    clear();
    setRoot(BalanceTree(num,0,num.size()-1));
}

/**
 @param root a pointer to the subtree to be searched
 @param num a reference vector of Recipe class
 @return a helper function that searches for the most left tree until it is done*/
void RecipeBook::InOrder(std::shared_ptr<BinaryNode<Recipe>> root, std::vector<Recipe>& num){
    if(root == nullptr) return; //base case

    InOrder(root->getLeftChildPtr(), num);
    num.push_back(root->getItem());
    InOrder(root->getRightChildPtr(), num);
}

/** 
    @param num a reference vector of Recipe class 
    @param start an integer of starting point
    @param end an integer of ending point
    @return a helper function the balance the tree*/
std::shared_ptr<BinaryNode<Recipe>> RecipeBook::BalanceTree(std::vector<Recipe>& num, int start, int end){
    if(start > end) return nullptr;

    int mid = (start + end) / 2;
    std::shared_ptr<BinaryNode<Recipe>> mid_root = std::make_shared<BinaryNode<Recipe>>(num[mid]); 
    mid_root->setLeftChildPtr(BalanceTree(num,start,mid-1));
    mid_root->setRightChildPtr(BalanceTree(num,mid+1,end));

    return mid_root;
}

/**
     @param root a pointer to the subtree to be searched
     @param num a reference vector of Recipe class
     @return a helper function that returns the most left tree to the most right tree.*/
void RecipeBook::PreOrder(std::shared_ptr<BinaryNode<Recipe>> root, std::vector<Recipe>& num){
    if(root == nullptr) return; //base case

    num.push_back(root->getItem());
    InOrder(root->getLeftChildPtr(), num);
    InOrder(root->getRightChildPtr(), num);
}

/** Task 9
* Displays the tree in preorder traversal.
* @post: Outputs the Recipes in the tree in preorder, formatted as:
* Name: [name_]
* Difficulty Level: [difficulty_level_]
* Description: [description_]
* Mastered: [Yes/No]
* (Add an empty line between Recipes)*/
void RecipeBook::preorderDisplay(){
    std::vector<Recipe> n;
    PreOrder(getRoot(),n);
            for(size_t i=0;i<n.size();i++){
                std::cout<< "Name: " << n[i].name_
                        << "\nDifficulty Level: " << n[i].difficulty_level_
                        << "\nDescription: " << n[i].description_
                        << "\nMastered: "; 
                        if(n[i].mastered_){
                            std::cout << "Yes\n\n";
                        }
                        else{std::cout <<"No\n\n";}
                }
}
