#pragma once
#include "../Libraries.h"
#include "Item.h"

class ShoppingCart { 
  public: 
    ShoppingCart(int count, vector<Item*> items, double total) {
      this->itemCount = count; 
      this->items = items; 
      this->total = total; 
    };
    ShoppingCart() {
      this->itemCount = 0;
      vector<Item*> items;  
      this->items = items; 
      this->total = 0.0; 
    };
    void add_item(Item *item);
    int remove_item(); 
    void print_items(); 

    // Getters 
    int get_count() { return this->itemCount; }; 
    vector<Item*> get_items() { return this->items; }; 
    double get_total() { return this->total; }; 

    // Setters
    void set_count(int count) { this->itemCount = count; }; 
    // void set_items(vector<Item> items) { this->items = items; }; 
    void set_total(double total) { this->total = total; }; 

  private: 
    int itemCount; 
    vector<Item*> items;
    double total;  
}; 

void ShoppingCart::add_item(Item *item) {
  if (item->get_current_stock() == 0) {
    cout << "OUT OF STOCK! Sorry for the inconvinience\n"; return; 
  }
  this->items.push_back(item);
  cout << "Item succesfully added\n";

  this->itemCount++;
  this->total += item->get_item_price(); 
  item->set_current_stock(item->get_current_stock() - 1);  
}

void ShoppingCart::print_items() { 
  cout << "Current cart: \n"; 
  for (auto item : this->items) {
    cout << "Item: " << item->get_item_name() << endl; 
    cout << "\tPrice: $" << item->get_item_price() << endl; 
  }
  cout << "Items in cart: " << this->itemCount << endl; 
  cout << "Subtotal: $" << this->total << endl; 
}