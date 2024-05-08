#include "HBitmapEx.h"

HBitmapEx::HBitmapEx(LPCTSTR szPath)
{
	hBitmap = NULL;

	std::wstring strAbsolutePath = GetAbsoluteImagePath(szPath);
	HANDLE hFile = CreateFile(strAbsolutePath.data(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	LARGE_INTEGER li{};
	GetFileSizeEx(hFile, &li);

	DWORD size = (DWORD)li.QuadPart;
	BYTE* buffer = new BYTE[size];

	BOOL bResult = ReadFile(hFile, buffer, size, NULL, NULL);

	if (bResult)
	{
		Microsoft::WRL::ComPtr<IStream> stream;
		stream.Attach(SHCreateMemStream(buffer, size));
		hBitmap = InternalLoadBitmapFromStream(stream.Get(), false, true);
	}
}

HBitmapEx::~HBitmapEx()
{
	if (hBitmap)
		DeleteObject(hBitmap);
}

std::wstring HBitmapEx::GetAbsoluteImagePath(LPCTSTR szPath)
{
	TCHAR szAbsoluteFilePath[260]{};
	GetModuleFileName(NULL, szAbsoluteFilePath, 260);
	std::wstring str = szAbsoluteFilePath;
	size_t index = str.find_last_of('\\');
	str = str.substr(0, index + 1);
	str += szPath;
	return str;
}

HBITMAP HBitmapEx::InternalLoadBitmapFromStream(IStream* pStream, bool bTopDown, bool bPremultiply)
{
	HRESULT hr = CoInitialize(NULL);

	if(FAILED(hr))
		return NULL;

	Microsoft::WRL::ComPtr<IWICImagingFactory> pFactory;
	hr = CoCreateInstance(CLSID_WICImagingFactory, 
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pFactory));
	
	if (FAILED(hr))
		return NULL;

	Microsoft::WRL::ComPtr<IWICBitmapSource> pBitmap;
	Microsoft::WRL::ComPtr<IWICBitmapDecoder> pDecoder;
	if (FAILED(pFactory->CreateDecoderFromStream(pStream, NULL, WICDecodeMetadataCacheOnLoad, &pDecoder)))
		return NULL;
	Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> pFrame;
	if (FAILED(pDecoder->GetFrame(0, &pFrame)))
		return NULL;
	pBitmap = pFrame;

	Microsoft::WRL::ComPtr<IWICFormatConverter> pConverter;
	if (FAILED(pFactory->CreateFormatConverter(&pConverter)))
		return NULL;
	pConverter->Initialize(pBitmap.Get(), bPremultiply ? GUID_WICPixelFormat32bppPBGRA : GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeNone, NULL, 0, WICBitmapPaletteTypeMedianCut);

	UINT width = 0, height = 0;
	pConverter->GetSize(&width, &height);

	BITMAPINFO bi = { 0 };
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = width;
	bi.bmiHeader.biHeight = bTopDown ? -(int)height : (int)height;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;

	HDC hdc = CreateCompatibleDC(NULL);
	BYTE* bits;
	HBITMAP bmp = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
	DeleteDC(hdc);

	if (bTopDown)
	{
		pConverter->CopyPixels(NULL, width * 4, width * height * 4, bits);
	}
	else
	{
		for (UINT y = 0; y < height; y++)
		{
			WICRect rc = { 0,(INT)y,(INT)width,1 };
			pConverter->CopyPixels(&rc, width * 4, width * 4, bits + (height - y - 1) * width * 4);
		}
	}

	CoUninitialize();
	return bmp;
}
