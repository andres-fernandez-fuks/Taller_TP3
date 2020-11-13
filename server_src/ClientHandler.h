//
// Created by andy on 7/11/20.
//

#ifndef TP_3_CLIENTHANDLER_H
#define TP_3_CLIENTHANDLER_H


#include <atomic>
#include <string>
#include <thread>
#include "../common_src/Socket.h"
#include "HtmlRequest.h"
#include "HtmlParser.h"
#include "InfoHandler.h"
#include "Thread.h"

class ClientHandler : public Thread {
public:
    explicit ClientHandler(int socket_fd, std::mutex& mutex);
    ~ClientHandler() override;

    void sendResponse(const std::string& response);
    void respondToRequest();
    void printResult();
    void closeConnection(bool should_shutdown);
    void stop();
    void setDefaultResponse(const std::string& default_response);
    void run() override;
    bool isDead();

private:
    Socket socket = Socket(1);
    std::stringbuf buffer;
    std::string output;
    HtmlParser parser;
    InfoHandler info_handler;
    std::mutex& m;
    std::atomic<bool> finished;
    std::string getStringFromBuffer();
    HtmlRequest parseInput();
    void receiveInput();
};


#endif //TP_3_CLIENTHANDLER_H
