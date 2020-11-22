//
// Created by andy on 20/11/20.
//

#include <utility>
#include <string>
#include "ProtectedMap.h"

bool ProtectedMap::contains(const std::string& resource) {
    std::lock_guard<std::mutex> lock(m);
    return (internal_map.find(resource) != internal_map.end());
}

void ProtectedMap::insert(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(m);
    internal_map.insert(std::pair<std::string, std::string>(key, value));
}

std::string ProtectedMap::at(const std::string& key) {
    std::lock_guard<std::mutex> lock(m);
    return internal_map.at(key);
}
