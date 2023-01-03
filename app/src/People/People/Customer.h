#pragma once
#include "Person.h"
#include "../Items/ShoppingCart.h"

class Customer : public Person {
  public:
    Customer(string name, PersonType type, int age, double rating, /*ShoppingCart cart,*/ string email) 
    : Person(name, type, age) {
      this->storeRating = rating; 
      this->shoppingCart = new ShoppingCart(); 
      this->email = email; 
    }; 
    virtual ~Customer() {
      delete this->shoppingCart; 
    }; 
    virtual int checkout() {return 0; }; 
    void leave_review() {return;}; 
    int store_review();
    int employee_review();
    void view_cart() {this->shoppingCart->print_items(); }

    // Getters
    double get_store_rating() {return this->storeRating; }; 
    ShoppingCart* get_shopping_cart() { return this->shoppingCart; };
    string get_email() { return this->email; }; 

    // Setters
    void set_store_rating(double rating) {this->storeRating = rating; }; 
    //void set_shopping_cart(ShoppingCart cart) { this->shoppingCart = cart; };
    void set_email(string email) { this->email = email; }; 
  protected:
    double storeRating; 
    ShoppingCart *shoppingCart;  
    string email; 
};
