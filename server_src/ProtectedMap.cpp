//
// Created by andy on 20/11/20.
//

#include <utility>
#include <string>
#include "ProtectedMap.h"

bool ProtectedMap::contains(const std::string& resource) {
    m.lock();
    return (internal_map.find(resource) != internal_map.end());
}

void ProtectedMap::insert(const std::string& key, const std::string& value) {
    m.lock();
    internal_map.insert(std::pair<std::string, std::string>(key, value));
    m.unlock();
}

std::string ProtectedMap::at(const std::string& key) {
    m.lock();
    return internal_map.at(key);
}
