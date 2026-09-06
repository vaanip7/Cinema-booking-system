#pragma once
#include "Seat.cpp"

enum class SeatStatus { AVAILABLE, BOOKED };

// ShowSeat = status of ONE physical seat FOR ONE particular show.
// The same physical Seat can exist across many shows; each Show owns its own ShowSeat objects.
class ShowSeat {
private:
    Seat seat;
    SeatStatus status;   // private -> Encapsulation, changed only through bookSeat()/releaseSeat()

public:
    ShowSeat() : status(SeatStatus::AVAILABLE) {}
    ShowSeat(Seat s) : seat(s), status(SeatStatus::AVAILABLE) {}

    bool checkAvailability() const { return status == SeatStatus::AVAILABLE; }

    void bookSeat()    { status = SeatStatus::BOOKED; }     // controlled mutation
    void releaseSeat() { status = SeatStatus::AVAILABLE; }  // controlled mutation

    Seat getSeat() const { return seat; }
    SeatStatus getStatus() const { return status; }
};
