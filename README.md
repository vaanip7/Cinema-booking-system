# Cinema-booking-system
Menu-driven Movie Ticket Booking System in modular C++ — built for a System Design (TCS-504) assignment. Covers requirement analysis, UML class/sequence diagrams, OOP concepts, and SOLID principles, with a working booking + payment (UPI/Card/Cash) workflow.
-----------------------------------------------------------------------------------------

#✨ Features
🎞️ List movies currently playing

🕒 View shows (screen + time) for a chosen movie

💺 View live seat layout — AVAILABLE / BOOKED

🎟️ Book one or more seats (rejects already-booked seats, nothing changes)

💰 Auto-priced by seat type — SILVER ₹150 · GOLD ₹250 · PLATINUM ₹400

💳 Pay via UPI, Card, or Cash — a failed payment never confirms a booking

🧾 Printed ticket: booking ID, movie, screen, time, seats, total

❌ Cancel a booking — seats return to AVAILABLE

🛡️ Never crashes on invalid input (bad seat number, bad menu choice)



🧱 Architecture
Designed around single-responsibility entity and service classes, wired together with the correct UML relationship for each pair (composition / aggregation / association / inheritance — every choice justified with the lifetime test).

Entities: Movie, Seat, Screen, Cinema, Show, ShowSeat, Customer, Booking Services: Payment (abstract) → UpiPayment / CardPayment / CashPayment, PriceCalculator, TicketPrinter, BookingService




->OOP Concepts Demonstrated
Concept	Where
Encapsulation	ShowSeat.status, Booking.totalAmount — private, mutated only through methods
Abstraction	Payment — pure virtual pay(amount): bool
Inheritance	UpiPayment, CardPayment, CashPayment : public Payment
Runtime Polymorphism	Payment* payment; payment->pay(total);
Compile-Time Polymorphism	Overloaded Seat() constructors
Static Members	Booking::nextBookingId — unique auto-incrementing booking IDs
this Keyword	Used in Booking's constructor
Composition	Cinema → Screen, Screen → Seat, Show → ShowSeat
Aggregation	Show → Movie, Booking → ShowSeat
Association	Show → Screen, Booking → Customer


🧩 SOLID Principles
Single Responsibility — Booking never prints tickets or calculates price; TicketPrinter and PriceCalculator own those jobs.
Open/Closed — adding NetBankingPayment needs only a new Payment subclass; BookingService is untouched.
Liskov Substitution — any Payment subclass works interchangeably through a Payment*.
Interface Segregation — Payment exposes only pay()/getMethodName(), no forced refund().
Dependency Inversion — BookingService depends on the Payment abstraction, not concrete payment classes.


📁 Project Structure

One class per file, no header files — each .cpp uses #pragma once and includes only its direct dependencies, so main.cpp assembles one clean translation unit.

main.cpp              Cinema.cpp            Booking.cpp
Movie.cpp              Screen.cpp             BookingService.cpp
Seat.cpp                Show.cpp                Payment.cpp
Customer.cpp           ShowSeat.cpp           UpiPayment.cpp
                                                CardPayment.cpp
                                                CashPayment.cpp
                                                PriceCalculator.cpp
                                                TicketPrinter.cpp
🚀 Build & Run
bash
g++ -std=c++17 -Wall -Wextra main.cpp -o mtbs
./mtbs

Compiles clean with zero warnings on g++ 13.3.0.

🖥️ Demo
===== MOVIE TICKET BOOKING SYSTEM =====
1. List Movies
2. View Shows & Seat Layout
3. Book Ticket
4. Print Ticket (by Booking ID)
5. Cancel Booking
7. Exit

--- Movies currently playing ---
1. Avengers: Endgame (English, 181 min)
2. Interstellar (English, 169 min)

Seat layout for Avengers: Endgame | Screen 1 | 06:00 PM
----------------------------------------------
A1 [SILVER] : AVAILABLE
B1 [GOLD] : AVAILABLE
C1 [PLATINUM] : AVAILABLE

Total amount: Rs.150
Processing UPI payment of Rs.150 ...
Payment successful via UPI.

================ TICKET ================

Booking ID : B1001
Movie      : Avengers: Endgame
Screen     : Screen 1
Time       : 06:00 PM
Seats      : A1
Total      : Rs.150
Status     : CONFIRMED
=========================================

🛠️ Tech Stack

C++17 · OOP · UML

