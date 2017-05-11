
// LifeDoc.h : ��������� ������ CLifeDoc
//


#pragma once

#define GAME_FIELD_SIZE 50
#define CNT_START 1000
#define CNT_BLOCKS 2500
#define ID_TIMER 1
#define MIN_FPS 1
#define MAX_FPS 60

#define ClearBit(reg, bit)       reg &= (~(1<<(bit)))
//������: ClearBit(PORTB, 1); //�������� 1-� ��� PORTB

#define SetBit(reg, bit)          reg |= (1<<(bit))
//������: SetBit(PORTB, 3); //���������� 3-� ��� PORTB

enum ConsoleColor
{
	Blue = 0x00FF0000,//Blue
	Green = 0x00008000,//Green
	Cyan = 0x00FFFF00,//Cyan
	Red = 0x000000FF,//Red
	Magenta = 0x00FF00FF,//Magenta
	Brown = 0x002A2AA5,//Brown
	Yellow = 0x0000FFFF,//Yellow
	Gray = 0x00808080, //Gray
	White = 0x00FFFFFF,//White
	Black = 0x00000000,//Black
	Lavender = 0x00FAE6E6,
	LightBlue = 0x00E6D8AD,
	Lime = 0x0032CD32,
	Indigo = 0x0082004B,
};

struct Field{
	BOOL Is_life;
	ConsoleColor clr;
	Field(){
		Is_life = false;
		clr = Black;
	}
	Field(BOOL live, ConsoleColor color){
		Is_life = live;
		clr = color;
	}
};

class CLifeDoc : public CDocument
{
protected: // ������� ������ �� ������������
	CLifeDoc();
	DECLARE_DYNCREATE(CLifeDoc)

// ��������
public:
	Field** Fild, **Fild_;

	INT SizeBlock,
		*Shiftx, *Shifty,
		Cnt_lived, Cnt_neighbors,
		currentX, currentY, 
		FPS;
	BOOL Flag_mtrix, Flag_mode, Flag_game, First_step;
	ConsoleColor Clr_background, Clr_border, Clr_block;
// ��������
public:
	void New_game(BOOL Flag_random_generation);
	void Do_live_move(Field** From, Field** To);
	void Clear_field(Field** Mtrix);	
	void Check_live_cell(INT x, INT y, Field** Mtrix, INT &cnt);
// ���������������
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ����������
public:
	virtual ~CLifeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ��������� ������� ����� ���������
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ��������������� �������, �������� ���������� ������ ��� ����������� ������
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
