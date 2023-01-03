#pragma once
#include "../../Item.h"
class Computer : public Item {
  public: 
    Computer(string name, double price, int count) : Item(name, price, count) {
      this->itemType = "Technology"; 
    };
    string get_item_type() {return this->itemType; }
  private:
    string itemType;   
};