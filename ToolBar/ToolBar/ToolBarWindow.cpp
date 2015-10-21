#include "ToolBarWindow.h"
#include <io.h>
#include "tinyxml/tinyxml.h"
CToolBarWindow::CToolBarWindow(void)
{
	m_hWnd = NULL;
	m_hbitmap = NULL;
	m_hmedc = NULL;
	m_Bmp = NULL;
	char szModuleFile[MAX_PATH];
	GetModuleFileName(NULL,szModuleFile,MAX_PATH);
	string sModuleFile = szModuleFile;
	string sExeCurFolder = sModuleFile.substr(0,sModuleFile.rfind('\\')+1);
	sExeCurFolder+="ToolImage\\dx_add.png";
	char cBuff[MAX_PATH];
	sprintf(cBuff,"%s",sExeCurFolder.c_str());
	WCHAR wFileName[512];
	MultiByteToWideChar(0,0,cBuff,-1,wFileName,512);
	m_AddBtn.SetImagePng(wFileName);
	m_AddBtn.SetCount(3);
	m_AddBtn.SetPos(0,0);
	m_AddBtn.SetCurIndex(1);
	string sShopImage = sModuleFile.substr(0,sModuleFile.rfind('\\')+1);
	sShopImage+="ToolImage\\dx_shopping.png";
	char cBuff1[MAX_PATH];
	sprintf(cBuff1,"%s",sShopImage.c_str());
	WCHAR wFileName1[512];
	MultiByteToWideChar(0,0,cBuff1,-1,wFileName1,512);
	m_ShopBtn.SetImagePng(wFileName1);
	m_ShopBtn.SetCount(3);
	m_ShopBtn.SetPos(33,0);
	m_ShopBtn.SetCurIndex(1);

}


CToolBarWindow::~CToolBarWindow(void)
{
}

bool CToolBarWindow::LoadXML()
{
	CHAR pBuf[MAX_PATH]={0};                     //存放路径的变量       
	::GetModuleFileNameA(NULL,pBuf,MAX_PATH); //获取程序的当前目录 
	string sModuleFile = pBuf;
	string sExeCurFolder = sModuleFile.substr(0,sModuleFile.rfind('\\')+1);
	string strPath = sModuleFile;
	m_strExePath = sModuleFile;
	strPath+="\\skinConfig\\virtualicon.xml";
	TiXmlDocument doc;

	if(!doc.LoadFile(strPath.c_str()))
	{

		return 0 ;
	}

	TiXmlElement* root = doc.FirstChildElement();
	if(root == NULL)
	{

		doc.Clear();
		return 0;
	}
	for (int i=0;i<m_vecXML.size();i++){
		delete m_vecXML[i];
	}
	m_vecXML.clear();
	for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		// 		string elemName = elem->Value();
		// 		const char* attr;
		// 		attr = elem->Attribute("priority");


		stXML* pXML = new stXML();
		string strID= elem->Attribute("id");
		pXML->m_nId = atoi(strID.c_str());
		TiXmlElement* logoXml = elem->FirstChildElement("titileimgname");
		TiXmlNode* logoText=logoXml->FirstChild();
		if(!logoText){

			return 0;
		}
		pXML->m_logoPath = logoText->ToText()->Value();

		TiXmlElement* widthXml = elem->FirstChildElement("width");
		TiXmlNode* widthText=widthXml->FirstChild();
		if(!widthText){

			return 0;
		}
		string strWidth = widthText->ToText()->Value();
		pXML->m_nWidth = atoi(strWidth.c_str());

		TiXmlElement* heightXml = elem->FirstChildElement("height");
		TiXmlNode* heightText=heightXml->FirstChild();
		if(!heightText){

			return 0;  
		}
		string strHeight = heightText->ToText()->Value();
		pXML->m_nHeight = atoi(strHeight.c_str());

		TiXmlElement* urlXml = elem->FirstChildElement("webloadurl");
		TiXmlNode* urlText=urlXml->FirstChild();
		if(!urlText){

			return 0;
		}
		pXML->m_strUrlPath = urlText->ToText()->Value();

		TiXmlElement* browserXml = elem->FirstChildElement("browser");
		TiXmlNode* browserText=browserXml->FirstChild();
		if(!urlText){

			return 0;
		}
		string setBrowser=browserText->ToText()->Value();
		pXML->m_nbrowser = atoi(setBrowser.c_str());
		m_vecXML.push_back(pXML);

	}
	doc.Clear();
	return 1;
}

void CToolBarWindow::CreateToolBarWindow()
{
	int nWide=GetSystemMetrics(SM_CXSCREEN);
	WNDCLASS ImgSee ;
	ZeroMemory(&ImgSee, sizeof(ImgSee));
	ImgSee.style          = NULL;
	ImgSee.lpfnWndProc    = ToolBarWndPrco;
	ImgSee.cbClsExtra     = 0;
	ImgSee.cbWndExtra     = 0;
	ImgSee.hInstance      = NULL;
	ImgSee.hIcon          = NULL;
	ImgSee.lpszMenuName   = NULL;
	ImgSee.lpszClassName  = "ToolBar";
	if(RegisterClass(&ImgSee)){
		m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW|WS_EX_LAYERED,"ToolBar",NULL,WS_VISIBLE|WS_POPUP,100,100,800,600,NULL,NULL,NULL,this);
		SetCursor(LoadCursor(NULL,IDC_ARROW));
		SetWindowPos(m_hWnd,HWND_BOTTOM,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	}
	//OnInitDlg();
	PostMessage(m_hWnd,WM_PAINT,0,0);
}

LRESULT WINAPI CToolBarWindow::ToolBarWndPrco( HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam )
{
	CToolBarWindow  *pThis = (CToolBarWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	switch(uMsg){
	case WM_CREATE:
		{
			LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
			SetWindowLongPtr(hWnd,GWLP_USERDATA,(long)pcs->lpCreateParams);
		}
		break;
	case WM_PAINT:
		{
			pThis->onPaint();
		}
		break;
	case WM_MOUSELEAVE:
		{
			pThis->m_AddBtn.SetCurIndex(1);
			pThis->m_ShopBtn.SetCurIndex(1);
			pThis->onPaint();
		}
		break;
	case WM_MOUSEMOVE:
		{
			TRACKMOUSEEVENT   tme;     
			tme.cbSize = sizeof(tme);     
			tme.dwFlags = TME_LEAVE ;   
			tme.hwndTrack = hWnd;     
			tme.dwHoverTime = HOVER_DEFAULT; 
			::TrackMouseEvent(&tme);
			POINT pt = {LOWORD(lParam),HIWORD(lParam)};
			if(pThis->m_AddBtn.OnColseLButtonDown(pt)){
				pThis->m_AddBtn.SetCurIndex(3);
				pThis->onPaint();
			}else if(pThis->m_ShopBtn.OnColseLButtonDown(pt)){
				pThis->m_ShopBtn.SetCurIndex(3);
				pThis->onPaint();
			}
		}
		break;
	case  WM_LBUTTONUP:
		{

			POINT pt = {LOWORD(lParam),HIWORD(lParam)};
			if(pThis->m_AddBtn.OnLButtonUp(pt)){
				pThis->m_AddBtn.SetCurIndex(3);

				pThis->onPaint();
				break;
			}else if(pThis->m_AddBtn.OnLButtonUp(pt)){
				pThis->m_AddBtn.SetCurIndex(3);
				pThis->onPaint();
				break;
			}else if(pThis->m_AddBtn.OnLButtonUp(pt)){
				pThis->m_AddBtn.SetCurIndex(3);
				pThis->onPaint();
				break;
			}
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void CToolBarWindow::onPaint()
{
	OnInitDlg();
	//m_hmedc = CreateCompatibleDC(NULL);
	PAINTSTRUCT ps;

	HDC hPaintDc = GetWindowDC(m_hWnd);

	RECT rcWnd;
	GetWindowRect(m_hWnd,&rcWnd);
	POINT ptDst = {0,0};

	// 	int nWidth =GetSystemMetrics(SM_CXSCREEN)*0.8;
	// 	int nHigth =GetSystemMetrics(SM_CYSCREEN)*0.8;

	RECT rect;
	static BOOL bIsSeat = FALSE;
	// 	if(!bIsSeat){
	// 		ptDst.x = (GetSystemMetrics(SM_CXSCREEN)*0.2)/2;
	// 		ptDst.y = (GetSystemMetrics(SM_CYSCREEN)*0.2)/2;
	// 		bIsSeat=TRUE;
	// 	}else{
	// 		GetWindowRect(m_hWnd,&rect);
	// 		ptDst.x = rect.left;
	// 		ptDst.y = rect.top;
	// 	}
	ptDst.x = 650;
	ptDst.y = 820;
	POINT ptSrc ={0,0};
	SIZE si = {100,40};
	BLENDFUNCTION bf = {0};
	bf.AlphaFormat = 1;
	bf.BlendFlags=0;
	bf.SourceConstantAlpha=255;
	bf.BlendOp=AC_SRC_OVER;

	Graphics oCanvas(m_hmedc);
	//oCanvas.Clear(Color(250,10,10,10));
	if(m_Bmp){
		oCanvas.DrawImage(m_Bmp,100,200,100,40);
	}
	m_AddBtn.Draw(oCanvas);
	m_ShopBtn.Draw(oCanvas);
	// 	m_CloseImg.Draw(oCanvas);
	// 	if(m_bisMouse){
	// 		m_BackImg.Draw(oCanvas);
	// 		m_NextImg.Draw(oCanvas);
	// 	}

	UpdateLayeredWindow(m_hWnd,hPaintDc,&ptDst,&si,m_hmedc,&ptSrc,0,&bf,0x0000002);
	DeleteDC(hPaintDc);
}

void CToolBarWindow::OnInitDlg()
{
	// 	int nWidth =GetSystemMetrics(SM_CXSCREEN)*0.8;
	// 	int nHigth =GetSystemMetrics(SM_CYSCREEN)*0.8;
	if (m_hmedc){
		DeleteDC(m_hmedc);
		m_hmedc = NULL;
	}
	m_hmedc = CreateCompatibleDC(NULL);

	BITMAPINFO bmi = {0};
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biHeight = -40;
	bmi.bmiHeader.biWidth = 100;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_hbitmap = ::CreateDIBSection(m_hmedc,&bmi,DIB_RGB_COLORS,NULL,NULL,0);
	::SelectObject(m_hmedc,m_hbitmap);
}

std::wstring CToolBarWindow::s2ws( const std::string& s )
{
	int len; 
	int slength = (int)s.length() + 1; 
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);  
	wchar_t* buf = new wchar_t[len]; 
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len); 
	std::wstring r(buf); 
	delete[] buf; 
	return r; 
}

void CToolBarWindow::ByteToWChar( const char* szByte, std::wstring& wstr )
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
