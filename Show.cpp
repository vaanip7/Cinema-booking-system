#pragma once
#include <vector>
#include <string>
#include "Movie.cpp"
#include "Screen.cpp"
#include "ShowSeat.cpp"

// Show = one screening = a Movie on a Screen at a specific time.
class Show {
private:
    int showId;
    Movie* movie;                    // Aggregation: Show does NOT own the Movie's lifetime
    Screen* screen;                  // Association: Show references an existing Screen
    std::string startTime;
    std::vector<ShowSeat> showSeats; // Composition: ShowSeats belong ONLY to this Show

public:
    Show() : showId(0), movie(nullptr), screen(nullptr) {}

    Show(int id, Movie* m, Screen* s, std::string time)
        : showId(id), movie(m), screen(s), startTime(time) {
        // Every seat on the physical screen gets its own fresh ShowSeat (starts AVAILABLE)
        for (const Seat& seat : s->getSeats()) {
            showSeats.push_back(ShowSeat(seat));
        }
    }

    int getShowId() const { return showId; }
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    std::string getStartTime() const { return startTime; }

    std::vector<ShowSeat>& getShowSeats() { return showSeats; }

    ShowSeat* findShowSeat(const std::string& seatNumber) {
        for (auto& ss : showSeats) {
            if (ss.getSeat().getSeatNumber() == seatNumber) return &ss;
        }
        return nullptr;   // Invalid seat number handled by caller
    }
};
