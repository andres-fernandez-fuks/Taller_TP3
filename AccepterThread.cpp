//
// Created by andy on 7/11/20.
//

#include <vector>
#include <mutex>
#include "AccepterThread.h"
#include "ClientHandler.h"

AccepterThread::AccepterThread(std::string port, std::string info_file) :
                        keep_talking(true) {
    socket.establishConnection(NULL, port.c_str());
    socket.listenToConnections();
    this-> info_file = info_file;
}

AccepterThread::~AccepterThread() {}

void AccepterThread::run() {
    std::vector<ClientHandler*> clients;
    std::mutex m;
    m.lock();
    while (keep_talking) {
        int client_fd = socket.acceptConnection();
        if (client_fd < 0 && !keep_talking)
            break;
        if (client_fd < 0)
            throw -1;
        ClientHandler* client_handler = new ClientHandler(client_fd);
        client_handler-> setInformation(info_file);
        clients.push_back(client_handler);
        client_handler-> start();

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

void AccepterThread::stopConnections() {
    std::mutex m;
    m.lock();
    keep_talking = false;
    socket.closeConnection(true);
    m.unlock();
}