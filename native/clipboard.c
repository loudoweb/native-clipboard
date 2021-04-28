#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Kernel32.lib")

#include <windows.h>
#include "clipboard.h"
#include <stdbool.h>
#include <strsafe.h>

void display_last_error();
void GetClipboardFormatName_helper (UINT uFormat, char *formats, char szFormatName[80], LPCSTR lpFormatName);

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
        return NULL;

	int a = CountClipboardFormats();

	if(a == 0)
	{
		CloseClipboard(); 
		return NULL;
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

LIB_EXPORT bool clear() {
	 if (!OpenClipboard(NULL)) 
        return FALSE; 
    bool isSuccess = EmptyClipboard(); 
	CloseClipboard();
	return isSuccess;
}

LIB_EXPORT bool set_text(const char *str) {
	//GetForegroundWindow()
	if (!OpenClipboard(0)) 
	{
		display_last_error();
		return FALSE; 
	}
		
	const size_t len = strlen(str) + 1;
	HGLOBAL hglb =  GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hglb), str, len);
	GlobalUnlock(hglb);
	//EmptyClipboard();
	HANDLE res = SetClipboardData(CF_TEXT, hglb);
	bool isSet = res ? TRUE: FALSE;
	if(!isSet)
	{
		GlobalFree(hglb);
		display_last_error();
	}
	CloseClipboard(); 
	return isSet;
}

LIB_EXPORT bool set_data(const char *type, const char *str) {
	if (!OpenClipboard(0)) 
	{
		display_last_error();
		return FALSE; 
	}

	int cfid = RegisterClipboardFormat(type);
		
	const size_t len = strlen(str) + 1;
	HGLOBAL hglb =  GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hglb), str, len);
	GlobalUnlock(hglb);
	//EmptyClipboard();
	HANDLE res = SetClipboardData(cfid, hglb);
	bool isSet = res ? TRUE: FALSE;
	if(!isSet)
	{
		GlobalFree(hglb);
		display_last_error();
	}
	CloseClipboard(); 
	return isSet;
}

void GetClipboardFormatName_helper (UINT uFormat, char *formats, char szFormatName[80], LPCSTR lpFormatName)
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

void display_last_error()
{
    DWORD dw = GetLastError(); 

	if(!dw)
		return;

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );
		lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
       		(lstrlen((LPCTSTR)lpMsgBuf) + 40) * sizeof(TCHAR)); 
    	StringCchPrintf((LPTSTR)lpDisplayBuf, 
        	LocalSize(lpDisplayBuf) / sizeof(TCHAR),
       		TEXT("clipboard.c >> Error %d: %s"), dw, lpMsgBuf);

	printf(lpDisplayBuf);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}