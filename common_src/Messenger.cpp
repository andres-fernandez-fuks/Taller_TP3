//
// Created by andy on 20/11/20.
//

#include "Messenger.h"
#include "Socket.h"

#define CHUNK_SIZE 64

int Messenger::sendMessage(const DataSocket& socket, std::stringstream& buffer){
    size_t message_size = buffer.str().length();
    size_t bytes_sent  = 0;
    size_t bytes_left = message_size;

    while (bytes_sent < message_size) {
        char msg_chunk[CHUNK_SIZE];
        size_t send_size = (bytes_left < CHUNK_SIZE) ? bytes_left : CHUNK_SIZE;
        buffer.read(msg_chunk, send_size);
        socket.sendMessage((unsigned char*) msg_chunk, send_size);
        bytes_sent += send_size;
        bytes_left -= send_size;
    }
    return 0;
}

int Messenger::receiveMessage(const DataSocket& socket,
                              std::stringstream &buffer) {
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
