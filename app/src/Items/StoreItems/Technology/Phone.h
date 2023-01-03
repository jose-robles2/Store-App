#pragma once
#include "../../Item.h"
class Phone : public Item {
  public: 
    Phone(string name, double price, int count) : Item(name, price, count) {
      this->itemType = "Technology"; 
    };
    string get_item_type() {return this->itemType; }
  private:
    string itemType;   
};