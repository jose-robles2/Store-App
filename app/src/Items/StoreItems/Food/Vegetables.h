#pragma once
#include "../../Item.h"

class Vegetables : public Item {
  public: 
    Vegetables(string name, double price, int count) : Item(name, price, count) {
      this->itemType = "Food"; 
    };
    string get_item_type() {return this->itemType; }
  private:
    string itemType;   
};