#pragma once
#include "./Warehouse.h"
#include "../People/Manager.h"
#include "../People/Customer.h"

// Declarations
int prompt_user_items_menu(int option, Item*i1, Item*i2, Item*i3);
bool process_user_input_items_menu(int numInput, Customer *customer, Item*i1, Item*i2, Item*i3);
void display_item_info (vector<Item*>items);
void add_item_to_customers_cart(int numInput, Customer *customer, Item* i1, Item* i2, Item* i3);

class StoreSupervisor {
  public: 
  StoreSupervisor() {
    init_store(); 
  } 
  ~StoreSupervisor() {
    delete this->warehouse; 
  }
  void browse_store(Customer *customer); 
  unordered_map<string, Person*> get_people() {return this->peopleMap;}

  private: 
    void init_vars(); 
    void init_store(); 
    void init_people(); 
    void read_csv(ifstream &file); 
    void create_people_records(); 
    void display_clothing(unordered_map<string,Item*> inventory, Customer *customer); 
    void display_drinks(unordered_map<string,Item*> inventory, Customer *customer); 
    void display_food(unordered_map<string,Item*> inventory, Customer *customer); 
    void display_tech(unordered_map<string,Item*> inventory, Customer *customer); 
    Warehouse *warehouse;
    vector<vector<string>> peopleData; 
    unordered_map<string, Person*> peopleMap; 
    int peopleCount; 
    int employeeCount; 
    int managerCount; 
    int customerCount; 
};

void StoreSupervisor::init_store() {
  init_vars(); 
  init_people(); 
  this->warehouse = new Warehouse(); 
}

void StoreSupervisor::init_vars() {
  this->peopleCount = 0; 
  this->employeeCount = 0; 
  this->managerCount = 0; 
  this->customerCount = 0; 
}

void StoreSupervisor::init_people() {
  ifstream file; file.open("data/people.csv", ios::in);
  if (!file.is_open())
    throw runtime_error("Could not open people.csv");   
  read_csv(file);
  create_people_records(); 
  file.close(); 
}

void StoreSupervisor::read_csv(ifstream &file) { 
  string line;   
  getline(file, line); getline(file, line); // skip headers
  while (!file.eof()) {
    getline(file, line);
    this->peopleData.push_back(split(line, ','));   
  }
}

void StoreSupervisor::create_people_records() {
  for (int i = 0; i < this->peopleData.size(); i++) {
    Person *p; 
    vector<string> currentRecord = this->peopleData[i]; 
    string name = currentRecord[0], personType = currentRecord[1]; int age = stoi(currentRecord[2]); 

    if (personType == "CUSTOMER_CLASS") {
      double storeRating = stold(currentRecord[3]); string email = currentRecord[4]; double budget = stold(currentRecord[5]); 
      p = new Customer(name, CUSTOMER_CLASS, age, storeRating, email, budget); 
      this->customerCount +=1;  
    }
    else {
      int id, yearsExp, sickDayCount; string position; double employeeRating, hourlyWage;
      id = stoi(currentRecord[3]);
      position = currentRecord[4]; 
      yearsExp = stoi(currentRecord[5]);
      employeeRating = stold(currentRecord[6]); 
      hourlyWage = stold(currentRecord[7]); 
      sickDayCount = stoi(currentRecord[8]); 

      if (personType == "MANAGER_CLASS") {
        p = new Manager(name, MANAGER_CLASS, age, id, MANAGER, yearsExp, employeeRating, hourlyWage, sickDayCount); 
        this->managerCount +=1;
      } else 
          p = new Employee(name, EMPLOYEE_CLASS, age, id, CASHIER, yearsExp, employeeRating, hourlyWage, sickDayCount); 
      this->employeeCount +=1; 
    }
    this->peopleCount +=1; 
    this->peopleMap.insert( {p->get_name(), p} );  
  }
}

void StoreSupervisor::browse_store(Customer *customer) {
  auto prompt_user_browse_store = [&customer]() {
    int numInput; 
    while (true) { 
      cout << "Welcome to our store!\nSelect a category:\n";
      cout << "Current budget: $" << customer->get_budget() << endl;
      cout << "1. Clothing\n2. Drink\n3. Food\n4. Technology\n5. View Cart\n6. Quit\n";
      cin >> numInput;
      if (numInput >=1 && numInput <=6)
        return numInput;
      cout << "Please enter a valid integer 1-6" << endl;
      cin.clear(); cin.ignore(123, '\n'); cin.get(); 
      system("cls"); 
    }
  };
  
  auto inventory = this->warehouse->get_inventory(); 
  while (true) { 
    int numInput = prompt_user_browse_store(); 
    switch(numInput) {
      case 1: 
        this->display_clothing(inventory, customer);     
        break; 
      case 2: 
        this->display_drinks(inventory, customer);     
        break; 
      case 3: 
        this->display_food(inventory, customer);     
        break;     
      case 4: 
        this->display_tech(inventory, customer);     
        break;  
      case 5: 
        customer->view_cart();
        break; 
      case 6: 
        return; 
      default: 
        break; 
    }    
  }
}

int prompt_user_items_menu(int option, Item*i1, Item*i2, Item*i3) {
  auto print_statements = [&option]() {
    system("cls");
    cout << "Current ";
    if (option == 1) cout << "clothing";
    else if (option == 2) cout << "drink"; 
    else if (option == 3) cout << "food"; 
    else if (option == 4) cout << "tech"; 
    cout << " items:\n"; 
  }; 
  
  print_statements(); 
  vector<Item*> tempItems; tempItems.push_back(i1); tempItems.push_back(i2); tempItems.push_back(i3); 
  display_item_info(tempItems);
  cout << "4. View Cart\n" <<  "5. Quit\n" << "Select an item to add to cart [1-3]\n"; 
  int numInput; cin >> numInput;
  return numInput; 
}

bool process_user_input_items_menu(int numInput, Customer *customer, Item*i1, Item*i2, Item*i3) {
  // T/F -> continue looping?   
  if (numInput >= 1 && numInput <= 3) {
      add_item_to_customers_cart(numInput, customer, i1, i2, i3); 
      cout << "Would you like to purchase another item? [Enter y or n]\n";
      char c; cin >> c; c = tolower(c);
      if (c == 'y') {return true;} else {return false;} 
    } 
    else if (numInput == 4) {
      customer->view_cart(); 
      system("pause");
      return true;  
    }
    else if (numInput == 5)
      return false; 
    else {
      cout << "Please enter a valid integer 1-5" << endl;
      cin.clear(); cin.ignore(123, '\n'); 
      system("pause"); system("cls"); 
      return true; 
    }
}

void display_item_info (vector<Item*>items) { 
  int label = 1; 
  for (int i = 0; i < items.size(); i++) {
    cout << label << ". " << items[i]->get_item_name() << endl;
    cout << "\tPrice: $" << items[i]->get_item_price() << "\n\tCurrent Stock: " << items[i]->get_current_stock() << endl; 
    label++; 
  }
}

void add_item_to_customers_cart(int numInput, Customer *customer, Item* i1, Item* i2, Item* i3) {
    switch (numInput) {
    case 1:
      customer->add_item_to_cart(i1); 
      break;
    case 2:
      customer->add_item_to_cart(i2); 
      break;    
    case 3:
      customer->add_item_to_cart(i3); 
      break;
    default:
      break;
    }
  };

void StoreSupervisor::display_clothing(unordered_map<string,Item*> inventory, Customer *customer) {
  Item * pants = inventory["Pants"], * shirt = inventory["Shirt"], * shoes = inventory["Shoes"];
  while (true) { 
    int numInput = prompt_user_items_menu(1, pants, shirt, shoes); 
    bool condition = process_user_input_items_menu(numInput, customer, pants, shirt, shoes);
    if (!condition)
      break;  
  }
} 

void StoreSupervisor::display_drinks(unordered_map<string,Item*> inventory, Customer *customer) {
  Item *soda = inventory["Soda"], *water = inventory["Water"], *beer = inventory["Beer"]; 
  while (true) { 
    int numInput = prompt_user_items_menu(1, soda, water, beer); 
    bool condition = process_user_input_items_menu(numInput, customer, soda, water, beer);
    if (!condition)
      break;  
  }
} 

void StoreSupervisor::display_food(unordered_map<string,Item*> inventory, Customer *customer) {
  Item *fruit = inventory["Fruit"], *meat = inventory["Meat"], *vegetables = inventory["Vegetables"]; 
  while (true) { 
    int numInput = prompt_user_items_menu(1, fruit, meat, vegetables); 
    bool condition = process_user_input_items_menu(numInput, customer, fruit, meat, vegetables);
    if (!condition)
      break;  
  }
} 

void StoreSupervisor::display_tech(unordered_map<string,Item*> inventory, Customer *customer) {
  Item *computer = inventory["Computer"], *phone = inventory["Phone"], *television= inventory["Television"]; 
  while (true) { 
    int numInput = prompt_user_items_menu(1, computer, phone, television); 
    bool condition = process_user_input_items_menu(numInput, customer, computer, phone, television);
    if (!condition)
      break;  
  }
} 
