# CMakeLists.txt для Linux (MauiApp)
cmake_minimum_required(VERSION 3.10)
project("MauiApp")

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ВАЖНО: Добавляем опции для статической линковки (чтобы бинарник был самодостаточным)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")

# Путь к PDFium
set(PDFIUM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/pdfium)

# Проверяем, что PDFium существует
if(NOT EXISTS ${PDFIUM_DIR}/include)
    message(FATAL_ERROR "PDFium include directory not found: ${PDFIUM_DIR}/include")
endif()

if(NOT EXISTS ${PDFIUM_DIR}/lib)
    message(FATAL_ERROR "PDFium lib directory not found: ${PDFIUM_DIR}/lib")
endif()

message(STATUS "PDFIUM_DIR: ${PDFIUM_DIR}")

# Добавляем все исходники
add_executable(MauiApp 
    "MauiApp.cpp" 
    "Service.cpp" 
    "ParsingPDF.cpp"
)

# Указываем директории для поиска заголовков
target_include_directories(MauiApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PDFIUM_DIR}/include
)

# Указываем директорию для поиска библиотек
target_link_directories(MauiApp PRIVATE
    ${PDFIUM_DIR}/lib
)

# Определяем, какая библиотека PDFium доступна
if(EXISTS "${PDFIUM_DIR}/lib/libpdfium.a")
    set(PDFIUM_LIB "${PDFIUM_DIR}/lib/libpdfium.a")
    message(STATUS "Found static PDFium library")
elseif(EXISTS "${PDFIUM_DIR}/lib/libpdfium.so")
    set(PDFIUM_LIB pdfium)
    message(STATUS "Found shared PDFium library")
else()
    message(FATAL_ERROR "PDFium library not found (.a or .so)")
endif()

# Линкуем библиотеки
target_link_libraries(MauiApp
    ${PDFIUM_LIB}
    pthread
    dl
    stdc++fs  # для файловой системы C++17
)

# Если используете shared library (.so), копируем её
if(NOT EXISTS "${PDFIUM_DIR}/lib/libpdfium.a")
    add_custom_command(TARGET MauiApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PDFIUM_DIR}/lib/libpdfium.so"
            $<TARGET_FILE_DIR:MauiApp>
        COMMENT "Копирование libpdfium.so в выходную директорию"
    )
endif()

# Выводим информацию о размере бинарника
add_custom_command(TARGET MauiApp POST_BUILD
    COMMAND ls -lh $<TARGET_FILE:MauiApp>
    COMMENT "Размер исполняемого файла:"
)