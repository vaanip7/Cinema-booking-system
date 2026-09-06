#pragma once
#include <iostream>
#include "Payment.cpp"

// ---- Inheritance: UpiPayment IS-A Payment ----
class UpiPayment : public Payment {
public:
    // ---- Runtime Polymorphism: this override runs when called through a Payment* ----
    bool pay(double amount) override {
        std::cout << "\nProcessing UPI payment of Rs." << amount << " ...\n";
        char choice;
        std::cout << "Simulate payment result -> success? (y/n): ";
        std::cin >> choice;
        return (choice == 'y' || choice == 'Y');
    }

    std::string getMethodName() const override { return "UPI"; }
};
