#pragma once
#include "../Libraries.h"

enum PersonType {
  CUSTOMER_CLASS = 1, EMPLOYEE_CLASS = 2, MANAGER_CLASS = 3
}; 

class Person { 
  public:
    Person (string name, PersonType type, int age) {
      this->name = name; 
      this->type = type;
      this->age = age; 
    };
    ~Person() {}  
    // Person (Person &A) {
    //   this->name = A.get_name(); 
    //   this->type = A.get_person_type();
    //   this->age = A.get_age(); 
    // }

    // Person & operator = (const Person &rhs) {
    //   if (this != &rhs) {
    //     this->name = rhs.get_name(); 
    //     this->type = rhs.get_person_type();
    //     this->age = rhs.get_age(); 
    //   }
    //   return *this; 
    // }

    int virtual checkout() = 0; 

    // Getters
    string get_name() const { return this->name; }
    PersonType get_person_type() const { return this->type; }
    int get_age() const { return this->age; }

    // Setters
    void set_name(string name) { this->name = name; }
    void set_person_type(PersonType type) { this->type = type; }
    void set_age(int age) { this->age = age; }
  private: 
    string name; 
    PersonType type; 
    int age;
};
