#include "stdafx.h"  //________________________________________ ReadingXML.cpp
#include "ReadingXML.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	ReadingXML app;
	return app.BeginDialog(IDI_READINGXML, hInstance);
}

void ReadingXML::Window_Open(Win::Event& e)
{
	::CoInitialize(NULL);
	try
	{
		VARIANT_BOOL ok(false);
		_variant_t fileName("people.xml");
		//_________________________________________Load the XML File:people.xml
		IXMLDOMDocumentPtr document;
		HRESULT hr= document.CreateInstance(__uuidof(DOMDocument));
		if (FAILED(hr)) throw _com_error(hr);
		document->load(fileName, &ok);
		//_________________________________________Get the List of Nodes (friend list)
		IXMLDOMNodeListPtr list;
		document->getElementsByTagName(_bstr_t(L"friend"),&list);
		//_________________________________________Get Node Count
		long friendCount= 0;
		list->get_length(&friendCount);
		//_________________________________________Travel Node by Node (Friend by Friend)
		list->reset();
		IXMLDOMNodePtr node;
		IXMLDOMNodeListPtr children;
		IXMLDOMNodePtr child;
		DOMNodeType nodeType;
		long childrenCount= 0;
		_bstr_t text;
		for(long i=0; i<friendCount; i++)
		{
			list->get_item(i,&node);
			//____________________________________Get Child Node List
			node->get_childNodes(&children);
			children->get_length(&childrenCount);
			for(long j=0; j<childrenCount; j++)
			{
				children->get_item(j,&child);
				child->get_nodeType(&nodeType);
				if(nodeType!=NODE_ELEMENT) continue;
				child->get_text(&text.GetBSTR());
				this->tbxOutput.Text+= text.GetBSTR();
				this->tbxOutput.Text+=L"\r\n";
			}
			this->tbxOutput.Text+=L"_____________________";
		}
	}
	catch(_com_error e)
	{
		this->MessageBox(e.ErrorMessage(),L"Using MS XML", MB_OK|MB_ICONERROR);
	}
	::CoUninitialize();
}

