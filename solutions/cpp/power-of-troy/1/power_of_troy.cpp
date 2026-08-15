#include "power_of_troy.h"

namespace troy {
    void give_new_artifact(human& ref, std::string new_power){
        ref.possession = std::make_unique<artifact>(new_power);
    }

    void exchange_artifacts(std::unique_ptr<artifact>& poss1, std::unique_ptr<artifact>& poss2){
        std::swap(poss1, poss2);
    }
    void manifest_power(human& ref, std::string str){
        ref.own_power = std::make_shared<power>(str);
    }
    void use_power(human& caster, human& target){
        target.influenced_by = caster.own_power;
    }
    int power_intensity(const human& human_ref) {
    if (!human_ref.own_power) {
        return 0;
    }
    return human_ref.own_power.use_count(); // 1 owner + N targets
}
}  // namespace troy
