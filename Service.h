#pragma once

#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

#pragma comment(lib, "Ws2_32.lib")

class Service
{

public:
    HANDLE hPipe;
    DWORD dwWritten;
    DWORD dwRead;
    char servBuff[1024];
    string send_message = "Hello";
    OVERLAPPED overlapped;

    Service(string name);
    ~Service();

    HANDLE ConnectedServer(string name);
    bool Read(HANDLE hPipe, char* buffer, DWORD size);
    bool Write(HANDLE hPipe, string& send_message);
};

#endif // CLIENT_H
