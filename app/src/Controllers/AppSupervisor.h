#pragma once
#include "./StoreSupervisor.h"

void remove_item_wrapper(Customer *customer); 


class CampaignDataRoot {
  object CampaignDataLoad
    object Campaigns
      List<>
        Campaign
        
}


class AppSupervisor {
  public: 
    AppSupervisor() {
      this->startup(); 
    }
    ~AppSupervisor() {
      delete this->store; 
    }
  private:
    void startup(); 
    void run_app(); 
    Person * get_person_from_user(); 
    void display_menu(int personType);
    void display_customer_menu();  
    void manage_customer_cart_menu(Customer *customer); 
    void display_employee_menu();  
    void display_manager_menu();  

    StoreSupervisor *store; 
    Person *currentPerson; 
};

void AppSupervisor::startup() {
  this->store = new StoreSupervisor(); 
  this->run_app(); 
}

Person *AppSupervisor::get_person_from_user() {
  auto get_person_type = []() { 
    int numInput = 0;
    while(true) {
      cout << "Select person type: " << endl << "1. Customer" << endl << "2. Employee" << endl << "3. Manager" << endl;           
      cin >> numInput; 
      if (numInput >= 1 && numInput <= 3)
        return numInput; 
      cout << "Please enter a valid integer 1-3" << endl;
      cin.clear(); cin.ignore(123, '\n'); 
      //cin.get(); 
      system("pause");
      system("cls"); 
    }  
  };
  auto validate_person_input = [](int numInput, unordered_map<string, Person*> people) { 
    while(true) {
      system("cls"); 
      string nameInput = ""; 
      cout << "Enter a name [First Last]" << endl; 
      getline(cin, nameInput);
      if (people.find(nameInput) != people.end()) {
        Person *p = people[nameInput];
        if (p->get_person_type() == numInput)
          return p; 
      }
      cout << "Please enter a name that exists within people.csv or make sure that the name entered is of the correct personType" << endl;
      cin.clear(); cin.ignore(123, '\n'); 
      //cin.get(); 
      system("pause");
      // system("cls"); 
    }      
  };

  int numInput = get_person_type(); 
  return validate_person_input(numInput, this->store->get_people()); 
} 

void AppSupervisor::run_app() {
  this->currentPerson = this->get_person_from_user(); 
  this->display_menu(this->currentPerson->get_person_type()); 
}

void AppSupervisor::display_menu(int personType) {
  switch (personType) { 
    case 1: 
      this->display_customer_menu(); 
      break; 
    case 2: 
      this->display_employee_menu(); 
      break; 
    case 3: 
      this->display_manager_menu(); 
      break; 
  }
}

void AppSupervisor::display_customer_menu() {
  auto prompt_user = [](string name) {
    while (true) {
      cout << "Logged in as: " << name << endl; 
      cout << "///////////////////////////" << endl; 
      cout << "1. Browse Store Items\n2. Checkout\n3. Leave a review\n4. Manage Cart\n5. Quit\n";
      int numInput; cin >> numInput; 
      if (numInput >= 1 && numInput <= 5)
        return numInput; 
      cout << "Please enter a valid integer 1-5" << endl;
      cin.clear(); cin.ignore(123, '\n'); cin.get(); 
      system("cls"); 
    }
  };

  int numInput; 
  Customer *customer = dynamic_cast<Customer *>(this->currentPerson);

  while(true) {
    int numInput = prompt_user(customer->get_name()); 
    switch(numInput) {
      case 1: 
        this->store->browse_store(customer); 
        break; 
      case 2: 
        customer->checkout(); 
        break; 
      case 3:
        customer->leave_review(this->store->get_people());   
        break; 
      case 4:
        manage_customer_cart_menu(customer); 
        break; 
      case 5: 
        return;
        break;  
      default: 
        break; 
    }    
  }
}

void AppSupervisor::manage_customer_cart_menu(Customer *customer) { 
  auto prompt_user = []() {
    while (true) { 
      cout << "1. View Cart\n2. Remove Item\n3. Quit\n"; 
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
        customer->view_cart(); 
        break; 
      case 2: 
        remove_item_wrapper(customer); 
        break; 
      case 3:
        return; 
        break; 
      default: 
        break; 
    }
  }
}

void remove_item_wrapper(Customer *customer) {
  if (customer->get_shopping_cart()->get_items().size() <= 0) {
    cout << "Error: Cannot remove - no items in cart\n"; 
    return; 
  }
  customer->view_cart(); 
  cout << "Select an item above: ";
  int option; cin >> option; 
  customer->remove_item_from_cart(option);   
}

void AppSupervisor::display_employee_menu() {
  // while (true) {
  //   while (true) {

  //   }
  //   switch (expression)
  //   {
  //   case /* constant-expression */:
  //     /* code */
  //     break;
    
  //   default:
  //     break;
  //   }
  // }
}

void AppSupervisor::display_manager_menu() {
  // while (true) {
  //   while (true) {

  //   }
  //   switch (expression)
  //   {
  //   case /* constant-expression */:
  //     /* code */
  //     break;
    
  //   default:
  //     break;
  //   }
  // }
}