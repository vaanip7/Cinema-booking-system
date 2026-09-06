#pragma once
#include <iostream>
#include "Payment.cpp"

class CardPayment : public Payment {
public:
    bool pay(double amount) override {
        std::cout << "\nProcessing Card payment of Rs." << amount << " ...\n";
        char choice;
        std::cout << "Simulate payment result -> success? (y/n): ";
        std::cin >> choice;
        return (choice == 'y' || choice == 'Y');
    }

    std::string getMethodName() const override { return "Card"; }
};
