#include "ParsingPDF.h"

ParsingPDF* ParsingPDF::instance = nullptr;

/// <summary>
/// Инициализируем библиотеку для работы с PDF
/// </summary>
ParsingPDF::ParsingPDF() {
    FPDF_InitLibrary();
}

/// <summary>
/// Вызвращаем ссылку на объект, объект может быть только один (реализация паттерна Singleton)
/// </summary>
/// <returns>Ссылка для работы с методами класса</returns>
ParsingPDF* ParsingPDF::getInstance() {
    if (instance == nullptr) {
        instance = new ParsingPDF();
    }
    return instance;
}

/// <summary>
/// Освобождаем память
/// </summary>
ParsingPDF::~ParsingPDF() {
    FPDF_CloseDocument(doc);
    FPDF_DestroyLibrary();
    delete instance;
}

/// <summary>
/// Загружаем PDF файл для парсинга
/// </summary>
/// <param name="path">Путь до файла</param>
void ParsingPDF::LoadDocument(string path) {
    doc = FPDF_LoadDocument((FPDF_STRING)path.c_str(), nullptr);
}

void ParsingPDF::LoadDocument(const unsigned char* data, int dataSize) {
    doc = FPDF_LoadMemDocument(data, dataSize, nullptr);
}

/// <summary>
/// Загружаем страницу с которой будем работать
/// </summary>
/// <param name="doc">Дескриптор файла PDF</param>
/// <param name="page_index">Номер страницы</param>
/// <returns>Дескриптор страницы</returns>
FPDF_PAGE ParsingPDF::LoadPage(FPDF_DOCUMENT doc, int page_index) {
    return FPDF_LoadPage(doc, page_index);
}

/// <summary>
/// Загружаем страницу с которой будем работать
/// </summary>
/// <param name="page">Дескриптор страницы</param>
/// <returns>Дескриптор с информацией текста со страницы</returns>
FPDF_TEXTPAGE ParsingPDF::LoadTextPage(FPDF_PAGE page) {
    return FPDFText_LoadPage(page);
}

/// <summary>
/// Считаем количество строк на странице
/// Смотрим под координатам символов, если разница по Y слишком большая, то считаем как новую строку
/// </summary>
/// <param name="text_page">Дескриптор страницы</param>
/// <returns>Количество строк на странице</returns>
int ParsingPDF::GetNumberRows(FPDF_TEXTPAGE text_page) {
    double bottom, y = 0;
    int count = 0;

    int numbr_symbol = FPDFText_CountChars(text_page);

    for (int i = 0; i < numbr_symbol;i++) {
        FPDFText_GetCharBox(text_page, i, NULL, NULL, &bottom, NULL);

        if (abs(bottom - y) > 10) {
            count++;
            y = bottom;
        }
    }

    return count;
};

/// <summary>
/// Считаем количество bounding-box на странице
/// </summary>
/// <param name="text_page">Дескриптор страницы</param>
/// <returns>Количество bounding-box</returns>
int ParsingPDF::GetNumberBoundingBox(FPDF_TEXTPAGE text_page) {
    return FPDFText_CountRects(text_page, 0, -1);
}

/// <summary>
/// Возвращаем количество страниц в файле
/// </summary>
/// <param name="doc">Дескриптор файла</param>
/// <returns>Количество страниц в файле</returns>
int ParsingPDF::GetNumberPage(FPDF_DOCUMENT doc) {
    return FPDF_GetPageCount(doc);
}

/// <summary>
/// Функция для получения дескриптора файла
/// </summary>
/// <returns>Возвращаем дескриптор файла</returns>
FPDF_DOCUMENT ParsingPDF::GetDocument() {
    return doc;
}