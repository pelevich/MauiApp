FROM ubuntu:22.04

# Переключаемся на российское зеркало (Яндекс)
RUN sed -i 's/archive.ubuntu.com/mirror.yandex.ru/g' /etc/apt/sources.list && \
    sed -i 's/security.ubuntu.com/mirror.yandex.ru/g' /etc/apt/sources.list

# Обновляемся и устанавливаем зависимости
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    cmake \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

# Сборка проекта
RUN mkdir build && \
    cd build && \
    cmake .. && \
    make -j$(nproc)

# Запуск
CMD ["./build/MauiApp"]