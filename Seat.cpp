#pragma once
#include <string>

// Encapsulation
enum class SeatType { SILVER, GOLD, PLATINUM };

class Seat {
private:
    std::string seatNumber;
    SeatType seatType;

public:
    // Compile-Time Polymorphism
    Seat() : seatNumber("UNSET"), seatType(SeatType::SILVER) {}
    Seat(std::string number, SeatType type) : seatNumber(number), seatType(type) {}

    std::string getSeatNumber() const { return seatNumber; }
    SeatType getSeatType() const { return seatType; }

    std::string getSeatTypeName() const {
        switch (seatType) {
            case SeatType::SILVER:   return "SILVER";
            case SeatType::GOLD:     return "GOLD";
            case SeatType::PLATINUM: return "PLATINUM";
        }
        return "UNKNOWN";
    }
};
