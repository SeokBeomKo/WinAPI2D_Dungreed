#include "framework.h"
#include "CRenderManager.h"
#include "CD2DImage.h"

CRenderManager::CRenderManager()
{
	m_pFactory = nullptr;
	m_pRenderTarget = nullptr;
	m_pWriteFactory = nullptr;
	m_pImageFactory = nullptr;
	m_pBitmap = nullptr;
	m_pBrush = nullptr;
	m_pTextFormat = nullptr;
	m_pPathGeometry = nullptr;
	geometry = nullptr;
}

CRenderManager::~CRenderManager()
{
	if (nullptr != m_pRenderTarget)
	{
		m_pRenderTarget->Release();
	}
	if (nullptr != m_pBrush)
	{
		m_pBrush->Release();
	}
	if (nullptr != m_pTextFormat)
	{
		m_pTextFormat->Release();
	}
}

void CRenderManager::init()
{
	RECT rc;
	GetClientRect(hWnd, &rc);

	// D2D1Factory 생성
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);

	// 지정한 윈도우의 클라이언트 영역에 그림을 그리기 위한 Render Target을 생성
	m_pFactory->CreateHwndRenderTarget(RenderTargetProperties(),
		HwndRenderTargetProperties(hWnd, SizeU(rc.right, rc.bottom),
			D2D1_PRESENT_OPTIONS_IMMEDIATELY),
		&m_pRenderTarget);

	// WICImagingFactory 생성
	if (S_OK == CoInitialize(nullptr))
	{

	}
	if (S_OK == CoCreateInstance(CLSID_WICImagingFactory, nullptr,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pImageFactory)))
	{

	}
	if (S_OK == DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_pWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pWriteFactory)))
	{

	}

	// 텍스트 포맷 생성
	m_pWriteFactory->CreateTextFormat(
		L"Aa카시오페아",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		10.f,
		L"ko",
		&m_pTextFormat);
	m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	// 브러쉬 생성
	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.f, 0.f, 0.f), &m_pBrush);
}

void CRenderManager::RenderImage(CD2DImage* img, float dstX, float dstY, float dstW, float dstH, float alpha, fVec2 pos, float angle)
{
	D2D1_RECT_F imgRect = { dstX, dstY, dstW, dstH };
	if (nullptr != img)
	{
		Matrix3x2F matrot = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(pos.x, pos.y));
		m_pRenderTarget->SetTransform(matrot);
		m_pRenderTarget->DrawBitmap(img->GetImage(), imgRect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
	}
}

void CRenderManager::RenderFrame(CD2DImage* img, float dstX, float dstY, float dstW, float dstH, float srcX, float srcY, float srcW, float srcH, float alpha, fVec2 pos, float angle)
{
	D2D1_RECT_F imgRect = { dstX, dstY, dstW, dstH };
	D2D1_RECT_F srcRect = { srcX, srcY, srcW, srcH };

	if (nullptr != img)
	{
		Matrix3x2F matrot = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(pos.x, pos.y));
		m_pRenderTarget->SetTransform(matrot);
		m_pRenderTarget->DrawBitmap(img->GetImage(), imgRect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcRect);
	}
}

void CRenderManager::RenderRevFrame(CD2DImage* img, float dstX, float dstY, float dstW, float dstH, float srcX, float srcY, float srcW, float srcH, float alpha, fVec2 pos, float angle)
{
	D2D1_RECT_F imgRect = { dstX, dstY, dstW, dstH };
	D2D1_RECT_F srcRect = { srcX, srcY, srcW, srcH };

	Matrix3x2F matlot = D2D1::Matrix3x2F::Scale(-1.f, 1.f,
		D2D1_POINT_2F{ (dstX + dstW) / 2.f, (dstY + dstH) / 2.f });

	if (nullptr != img)
	{
		Matrix3x2F matrot = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(pos.x, pos.y));
		Matrix3x2F matlr = matlot * matrot;
		m_pRenderTarget->SetTransform(matlr);
		m_pRenderTarget->DrawBitmap(img->GetImage(), imgRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcRect);
	}

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(1.f, 1.f,
		D2D1_POINT_2F{ (dstX + dstW) / 2.f, (dstY + dstH) / 2.f }));
}

void CRenderManager::RenderText(wstring str, float dstX, float dstY, float dstW, float dstH, float fontSize, COLORREF color)
{
	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	if (m_pTextFormat->GetFontSize() != fontSize)
	{
		m_pTextFormat->Release();
		m_pWriteFactory->CreateTextFormat(
			L"Aa카시오페아",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			fontSize,
			L"ko",
			&m_pTextFormat);
		m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	m_pBrush->SetColor(D2D1::ColorF(red / 255.f, green / 255.0f, blue / 255.0f, 1.f));
	m_pRenderTarget->DrawTextW(str.c_str(), (UINT)str.size(), m_pTextFormat,
		D2D1::RectF(dstX, dstY, dstW, dstH), m_pBrush);
}

void CRenderManager::RenderRectangle(float dstX, float dstY, float dstW, float dstH, COLORREF color, fVec2 pos, float angle)
{
	D2D1_RECT_F m_imgRect = { dstX, dstY, dstW, dstH };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	m_pBrush->SetColor(D2D1::ColorF(red / 255.f, green / 255.0f, blue / 255.0f, 1.f));
	Matrix3x2F matrot = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(pos.x, pos.y));
	m_pRenderTarget->SetTransform(matrot);
	m_pRenderTarget->DrawRectangle(m_imgRect, m_pBrush);
}

void CRenderManager::RenderFillRectangle(float dstX, float dstY, float dstW, float dstH, COLORREF color, float alpha, fVec2 pos, float angle)
{
	D2D1_RECT_F m_imgRect = { dstX, dstY, dstW, dstH };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	m_pBrush->SetColor(D2D1::ColorF(red / 255.f, green / 255.0f, blue / 255.0f, alpha));
	Matrix3x2F matrot = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(pos.x, pos.y));
	m_pRenderTarget->SetTransform(matrot);
	m_pRenderTarget->FillRectangle(m_imgRect, m_pBrush);
}

void CRenderManager::RenderEllipse(float dstX, float dstY, float dstW, float dstH, COLORREF color, float strokeWidth, fVec2 pos, float angle)
{
	D2D1_ELLIPSE m_imgRect = { dstX, dstY, dstW, dstH };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	m_pBrush->SetColor(D2D1::ColorF(red / 255.f, green / 255.0f, blue / 255.0f, 1.f));
	Matrix3x2F matrot = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(pos.x, pos.y));
	m_pRenderTarget->SetTransform(matrot);
	m_pRenderTarget->DrawEllipse(m_imgRect, m_pBrush, strokeWidth);
}

void CRenderManager::RenderGeometry(float dstX, float dstY, float dstW, float dstH, COLORREF color, float strokeWidth, bool right)
{
	if (right)
		geometry = GenTriangleGeometry(
			Point2F(dstX, dstY), Point2F(dstX, dstH), Point2F(dstW, dstH));
	else
		geometry = GenTriangleGeometry(
			Point2F(dstW, dstY), Point2F(dstX, dstH), Point2F(dstW, dstH));

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	m_pBrush->SetColor(D2D1::ColorF(red / 255.f, green / 255.0f, blue / 255.0f, 1.f));
	m_pRenderTarget->DrawGeometry(geometry, m_pBrush, strokeWidth);
}

void CRenderManager::RenderFillEllipse(float dstX, float dstY, float dstW, float dstH, COLORREF color, fVec2 pos, float angle)
{
	D2D1_ELLIPSE m_imgRect = { dstX, dstY, dstW, dstH };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	m_pBrush->SetColor(D2D1::ColorF(red / 255.f, green / 255.0f, blue / 255.0f, 1.f));
	Matrix3x2F matrot = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(pos.x, pos.y));
	m_pRenderTarget->SetTransform(matrot);
	m_pRenderTarget->FillEllipse(m_imgRect, m_pBrush);
}

void CRenderManager::RenderLine(fVec2 startPoint, fVec2 endPoint, COLORREF color, float strokeWidth, fVec2 pos, float angle)
{
	D2D1_POINT_2F start = { startPoint.x, startPoint.y };
	D2D1_POINT_2F end = { endPoint.x, endPoint.y };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	m_pBrush->SetColor(D2D1::ColorF(red / 255.f, green / 255.0f, blue / 255.0f, 1.f));
	Matrix3x2F matrot = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(pos.x, pos.y));
	m_pRenderTarget->SetTransform(matrot);
	m_pRenderTarget->DrawLine(start, end, m_pBrush, strokeWidth);
}

ID2D1PathGeometry* CRenderManager::GenTriangleGeometry(D2D1_POINT_2F pt1, D2D1_POINT_2F pt2, D2D1_POINT_2F pt3)
{
	ID2D1GeometrySink* pSink = NULL;
	HRESULT hr = S_OK;
	m_pPathGeometry;

	if (SUCCEEDED(hr))
	{
		hr = m_pFactory->CreatePathGeometry(&m_pPathGeometry);

		if (SUCCEEDED(hr))
		{
			// Write to the path geometry using the geometry sink.
			hr = m_pPathGeometry->Open(&pSink);

			if (SUCCEEDED(hr))
			{
				pSink->BeginFigure(
					pt1,
					D2D1_FIGURE_BEGIN_FILLED
				);

				pSink->AddLine(pt2);

				pSink->AddLine(pt3);

				pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

				hr = pSink->Close();
			}
			SafeRelease(&pSink);
		}
	}
	return m_pPathGeometry;
}

ID2D1Bitmap* CRenderManager::GetBitmap()
{
	return m_pBitmap;
}

ID2D1HwndRenderTarget* CRenderManager::GetRenderTarget()
{
	return m_pRenderTarget;
}

IWICImagingFactory* CRenderManager::GetImageFactory()
{
	return m_pImageFactory;
}

IDWriteFactory* CRenderManager::GetWriteFactory()
{
	return m_pWriteFactory;
}

