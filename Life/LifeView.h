
// LifeView.h : ��������� ������ CLifeView
//

#pragma once


class CLifeView : public CView
{
protected: // ������� ������ �� ������������
	CLifeView();
	DECLARE_DYNCREATE(CLifeView)

// ��������
public:
	CLifeDoc* GetDocument() const;	
	CLifeDoc* pDoc;

	CRect Rc;
	BOOL Timer_on, 
		Flag_button_left, Flag_button_right,
		Flag_old_mode;
// ��������
public:
	void Check_timer(BOOL Flag_on_timer);
	void drawSBow(INT i, INT j, Field Cell, CDC& memDC);
	void drawSBow(INT i, INT j, Field Cell);
	//void 
// ���������������
public:
	virtual void OnDraw(CDC* pDC);  // �������������� ��� ��������� ����� �������������
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ����������
public:
	virtual ~CLifeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ��������� ������� ����� ���������
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnIdsNewGame();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnIdsStartLife();
	afx_msg void OnIdsPauseLife();
	afx_msg void OnIdsResetLife();
	afx_msg void OnIdsOption();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // ���������� ������ � LifeView.cpp
inline CLifeDoc* CLifeView::GetDocument() const
   { return reinterpret_cast<CLifeDoc*>(m_pDocument); }
#endif

