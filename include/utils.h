//
// Created by Usuario on 20/06/2024.
//

#ifndef MYCPPRESTPROJECT_UTILS_H
#define MYCPPRESTPROJECT_UTILS_H

#include <string>
#include <vector>

std::string readCSVToString(const std::string& filename);
std::vector<std::string> splitString(const std::string& str, const std::string& delimiter);
std::vector<std::vector<std::string>> groupData(const std::vector<std::string>& data, size_t groupSize);
void removeQuotes(std::vector<std::vector<std::string>>& data);

#endif //MYCPPRESTPROJECT_UTILS_H
