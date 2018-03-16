#include "ErrorBox.h"

namespace utility
{
	int showErrorMessageBox(LPCTSTR lpText, LPCTSTR lpTitle, HWND hWnd)
	{
		return MessageBox(hWnd, lpText, lpTitle, MB_OK | MB_ICONERROR);
	}

	int showWarningMessageBox(LPCTSTR lpText, LPCTSTR lpTitle, HWND hWnd)
	{
		return MessageBox(hWnd, lpText, lpTitle, MB_OK | MB_ICONWARNING);
	}

	HRESULT readTextFile(const std::string& fileName, std::string& outText)
	{
		std::ifstream file(fileName.c_str());
		if (file.is_open())
		{
			outText = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			return S_OK;
		}
		else
			return E_FAIL;
	}

	std::wstring toWString(const std::string& str)
	{
		std::wstring ret(str.begin(), str.end());
		return ret;
	}

	std::wstring toWString(const char* const str)
	{
		if (str == nullptr)
			return std::wstring();

		std::wstring ret(str, str + strlen(str));
		return ret;
	}
}