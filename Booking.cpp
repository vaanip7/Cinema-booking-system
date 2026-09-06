#pragma once
#include <vector>
#include <string>
#include "Show.cpp"
#include "Customer.cpp"
#include "ShowSeat.cpp"

enum class BookingStatus { PENDING, CONFIRMED, CANCELLED, FAILED };

// Booking = booking id, which show, which seats, total amount, status.
class Booking {
private:
    static int nextBookingId;       // ---- Static Member: shared by ALL Booking objects ----

    int bookingId;
    Show* show;                     // Association: Booking refers to a Show it does not own
    Customer customer;
    std::vector<ShowSeat*> seats;   // Aggregation: references ShowSeats owned by Show
    double totalAmount;
    BookingStatus status;
    std::string paymentMethod;

public:
    Booking(Show* s, Customer c, std::vector<ShowSeat*> selectedSeats, double amount)
        : show(s), customer(c), seats(selectedSeats), totalAmount(amount), status(BookingStatus::PENDING) {
        this->bookingId = nextBookingId++;   // ---- 'this' keyword used to disambiguate ----
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

int Booking::nextBookingId = 1001;   // static member definition -- booking IDs start at B1001
