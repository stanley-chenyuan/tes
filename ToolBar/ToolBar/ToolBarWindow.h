#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <GdiPlus.h>
#pragma comment(lib,"GdiPlus.lib")
#include "ImgUI.h"
using namespace Gdiplus;
using namespace std;
#include <vector>
struct stXML
{

	string m_logoPath;
	string m_strUrlPath;
	int m_nWidth;
	int m_nHeight;
	int m_nId;
	int m_nbrowser;
	stXML &operator = (stXML &lp)
	{
		this->m_logoPath = lp.m_logoPath;
		this->m_strUrlPath  = lp.m_strUrlPath;
		this->m_nWidth = lp.m_nWidth;
		this->m_nHeight = lp.m_nHeight;
		this->m_nId = lp.m_nId;
		this->m_nbrowser = lp.m_nbrowser;
		return *this;
	}
};
class CToolBarWindow
{
public:
	CToolBarWindow(void);
	~CToolBarWindow(void);
	void CreateToolBarWindow();
private:
	bool LoadXML();
	
	static LRESULT WINAPI ToolBarWndPrco( HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam );
	void onPaint();
	void OnInitDlg();
	std::wstring s2ws(const std::string& s) ;
	void ByteToWChar(const char* szByte, std::wstring& wstr);

	HWND m_hWnd;
	HDC m_hmedc;
	HBITMAP m_hbitmap;
	Bitmap *m_Bmp;
	CImgUI m_AddBtn;
	CImgUI m_ShopBtn;
	string m_strExePath;
	vector<stXML *> m_vecXML;	

};

