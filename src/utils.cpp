#include "../include/utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>

std::string readCSVToString(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<std::string> splitString(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    size_t len = str.length();
    size_t delimiter_len = delimiter.length();
    while (pos < len) {
        size_t find_pos = str.find(delimiter, pos);
        if (find_pos == std::string::npos) {
            tokens.push_back(str.substr(pos));
            break;
        }
        tokens.push_back(str.substr(pos, find_pos - pos));
        pos = find_pos + delimiter_len;
    }
    return tokens;
}

std::vector<std::vector<std::string>> groupData(const std::vector<std::string>& data, size_t groupSize) {
    std::vector<std::vector<std::string>> groupedData;
    for (size_t i = 0; i < data.size(); i += groupSize) {
        std::vector<std::string> group;
        for (size_t j = i; j < i + groupSize && j < data.size(); ++j) {
            group.push_back(data[j]);
        }
        groupedData.push_back(group);
    }
    return groupedData;
}

void removeQuotes(std::vector<std::vector<std::string>>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            if (i >= 1 && j == 0) {
                data[i][j] = data[i][j].substr(2, data[i][j].length() - 3);
            } else if (j == data[i].size() - 1) {
                data[i][j] = data[i][j].substr(1, data[i][j].length() - 1);
            } else {
                data[i][j] = data[i][j].substr(1, data[i][j].length() - 2);
            }
            data[i][j].erase(std::remove(data[i][j].begin(), data[i][j].end(), '"'), data[i][j].end());
            data[i][j].erase(std::remove(data[i][j].begin(), data[i][j].end(), '\\'), data[i][j].end());
        }
    }
}
