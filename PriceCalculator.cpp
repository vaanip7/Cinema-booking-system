#pragma once
#include <vector>
#include "ShowSeat.cpp"

// Single Responsibility: turns a list of seats into a total amount -- pricing only.
class PriceCalculator {
public:
    static double calculateTotal(const std::vector<ShowSeat*>& seats) {
        double total = 0.0;
        for (ShowSeat* s : seats) {
            total += priceForType(s->getSeat().getSeatType());
        }
        return total;
    }

private:
    static double priceForType(SeatType type) {
        // Constants instead of magic numbers
        const double SILVER_PRICE   = 150.0;
        const double GOLD_PRICE     = 250.0;
        const double PLATINUM_PRICE = 400.0;

        switch (type) {
            case SeatType::SILVER:   return SILVER_PRICE;
            case SeatType::GOLD:     return GOLD_PRICE;
            case SeatType::PLATINUM: return PLATINUM_PRICE;
        }
        return 0.0;
    }
};
