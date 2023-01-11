#pragma once
#include "../Items/Item.h"
#include "../Items/StoreItems/Clothing/Shirt.h"
#include "../Items/StoreItems/Clothing/Pants.h"
#include "../Items/StoreItems/Clothing/Shoes.h"
#include "../Items/StoreItems/Drink/Soda.h"
#include "../Items/StoreItems/Drink/Water.h"
#include "../Items/StoreItems/Drink/Beer.h"
#include "../Items/StoreItems/Food/Fruit.h"
#include "../Items/StoreItems/Food/Meat.h"
#include "../Items/StoreItems/Food/Vegetables.h"
#include "../Items/StoreItems/Technology/Computer.h"
#include "../Items/StoreItems/Technology/Phone.h"
#include "../Items/StoreItems/Technology/Television.h"

// Declaration
vector<string> split(string s, char delim);

class Warehouse {
  public: 
    Warehouse() {
      this->init_warehouse(); 
    }

    // Getters
    int get_total_item_count() {return this->totalItemCount; }; 
    double get_total_item_value() {return this->totalItemValue; }; 
    unordered_map<string, Item*> get_inventory() {return this->inventory; }; 

    // Setters
    void set_total_item_count(int count) {this->totalItemCount = count; }; 
    void add_total_item_count(int count) {this->totalItemCount += count; }; 
    void set_total_item_value(double value) {this->totalItemValue = value; };  
    void add_total_item_value(double value) {this->totalItemValue += value; };  
  private:
    void init_warehouse(); 
    void init_vars(); 
    void init_items(); 
    void read_csv(ifstream &file); 
    void create_item_records(); 
    Item* create_object(string name, double price, int stock); 

    int totalItemCount; 
    double totalItemValue;
    int foodCount; 
    int drinkCount; 
    int techCount; 
    int clothingCount; 
    vector<vector<string>> itemData; 
    unordered_map<string, Item*>inventory;    
};

void Warehouse::init_warehouse() {
  this->init_vars(); 
  this->init_items(); 
}

void Warehouse::init_vars() { 
  this->totalItemCount = 0; 
  this->totalItemValue = 0.0; 
  this->foodCount = 0; 
  this->drinkCount = 0; 
  this->techCount = 0; 
  this->clothingCount = 0; 
}

void Warehouse::init_items() { 
  ifstream file; file.open("data/items.csv", ios::in);
  if (!file.is_open())
    throw runtime_error("Could not open items.csv");   
  read_csv(file);
  create_item_records(); 
  file.close(); 
}

void Warehouse::read_csv(ifstream &file) { 
  string line; 
  getline(file, line);
  while (!file.eof()) { 
    getline(file, line); 
    this->itemData.push_back(split(line,',')); 
  } 
}

vector<string> split(string s, char delim) {
  vector<string> res; 
  string currentWord = ""; 
  for (int i = 0; s[i] != '\0'; i++) {
    if (s[i] == delim) {
      res.push_back(currentWord); 
      currentWord = ""; 
      continue;
    } 
    currentWord += s[i];  
  }
  return res;  
}

void Warehouse::create_item_records() {
  for (int i = 0; i < this->itemData.size(); i++) { 
    Item *item; 
    vector<string>currentRecord = this->itemData[i];
    string name = currentRecord[0]; double price = stold(currentRecord[1]); int stock = stoi(currentRecord[2]);
    item = create_object(name, price, stock); 
    this->inventory.insert( {item->get_item_name(), item} );
  }
}

Item * Warehouse::create_object(string name, double price, int stock) { 
  Item *i; 
  if (name == "Shirt") {
    i = new Shirt(name,price,stock); 
    this->clothingCount+=stock; 
  }
  else if (name == "Pants") { 
    i = new Pants(name,price,stock); 
    this->clothingCount+=stock; 
  }
  else if (name == "Shoes") { 
    i = new Shoes(name,price,stock);
    this->clothingCount+=stock;  
  }
  else if (name == "Soda") { 
    i = new Soda(name,price,stock);
    this->drinkCount +=stock;  
  }
  else if (name == "Water") { 
    i = new Water(name,price,stock); 
    this->drinkCount +=stock;  
  }
  else if (name == "Beer") { 
    i = new Beer(name,price,stock); 
    this->drinkCount +=stock;  
  }
  else if (name == "Fruit") { 
    i = new Fruit(name,price,stock); 
    this->foodCount +=stock;  
  }
  else if (name == "Meat") { 
    i = new Meat(name,price,stock); 
    this->foodCount +=stock;  
  }
  else if (name == "Vegetables") { 
    i = new Vegetables(name,price,stock); 
    this->foodCount +=stock;  
  }
  else if (name == "Computer") { 
    i = new Computer(name,price,stock); 
    this->techCount +=stock;  
  }
  else if (name == "Phone") { 
    i = new Phone(name,price,stock); 
    this->techCount +=stock;  
  }
  else if (name == "Television") { 
    i = new Television(name,price,stock);
    this->techCount +=stock;   
  }
  this->totalItemCount += stock; 
  this->totalItemValue += price; 
  return i; 
}