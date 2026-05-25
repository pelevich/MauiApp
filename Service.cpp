#include "Service.h"

#pragma comment(lib, "Ws2_32.lib")

/// <summary>
/// </summary>
Service::Service(string name) {
    string path = "\\\\.\\pipe\\" + name;
    hPipe = CreateFileA(
        path.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );
}

/// <summary>
/// Отключаемся от пайпов
/// </summary>
Service::~Service() {
    CloseHandle(hPipe);
}

/// <summary>
/// Подключаемся к пайпу
/// Если не удалось подключится запускаем сервис и пробуем опять подключится
/// </summary>
/// <param name="name">Имя пайпа для подключения</param>
/// <returns>Возвращаем дескриптор пайпа</returns>
HANDLE Service::ConnectedServer(string name) {
    string path = "\\\\.\\pipe\\" + name;
    hPipe = CreateFileA(
        path.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    return hPipe;
}

/// <summary>
/// Очищаем буфер для записи сообщеиня от мусора и читаем сообщение от сервера
/// </summary>
/// <param name="hPipe">Дескриптор пайпа для чтения сообщения</param>
/// <param name="buffer">Ссылка на буффер для записи</param>
/// <param name="size">Размер буффера</param>
/// <returns>Возвращаем 1 в случае успеха, иначе 0</returns>
bool Service::Read(HANDLE hPipe, char* buffer, DWORD size) {
    memset(buffer, 0, size);
    bool result = ReadFile(hPipe, buffer, size - 1, &dwRead, NULL);
    return result;
}

/// <summary>
/// отправляем сообщение серверу
/// </summary>
/// <param name="hPipe">Дескриптор пайпа для отправки сообщения</param>
/// <param name="send_message">Отправляемое сообщение</param>
/// <returns>Возвращаем 1 в случае успеха, иначе 0</returns>
bool Service::Write(HANDLE hPipe, string& send_message) {
    bool result = WriteFile(hPipe, send_message.c_str(), send_message.size(), &dwWritten, NULL);
    return result;
}
