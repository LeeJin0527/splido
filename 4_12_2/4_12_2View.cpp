
// 4_12_2View.cpp: CMy4122View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "4_12_2.h"
#endif

#include "4_12_2Doc.h"
#include "4_12_2View.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy4122View

IMPLEMENT_DYNCREATE(CMy4122View, CFormView)

BEGIN_MESSAGE_MAP(CMy4122View, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy4122View::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy4122View::OnBnClickedButton2)
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CMy4122View::OnBnClickedMfcbutton2)
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CMy4122View::OnBnClickedMfcbutton1)
	ON_COMMAND(ID_NEXT_STOP, &CMy4122View::OnNextStop)
	ON_LBN_SELCHANGE(IDC_LIST4, &CMy4122View::OnLbnSelchangeList4)
END_MESSAGE_MAP()

// CMy4122View 생성/소멸

CMy4122View::CMy4122View() noexcept
	: CFormView(IDD_MY4_12_2_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	srand((unsigned)time(NULL));
	int nX[10];
	int nY[10];
	int nX1[10];
	int nY1[10];
	int nX2[10];
	int nY2[10];
	count = 0;
	m_dir = 1;
	m_dir2 = 0;
	x = 500;
	y = 860;
	x_ball = 500;
	y_ball = 850;
	clear = 0;
	btn_cnt = 0;
	RoundX = 400;
	RoundY = 55;
	left_count = 0; 
	m_click_count = 0;
}

CMy4122View::~CMy4122View()
{
}

void CMy4122View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_LIST3, m_list3);
	DDX_Control(pDX, IDC_LIST4, m_list5);
}

BOOL CMy4122View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	

	return CFormView::PreCreateWindow(cs);
}

void CMy4122View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// GetParentFrame()->RecalcLayout();
	// ResizeParentToFit();
	// 리소스에 추가된 bitmap 파일 로딩 
	m_hBitmap = LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP8));
	// 비트맵 개체에서 비트맵 헤더를 구한다. (이미지 사이즈 얻기위해)
	GetObject(m_hBitmap, sizeof(BITMAP), &m_bBit);
	// Dialog 위치및 크기 변경 ( full screen 만들기 위해 )
	SetWindowPos(NULL, 0, 0, m_bBit.bmWidth, m_bBit.bmHeight, SWP_NOZORDER);


}


// CMy4122View 인쇄

BOOL CMy4122View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy4122View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy4122View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMy4122View::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CMy4122View 진단

#ifdef _DEBUG
void CMy4122View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMy4122View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMy4122Doc* CMy4122View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy4122Doc)));
	return (CMy4122Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy4122View 메시지 처리기


void CMy4122View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	GetDlgItem(IDC_MFCBUTTON2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_MFCBUTTON1)->ShowWindow(SW_SHOW);
	if (nIDEvent == 1 && m_bClicked == FALSE)
	{
		m_circlePt.x += m_step.cx;
		m_circlePt.y += m_step.cy;

		/*if (m_circlePt.y - m_radius < 1 || m_circlePt.y + m_radius >= m_viewRect.Height())
		{
			m_step.cy *= -1;
		}
		if (m_circlePt.x - m_radius < 0 || m_circlePt.x + m_radius >= m_viewRect.Width())
		{
			//m_step.cx *= 1;
		}*/
		if ( m_circlePt.y + m_radius >= m_viewRect.Height())
		{
			m_step.cy *= 0;
			m_step.cx *= 0;
			m_circlePt = { 200, 500 };

			AfxMessageBox(_T("실패"));
		}
		if (m_circlePt.x - m_radius < 1 || m_circlePt.x + m_radius >= m_viewRect.Width())
		{
			m_step.cx *= 0;
			m_step.cy *= 0;

			m_circlePt = { 200, 500 };
			AfxMessageBox(_T("실패"));
		}
		for (int i = 0; i < 4; i++) {
			if ((m_circlePt.x - m_radius) <= 40 && m_circlePt.y + m_radius >=nY[i] &&  m_circlePt.y - m_radius <=nY[i] + 100)
			{
				m_step.cx *= -1;
			}
		}

		for (int i = 0; i < 4; i++) {
			if ((m_circlePt.x + m_radius) >=1000 && (m_circlePt.y + m_radius) >= nY1[i] && (m_circlePt.y - m_radius) <= nY1[i] + 100)
			{
				m_step.cx *= -1;
			}
		}
		for (int i = 0; i < 4; i++) {
			if ((m_circlePt.x + m_radius) >= 500 && (m_circlePt.x + m_radius) <= 520 && (m_circlePt.y + m_radius) >= nY2[i] - 50 && (m_circlePt.y - m_radius) <= nY2[i] + 50)
			{

				m_circlePt.x = 480;
				m_circlePt.y = m_circlePt.y;
				m_circlePt.y -= m_step.cy;

			}
		}
		for (int i = 0; i < 4; i++) {

		
			  if ((m_circlePt.x + m_radius) > 520 &&(m_circlePt.x - m_radius) <= 540 && (m_circlePt.y + m_radius) >= nY2[i] - 50 && (m_circlePt.y - m_radius) <= nY2[i] + 50)
			{

				m_circlePt.x = 570;
				m_circlePt.y = m_circlePt.y;
				m_circlePt.y -= m_step.cy;

			}
		}
		
		if ((m_circlePt.y + m_radius) > (y-5) && (m_circlePt.y + m_radius) < (y+50) && (m_circlePt.x - m_radius) >= (x - 100) && (m_circlePt.x + m_radius) <= (x+100))
		{

			m_step.cy *= -1;

		}
		//종료조건 
		CString str;
		if ((m_circlePt.x - m_radius ) >= (RoundX - 50) && (m_circlePt.x + m_radius) <= (RoundX + 50) && (m_circlePt.y - m_radius) >= (RoundY - 25) && (m_circlePt.y + m_radius) <= (RoundY + 25))
		{
			m_circlePt = { 400, -50 };
			m_step.cx *= 0;
			m_step.cy *= 0;
			MessageBox(L"STAGE1 CLEAR");
		
			
			KillTimer(0);

		}


		if (m_circlePt.x - m_radius < 1)
		{
			KillTimer(0);
		}
		if (m_circlePt.y - m_radius < 1)
		{
			KillTimer(0);
		}

		
		Invalidate();
	}
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rc;
	CClientDC dc(this);
	GetClientRect(rc);

	switch (m_dir) {

	case 1:
		x += 30;
		break;

	case -1:
		x -= 30;
	}

	if (x + 100 > rc.right || x - 100 < 0) {
		m_dir = m_dir * (-1);
	}

	/*if (y - 5 <= m_circlePt.y + m_radius) {
		m_step.cy *= -1;
	}
	*/
	

	Invalidate();

	CFormView::OnTimer(nIDEvent);
}


void CMy4122View::OnDraw(CDC* pDC)
{
	
	GetDlgItem(IDC_MFCBUTTON2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_MFCBUTTON1)->ShowWindow(SW_SHOW);
	CMy4122Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CClientDC dc(this);
	HDC hMemDC = CreateCompatibleDC(dc);
	
	CString str;
	
	
	// 호환DC에 비트맵을 선정.
	SelectObject(hMemDC, m_hBitmap);
	// 메모리 DC에서 스크린 DC로 이미지 복사
	BitBlt(dc, 0, 0, m_bBit.bmWidth, m_bBit.bmHeight, hMemDC, 0, 0, SRCCOPY);
	// 메모리 DC삭제
	DeleteDC(hMemDC);
	
	// 화면 DC와 호환되는 메모리 DC를 생성
	
	//CClientDC dc(this);
	CBrush  bs1(RGB(255, 0, 0));
	//dc.SelectObject(&bs1);
	CPen circlePen(PS_SOLID, 2, RGB(255, 0, 0));
	HGDIOBJ circleOldPen = pDC->SelectObject(&bs1);
	pDC->Ellipse(m_circlePt.x - m_radius, m_circlePt.y - m_radius,
		m_circlePt.x + m_radius, m_circlePt.y + m_radius);

	pDC->SelectObject(circleOldPen);
	DeleteObject(circlePen);

	//CString str;
	
	CBitmap bitmap; 
	bitmap.LoadBitmap(IDB_BITMAP9); 
	CBrush brush3(&bitmap); 
	dc.SelectObject(&brush3); 
	dc.RoundRect(350, 30, 450, 80, 30, 30);
	dc.RoundRect(RoundX - 50, RoundY -25, RoundX + 50, RoundY + 25, 30, 30);

	if (m_bClicked == TRUE)
	{
		if (m_bPressShift == TRUE)
		{
			CPen boldPen(PS_SOLID, 5, RGB(0, 0, 0));
			HGDIOBJ oldPen = pDC->SelectObject(&boldPen);
			pDC->MoveTo(m_startPt);
			pDC->LineTo(m_fixedPt);
			pDC->SelectObject(oldPen);
			DeleteObject(boldPen);
		}
		else
		{
			CPen boldPen(PS_SOLID, 5, RGB(0, 0, 0));
			HGDIOBJ oldPen = pDC->SelectObject(&boldPen);
			pDC->MoveTo(m_startPt);
			pDC->LineTo(m_endPt);
			pDC->SelectObject(oldPen);
			DeleteObject(boldPen);
		}
	}// 선 생성 및 굵기 색 변환

	//CString str;
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	GetDlgItem(IDC_LIST1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LIST2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LIST3)->ShowWindow(SW_HIDE);

	//CClientDC dc(this);
	if (btn_cnt == 1) {
		for (int i = 0; i < m_list.GetCount(); i++) {
			m_list.GetText(i, str);
			int n = _ttoi(str);

			int x = nX[i] / 10000;
			int y = nY[i] % 10000;
			//dc.Ellipse(x - 30, y - 30, x + 30, y + 30);
			CBrush bs3(RGB(0, 204, 255));
			dc.SelectObject(&bs3);
			dc.Rectangle(nX[i], nY[i], nX[i] + 40, nY[i] + 100);

		}
		for (int i = 0; i < m_list2.GetCount(); i++) {
			m_list2.GetText(i, str);
			int n = _ttoi(str);

			int x = nX1[i] / 10000;
			int y = nY1[i] % 10000;
			//dc.Ellipse(x - 30, y - 30, x + 30, y + 30);
			CBrush bs4(RGB(0, 204, 255));
			dc.SelectObject(&bs4);
			dc.Rectangle(nX1[i], nY1[i], nX1[i] + 40, nY1[i] + 100);

		}
		for (int i = 0; i < m_list3.GetCount(); i++) {
			m_list3.GetText(i, str);
			int n = _ttoi(str);

			int x = nX2[i] / 10000;
			int y = nY2[i] % 10000;
			//dc.Ellipse(x - 30, y - 30, x + 30, y + 30);
			CBrush bs5(RGB(230, 100, 100));
			dc.SelectObject(&bs5);
			dc.Rectangle(nX2[i], nY2[i] - 50, nX2[i] + 50, nY2[i] + 50);

		}
	}
	
	CBrush bs(RGB(60, 179, 113));
	dc.SelectObject(&bs);
	dc.Rectangle(x - 100, y +5, x + 100, y +30);

	GetDlgItem(IDC_LIST4)->ShowWindow(SW_SHOW);
	str.Format(_T(" 횟 수: %d"), m_click_count);
	pDC->DrawText(str, CRect(500, 40, 600, 70), DT_CENTER);

	if (m_click_count == 5) {
		m_click_count = 0;
		MessageBox(L"종료");
		KillTimer(0);
	}

	

	/*for (int i = 0; i < m_list.GetCount(); i++) {
		m_list5.GetText(i, str);
		
	}*/
	

}


BOOL CMy4122View::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	GetDlgItem(IDC_MFCBUTTON2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_MFCBUTTON1)->ShowWindow(SW_SHOW);
	switch (pMsg->wParam) {
	//case VK_UP:	m_dir = 0; Invalidate(); break;
	case VK_RIGHT: m_dir = 1; Invalidate(); break;
	//case VK_DOWN: m_dir = 2;  Invalidate(); break;
	case VK_LEFT: m_dir = -1; Invalidate();

	}
	return false;

	return CFormView::PreTranslateMessage(pMsg);
}


void CMy4122View::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_click_count++;
	KillTimer(1000);
	m_bClicked = TRUE;
	m_startPt = m_circlePt; // client pos
	m_endPt = point;
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	p[count] = point;
	count++;

	
	Invalidate();

	CFormView::OnLButtonDown(nFlags, point);
}


void CMy4122View::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
}


void CMy4122View::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
}


void CMy4122View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bClicked = FALSE;
	m_endPt = point;

	int height = m_startPt.y - m_endPt.y;
	int width = m_startPt.x - m_endPt.x;
	m_seta = (atan2(height, width) * 180) / 3.141592;

	int r = (int)sqrt((double)(width * width + height * height));

	m_radian = m_seta * 3.141592 / 180.0;
	r /= 10;
	m_step.cx = (int)(r * cos(m_radian));
	m_step.cy = (int)(r * sin(m_radian));
	


	//길이
	if (abs(r) >= 3)
	{
		SetTimer(1, 50, 0);
	}// 속도 r;

	/*CString str;
	left_count++;
	//str.Format(L"%d", left_count);
	str.Format(_T("남은횟수:%d", left_count));
	m_list5.AddString(str);*/
	Invalidate();
	CFormView::OnLButtonUp(nFlags, point);
}


void CMy4122View::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	GetWindowRect(&m_viewRect);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CMy4122View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bClicked == TRUE)
	{
		int height = m_startPt.y - m_endPt.y;
		int width = m_startPt.x - m_endPt.x;
		m_seta = (atan2(height, width) * 180) / 3.141592;

		m_endPt = point;
		int r = (int)sqrt((double)(width * width + height * height));
		Invalidate();

		if (m_bPressShift == TRUE)
		{
			const static double m_setaList[] = { -135.0, -90.0, -45.0, 0.0, 45.0, 90.0, 135.0, 180.0 };
			//const static double m_setaList[] = { -90.0, 0.0, 90.0, 180.0 };
			double diff = 0.0;
			double prevDiff = 0.0;
			for (int i = 0; i < sizeof(m_setaList) / sizeof(m_setaList[0]); ++i)
			{
				diff = abs(m_seta - m_setaList[i]);
				if (abs(diff) >= 180.0)
				{
					diff = 360.0 - diff;
				}

				if (diff > prevDiff)
				{
					prevDiff = diff;
					m_fixedSeta = m_setaList[i];
				}
			}
			m_seta = m_fixedSeta;
			CString str;
			double radian = m_fixedSeta * 3.141592 / 180.0;

			int r1 = (int)(r * cos(radian));
			int r2 = (int)(r * sin(radian));
			m_fixedPt.x = (m_circlePt.x + r1);
			m_fixedPt.y = (m_circlePt.y + r2);

			Invalidate();
		}
	}
	CFormView::OnMouseMove(nFlags, point);
}


void CMy4122View::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_SHIFT)
	{
		m_bPressShift = FALSE;
	}
	CFormView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CMy4122View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_SHIFT)
	{
		m_bPressShift = TRUE;

		const static double m_setaList[] = { -135.0, -90.0, -45.0, 0.0, 45.0, 90.0, 135.0, 180.0 };
		//const static double m_setaList[] = { -90.0, 0.0, 90.0, 180.0 };
		double diff = 0.0;
		double prevDiff = 0.0;
		for (int i = 0; i < sizeof(m_setaList) / sizeof(m_setaList[0]); ++i)
		{
			diff = abs(m_seta - m_setaList[i]);
			if (abs(diff) >= 180.0)
			{
				diff = 360.0 - diff;
			}

			if (diff > prevDiff)
			{
				prevDiff = diff;
				m_fixedSeta = m_setaList[i];
			}
		}
	}



	m_seta = m_fixedSeta;
	CString str;
	double radian = m_fixedSeta * 3.141592 / 180.0;

	int r1 = (int)(100.0 * cos(radian));
	int r2 = (int)(100.0 * sin(radian));
	m_fixedPt.x = (m_circlePt.x + r1);
	m_fixedPt.y = (m_circlePt.y + r2);

	Invalidate();

	CFormView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMy4122View::OnBnClickedMfcbutton2()
{
	GetDlgItem(IDC_MFCBUTTON2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_MFCBUTTON1)->ShowWindow(SW_SHOW);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (clear == 0)
		SetTimer(0, 100, NULL);
	else {
		KillTimer(0);
	}
	clear = !clear;
	Invalidate();
}


void CMy4122View::OnBnClickedMfcbutton1()
{
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_LIST1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LIST2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LIST3)->ShowWindow(SW_HIDE);
	CClientDC dc(this);
	CString str;
	CRect rc;
	GetClientRect(rc);
	//중복되지 않게 
	
	int cnt = 0;
	int sub;
	if (btn_cnt == 1) {
		for (int i = 0; i < 4; i++) {
			nX[i] = 0;
			nY[i] = rand() % (rc.bottom - 225);

			for (sub = 0; sub < i; sub++) {
				if (abs(nY[i] - nY[sub]) <= 100) {
					i--;
					break;
				}
			}

			str.Format(L"%d%04d", nX[i], nY[i]);
			m_list.AddString(str);


		}

		for (int i = 0; i < 4; i++) {
			nX1[i] = 1000;
			nY1[i] = rand() % (rc.bottom - 225);

			for (sub = 0; sub < i; sub++) {
				if (abs(nY1[i] - nY1[sub]) <= 100) {
					i--;
					break;
				}
			}
			str.Format(L"%d%04d", nX1[i], nY1[i]);
			m_list2.AddString(str);
		}

		for (int i = 0; i < 3; i++) {
			nX2[i] = 500;
			nY2[i] = rand() % (rc.bottom - 260) + 100;

			for (sub = 0; sub < i; sub++) {
				if (abs(nY2[i] - nY2[sub]) <= 100) {
					i--;
					break;
				}
			}
			str.Format(L"%d%04d", nX2[i], nY2[i]);
			m_list3.AddString(str);
		}
		//Invalidate();
	}
	else {
		
		for (int i = 0; i < m_list.GetCount(); i++) {
			m_list.DeleteString(i);

		}
		for (int i = 0; i < m_list2.GetCount(); i++) {
			m_list2.DeleteString(i);

		}
		for (int i = 0; i < m_list3.GetCount(); i++) {
			m_list3.DeleteString(i);
		}
		
		//Invalidate();
	
	}
	btn_cnt = !btn_cnt;
	Invalidate();
}


void CMy4122View::OnNextStop()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	KillTimer(0);
	Invalidate();
}


void CMy4122View::OnLbnSelchangeList4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//남은 횟수 카운트 
	
}
