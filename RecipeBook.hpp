/**
 * @file RecipeBook.hpp
 * @brief This file contains the implementation of the RecipeBook class, which represents a RecipeBook in the Recipe.
 * 
 * The RecipeBook class includes methods to manage a Recipe.
 * @date Due: 12/16
 * @author Weini Li
 */
#ifndef RECIPE_BOOK_
#define RECIPE_BOOK_

#include <string>
#include "BinarySearchTree.hpp"
#include <fstream>
struct Recipe{
    std::string name_;
    int difficulty_level_;
    std::string description_;
    bool mastered_;
    
    public: 
    /**
    * Default constructor.
    * @post: Initializes name_ and description_ to empty strings, difficulty_level_ to 0, and mastered_ to false.*/
    Recipe();

    /**
    * Parameterized Constructor.
    * @param name The name of the recipe. Operator Overloads
        Implement the following operators based on difficulty_level_ :
    * @param difficulty_level The difficulty level of the recipe.
    * @param description A brief description of the recipe.
    * @param mastered Indicates whether the recipe has been mastered (default is false).
    * @post: Initializes the Recipe with the provided values.*/
    Recipe(std::string name, int difficulty_level, std::string description, bool mastered);

    /**
    * Equality operator.
    * @param other A const reference to another Recipe.
    * @return True if difficulty_level_ is equal to other's difficulty_level_; false otherwise.*/
    bool operator==(const Recipe& other);

    /**
    * Less-than operator.
    * @param other A const reference to another Recipe.
    * @return True if difficulty_level_ is less than other's difficulty_level_;
    false otherwise.*/
    bool operator<(const Recipe& other);

    /**
    * Greater-than operator.
    * @param other A const reference to another Recipe.
    * @return True if difficulty_level_ is greater than other's difficulty_level_; false otherwise.*/
    bool operator>(const Recipe& other);
};

class RecipeBook: public BinarySearchTree<Recipe>{
    public:
    /**
    * Default Constructor.
    * @post: Initializes an empty RecipeBook.*/
    RecipeBook();

    /**
    * Parameterized Constructor.
    * @param filename A const reference to a string representing the name of a CSV file.
    * @post: The RecipeBook is populated with Recipes from the CSV file.
    * The file format is as follows:
    * name,difficulty_level,description,mastered
    * Ignore the first line. Each subsequent line represents a Recipe to be added to the RecipeBook.*/
    RecipeBook(const std::string& filename);

    /** Task 3
    * Finds a Recipe in the tree by name.
    * @param name A const reference to the name.
    * @return A pointer to the node containing the Recipe with the given difficulty level, or nullptr if not found.*/
    std::shared_ptr<BinaryNode<Recipe>> findRecipe(const std::string& name);

    /** Task 4
    * Adds a Recipe to the tree.
    * @param recipe A const reference to a Recipe object.
    * @pre: The Recipe does not already exist in the tree (based on name).
    * @post: The Recipe is added to the tree in BST order (based on difficult level).
    * @return: True if the Recipe was successfully added; false if a Recipe with the same name already exists.*/
    bool addRecipe(const Recipe recipe);

    /** Task 5
    * Removes a Recipe from the tree by name.
    * @param name A const reference to a string representing the name of the Recipe.
    * @post: If found, the Recipe is removed from the tree.
    * @return: True if the Recipe was successfully removed; false otherwise.*/
    bool removeRecipe(const std::string& name);

    /** Task 6
    * Clears all Recipes from the tree.
    * @post: The tree is emptied, and all nodes are deallocated.*/
    void clear();

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
    int calculateMasteryPoints(const std::string &name);

    /** Task 8
    * Balances the tree.
    * @post: The tree is balanced such that for any node, the heights of its
        left and right subtrees differ by no more than 1.
    * @note: You may implement this by performing an inorder traversal to get sorted Recipes and rebuilding the tree.*/
    void balance();

    /** Task 9
    * Displays the tree in preorder traversal.
    * @post: Outputs the Recipes in the tree in preorder, formatted as:
    * Name: [name_]
    * Difficulty Level: [difficulty_level_]
    * Description: [description_]
    * Mastered: [Yes/No]
    * (Add an empty line between Recipes)*/
    void preorderDisplay();

    private:
    /**
      @param subtree_ptr a pointer to the subtree to be searched
      @param target a reference to the item to be found
      @return a helper pointer to the node containing the target, nullptr if not found**/
    std::shared_ptr<BinaryNode<Recipe>> findRecipeHelper(std::shared_ptr<BinaryNode<Recipe>> subtree_ptr, Recipe& target);

    /**
    @param node a pointer to the subtree to be searched
    @param difficulty a integer of difficulty level.
    @return a integer of all unmastered Recipe at a specify difficulty level.*/
    int calculateMasteryPointsHelper(std::shared_ptr<BinaryNode<Recipe>>,int);

    /**
     @param root a pointer to the subtree to be searched
     @param num a reference vector of Recipe class
     @return a helper function that searches for the most left tree until it is done*/
    void InOrder(std::shared_ptr<BinaryNode<Recipe>> root, std::vector<Recipe>& num);

    /** 
        @param num a reference vector of Recipe class 
        @param start an integer of starting point
        @param end an integer of ending point
        @return a helper function the balance the tree*/
    std::shared_ptr<BinaryNode<Recipe>> BalanceTree(std::vector<Recipe>& num, int start, int end);

    /**
     @param root a pointer to the subtree to be searched
     @param num a reference vector of Recipe class
     @return a helper function that returns the most left tree to the most right tree.*/
    void PreOrder(std::shared_ptr<BinaryNode<Recipe>> root, std::vector<Recipe>& num);
};
#endif