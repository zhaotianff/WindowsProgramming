#pragma once

#include"framework.h"

class HBitmapEx
{
public:
	HBitmapEx(LPCTSTR szPath);
	~HBitmapEx();
	std::wstring GetAbsoluteImagePath(LPCTSTR szPath);

	HBITMAP hBitmap;

private:
	HBITMAP InternalLoadBitmapFromStream(IStream* pStream, bool bTopDown, bool bPremultiply);
};
