//
// Created by andy on 20/11/20.
//

#include "Messenger.h"
#include "Socket.h"

#define CHUNK_SIZE 64

size_t aux_min(size_t size_1, size_t size_2) {
    return (size_1 < size_2) ? size_1 : size_2;
}

int Messenger::sendMessage(const Socket& socket, std::stringstream& buffer) {
    size_t message_size = buffer.str().length();
    size_t bytes_sent  = 0;
    size_t bytes_left = message_size;

    while (bytes_sent < message_size) {
        char msg_chunk[CHUNK_SIZE];
        size_t sending_size = aux_min(bytes_left, CHUNK_SIZE);
        buffer.read(msg_chunk, sending_size);
        socket.sendMessage((unsigned char*) msg_chunk, sending_size);
        bytes_sent += sending_size;
        bytes_left -= sending_size;
    }
    return 0;
}

int Messenger::receiveMessage(const Socket& socket, std::stringstream &buffer) {
    int total_received = 0;
    while (true) {
        unsigned char aux_buf[CHUNK_SIZE];
        int bytes_received = socket.receiveMessage(aux_buf, CHUNK_SIZE);
        buffer.write((const char*) aux_buf, bytes_received);
        total_received += bytes_received;
        if (bytes_received < CHUNK_SIZE)
            break;
    }
    return total_received;
}
