#pragma once
#include "Person.h"
#include "../Items/ShoppingCart.h"

class Customer : public Person {
  public:
    Customer(string name, PersonType type, int age, double rating, /*ShoppingCart cart,*/ string email, double budget) 
    : Person(name, type, age) {
      this->storeRating = rating; 
      this->shoppingCart = new ShoppingCart(); 
      this->email = email;
      this->budget = budget;  
    }; 
    virtual ~Customer() {
      delete this->shoppingCart; 
    }; 
    void add_item_to_cart(Item *item); 
    void remove_item_from_cart(int option); 
    virtual int checkout();// {return 0; }; 
    void leave_review(unordered_map<string, Person*> people); 
    void store_review();
    void employee_review(unordered_map<string, Person*> people);
    void view_cart();

    // Getters
    double get_store_rating() {return this->storeRating; }; 
    double get_budget() {return this->budget; };
    ShoppingCart* get_shopping_cart() { return this->shoppingCart; };
    string get_email() { return this->email; }; 

    // Setters
    void set_store_rating(double rating) {this->storeRating = rating; }; 
    void set_email(string email) { this->email = email; }; 
  protected:
    double storeRating;
    double budget;  
    ShoppingCart *shoppingCart;  
    string email; 
};

int Customer::checkout() { 
  system("cls"); 
  cout << "Items succesfully checked out!" << endl; 
  
  this->get_shopping_cart()->clear_items();  

  cout << "Shopping cart: \n";
  cout << "\tItems: " << this->get_shopping_cart()->get_count(); 
  cout << "\n\tTotal: " << this->get_shopping_cart()->get_total(); 
  cout << "\nBudget remaining: " << this->budget << endl;
  return 1; 
}

void Customer::add_item_to_cart(Item *item) { 
  int success = this->shoppingCart->add_item(item, this->budget);
  if (success)  
    this->budget -= item->get_item_price(); 
}

void Customer::remove_item_from_cart(int option) { 
  Item *removedItem = this->shoppingCart->remove_item(option-1); 
  if (removedItem) {
    this->budget += removedItem->get_item_price(); 
    removedItem->set_current_stock(removedItem->get_current_stock() + 1); 
  }
  // dont delete removedItem as this pointer points to the item in <string, Item*> inventoryMap 
}

void Customer::view_cart() { 
  this->shoppingCart->print_items();
}

void Customer::leave_review(unordered_map<string, Person*> people) {
auto prompt_user = []() {
    while (true) { 
      cout << "1. Leave Store Review\n2. Leave Employee Review\n3. Quit\n"; 
      int numInput; cin >> numInput; 
      if (numInput >=1 && numInput <=3)
        return numInput;
      cout << "Please enter a valid integer 1-3" << endl;
      cin.clear(); cin.ignore(123, '\n'); cin.get(); 
      system("cls"); 
    }
  };

  while(true) {
    int numInput = prompt_user(); 
    switch(numInput) {
      case 1: 
        this->store_review(); 
        break; 
      case 2:
        this->employee_review(people);  
        break; 
      case 3:
        return; 
        break; 
      default: 
        break; 
    }
  }}

  void Customer::store_review() {
    while(true) {
      cout << "Your current rating of the store is: " << this->storeRating << endl; 
      cout << "Would you like to update this review? [Enter y or n]\n";
      char c; cin >> c; c = tolower(c); 
      if (c == 'y') {
        cout << "Enter new rating from 0.0 to 5.0: \n"; 
        double newRating; cin >> newRating; 
        if (newRating >= 0.0 && newRating <= 5.0) {
          cout << "Store rating updated succesfully\n"; 
          this->storeRating = newRating; 
          system("pause");
          return;  
        }
        cout << "Please enter a valid decimal 0.0 - 5.0" << endl;
        cin.clear(); cin.ignore(123, '\n'); cin.get(); 
        system("cls"); 
      }
      else if (c=='n')
        break; 
      else {
        cout << "Please enter a valid integer 1-3" << endl;
        cin.clear(); cin.ignore(123, '\n'); cin.get(); 
        system("cls"); 
      } 
    }
  }

  void Customer::employee_review(unordered_map<string, Person*> people) {
    auto display_employee = [](Employee *emp) {        
        string position = ""; 
        switch(emp->get_position()) {
          case 1: 
            position = "Cashier"; 
            break; 
          case 2: 
            position = "Manager"; 
            break; 
          default: 
            position = "None"; 
            break; 
        }
        cout << "\n\tPosition: " << position << "\n\tAge: " << emp->get_age() << endl;  
    };
    
    auto display_employees =[&people, &display_employee]() {
      cout << "Select a person: \n"; 
      int label = 1; 
      for (auto it : people) {
        int type = it.second->get_person_type();
        if (type == EMPLOYEE_CLASS || type == MANAGER_CLASS) {
          Employee *emp = dynamic_cast<Employee*>(it.second);  
          cout << label << ". " << emp->get_name(); 
          display_employee(emp); 
          label++; 
        }
      }
      return label; 
    };

    auto prompt_user = [](int label) {
      while (true) {
        int numInput; 
        cin >> numInput; 
        if (numInput >= 1 && numInput <= label)
          return numInput; 
        cout << "Please enter a valid integer 1-" << label << endl;
        cin.clear(); cin.ignore(123, '\n'); cin.get(); 
        system("cls"); 
      }
    };
    
    auto find_employee = [&people](int numInput) { 
      unordered_map<string, Person*>employeeMap; 
      for (auto it : people) {
        int type = it.second->get_person_type();
        if (type == EMPLOYEE_CLASS || type == MANAGER_CLASS) {
          employeeMap.insert(it); 
        }
      }

      int count = 1; 
      for (auto it : employeeMap) {
        if (count == numInput) {
          return it.second; 
        }
        count++;
      }
      Person *notFound = nullptr;
      return notFound;  
    };

    auto process_employee_rating = [&display_employee](Person *emp) { 
      cout << "Employee chosen: "; 
      Employee *employee = dynamic_cast<Employee*>(emp);
      display_employee(employee);              
      while (true) {
        cout << "Enter new rating from 0.0 to 5.0: \n"; 
        double newRating; cin >> newRating; 
        if (newRating >= 0.0 && newRating <= 5.0) {
          cout << "Employee rating updated succesfully\n"; 
          employee->set_employee_rating(newRating);  
          system("pause");
          return;  
        }
        cout << "Please enter a valid decimal 0.0 - 5.0" << endl;
        cin.clear(); cin.ignore(123, '\n'); cin.get(); 
        system("cls"); 
      }
    };

    while (true) {
      int label = display_employees(); 
      int numInput = prompt_user(label); 
      Person *emp = find_employee(numInput); 
      if (emp)
        process_employee_rating(emp);
      else {
        cout << "Employee Not found\n";
        system("pause"); 
        system("cls"); 
      }  
      return; 
    }
  }