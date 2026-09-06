#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include "Cinema.cpp"
#include "BookingService.cpp"

// ---------- helpers ----------
void printSeatLayout(Show* show) {
    std::cout << "\nSeat layout for " << show->getMovie()->getTitle()
              << " | Screen " << show->getScreen()->getScreenNumber()
              << " | " << show->getStartTime() << "\n";
    std::cout << "----------------------------------------------\n";
    for (ShowSeat& ss : show->getShowSeats()) {
        bool isAvailable = ss.checkAvailability();
        std::cout << ss.getSeat().getSeatNumber()
                   << " [" << ss.getSeat().getSeatTypeName() << "] : "
                   << (isAvailable ? "AVAILABLE" : "BOOKED") << "\n";
    }
}

std::vector<std::string> splitSeatInput(const std::string& line) {
    std::vector<std::string> seats;
    std::stringstream ss(line);
    std::string token;
    while (ss >> token) seats.push_back(token);
    return seats;
}

Show* pickShow(Cinema& cinema) {
    std::cout << "\n--- Movies currently playing ---\n";                 // F1
    std::vector<Movie>& movies = cinema.getMovies();
    for (size_t i = 0; i < movies.size(); i++) {
        std::cout << (i + 1) << ". " << movies[i].getTitle()
                   << " (" << movies[i].getLanguage() << ", "
                   << movies[i].getDuration() << " min)\n";
    }

    std::cout << "Choose a movie number: ";
    int movieChoice;
    if (!(std::cin >> movieChoice) || movieChoice < 1 || movieChoice > (int)movies.size()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice.\nPlease enter a valid option.\n";
        return nullptr;
    }

    std::vector<Show*> shows = cinema.getShowsForMovie(movies[movieChoice - 1].getTitle()); // F2
    std::cout << "\n--- Shows for " << movies[movieChoice - 1].getTitle() << " ---\n";
    for (size_t i = 0; i < shows.size(); i++) {
        std::cout << (i + 1) << ". Screen " << shows[i]->getScreen()->getScreenNumber()
                   << " | " << shows[i]->getStartTime() << "\n";
    }

    std::cout << "Choose a show number: ";
    int showChoice;
    if (!(std::cin >> showChoice) || showChoice < 1 || showChoice > (int)shows.size()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice.\nPlease enter a valid option.\n";
        return nullptr;
    }

    return shows[showChoice - 1];
}

// ---------- sample data ----------
void loadSampleData(Cinema& cinema) {
    cinema.addMovie(Movie("Avengers: Endgame", "English", 181));
    cinema.addMovie(Movie("Interstellar", "English", 169));

    Screen screen1(1);
    screen1.addSeat(Seat("A1", SeatType::SILVER));
    screen1.addSeat(Seat("A2", SeatType::SILVER));
    screen1.addSeat(Seat("B1", SeatType::GOLD));
    screen1.addSeat(Seat("B2", SeatType::GOLD));
    screen1.addSeat(Seat("C1", SeatType::PLATINUM));
    cinema.addScreen(screen1);

    Screen screen2(2);
    screen2.addSeat(Seat("A1", SeatType::SILVER));
    screen2.addSeat(Seat("A2", SeatType::SILVER));
    screen2.addSeat(Seat("B1", SeatType::GOLD));
    screen2.addSeat(Seat("C1", SeatType::PLATINUM));
    cinema.addScreen(screen2);

    // NOTE: screens/movies vectors are fully populated BEFORE we take their addresses,
    // so the pointers used below stay valid (no further push_back on those vectors).
    Movie* endgame = &cinema.getMovies()[0];
    Movie* interstellar = &cinema.getMovies()[1];
    Screen* scr1 = &cinema.getScreens()[0];
    Screen* scr2 = &cinema.getScreens()[1];

    cinema.addShow(Show(1, endgame, scr1, "10:00 AM"));
    cinema.addShow(Show(2, endgame, scr1, "06:00 PM"));
    cinema.addShow(Show(3, interstellar, scr2, "02:00 PM"));
}

// ---------- main menu ----------
int main() {
    Cinema cinema("City Cinemas");
    loadSampleData(cinema);
    BookingService bookingService;   // Association: main/menu interacts with BookingService

    int choice = 0;
    while (choice != 7) {
        std::cout << "\n===== MOVIE TICKET BOOKING SYSTEM =====\n";
        std::cout << "1. List Movies\n";
        std::cout << "2. View Shows & Seat Layout\n";
        std::cout << "3. Book Ticket\n";
        std::cout << "4. Print Ticket (by Booking ID)\n";
        std::cout << "5. Cancel Booking\n";
        std::cout << "6. (reserved)\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice.\nPlease enter a valid option.\n";
            continue;
        }

        if (choice == 1) {
            std::cout << "\n--- Movies currently playing ---\n";
            for (Movie& m : cinema.getMovies()) {
                std::cout << "- " << m.getTitle() << " (" << m.getLanguage()
                           << ", " << m.getDuration() << " min)\n";
            }
        }
        else if (choice == 2) {
            Show* show = pickShow(cinema);
            if (show != nullptr) printSeatLayout(show);
        }
        else if (choice == 3) {
            Show* show = pickShow(cinema);
            if (show == nullptr) continue;
            printSeatLayout(show);

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nEnter customer name: ";
            std::string name;
            std::getline(std::cin, name);
            std::cout << "Enter customer phone: ";
            std::string phone;
            std::getline(std::cin, phone);

            std::cout << "Enter seat numbers to book (space separated, e.g. A1 B2): ";
            std::string seatLine;
            std::getline(std::cin, seatLine);
            std::vector<std::string> seatNumbers = splitSeatInput(seatLine);

            Customer customer(name, phone);
            Booking* booking = bookingService.createBooking(show, customer, seatNumbers);
            if (booking == nullptr) continue;   // rejected: message already printed

            std::cout << "\nTotal amount: Rs." << booking->getTotalAmount() << "\n";
            std::cout << "Choose payment method -> 1. UPI  2. Card  3. Cash: ";
            int payChoice;
            std::cin >> payChoice;
            bookingService.processPayment(booking, payChoice);
        }
        else if (choice == 4) {
            std::cout << "Enter Booking ID (e.g. 1001): ";
            int id;
            std::cin >> id;
            Booking* booking = bookingService.findBooking(id);
            if (booking == nullptr || booking->getStatus() != BookingStatus::CONFIRMED) {
                std::cout << "No confirmed booking found with that ID.\n";
            } else {
                TicketPrinter::printTicket(booking);
            }
        }
        else if (choice == 5) {
            std::cout << "Enter Booking ID to cancel: ";
            int id;
            std::cin >> id;
            bookingService.cancelBooking(id);
        }
        else if (choice == 7) {
            std::cout << "\nThank you for using the booking system. Goodbye!\n";
        }
        else {
            std::cout << "Invalid choice.\nPlease enter a valid option.\n";
        }
    }

    return 0;
}
