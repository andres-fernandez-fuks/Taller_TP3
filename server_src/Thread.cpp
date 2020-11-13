//
// Created by andy on 6/11/20.
//

#include "Thread.h"

void Thread::start() {
    thread = std::thread(&Thread::run, this);
}

void Thread::join() {
    thread.join();
}
