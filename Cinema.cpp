#pragma once
#include <vector>
#include <string>
#include "Movie.cpp"
#include "Screen.cpp"
#include "Show.cpp"

// Cinema = the theatre: name; owns its screens.
class Cinema {
private:
    std::string name;
    std::vector<Screen> screens;   // Composition: Cinema owns its Screens
    std::vector<Movie> movies;
    std::vector<Show> shows;

public:
    Cinema(std::string n) : name(n) {}

    void addScreen(const Screen& s) { screens.push_back(s); }
    void addMovie(const Movie& m)   { movies.push_back(m); }
    void addShow(const Show& s)     { shows.push_back(s); }

    std::vector<Movie>& getMovies()   { return movies; }
    std::vector<Show>& getShows()     { return shows; }
    std::vector<Screen>& getScreens() { return screens; }

    std::vector<Show*> getShowsForMovie(const std::string& title) {
        std::vector<Show*> result;
        for (Show& s : shows) {
            if (s.getMovie()->getTitle() == title) result.push_back(&s);
        }
        return result;
    }
};
