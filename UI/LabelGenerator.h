#ifndef LABEL_GENERATOR_H
#define LABEL_GENERATOR_H

// GPU-accelerated off-screen text rendering using Direct2D + DirectWrite.
// Renders into a WIC bitmap (Direct2D rasterization is GPU-accelerated when
// hardware is available), then exposes CPU pixels so you can upload them to
// an SFML texture with:
//
//   sf::Texture texture;
//   texture.create(label.getWidth(), label.getHeight());
//   texture.update(label.getPixels());   // BGRA -> swap R/B if needed

#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <wrl/client.h>
#include <string>
#include <vector>
#include <stdexcept>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

struct CaretPosition
{
    float x;
    float y;
    float height;
};

class LabelGenerator
{
public:
    LabelGenerator()
    {
        HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
        // S_FALSE and RPC_E_CHANGED_MODE are acceptable.
        if (FAILED(hr) && hr != S_FALSE && hr != RPC_E_CHANGED_MODE)
            throw std::runtime_error("CoInitializeEx failed");

        // Direct2D factory
        if (!direct2DFactory)
        {
            hr = D2D1CreateFactory(
                D2D1_FACTORY_TYPE_SINGLE_THREADED,
                direct2DFactory.GetAddressOf());
            if (FAILED(hr))
                throw std::runtime_error("D2D1CreateFactory failed");
        }

        if (!directWriteFactory)
        {
            // DirectWrite factory
            hr = DWriteCreateFactory(
                DWRITE_FACTORY_TYPE_SHARED,
                __uuidof(IDWriteFactory),
                reinterpret_cast<IUnknown**>(
                    directWriteFactory.GetAddressOf()));
            if (FAILED(hr))
                throw std::runtime_error("DWriteCreateFactory failed");
        }

        makeTextFormat();

        //// WIC factory
        //if (!wicFactory)
        //{
        //    hr = CoCreateInstance(
        //        CLSID_WICImagingFactory,
        //        nullptr,
        //        CLSCTX_INPROC_SERVER,
        //        IID_PPV_ARGS(wicFactory.GetAddressOf()));
        //    if (FAILED(hr))
        //        throw std::runtime_error("CoCreateInstance(WIC) failed");
        //}

        // Off-screen bitmap (32-bit premultiplied BGRA)
        //if (!wicBitmap) {
        //    hr = wicFactory->CreateBitmap(
        //        m_width,
        //        m_height,
        //        GUID_WICPixelFormat32bppPBGRA,
        //        WICBitmapCacheOnLoad,
        //        wicBitmap.GetAddressOf());
        //    if (FAILED(hr))
        //        throw std::runtime_error("CreateBitmap failed");
        //}
        if (!renderTarget)
        {
            // Off-screen render target
            hr = direct2DFactory->CreateWicBitmapRenderTarget(
                wicBitmap.Get(),
                D2D1::RenderTargetProperties(
                    D2D1_RENDER_TARGET_TYPE_DEFAULT, // use GPU when available
                    D2D1::PixelFormat(
                        DXGI_FORMAT_UNKNOWN,
                        D2D1_ALPHA_MODE_PREMULTIPLIED)),
                renderTarget.GetAddressOf());
            if (FAILED(hr))
                throw std::runtime_error("CreateWicBitmapRenderTarget failed");
        }

        textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        textFormat->SetParagraphAlignment(
            DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

        // Brush
        hr = renderTarget->CreateSolidColorBrush(
            D2D1::ColorF(D2D1::ColorF::Red),
            brush.GetAddressOf());
        if (FAILED(hr))
            throw std::runtime_error("CreateSolidColorBrush failed");

        // Better text quality
        renderTarget->SetTextAntialiasMode(
            D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
    }

    static void init()
    {
        //wic factory
        HRESULT hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(wicFactory.GetAddressOf()));
        if (FAILED(hr))
            throw std::runtime_error("CoCreateInstance(WIC) failed");
		//wic bitmap
        hr = wicFactory->CreateBitmap(
            m_width,
            m_height,
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapCacheOnLoad,
            wicBitmap.GetAddressOf());
        if (FAILED(hr))
            throw std::runtime_error("CreateBitmap failed");
    }

    // Clear to transparent
    void clear()
    {
        renderTarget->BeginDraw();
        renderTarget->Clear(
            D2D1::ColorF(0.f, 0.f, 0.f, 0.f));
        renderTarget->EndDraw();
    }

    // Render centered text over the whole bitmap
    void renderText(const std::wstring& text, float textBoxWidth)
    {
        renderTarget->BeginDraw();

        // Transparent background
        renderTarget->Clear(
            D2D1::ColorF(0.f, 0.f, 0.f, 0.f));

        // Full bitmap rectangle
        D2D1_RECT_F rect = D2D1::RectF(
            0.0f,
            0.0f,
            static_cast<float>(m_width),
            static_cast<float>(m_height));

        directWriteFactory->CreateTextLayout(
            text.c_str(),
            static_cast<UINT32>(text.length()),
            textFormat.Get(),
			textBoxWidth,
			rect.bottom - rect.top,
            &layout
        );

        renderTarget->DrawTextLayout(
            D2D1::Point2F(0.f, 0.f),
            layout.Get(),
            brush.Get()
        );

        HRESULT hr = renderTarget->EndDraw();
		if (FAILED(hr))
			throw std::runtime_error("EndDraw failed");
    }

    CaretPosition charPosition(UINT charIndex)
	{
        FLOAT x;
        FLOAT y;
        DWRITE_HIT_TEST_METRICS metrics;

        HRESULT hr = layout->HitTestTextPosition(
            static_cast<UINT32>(charIndex),
            FALSE,
            &x,
            &y,
            &metrics);

		if (FAILED(hr))
			throw std::runtime_error("HitTestTextPosition failed");
		CaretPosition pos;
		pos.x = metrics.left;
		pos.y = metrics.top;
		pos.height = metrics.height;
		return pos;
	}

    // Copy pixels from the off-screen bitmap into m_pixels.
    // Returns BGRA premultiplied pixels.
    const unsigned char* getPixels(int width, int height)
    {
		int nChars = width * height * 4;
		if (m_pixels.size() < static_cast<size_t>(nChars))
			m_pixels.resize(nChars);
        WICRect rect = {
            0, 0,
            static_cast<INT>(width),
            static_cast<INT>(height)
        };

        wicBitmap->CopyPixels(
            &rect,
            width * 4,                    // stride
            static_cast<UINT>(m_pixels.size()),
            m_pixels.data());
		char* pixels = reinterpret_cast<char*>(m_pixels.data());
        for (int i = 0; i < width * height * 4; i += 4)
        {
            std::swap(pixels[i + 0], pixels[i + 2]); // fix B <-> R
        }
        return m_pixels.data();
    }

	void setFont(const std::wstring& fontName)
	{
		this->fontName = fontName;
		makeTextFormat();
	}

	void setFontSize(float size)
	{
		fontSize = size;
		makeTextFormat();
	}

    void justifyTextCenter()
    {
        textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    }

	void justifyTextLeft()
	{
		textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	}

	void justifyTextRight()
	{
		textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
	}

    int getTextWidth()
    {
        DWRITE_TEXT_METRICS metrics;
		layout->GetMetrics(&metrics);
		return static_cast<int>(metrics.width);
    }

    UINT getWidth() const { return m_width; }
    UINT getHeight() const { return m_height; }

private:
    static const UINT m_width = 1920 / 2;
    static const UINT m_height = 1080 / 2;
    float fontSize = 15;
    std::wstring fontName = L"Arial";
    static std::vector<unsigned char> m_pixels;
    inline static Microsoft::WRL::ComPtr<ID2D1Factory> direct2DFactory;
    inline static Microsoft::WRL::ComPtr<IDWriteFactory> directWriteFactory;
    inline static Microsoft::WRL::ComPtr<IWICImagingFactory> wicFactory;

    inline static Microsoft::WRL::ComPtr<IWICBitmap> wicBitmap;
    inline static Microsoft::WRL::ComPtr<ID2D1RenderTarget> renderTarget;
    inline static Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush;
    inline static Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormat;
    Microsoft::WRL::ComPtr<IDWriteTextLayout> layout;

	void makeTextFormat()
	{
        if (!textFormat)
        {
            HRESULT hr = directWriteFactory->CreateTextFormat(
                fontName.c_str(),
                nullptr,
                DWRITE_FONT_WEIGHT_NORMAL,
                DWRITE_FONT_STYLE_NORMAL,
                DWRITE_FONT_STRETCH_NORMAL,
                fontSize,
                L"", // locale
                textFormat.GetAddressOf());
            if (FAILED(hr))
                throw std::runtime_error("CreateTextFormat failed");
        }
	}
};

#endif