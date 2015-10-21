#pragma once
#include <Windows.h>
#include <GdiPlus.h>
#pragma comment(lib,"GdiPlus.lib")
#include <string>
using namespace std;
using namespace Gdiplus;
class CUIClass
{
public:
	CUIClass(void);
	~CUIClass(void);
	void SetCurIndex(int n);
	void BmpEmpty();
    void Draw(Graphics& oCanvas);
	void ByteToWChar(const char* szByte, std::wstring& wstr);
	virtual void SetCount(int n);
	virtual void SetPos(int x,int y);
	virtual BOOL SetBimp(Bitmap* pBmp);
	virtual BOOL SetImage(DWORD dwResId);
	virtual BOOL SetImagePng(WCHAR* wsPath);
    Bitmap*GetPngFromResource( DWORD dwResId );
	Bitmap* m_pBmp;
protected:
	
	int m_nCount;
	int m_nIndex;
	POINT m_ptPos;
	int m_nWidth;
	int m_nHeight;
};

