#include "Service.h"

#pragma comment(lib, "Ws2_32.lib")

/// <summary>
/// </summary>
Service::Service(string name) {
    string path = "/tmp/" + name;
    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path.c_str(), sizeof(addr.sun_path) - 1);
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
}

/// <summary>
/// Отключаемся от пайпов
/// </summary>
Service::~Service() {
    close(sock);
}

/// <summary>
/// Подключаемся к пайпу
/// Если не удалось подключится запускаем сервис и пробуем опять подключится
/// </summary>
/// <param name="name">Имя пайпа для подключения</param>
/// <returns>Возвращаем дескриптор пайпа</returns>
int Service::ConnectedServer(string name) {
    string path = "/tmp/" + name;

    if (sock >= 0) {
        close(sock);
    }

    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path.c_str(), sizeof(addr.sun_path) - 1);

    return sock;
}

/// <summary>
/// Очищаем буфер для записи сообщеиня от мусора и читаем сообщение от сервера
/// </summary>
/// <param name="hPipe">Дескриптор пайпа для чтения сообщения</param>
/// <param name="buffer">Ссылка на буффер для записи</param>
/// <param name="size">Размер буффера</param>
/// <returns>Возвращаем 1 в случае успеха, иначе 0</returns>
bool Service::Read(int sock, char* buffer, size_t size) {
    int totalRead = 0;
    memset(buffer, 0, size);
    while (totalRead < size - 1) {
        ssize_t bytes_read = recv(sock, buffer, size - 1, 0);
        totalRead += bytes_read;
    }
    return totalRead > 0;
}

/// <summary>
/// отправляем сообщение серверу
/// </summary>
/// <param name="hPipe">Дескриптор пайпа для отправки сообщения</param>
/// <param name="send_message">Отправляемое сообщение</param>
/// <returns>Возвращаем 1 в случае успеха, иначе 0</returns>
bool Service::Write(int sock, const string& send_message) {
    ssize_t bytes_written = send(sock, send_message.c_str(), send_message.size(), 0);
    return bytes_written > 0;
}
