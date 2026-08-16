#pragma once
#include <vector>
#include <string> 

namespace lasagna_master {

struct amount {
    int noodles;
    double sauce;
};

int preparationTime(std::vector<std::string> layers, int avg=2);
amount quantities(std::vector<std::string> layers);
void addSecretIngredient(std::vector<std::string>& ingredients1 ,const std::vector<std::string>& ingredients2);
std::vector<double> scaleRecipe(std::vector<double> quantities, int portion);
void addSecretIngredient(std::vector<std::string>& ingredients, std::string secret);

}  // namespace lasagna_master
