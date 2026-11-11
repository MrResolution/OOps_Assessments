#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <vector>

class TrackTimer {
    int hours;
    int minutes;
    int seconds;

public:
    TrackTimer(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {}

    TrackTimer& operator++() {
        if (++seconds >= 60) {
            seconds = 0;
            if (++minutes >= 60) {
                minutes = 0;
                ++hours;
            }
        }
        return *this;
    }

    TrackTimer operator++(int) {
        TrackTimer temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const TrackTimer& other) const {
        return (hours == other.hours && minutes == other.minutes && seconds == other.seconds);
    }

    bool operator<(const TrackTimer& other) const {
        if (hours != other.hours) return hours < other.hours;
        if (minutes != other.minutes) return minutes < other.minutes;
        return seconds < other.seconds;
    }

    friend std::ostream& operator<<(std::ostream& os, const TrackTimer& t) {
        os << std::setfill('0') << std::setw(2) << t.hours << ":"
           << std::setfill('0') << std::setw(2) << t.minutes << ":"
           << std::setfill('0') << std::setw(2) << t.seconds << std::setfill(' ');
        return os;
    }
};

class Playlist {
    std::vector<std::string> tracks;

public:
    Playlist(std::initializer_list<std::string> list) : tracks(list) {}

    size_t size() const { return tracks.size(); }

    std::string& operator[](int index) {
        if (index < 0 || static_cast<size_t>(index) >= tracks.size()) {
            throw std::out_of_range("Playlist index out of bounds: " + std::to_string(index));
        }
        return tracks[index];
    }

    const std::string& operator[](int index) const {
        if (index < 0 || static_cast<size_t>(index) >= tracks.size()) {
            throw std::out_of_range("Playlist const index out of bounds: " + std::to_string(index));
        }
        return tracks[index];
    }
};

int main() {
    std::cout << "=== Track Timer Rollover Test ===\n";
    TrackTimer t(0, 59, 58);
    std::cout << "Start:         " << t << "\n";
    t++;
    std::cout << "After postfix: " << t << "\n";
    ++t;
    std::cout << "After prefix:  " << t << " (Rolled over to 1 hour)\n";

    std::cout << "\n=== Playlist Subscript Bounds Verification ===\n";
    Playlist pl = {"Song A - Symphony", "Song B - Concerto", "Song C - Sonata"};

    for (size_t i = 0; i < pl.size(); ++i) {
        std::cout << "Track [" << i << "]: " << pl[static_cast<int>(i)] << "\n";
    }

    try {
        std::cout << pl[-1] << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Caught Expected Exception: " << e.what() << "\n";
    }

    try {
        std::cout << pl[3] << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Caught Expected Exception: " << e.what() << "\n";
    }

    return 0;
}
