// ComPtrQueryInterface.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<Windows.h>
#include<ShlObj_core.h>
#include<wrl/client.h>
#include<atlbase.h>
#include<wincodec.h>

int main()
{

    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
        COINIT_DISABLE_OLE1DDE);

    Microsoft::WRL::ComPtr<IWICImagingFactory> m_pIWICFactory;

    hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&m_pIWICFactory)
    );

    if (FAILED(hr))
        return 0;

    Microsoft::WRL::ComPtr<IWICBitmapDecoder> pDecoder;

    hr = m_pIWICFactory->CreateDecoderFromFilename(
        L"explorer_back.png",            // Image to be decoded
        NULL,                            // Do not prefer a particular vendor
        GENERIC_READ,                    // Desired read access to the file
        WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
        &pDecoder                        // Pointer to the decoder
    );

    Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> pFrame;

    // Retrieve the first frame of the image from the decoder
    if (SUCCEEDED(hr))
    {
        hr = pDecoder->GetFrame(0, &pFrame);
    }

    Microsoft::WRL::ComPtr<IWICBitmapSource> m_pOriginalBitmapSource;
    // Retrieve IWICBitmapSource from the frame
    if (SUCCEEDED(hr))
    {
        //ComPtr provides a much simpler syntax for doing QueryInterface calls on COM Objects
        //You can also use CopyTo to perform similar operations to As.     
        hr = pFrame.As(&m_pOriginalBitmapSource);

        //QueryInterface
        /*
        *  hr = pFrame->QueryInterface(
        *        IID_IWICBitmapSource, 
        *        reinterpret_cast<void **>(&m_pOriginalBitmapSource));
        */

        //...
    }
    return 0;
}