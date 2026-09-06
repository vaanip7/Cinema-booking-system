#pragma once
#include <string>

// ---- Abstraction: defines the payment CONTRACT only, no implementation details ----
// «abstract»
class Payment {
public:
    virtual bool pay(double amount) = 0;          // pure virtual -> makes class abstract
    virtual std::string getMethodName() const = 0;
    virtual ~Payment() {}                          // virtual destructor: safe polymorphic deletion
};
