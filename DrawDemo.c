#include "DrawDemo.h"
/*********************************************
***   ���ļ��������ڻ�����ҳ�������           ***
**********************************************/

int	start_game_end = 0;    // ��Ϸ��ʼ���߽���
int restart_the_game = 0;  // ��Ϸ�Ƿ����¿�ʼ
int game_record = 0;	   // �Ƿ���¼�ƶԾ�
int	pause_or_continue = 0; // ��ͣ���߼���
int playback_or_exit = 0;  // �Ծֻط�
int manual = 0;

static double winwidth, winheight;   // ���ڳߴ�
static int    show_more_buttons = 0; // ��ʾ���ఴť

static char* menuListGame[] = { "Game", // �������в˵���
	"Start | Ctrl-A",  // ��ݼ��������[Ctrl-X]��ʽ�������ַ����Ľ�β
	"End | Ctrl-Z",
	"Pause | Ctrl-P",
	"Restart | Ctrl-R",
	"Exit | Ctrl-E" };

static char* menuListRecord[] = { "Record", // �Ծּ�¼�ͶԾֻطŲ˵���
	"Begin Record | Ctrl-C",
	"Begin Playback | Ctrl-B" };

static char* menuListHelp[] = { "Help",  // �����˵���
	"Show More | Ctrl-M",
	"Basic Rules",
	"Rules of Move Chess",
	"About the Program"};

static char* menuListShortcutKeys[] = {"Keys", // ��ݼ��˵���
	"Start | Ctrl-A", 
	"End | Ctrl-Z",
	"Pause | Ctrl-P",
	"Restart | Ctrl-R",
	"Exit | Ctrl-E", 
	"Begin Record | Ctrl-C",
	"End Playback | Ctrl-B", 
};

static char* selectedLabel = NULL;
static double fH, x, y, h, w, wlist, xindent;

// �����˵���
void drawMenu()
{
	usePredefinedColors(4);
	
	// ��ô��ڳߴ�
	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	fH = GetFontHeight();
	x = 0; 
	y = winheight;
	h = fH * 1.5; // �ؼ��߶�
	w = TextStringWidth(menuListRecord[0]) * 1.4; // �ؼ����
	wlist = TextStringWidth(menuListRecord[2]) * 1.3;
	xindent = winheight / 20; // ����
	
	int selection;

	// menu bar
	drawMenuBar(0, y - h, winwidth, h);
	
	// Game Tool�˵�
	menuListGame[3] = pause_or_continue ? "Continue | Ctrl-O" : "Pause | Ctrl-P";
	selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListGame, sizeof(menuListGame) / sizeof(menuListGame[0]));
	if (selection > 0) selectedLabel = menuListGame[selection];
	if (selection == 1)
		start_game_end = 1;
	if (selection == 2)
		start_game_end = 0;
	if (selection == 3)
		pause_or_continue = !pause_or_continue;
	if (selection == 4)
		restart_the_game = 1;
	if (selection == 5)
		exit(-1); // choose to exit

	// Record Tool�˵�
	menuListRecord[1] = game_record ? "End Record | Ctrl-C" : "Begin Record | Ctrl-C";
	menuListRecord[2] = playback_or_exit ? "End Playback | Ctrl-B" : "Begin Playback | Ctrl-B";
	selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListRecord, sizeof(menuListRecord) / sizeof(menuListRecord[0]));
	if (selection > 0) selectedLabel = menuListRecord[selection];
	if (selection == 1)
		game_record = !game_record;
	if (selection == 2)
		playback_or_exit = !playback_or_exit;

	// Help �˵�
	menuListHelp[1] = show_more_buttons ? "Show Less | Ctrl-M" : "Show More | Ctrl-M";
	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	if (selection > 0) selectedLabel = menuListHelp[selection];
	if (selection == 1)
		show_more_buttons = !show_more_buttons;
	if (selection == 2)
		MessageBox(NULL, "�����淨: �й��������Ϸ�þ������̺�������ɣ��Ծ�ʱ����ִ�����һ�����ߣ�˫����������һ�У�ֱ���ֳ�ʤ�������ͣ��Ծּ����ˡ��ֵ������һ������ĳ�����Ӵ�һ��������ߵ���һ������㣬���߳Ե��Է������Ӷ�ռ���佻��㣬��������һ�š�˫������һ�ţ���Ϊһ���غϡ�\n", "��Ϸ�淨����", MB_OK);
	if (selection == 3)
		MessageBox(NULL, "�������: �����������˧/���ƶ���Χ��ֻ���ھŹ����ƶ��ƶ�����ÿһ��ֻ����ˮƽ��ֱ�ƶ�һ���������˧�ͽ���׼��ͬһֱ����ֱ�Ӷ��棨�м������ӣ�����һ������ռ��λ�ã�����һ������رܣ������������/ʿ�ƶ���Χ��ֻ���ھŹ����ƶ��ƶ�����ÿһ��ֻ�����ضԽ��߷����ƶ�һ����/���ƶ���Χ���ӽ��һ���ƶ�����ÿһ��ֻ�����ضԽ��߷����ƶ����㣬��ʹ�ú����е���������ر��������ָ�ĶԽ��ߣ��׳��ࣨ�������֡����ࣨ������·���У�����������������ʱ�����ۼ������ǶԷ����ӣ����������߹�ȥ���׳ƣ����ࣨ���ۡ��R�ƶ���Χ���κ�λ���ƶ�����ÿһ��ֻ����ˮƽ��ֱ�ƶ�һ�㣬�ٰ��Խ��߷�������������ƶ�����ʹ�ú����е�����������������߷�ʽ���׳ƣ��������֣�б�Խ��ߣ������R����ʱ����һ��ֱ�л���д��б�����ӣ����ۼ������ǶԷ����ӣ���ס�������߹�ȥ���׳ƣ������ȡ�܇�ƶ���Χ���κ�λ���ƶ����򣺿���ˮƽ��ֱ�����ƶ���������谭�ĵ���/�h�ƶ���Χ���κ�λ���ƶ������ƶ������ͳ������ƣ�������������һ���������Ե��Է����ӡ���/���ƶ���Χ���κ�λ���ƶ����򣺹��ӽ�ǰ��ÿ��ֻ����ǰ�ƶ�һ�㡣���ӽ���������������ƶ��������������䣩����������ƶ���\n", "����������", MB_OK);
	if (selection == 4)
		MessageBox(NULL, "C��̴���ҵ��������Ϸ\n�汾��1.0.4\n���ߣ�Ĳ��տ\n������:\n˫�˶�ս���Ծֻطš��������׼��͵�\n��Ϸ�������\nBasic Rules && Rules of Move Chess", "����", MB_OK);
			 
	
	// Shortcup_Keys �˵�
	menuListShortcutKeys[6] = game_record ? "End Record | Ctrl-C" : "Begin Record | Ctrl-C";
	menuListShortcutKeys[7] = playback_or_exit ? "End Playback | Ctrl-B" : "Begin Playback | Ctrl-B";
	selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListShortcutKeys, sizeof(menuListShortcutKeys) / sizeof(menuListShortcutKeys[0]));
	if (selection > 0) selectedLabel = menuListShortcutKeys[selection];
	if (selection == 1)
		start_game_end = 1;
	if (selection == 2)
		start_game_end = 0;
	if (selection == 3)
		pause_or_continue = !pause_or_continue;
	if (selection == 4)
		start_game_end = 1;
	if (selection == 5)
		exit(-1); // choose to exit
	if (selection == 6)
		game_record = !game_record;
	if (selection == 7)
		playback_or_exit = !playback_or_exit;
}

// �˵����
void drawMenuResult(){
	SetPointSize(50);
	SetPenColor("Orange");
	drawLabel(0.3, winheight / 1.3, "Chinese Chess Game");
	SetPointSize(22);
	
	// ��ʾ�˵����н��
	x = winwidth/8;
	y = winheight/8*5.5;
	
	SetPenColor("Black");
	drawLabel(x, y -= h, "Game Progress Status:");
	SetPenColor("Red");
	char status[20];
	if (start_game_end == 0) {
		strcpy(status, "Wait for Start");
	}
	else {
		if (pause_or_continue)
			strcpy(status, "Game on Pause");
		else
			strcpy(status, "Game in Progress");
	}
	drawLabel(x + xindent, y -= h, status);
	
	SetPenColor("Black");
	drawLabel(x, y-=h, "Playback Process Status:");
	SetPenColor("Red");
	drawLabel(x + xindent, y -= h, playback_or_exit ? "Game Being Playbacked" : "Wait for PlayBack");
	
	SetPenColor("Black");
	drawLabel(x,    y-=h, "Control Variable Status");
	SetPenColor("Red");
	drawLabel(x+xindent, y-=h, show_more_buttons ? "More Buttons" : "Less Button");

	SetPenColor("Black");
	drawLabel(x, y -= h, "Most recently selected menu is:");
	SetPenColor("Red");
	drawLabel(x + xindent, y -= h, selectedLabel);
}

// ��ť����
void drawButtons()
{
	setButtonColors("Dark Gray", "Gray", "Light Gray", "White", 1);
		
	double fH = GetFontHeight();
	double h = fH * 2;  // �ؼ��߶�
	double x = winwidth / 1.7;
	double y = winheight - h;
	double w = winwidth / 5; // �ؼ����
	
		// ��Ϸ��ʼ��ť
	if (button(GenUIID(0), x, y - 3 * h, w, h, start_game_end ? "������Ϸ" : "��ʼ��Ϸ" ))
		start_game_end = start_game_end ? 0: 1;
		// ��ʼ�������͵İ�ť
	if (button(GenUIID(0), x, y - 5 * h, w, h, "��������"))
		manual = 1;
		// ��Ϸ¼�ư�ť
	if (button(GenUIID(0), x, y - 7 * h, w, h, playback_or_exit ? "�˳��ط�" : "�Ծֻط�"))
		playback_or_exit = !playback_or_exit;
		// �����˳���ť
	if (button(GenUIID(0), x, y - 9 * h, w, h, "�˳���Ϸ")) {
		int result = MessageBox(NULL, "��ȷ��Ҫ�˳���Ϸ��?", "Tips", MB_OKCANCEL);
		if (result == 1)
		{
			exit(0);
		}
	}

	// ��ʾӢ�İ���
	if (show_more_buttons)
	{
		if (button(GenUIID(0), x * 1.35, y - 3 * h, w, h, start_game_end ? "End the Game" : "Begin the Game"))
			start_game_end = start_game_end ? 0 : 1;
		// ��ʼ�������͵İ�ť
		if (button(GenUIID(0), x * 1.35, y - 5 * h, w, h, "Manual"))
			manual = 1;
		// ��Ϸ¼�ư�ť
		if (button(GenUIID(0), x * 1.35, y - 7 * h, w, h, playback_or_exit ? "End the Playback" : "PlayBack"))
			playback_or_exit = !playback_or_exit;
		// �����˳���ť
		if (button(GenUIID(0), x * 1.35, y - 9 * h, w, h, "Click to Exit")) {
			int result = MessageBox(NULL, "��ȷ��Ҫ�˳���Ϸ��?", "Tips", MB_OKCANCEL);
			if (result == 1)
			{
				exit(0);
			}
		}
	}
}


