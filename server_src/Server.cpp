//
// Created by andy on 7/11/20.
//

#include <mutex>
#include <string>
#include <utility>
#include <iostream>
#include "Server.h"
#include "ClientHandler.h"
#include "../common_src/ConnectionException.h"

Server::Server() : keep_talking(true) {}

Server::~Server() {}

void Server::run() {
    std::mutex m;
    m.lock();
    while (keep_talking) {
        int client_fd = socket.acceptConnection();
        if (client_fd < 0 && !keep_talking)
            break;
        if (client_fd < 0)
            throw ConnectionException("Error al intentar aceptar conexiones");
        auto* client_handler = new ClientHandler(client_fd);
        client_handler-> setDefaultResponse(default_response);
        clients.push_back(client_handler);
        try {
            client_handler-> start();
        }
        catch(ConnectionException& e) {
            std::cout << e.what() << std::endl;
            break;
        }
        cleanConnections();
    }
    closeAllConnections();
    m.unlock();
}

void Server::stopConnections() {
    std::mutex m;
    m.lock();
    keep_talking = false;
    socket.closeConnection(true);
    m.unlock();
}

void Server::cleanConnections() {
    std::atomic<int> counter(0);
    for (auto each_client : clients) {
        if (each_client->isDead()){
            each_client->join();
            delete(each_client);
            clients.erase(clients.begin()+counter);
        }
        counter++;
    }
}

void Server::closeAllConnections() {
    for (auto each_client : clients) {
        if (!each_client)
            continue;
        each_client->stop();
        each_client->join();
        delete(each_client);
    }
}

void Server::setConnection(const std::string& port,
                           const std::string& default_get_respomse) {
    this-> default_response = default_get_respomse;
    socket.establishConnection(nullptr, port.c_str());
    socket.listenToConnections();
}
