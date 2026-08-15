#ifndef DOCTOR_DATA_H
#define DOCTOR_DATA_H

#include <string>

namespace star_map {

enum class System {
    Sol,
    BetaHydri,
    AlphaCentauri,
    DeltaEridani,
    EpsilonEridani,
    Omicron2Eridani
};

} // namespace star_map

namespace heaven {

class Vessel {
public:
    std::string name;
    int generation;
    star_map::System current_system;
    int busters{0};

    // Constructor with default argument for system (defaults to Sol)
    Vessel(std::string name, int generation, star_map::System system = star_map::System::Sol);

    // Creates a new Vessel instance with incremented generation
    Vessel replicate(std::string new_name);

    // Buster management member functions
    void make_buster();
    bool shoot_buster();
};

// Non-member utility functions in heaven namespace
std::string get_older_bob(const Vessel& vessel1, const Vessel& vessel2);
bool in_the_same_system(const Vessel& vessel1, const Vessel& vessel2);

} // namespace heaven

#endif // DOCTOR_DATA_H