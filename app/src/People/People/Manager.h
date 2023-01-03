#pragma once
#include "Employee.h"

class Manager : public Employee {
  public: 
    Manager(string name, PersonType type, int age, int id, Position position, int years, double rating, double wage, int count) 
    : Employee(name, type, age, id, position, years, rating, wage, count) {};
    
    virtual ~Manager() {}; 
    virtual int checkout() {return 0; }; 

    int hire_employee(); 
    int fire_employee();
    int manage_sick_days(); 
    int add_sick_day();  
    int remove_sick_day();  
  private: 
};