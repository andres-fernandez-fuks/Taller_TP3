//
// Created by andy on 20/11/20.
//

#ifndef TP3_FUNCIONANDO_PROTECTEDMAP_H
#define TP3_FUNCIONANDO_PROTECTEDMAP_H


#include <map>
#include <string>
#include <mutex>

class ProtectedMap {
public:
    bool contains(const std::string& resource);
    void insert(const std::string& key, const std::string& value);
    std::string at(const std::string& key);
private:
    std::map<std::string,std::string> internal_map;
    std::mutex m;
};


#endif //TP3_FUNCIONANDO_PROTECTEDMAP_H
