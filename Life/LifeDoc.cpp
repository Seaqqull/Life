
// LifeDoc.cpp : ���������� ������ CLifeDoc
//

#include "stdafx.h"
// SHARED_HANDLERS ����� ���������� � ������������ �������� ��������� ���������� ������� ATL, �������
// � ������; ��������� ��������� ������������ ��� ��������� � ������ �������.
#ifndef SHARED_HANDLERS
#include "Life.h"
#endif

#include "LifeDoc.h"
#include <ctime>

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLifeDoc

IMPLEMENT_DYNCREATE(CLifeDoc, CDocument)

BEGIN_MESSAGE_MAP(CLifeDoc, CDocument)
END_MESSAGE_MAP()


// ��������/����������� CLifeDoc

CLifeDoc::CLifeDoc()
{
	// TODO: �������� ��� ��� ������������ ������ ������������
	srand((unsigned int)time(NULL));
	Shiftx = new INT[8]{-1, -1, 0, 1, 1,  1, 0, -1};//{ -1, 0, 1, 0 };
	Shifty = new INT[8]{0,   1, 1, 1, 0, -1,  -1, -1};//{ 0, 1, 0, -1 };

	Fild = new Field*[GAME_FIELD_SIZE];
	Fild_ = new Field*[GAME_FIELD_SIZE];

	for (INT i(0); i < GAME_FIELD_SIZE; i++){
		Fild[i] = new Field[GAME_FIELD_SIZE];
		Fild_[i] = new Field[GAME_FIELD_SIZE];
	}
	FPS = MIN_FPS;
	Clr_background = Gray;
	Clr_border = LightBlue;
	Clr_block = Black;
	Flag_mode = Flag_game = First_step = true;
	Cnt_lived = 0;
	//New_game(Flag_mode);//false

}

void CLifeDoc::New_game(BOOL Flag_random_generation){
	Clear_field(Fild);
	Clear_field(Fild_);
	Flag_mtrix = First_step = false;
	Cnt_lived = Cnt_neighbors = currentX = currentY = 0;
	
	if (Flag_random_generation){
		int i, j;
		while (Cnt_lived < CNT_START){
			i = rand() % GAME_FIELD_SIZE;
			j = rand() % GAME_FIELD_SIZE;
			if (!Fild[i][j].Is_life){
				Fild[i][j].Is_life = TRUE;
				Fild[i][j].clr = Clr_block;
				Cnt_lived++;
			}
		}
	}
	
}

void CLifeDoc::Clear_field(Field** Mtrix){
	for (INT i(0); i < GAME_FIELD_SIZE; i++)
		for (int j(0); j < GAME_FIELD_SIZE; j++)
			Mtrix[i][j].Is_life = false;
}

void CLifeDoc::Do_live_move(Field** From, Field** To){
	for (INT i(0); i < GAME_FIELD_SIZE; i++){
		for (int j(0); j < GAME_FIELD_SIZE; j++){
			Check_live_cell(i, j, From, (Cnt_neighbors = 0));
			if (From[i][j].Is_life){
				if (Cnt_neighbors == 2 || Cnt_neighbors == 3){
					To[i][j].Is_life = true;					
				}
				else {
					To[i][j].Is_life = false;
					Cnt_lived--;
				}
			}
			else{
				if (Cnt_neighbors == 3){
					To[i][j].Is_life = true;
					Cnt_lived++;
				}
				else{
					To[i][j].Is_life = false;

				}
			}
		}
	}
}

void CLifeDoc::Check_live_cell(INT x, INT y, Field** Mtrix, INT &cnt){
	INT nx, ny;
	for (int i(0); i < 8; i++){
		nx = x + Shiftx[i];
		ny = y + Shifty[i];
		if (nx < 0)
			nx = GAME_FIELD_SIZE - 1;
		else if (nx >= GAME_FIELD_SIZE)
			nx = 0;
		if (ny < 0)
			ny = GAME_FIELD_SIZE - 1;
		else if (ny >= GAME_FIELD_SIZE)
			ny = 0;		
		if (Mtrix[nx][ny].Is_life)
			cnt++;		
	}
}

CLifeDoc::~CLifeDoc()
{

	for (INT i(0); i < GAME_FIELD_SIZE; i++){
		delete Fild[i];
		delete Fild_[i];
	}
	delete[]Fild;
	delete[]Fild_;
	delete[]Shifty;
	delete[]Shiftx;
}

BOOL CLifeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �������� ��� ��������� �������������
	// (��������� SDI ����� �������� ������������ ���� ��������)

	return TRUE;
}

// ������������ CLifeDoc

void CLifeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �������� ��� ����������
	}
	else
	{
		// TODO: �������� ��� ��������
	}
}

#ifdef SHARED_HANDLERS

// ��������� ��� �������
void CLifeDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �������� ���� ��� ��� ����������� ������ ���������
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ��������� ������������ ������
void CLifeDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������� ���������� ������ �� ������ ���������. 
	// ����� ����������� ������ ����������� ������ � ������� ";"

	// ��������:  strSearchContent = _T("�����;�������������;����;������ ole;");
	SetSearchContent(strSearchContent);
}

void CLifeDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// ����������� CLifeDoc

#ifdef _DEBUG
void CLifeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLifeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// ������� CLifeDoc
