#include "speedywagon.h"

namespace speedywagon {

// Enter your code below:

bool connection_check(pillar_men_sensor *check) {
    return check != nullptr;
}

int activity_counter(pillar_men_sensor *ptr, int counter) {
    if (ptr == nullptr || counter <= 0) {
        return 0;
    }
    int totalActivity{0};
    for (int i = 0; i < counter; i++) {
        totalActivity += (ptr + i)->activity;
    }
    return totalActivity;
}

bool alarm_control(pillar_men_sensor *ptr) {
    if (ptr != nullptr && ptr->activity > 0) {
        return true;
    }
    return false;
}

// Please don't change the interface of the uv_light_heuristic function
int uv_light_heuristic(std::vector<int>* data_array) {
    if (data_array == nullptr || data_array->empty()) {
        return 0;
    }
    double avg{};
    for (auto element : *data_array) {
        avg += element;
    }
    avg /= data_array->size();
    int uv_index{};
    for (auto element : *data_array) {
        if (element > avg) ++uv_index;
    }
    return uv_index;
}

bool uv_alarm(pillar_men_sensor *ptr) {
    if (ptr == nullptr) {
        return false;
    }
    return uv_light_heuristic(&(ptr->data)) > ptr->activity;
}

}  // namespace speedywagon