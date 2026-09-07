#pragma once
#include <vector>
#include <string>
#include "Show.cpp"
#include "Customer.cpp"
#include "ShowSeat.cpp"

enum class BookingStatus { PENDING, CONFIRMED, CANCELLED, FAILED };

// Booking 
class Booking {
private:
    static int nextBookingId;       

    int bookingId;
    Show* show;                    
    Customer customer;
    std::vector<ShowSeat*> seats;   
    double totalAmount;
    BookingStatus status;
    std::string paymentMethod;

public:
    Booking(Show* s, Customer c, std::vector<ShowSeat*> selectedSeats, double amount)
        : show(s), customer(c), seats(selectedSeats), totalAmount(amount), status(BookingStatus::PENDING) {
        this->bookingId = nextBookingId++;  
    }

    int getBookingId() const { return this->bookingId; }
    Show* getShow() const { return show; }
    Customer getCustomer() const { return customer; }
    std::vector<ShowSeat*> getSeats() const { return seats; }
    double getTotalAmount() const { return totalAmount; }
    BookingStatus getStatus() const { return status; }
    std::string getPaymentMethod() const { return paymentMethod; }

    void confirm(const std::string& method) {
        status = BookingStatus::CONFIRMED;
        paymentMethod = method;
    }

    void fail()   { status = BookingStatus::FAILED; }
    void cancel() { status = BookingStatus::CANCELLED; }
};

int Booking::nextBookingId = 1001;  
