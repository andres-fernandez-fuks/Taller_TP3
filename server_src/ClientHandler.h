//
// Created by andy on 7/11/20.
//

#ifndef TP_3_CLIENTHANDLER_H
#define TP_3_CLIENTHANDLER_H


#include <atomic>
#include <string>
#include <thread>
#include "HtmlRequest.h"
#include "HtmlParser.h"
#include "InfoHandler.h"
#include "Thread.h"
#include "../common_src/Printer.h"
#include "../common_src/AcceptanceSocket.h"

class ClientHandler : public Thread {
public:
    explicit ClientHandler(AcceptanceSocket socket,
                           InfoHandler& handler_ref,
                           Printer& printer_ref);
    ~ClientHandler() override;

    void sendResponse(const std::string& response);
    void respondToRequest();
    void printResult();
    void closeConnection(bool should_shutdown);
    void stop();
    void run() override;
    bool isDead();

private:
    AcceptanceSocket socket;
    std::stringstream buffer;
    std::string output;
    Printer& printer;
    std::atomic<bool> finished;
    InfoHandler& info_handler;

    std::string getStringFromBuffer();
    HtmlRequest parseInput();
    void receiveInput();
};


#endif //TP_3_CLIENTHANDLER_H
