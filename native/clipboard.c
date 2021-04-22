#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib, "user32.lib")

#include <windows.h>
#include "clipboard.h"

LIB_EXPORT int count_formats() {
	int a = CountClipboardFormats();
	return a;
}

LIB_EXPORT char *list_available_format() {
	UINT uFormat; 
	LPCSTR formats = TEXT(""); 
	LPCSTR lpFormatName = NULL; 
	char szFormatName[80];
	int i = 0;

	// Open the clipboard. 
	if (!OpenClipboard(NULL)) 
        return "";

	int a = CountClipboardFormats();

	if(a == 0)
	{
		CloseClipboard(); 
		return "";
	}

	uFormat = EnumClipboardFormats(0);

	while (uFormat) 
	{ 
		GetClipboardFormatName_helper(uFormat, formats, szFormatName, lpFormatName);
		if(i < a - 1)
			formats = lstrcat(formats, TEXT(","));

		i++;

		uFormat = EnumClipboardFormats(uFormat); 
	}

	CloseClipboard(); 

	return formats;
}

LIB_EXPORT char *get_text() {
	
	if(IsClipboardFormatAvailable(CF_TEXT))
	{
		OpenClipboard(NULL);
		HGLOBAL hglb = GetClipboardData(CF_TEXT); 
		CloseClipboard(); 
		return hglb;
	}
	return NULL;
}

LIB_EXPORT unsigned char *get_image(size_t *loaded) {
	
	UINT png_format = RegisterClipboardFormatA("PNG");
	if (png_format && IsClipboardFormatAvailable(png_format)) {
		printf("clipboard.c >> find png\n");
		OpenClipboard(NULL);
		HANDLE png_handle = GetClipboardData(png_format);
		
		size_t png_size = GlobalSize(png_handle);
		*loaded = png_size;
		CloseClipboard(); 
		return png_handle;
		
	}else if(IsClipboardFormatAvailable(CF_BITMAP)){
		printf("clipboard.c >> find Bitmap\n");
		OpenClipboard(NULL);
		HGLOBAL png_handle = GetClipboardData(CF_BITMAP); 
		size_t png_size = GlobalSize(png_handle);
		*loaded = png_size;
		CloseClipboard(); 
		return png_handle;
	}else if(IsClipboardFormatAvailable(CF_DIB)){
		printf("clipboard.c >> find DIB\n");
		OpenClipboard(NULL);
		HGLOBAL png_handle = GetClipboardData(CF_DIB); 
		size_t png_size = GlobalSize(png_handle);
		*loaded = png_size;
		CloseClipboard(); 
		return png_handle;
	}

	
	return NULL;
}

LIB_EXPORT char *get_data(const char *type) {
	int cfid = RegisterClipboardFormat(type);
	
	if(IsClipboardFormatAvailable(cfid))
	{
		OpenClipboard(NULL);
		HGLOBAL hglb = GetClipboardData(cfid); 
		CloseClipboard(); 
		return hglb;
	}
	return NULL;
	
}

LIB_EXPORT unsigned char *get_bytes(const char *type, size_t *loaded) {
	int cfid = RegisterClipboardFormat(type);
	
	if(IsClipboardFormatAvailable(cfid))
	{
		OpenClipboard(NULL);
		HGLOBAL hglb = GetClipboardData(cfid); 
		size_t size = GlobalSize(hglb);
		*loaded = size;
		CloseClipboard(); 
		return hglb;
	}
	return NULL;
	
}

GetClipboardFormatName_helper (UINT uFormat, char *formats, char szFormatName[80], LPCSTR lpFormatName)
{
    switch (uFormat)
    {
		case CF_TEXT:
			lpFormatName = TEXT("Text");
			break;
		case CF_UNICODETEXT:
			lpFormatName = TEXT("Unicode Text Format");
			break;
		case CF_OEMTEXT:
			lpFormatName = TEXT("OEM Text");
			break;
		case CF_LOCALE:
			lpFormatName = TEXT("Locale Identifier");
			break;
		case CF_BITMAP:
			lpFormatName = TEXT("Bitmap");
			break;
		case CF_DIB:
			lpFormatName = TEXT("CF_DIB");
			break;
		case CF_TIFF:
			lpFormatName = TEXT("CF_TIFF");
			break;
		default:
			if(GetClipboardFormatName(uFormat, szFormatName, 80)) 
			{
				lpFormatName = szFormatName; 
			}else{
				lpFormatName = TEXT("unknown");
			}
			break;
    }
   formats = lstrcat(formats, lpFormatName);
}