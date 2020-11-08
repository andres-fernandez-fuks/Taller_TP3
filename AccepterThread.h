//
// Created by andy on 7/11/20.
//

#ifndef TP_3_ACCEPTERTHREAD_H
#define TP_3_ACCEPTERTHREAD_H

#include <atomic>
#include "Thread.h"
#include "Socket.h"

class AccepterThread : public Thread {
public:
    AccepterThread(std::string port, std::string info_file);
    ~AccepterThread() override;
    void run() override;
    void stopConnections();
private:
    Socket socket = Socket(1);
    std::atomic<bool> keep_talking;
    std::string info_file;
};


#endif //TP_3_ACCEPTERTHREAD_H
