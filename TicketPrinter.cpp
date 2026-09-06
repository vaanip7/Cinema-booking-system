#pragma once
#include <iostream>
#include "Booking.cpp"

// Single Responsibility: format and print a ticket -- printing ONLY.
// (Booking deliberately does NOT print itself -- see SOLID: S.)
class TicketPrinter {
public:
    static void printTicket(Booking* booking) {
        std::cout << "\n================ TICKET ================\n";
        std::cout << "Booking ID : B" << booking->getBookingId() << "\n";
        std::cout << "Movie      : " << booking->getShow()->getMovie()->getTitle() << "\n";
        std::cout << "Screen     : Screen " << booking->getShow()->getScreen()->getScreenNumber() << "\n";
        std::cout << "Time       : " << booking->getShow()->getStartTime() << "\n";

        std::cout << "Seats      : ";
        std::vector<ShowSeat*> seats = booking->getSeats();
        for (size_t i = 0; i < seats.size(); i++) {
            std::cout << seats[i]->getSeat().getSeatNumber();
            if (i != seats.size() - 1) std::cout << ", ";
        }
        std::cout << "\n";

        std::cout << "Total      : Rs." << booking->getTotalAmount() << "\n";
        std::cout << "Status     : CONFIRMED\n";
        std::cout << "=========================================\n";
    }
};
