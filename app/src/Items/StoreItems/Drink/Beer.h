#pragma once
#include "../../Item.h"
class Beer : public Item {
  public: 
    Beer(string name, double price, int count) : Item(name, price, count) {
      this->itemType = "Drink"; 
    };
    string get_item_type() {return this->itemType; }
  private:
    string itemType;   
};