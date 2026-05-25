# CMakeList.txt: проект CMake для MauiApp

cmake_minimum_required(VERSION 3.10)

# Включение горячей перезагрузки для компиляторов MSVC
if (POLICY CMP01141)
    cmake_policy(SET CMP01141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<AND:$<COMPILER_ID:MSVC>,$<$CONFIG:Debug,RelWithDebInfo>:EditAndContinue,$<$CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("MauiApp")

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем все исходники в исполняемый файл
add_executable(MauiApp 
    "MauiApp.cpp" 
    "MauiApp.h" 
    "Service.h" 
    "Service.cpp" 
    "ParsingPDF.cpp" 
    "ParsingPDF.h" 
    "fpdfview.h" 
    "fpdf_text.h"
)

# Указываем директорию для поиска заголовков
target_include_directories(MauiApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 🔧 ИСПРАВЛЕНО: Правильный способ подключить pdfium.lib
# Создаем импортируемую библиотеку
add_library(pdfium STATIC IMPORTED)

# Указываем полный путь к .lib файлу
set_target_properties(pdfium PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/pdfium.lib"
)

# Линкуем библиотеку с проектом
target_link_libraries(MauiApp pdfium)

# Копируем DLL в папку с EXE при сборке
add_custom_command(TARGET MauiApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/pdfium.dll"
        $<TARGET_FILE_DIR:MauiApp>
    COMMENT "Копирование pdfium.dll в выходную директорию"
)