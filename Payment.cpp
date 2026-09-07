#pragma once
#include <string>

//  Abstraction
// «abstract»
class Payment {
public:
    virtual bool pay(double amount) = 0;          // pure virtual 
    virtual std::string getMethodName() const = 0;
    virtual ~Payment() {}                          // virtual destructor
};
