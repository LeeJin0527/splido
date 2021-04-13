
// 4_12_2View.h: CMy4122View 클래스의 인터페이스
//

#pragma once


class CMy4122View : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CMy4122View() noexcept;
	DECLARE_DYNCREATE(CMy4122View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MY4_12_2_FORM };
#endif

// 특성입니다.
public:
	CMy4122Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMy4122View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CBitmap m_background;
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtmExplain();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnDraw(CDC* /*pDC*/);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	CPoint m_circlePt = { 500, 845 };
	CSize m_step = { 1, 1 };
	BOOL m_bClicked = false;
	BOOL m_bPressShift = false;
	CRect m_viewRect;

	CPoint m_startPt = { 0, 0 };
	CPoint m_endPt = { 0, 0 };
	CPoint m_fixedPt = { 0, 0 };


	const int m_radius = 20;
	double m_seta = 0.0;
	double m_fixedSeta = 0.0;
	double m_radian = 0.0;

	int m_test = 0;

	int nX[10];
	int nY[10];
	int nX1[10];
	int nY1[10]; 
	int nX2[10];
	int nY2[10];
	CPoint p[10 * 10];
	int count;
	int m_dir;
	int m_dir2;
	int x;
	int y;
	int x_ball;
	int y_ball;
	int clear;
	int btn_cnt;
	CListBox m_list;
	CListBox m_list2;
	CListBox m_list3;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBnClickedMfcbutton2();
	afx_msg void OnBnClickedMfcbutton1();
public:

	HBITMAP m_hBitmap; // Dialog에 배경이미지 입히기 위한 변수.
	BITMAP m_bBit;
	int RoundX;
	int RoundY;
	afx_msg void OnNextStop();
	afx_msg void OnLbnSelchangeList4();
	int left_count;
	int m_click_count;
	CListBox m_list5;
};

#ifndef _DEBUG  // 4_12_2View.cpp의 디버그 버전
inline CMy4122Doc* CMy4122View::GetDocument() const
   { return reinterpret_cast<CMy4122Doc*>(m_pDocument); }
#endif

