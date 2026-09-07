#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Show.cpp"
#include "Booking.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"


class BookingService {
private:
    std::vector<Booking*> bookings;

public:
    ~BookingService() {
        for (Booking* b : bookings) delete b;
    }

    
    Booking* createBooking(Show* show, Customer customer, const std::vector<std::string>& seatNumbers) {
        std::vector<ShowSeat*> selectedSeats;

        for (const std::string& seatNo : seatNumbers) {
            ShowSeat* ss = show->findShowSeat(seatNo);

            if (ss == nullptr) {
                std::cout << "Invalid seat number: " << seatNo << "\n";
                return nullptr;
            }
            bool isSeatFree = ss->checkAvailability();
            if (!isSeatFree) {
                std::cout << "Seat " << seatNo << " is already booked.\n";
                std::cout << "Booking rejected.\n";
                return nullptr;
            }
            selectedSeats.push_back(ss);
        }

        double total = PriceCalculator::calculateTotal(selectedSeats);
        Booking* booking = new Booking(show, customer, selectedSeats, total); 
        bookings.push_back(booking);
        return booking;
    }

    
    bool processPayment(Booking* booking, int paymentChoice) {
        Payment* payment = nullptr;  

        
        if (paymentChoice == 1)      payment = new UpiPayment();   
        else if (paymentChoice == 2) payment = new CardPayment();  
        else                          payment = new CashPayment();  

        bool paymentSucceeded = payment->pay(booking->getTotalAmount());

        if (paymentSucceeded) {
            for (ShowSeat* seat : booking->getSeats()) seat->bookSeat();
            booking->confirm(payment->getMethodName());
            std::cout << "\nPayment successful via " << payment->getMethodName() << ".\n";
            TicketPrinter::printTicket(booking);
        } else {
            booking->fail();
            std::cout << "\nPayment failed.\n";
            std::cout << "Booking cancelled.\n";
            std::cout << "Seats released.\n";
            std::cout << "No ticket generated.\n";
            
        }

        delete payment;
        return paymentSucceeded;
    }

    
    bool cancelBooking(int bookingId) {
        for (Booking* b : bookings) {
            bool isConfirmed = (b->getStatus() == BookingStatus::CONFIRMED);
            if (b->getBookingId() == bookingId && isConfirmed) {
                for (ShowSeat* seat : b->getSeats()) seat->releaseSeat();
                b->cancel();
                std::cout << "\nBooking cancelled successfully.\n";
                std::cout << "Seats are AVAILABLE again.\n";
                return true;
            }
        }
        std::cout << "\nBooking not found or cannot be cancelled.\n";
        return false;
    }

    Booking* findBooking(int bookingId) {
        for (Booking* b : bookings) {
            if (b->getBookingId() == bookingId) return b;
        }
        return nullptr;
    }
};
