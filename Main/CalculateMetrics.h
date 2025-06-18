#ifndef CALCULATEMETRICS_H
#define CALCULATEMETRICS_H

#include <iostream>
#include <vector>
#include "Human.h"
#include <map>

class CalculateMetrics
{
public:
    static std::unordered_map<std::string, int> simpleItemRatio(const std::vector<Human> &humans); 
    static std::unordered_map<std::string, int> compositeItemRatio(const std::vector<Human> &humans, std::string item); 
    static int countByProfessionAndDecade(const std::vector<Human> &humans, const std::string &professionFilter, std::map<std::string, int> &output);
    static int averageAge(const std::vector<Human> &humans);
};

#endif