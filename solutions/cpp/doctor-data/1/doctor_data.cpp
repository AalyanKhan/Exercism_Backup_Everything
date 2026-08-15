#include "doctor_data.h"

namespace heaven {

Vessel::Vessel(std::string name, int generation, star_map::System system)
    : name(std::move(name)), generation(generation), current_system(system) {}

Vessel Vessel::replicate(std::string new_name) {
    return Vessel(std::move(new_name), this->generation + 1, this->current_system);
}

void Vessel::make_buster() {
    ++busters;
}

bool Vessel::shoot_buster() {
    if (busters > 0) {
        --busters;
        return true;
    }
    return false;
}

std::string get_older_bob(const Vessel& vessel1, const Vessel& vessel2) {
    return (vessel1.generation <= vessel2.generation) ? vessel1.name : vessel2.name;
}

bool in_the_same_system(const Vessel& vessel1, const Vessel& vessel2) {
    return vessel1.current_system == vessel2.current_system;
}

} // namespace heaven