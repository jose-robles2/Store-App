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
    int add_item(Item *item, double customerBudget);
    Item* remove_item(int option); 
    void clear_items(); 
    void print_items(); 

    // Getters 
    int get_count() { return this->itemCount; }; 
    vector<Item*> get_items() { return this->items; }; 
    double get_total() { return this->total; }; 

    // Setters
    void set_count(int count) { this->itemCount = count; }; 
    void set_total(double total) { this->total = total; }; 

  private: 
    int itemCount; 
    vector<Item*> items;
    double total;  
}; 

int ShoppingCart::add_item(Item *item, double customerBudget) {
  if (item->get_item_price() > customerBudget) {
    cout << "Item of cost $" << item->get_item_price() << " exceeds budget of $" << customerBudget << endl; 
    return 0; 
  }
  if (item->get_current_stock() == 0) {
    cout << "OUT OF STOCK! Sorry for the inconvinience\n"; 
    return 0; 
  }
  this->items.push_back(item);
  cout << "Item succesfully added\n";

  this->itemCount++;
  this->total += item->get_item_price(); 
  item->set_current_stock(item->get_current_stock() - 1);  
  return 1; 
}

Item* ShoppingCart::remove_item(int option) {
  for (int i = 0; i < this->items.size(); i++) {
    if (i==option) {
      cout << "Item found\n";
      Item *item = items[i]; 
      items.erase(items.begin() + i); 
      this->itemCount--; 
      this->total -=item->get_item_price(); 
      return item; 
    }
  }
  cout << "Item could not be found\n";
  return nullptr; 
}

void ShoppingCart::clear_items() { 
  cout << "Clearing shopping cart...\n"; 
  this->items.clear(); 
  this->itemCount = 0; 
  this->total = 0.0; 
}

void ShoppingCart::print_items() { 
  cout << "Current cart: \n"; 
  int label = 1; 
  for (auto item : this->items) {
    cout << label << ". Item: " << item->get_item_name() << endl; 
    cout << "\tPrice: $" << item->get_item_price() << endl; 
    label++;
  }
  cout << "Items in cart: " << this->itemCount << endl; 
  cout << "Subtotal: $" << this->total << endl; 
}