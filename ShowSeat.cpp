#pragma once
#include "Seat.cpp"

enum class SeatStatus { AVAILABLE, BOOKED };

class ShowSeat {
private:
    Seat seat;
    SeatStatus status;   // private -> Encapsulation, will change only through bookSeat()

public:
    ShowSeat() : status(SeatStatus::AVAILABLE) {}
    ShowSeat(Seat s) : seat(s), status(SeatStatus::AVAILABLE) {}

    bool checkAvailability() const { return status == SeatStatus::AVAILABLE; }

    void bookSeat()    { status = SeatStatus::BOOKED; }   
    void releaseSeat() { status = SeatStatus::AVAILABLE; } 

    Seat getSeat() const { return seat; }
    SeatStatus getStatus() const { return status; }
};
