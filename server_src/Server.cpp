//
// Created by andy on 7/11/20.
//

#include <vector>
#include <mutex>
#include <string>
#include <utility>
#include <iostream>
#include "Server.h"
#include "ClientHandler.h"
#include "../common_src/ConnectionException.h"

Server::Server(std::string port, std::string default_get_response) :
                        keep_talking(true) {
    socket.establishConnection(NULL, port.c_str());
    socket.listenToConnections();
    default_response = std::move(default_get_response);
}

Server::~Server() {}

void Server::run() {
    std::vector<ClientHandler*> clients;
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

    for (auto each_client : clients) {
        if (!each_client)
            continue;
        each_client->stop();
        each_client->join();
        delete(each_client);
    }
    m.unlock();
}

void Server::stopConnections() {
    std::mutex m;
    m.lock();
    keep_talking = false;
    socket.closeConnection(true);
    m.unlock();
}
