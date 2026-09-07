#pragma once
#include <string>

// Single Responsibility
class Movie {
private:
    std::string title;
    std::string language;
    int durationMinutes;

public:
    Movie() : title(""), language(""), durationMinutes(0) {}
    Movie(std::string t, std::string lang, int duration)
        : title(t), language(lang), durationMinutes(duration) {}

    std::string getTitle() const    { return title; }
    std::string getLanguage() const { return language; }
    int getDuration() const         { return durationMinutes; }
};
