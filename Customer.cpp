#pragma once
#include <string>

class Customer {
private:
    std::string name;
    std::string phone;

public:
    Customer() {}
    Customer(std::string n, std::string p) : name(n), phone(p) {}

    std::string getName() const  { return name; }
    std::string getPhone() const { return phone; }
};
