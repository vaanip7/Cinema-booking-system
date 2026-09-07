#pragma once
#include <iostream>
#include "Payment.cpp"

class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        
        std::cout << "\nCollecting Rs." << amount << " in cash at the counter...\n";
        std::cout << "Cash payment received.\n";
        return true;
    }

    std::string getMethodName() const override { return "Cash"; }
};
