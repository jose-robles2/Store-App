#pragma once
#include "../../Item.h"
class Television : public Item {
  public: 
    Television(string name, double price, int count) : Item(name, price, count) {
      this->itemType = "Technology"; 
    };
    string get_item_type() {return this->itemType; }
  private:
    string itemType;   
};