#pragma once

#include "Windows.h"
#include <d3d11.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <D3Dcompiler.h>

namespace utility
{
	int showErrorMessageBox(LPCTSTR lpText, LPCTSTR lpTitle = L"Error", HWND hWnd = nullptr);
	int showWarningMessageBox(LPCTSTR lpText, LPCTSTR lpTitle = L"Waring", HWND hWnd = nullptr);

	HRESULT readTextFile(const std::string& fileName, std::string& outText);

	std::wstring toWString(const std::string& str);
	std::wstring toWString(const char* const str);
}