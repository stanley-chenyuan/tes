#pragma once
#include "UIClass.h"
class CImgUI: public CUIClass
{
public:
	CImgUI(void);
	~CImgUI(void);
	BOOL SetBimp(Bitmap* pBmp);
	BOOL SetImage(DWORD dwResId);
	BOOL SetImagePng(WCHAR* wsPath);
	void SetCount(int n);
	void SetPos(int x,int y);
	BOOL OnLButtonUp(POINT pt);
	BOOL OnColseLButtonDown(POINT pt);
	BOOL OnLButtonDown(POINT pt);
protected:
		RECT m_rc;
};

