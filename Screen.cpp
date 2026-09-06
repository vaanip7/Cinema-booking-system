#pragma once
#include <vector>
#include "Seat.cpp"

// Composition: a Screen owns its Seats. If the Screen is destroyed, the Seats go with it.
class Screen {
private:
    int screenNumber;
    std::vector<Seat> seats;

public:
    Screen() : screenNumber(0) {}
    Screen(int number) : screenNumber(number) {}

    void addSeat(const Seat& seat) { seats.push_back(seat); }

    int getScreenNumber() const { return screenNumber; }
    std::vector<Seat> getSeats() const { return seats; }
};
