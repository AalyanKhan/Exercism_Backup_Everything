#include "lasagna_master.h"
#include <vector>
#include <string>

namespace lasagna_master {

// TODO: add your solution here

    int preparationTime(std::vector<std::string> layers, int avg){
        size_t total_elements = layers.size();
        return total_elements * avg;
    }
    amount quantities(std::vector<std::string> layers){
        amount result = {0 , 0.0};
        for (auto lay : layers){
            if (lay == "noodles" ){
                result.noodles += 50;
            }
            else if (lay == "sauce" ){
                result.sauce += 0.2; 
            }
        }
        return result;
    }

    void addSecretIngredient(std::vector<std::string>& ingredients1 ,const std::vector<std::string>& ingredients2) {
        ingredients1.back() = ingredients2.back();
    }
    
    std::vector<double> scaleRecipe(std::vector<double> quantities, int portion){
        std::vector<double> result{};
        for (auto quant : quantities){
            result.push_back(quant * portion / 2.0);
        }
        return result;
    }
    void addSecretIngredient(std::vector<std::string>& ingredients, std::string secret){
        ingredients.back() = secret;
    }

}  // namespace lasagna_master
