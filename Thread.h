//
// Created by andy on 29/10/20.
//

#ifndef UNTITLED_THREAD_H
#define UNTITLED_THREAD_H
#include <thread>
#include <pthread.h>

class Thread {
public:
    Thread();
    virtual ~Thread() {}
    void start();
    void join();
    virtual void run() = 0;

private:
    std::thread thread;
};


#endif //UNTITLED_THREAD_H
