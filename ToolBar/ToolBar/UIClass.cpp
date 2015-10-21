#include "UIClass.h"


CUIClass::CUIClass(void)
{
	m_nCount = 1;
	m_nIndex = 0;
	m_nHeight = 0;
	m_nWidth = 0;
	m_pBmp = NULL;
	//Bitmap* m_pBmp;
	m_ptPos.x = NULL;
	m_ptPos.y = NULL;
}


CUIClass::~CUIClass(void)
{
	if(m_pBmp){
		delete m_pBmp;
		m_pBmp = NULL;
	}
}

void CUIClass::SetCurIndex( int n )
{
	m_nIndex = (n<0 || n>=m_nCount) ? 0 : n;
}

void CUIClass::BmpEmpty()
{
	if (m_pBmp){
		delete m_pBmp;
		m_pBmp = NULL;
	}
}

 void CUIClass::Draw( Graphics& oCanvas )
{
	if (m_pBmp){
		oCanvas.DrawImage(m_pBmp,RectF(m_ptPos.x,m_ptPos.y,m_nWidth,m_nHeight),m_nWidth*m_nIndex,0,m_nWidth,m_nHeight,UnitPixel);
	}
}

void CUIClass::ByteToWChar( const char* szByte, std::wstring& wstr )
{
	//预转换，得到所需空间的大小
	int nstrlen = strlen(szByte);
	int wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, szByte, nstrlen, NULL, 0);
	//
	wchar_t* pWChar = new wchar_t[wcsLen+1];
	memset(pWChar, 0, (wcsLen+1)*sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, NULL, szByte, nstrlen, pWChar, wcsLen);
	wstr = pWChar;
	delete[] pWChar;
}

void CUIClass::SetCount( int n )
{
	m_nCount =  n<=0 ? 1 : n;
	if (m_pBmp){
		m_nWidth = m_pBmp->GetWidth()/m_nCount;
	}
}

void CUIClass::SetPos( int x,int y )
{
	m_ptPos.x = x;
	m_ptPos.y = y;
}

BOOL CUIClass::SetBimp( Bitmap* pBmp )
{
	if (m_pBmp){
		delete m_pBmp;
		m_pBmp = NULL;
	}
	m_pBmp =pBmp;
	m_nHeight = m_pBmp->GetHeight();
	m_nWidth = m_pBmp->GetWidth()/m_nCount;
	return (m_pBmp->GetWidth() != 0);
}

BOOL CUIClass::SetImage(DWORD dwResId )
{
	if (m_pBmp){
		delete m_pBmp;
		m_pBmp = NULL;
	}
	m_pBmp =GetPngFromResource(dwResId);
	m_nHeight = m_pBmp->GetHeight();
	m_nWidth = m_pBmp->GetWidth()/m_nCount;
	return (m_pBmp->GetWidth() != 0);
}
BOOL CUIClass:: SetImagePng(WCHAR* wsPath){
	if (m_pBmp){
		delete m_pBmp;
		m_pBmp = NULL;
	}
	m_pBmp = Bitmap::FromFile(wsPath);
	m_nHeight = m_pBmp->GetHeight();
	m_nWidth = m_pBmp->GetWidth()/m_nCount;
	return (m_pBmp->GetWidth() != 0);
}

Bitmap* CUIClass::GetPngFromResource( DWORD dwResId )
{
	Bitmap* pImg = nullptr;
	HRSRC hRsrc =  ::FindResource(NULL,MAKEINTRESOURCE(dwResId),"PNG");
	HGLOBAL hRscData = LoadResource(NULL,hRsrc);

	size_t nDataSize = SizeofResource(NULL,hRsrc);
	HGLOBAL hPngData = GlobalAlloc(GHND,nDataSize);
	void* pData = LockResource(hRscData);
	void* pPng = GlobalLock(hPngData);
	memcpy(pPng,pData,nDataSize);
	IStream* pStream;
	CreateStreamOnHGlobal(hPngData,TRUE,&pStream);
	pImg = Gdiplus::Bitmap::FromStream(pStream);
	FreeResource(hPngData);
	return pImg;
}
