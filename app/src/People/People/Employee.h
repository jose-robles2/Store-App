#pragma once
#include "Person.h"

enum Position {
    NONE, CASHIER, MANAGER //, WAREHOUSE
};

class Employee : public Person {
  public:
    Employee(string name, PersonType type, int age, int id, Position position, int years, double rating, double wage, int count) 
    : Person(name, type, age) 
    {
      this->id = id; 
      this->position = position; 
      this->yearsOfExp = years; 
      this->employeeRating = rating; 
      this->hourlyWage = wage; 
      this->sickDayCount = count; 
    };
    virtual ~Employee() {}; 

    virtual int checkout() {return 0; }; 
    void check_inventory();
    int quit_job(); 

    // Getters 
    int get_id() {return this->id; }; 
    int get_position() {return this->position; }; 
    int get_years_exp() {return this->yearsOfExp; }; 
    double get_employee_rating() {return this->employeeRating; }; 
    double get_hourly_wage() {return this->hourlyWage; };
    int get_sick_days() {return this->sickDayCount; }; 
    
    // Setters
    void set_id(int id) {this->id = id; }; 
    void set_position(Position position) {this->position = position; }; 
    void set_years_exp(int years) {this->yearsOfExp = years; }; 
    void set_employee_rating(double rating) {this->employeeRating = rating; }; 
    void set_hourly_wage(double wage) {this->hourlyWage = wage; };
    void set_sick_days(int days) {this->sickDayCount = days; }; 
  private: 
    int id; 
    Position position; 
    int yearsOfExp; 
    double employeeRating; 
    double hourlyWage; 
    int sickDayCount; 
};
