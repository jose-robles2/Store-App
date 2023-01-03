#pragma once
#include "../Libraries.h"

class Item {
  public: 
    Item(string name, double price, int stock) {
      this->itemName = name; 
      this->price = price; 
      this->currentStock = stock; 
    };
    // Getters
    string get_item_name() {return this->itemName; }; 
    double get_item_price() {return this->price; }; 
    int get_current_stock() {return this->currentStock; }; 

    // Setters
    void set_item_name(string name) {this->itemName = name; }; 
    void set_item_price(double price) {this->price = price; }; 
    void set_current_stock(int stock) {this->currentStock = stock; }; 

  private:
    string itemName;
    double price; 
    int currentStock; 
}; 