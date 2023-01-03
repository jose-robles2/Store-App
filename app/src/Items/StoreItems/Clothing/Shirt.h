#pragma once
#include "../../Item.h"
class Shirt : public Item {
  public: 
    Shirt(string name, double price, int count) : Item(name, price, count) {
      this->itemType = "Clothing"; 
    };
    string get_item_type() {return this->itemType; }
  private:
    string itemType;   
};