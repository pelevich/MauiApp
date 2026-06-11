#pragma once
#include <iostream>
#include "pdfium/include/fpdfview.h"
#include "pdfium/include/fpdf_text.h"
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class ParsingPDF
{
private:

	static ParsingPDF* instance;

	ParsingPDF();
	~ParsingPDF();

	ParsingPDF(const ParsingPDF&) = delete;
	ParsingPDF& operator=(const ParsingPDF&) = delete;

	FPDF_DOCUMENT doc;

public:
	static ParsingPDF* getInstance();
	void LoadDocument(string path);
	void LoadDocument(const unsigned char* data, int dataSize);
	FPDF_PAGE LoadPage(FPDF_DOCUMENT doc, int page_index);
	FPDF_TEXTPAGE LoadTextPage(FPDF_PAGE page);
	FPDF_DOCUMENT GetDocument();
	int GetNumberPage(FPDF_DOCUMENT doc);
	int GetNumberRows(FPDF_TEXTPAGE text_page);
	int GetNumberBoundingBox(FPDF_TEXTPAGE text_page);
};