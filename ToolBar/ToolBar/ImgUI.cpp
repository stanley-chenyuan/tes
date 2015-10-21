#include "ImgUI.h"


CImgUI::CImgUI(void)
{
}


CImgUI::~CImgUI(void)
{
}

BOOL CImgUI::OnLButtonDown( POINT pt )
{
	if(PtInRect(&m_rc,pt)){
		SetCurIndex(2);
		return TRUE;
	}
	return FALSE;
}

BOOL CImgUI::OnColseLButtonDown( POINT pt )
{
	if(PtInRect(&m_rc,pt)){
		SetCurIndex(1);
		return TRUE;
	}
	return FALSE;
}

BOOL CImgUI::OnLButtonUp( POINT pt )
{
	if(PtInRect(&m_rc,pt)){
		SetCurIndex(1);
		return TRUE;
	}
	return FALSE;
}

void CImgUI::SetPos( int x,int y )
{
	CUIClass::SetPos(x,y);
	m_rc.left = x;
	m_rc.right = m_rc.left + m_nWidth;
	m_rc.top = y;
	m_rc.bottom = m_rc.top + m_nHeight;
}

void CImgUI::SetCount( int n )
{
	CUIClass::SetCount(n);
	if (m_nHeight){
		m_rc.bottom = m_rc.top + m_nHeight;
	}
	if (m_nWidth){
		m_rc.right = m_rc.left + m_nWidth;
	}
}

BOOL CImgUI::SetImage( DWORD dwResId )
{
	CUIClass::SetImage(dwResId);
	if (m_nHeight){
		m_rc.bottom = m_rc.top + m_nHeight;
	}
	if (m_nWidth){
		m_rc.right = m_rc.left + m_nWidth;
	}
	return m_nWidth>0;
}
BOOL CImgUI:: SetImagePng(WCHAR* wsPath){
	CUIClass::SetImagePng(wsPath);
	if (m_nHeight){
		m_rc.bottom = m_rc.top + m_nHeight;
	}
	if (m_nWidth){
		m_rc.right = m_rc.left + m_nWidth;
	}
	return m_nWidth>0;
}

BOOL CImgUI::SetBimp( Bitmap* pBmp )
{
	CUIClass::SetBimp(pBmp);
	if (m_nHeight){
		m_rc.bottom = m_rc.top + m_nHeight;
	}
	if (m_nWidth){
		m_rc.right = m_rc.left + m_nWidth;
	}
	return m_nWidth>0;
}
