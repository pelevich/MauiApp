#pragma once

#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>

using namespace std;

class Service
{
public:
    int sock;
    char servBuff[1024];
    string send_message = "Hello";

    Service(string name);
    ~Service();

    int ConnectedServer(string name);
    bool Read(int sock, char* buffer, size_t size);
    bool Write(int sock, const string& send_message);
};

#endif // CLIENT_H
