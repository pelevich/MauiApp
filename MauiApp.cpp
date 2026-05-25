#include "MauiApp.h"
#include "Service.h"
#include "ParsingPDF.h"


using namespace std;

int main(int argc, char* argv[])
{

	string pipeName = argv[1];
	int fileLight = stoi(argv[2]);
	ParsingPDF* obj = ParsingPDF::getInstance();
	Service pipe = Service(pipeName);
	char* file = new char[fileLight];
	pipe.Read(pipe.hPipe, file, fileLight);
	obj->LoadDocument((unsigned char*)file, fileLight);
	int count_rows = 0, count_boundingbox = 0;
	obj->GetNumberPage(obj->GetDocument());
	for (int i = 0; i < obj->GetNumberPage(obj->GetDocument()); i++) {
		FPDF_PAGE page = obj->LoadPage(obj->GetDocument(), i);
		FPDF_TEXTPAGE text_page = obj->LoadTextPage(page);
		count_rows += obj->GetNumberRows(text_page);
		count_boundingbox += obj->GetNumberBoundingBox(text_page);
	}
	pipe.Write(pipe.hPipe, to_string(count_rows) + " " + to_string(count_boundingbox));
	return 0;
}
