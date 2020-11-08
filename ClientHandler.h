//
// Created by andy on 7/11/20.
//

#ifndef TP_3_CLIENTHANDLER_H
#define TP_3_CLIENTHANDLER_H


#include <atomic>
#include "Socket.h"
#include "Thread.h"
#include "HtmlRequest.h"
#include "HTMLParser.h"
#include "InfoHandler.h"

class ClientHandler : public Thread {
public:
    explicit ClientHandler(int socket_fd);
    ~ClientHandler() override;
    int receiveInput();
    void sendResponse(std::string response);
    void respondToRequest();
    void printResult();
    void closeConnection(bool should_shutdown);
    void stop();
    void setInformation(std::string info_file);
    void run() override;
    bool isDead();
private:
    Socket socket = Socket(1);
    std::stringbuf buffer;
    std::string output;
    HTMLParser parser;
    InfoHandler info_handler;
    std::string getStringFromBuffer();
    HtmlRequest parseInput();
    std::atomic<bool> finished;
};


#endif //TP_3_CLIENTHANDLER_H
