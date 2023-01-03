#pragma once
#include "../../Item.h"
class Soda : public Item {
  public: 
    Soda(string name, double price, int count) : Item(name, price, count) {
      this->itemType = "Drink"; 
    };
    string get_item_type() {return this->itemType; }
  private:
    string itemType;   
};