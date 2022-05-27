#include "ChessBoard.h"
/*********************************************
***   ���ļ��е������������ڻ�����Ϸ���水ť    ***
**********************************************/

static int playBackMyFlag = 0; // �б𵽴�ջ��
static double winwidth, winheight;   // ���ڳߴ�
extern int   Repent_the_move;  // �Ƿ���������
int   playBackAccount = 0;  // �ط����׼���
extern int playBackTop; // ���̻طż�¼��ջ��Ԫ��


// ������Ϸ����İ�ť����
void DrawChessButtons()
{
	usePredefinedColors(3);
	SetPointSize(22);
	setButtonColors("Dark Gray", "Gray", "Light Gray", "White", 1);

	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();
	double fH = GetFontHeight();
	double h = fH * 2;  // �ؼ��߶�
	double x = winwidth / 1.5;
	double y = winheight - h/1.5;
	double w = winwidth / 5; // �ؼ����

	// ��Ϸ��ʼ��ť
	if (button(GenUIID(0), x, y - 3 * h, w, h, start_game_end ? "End the Game" : "Start the Game"))
		start_game_end = start_game_end ? 0 : 1;
	// ��Ϸ��ͣ��ť
	if (button(GenUIID(0), x, y - 5 * h, w, h, pause_or_continue ? "Continue" : "Pause"))
		pause_or_continue = !pause_or_continue;
	// ���尴ť
	if (button(GenUIID(0), x, y - 7 * h, w, h, "Repent"))
		Repent_the_move = 1;
	// ��Ϸ¼�ư�ť
	if (button(GenUIID(0), x, y - 9 * h, w, h, game_record ? "End Record" : "Start Record"))
		game_record = !game_record;
	// �����˳���ť
	if (button(GenUIID(0), x, y - 11 * h, w, h, "Click to Quit"))
	{
		int result = MessageBox(NULL, "��ȷ��Ҫ�˳���Ϸ��?", "Tips", MB_OKCANCEL);
		if (result == 1)
		{
			exit(0);
		}
	}
}

// �ط�ʱ�İ�ť����
void DrawPlayBackButtons(int * playback_or_exit)
{
	usePredefinedColors(3);
	SetPointSize(22);
	setButtonColors("Dark Gray", "Gray", "Light Gray", "White", 1);

	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();
	double fH = GetFontHeight();
	double h = fH * 2;  // �ؼ��߶�
	double x = winwidth / 1.5;
	double y = winheight - h / 1.5;
	double w = winwidth / 5; // �ؼ����

	
	// ��һ��
	if (button(GenUIID(0), x, y - 4 * h, w, h, playBackMyFlag ? "PlayBack End" : "Next"))
	{
		if (playBackAccount < playBackTop)
		{
			printf("%d %d\n", playBackAccount, playBackTop);
			PlayBackStackPrint(playBackAccount);
			playBackAccount++;
		}
		else
		{
			int result = MessageBox(NULL, "�Ծֻط��Ѿ�����", "Tips", MB_OKCANCEL);
			playBackMyFlag = 1;
		}
	}
	// �˳��ԾֻطŰ�ť
	if (button(GenUIID(0), x, y - 6 * h, w, h, "End PlayBack"))
	{
	
		int result = MessageBox(NULL, "��ȷ��Ҫ�˳��Ծֻط���?", "Tips", MB_OKCANCEL);
		// ����ȷ�������ԾֻطŲŻ��˳�
		if (result == 1)
		{
			// �˳��ԾֻطŲ�������flag
			*playback_or_exit = 0;
			playBackMyFlag = 0;
		}
	}
	// �����˳���ť
	if (button(GenUIID(0), x, y - 8 * h, w, h, "Click to Quit"))
	{ 
		int result = MessageBox(NULL, "��ȷ��Ҫ�˳���Ϸ��?", "Tips", MB_OKCANCEL);
		// ֻ�а���ȷ����������Ż����
		if (result == 1)
		{
			exit(0);
		}
	}
}


// ����չʾʱ�İ�ť����
void DrawManualButtons(int *mode, int *manual)
{
	usePredefinedColors(3);
	SetPointSize(22);
	setButtonColors("Dark Gray", "Gray", "Light Gray", "White", 1);

	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();
	double fH = GetFontHeight();
	double h = fH * 2;  // �ؼ��߶�
	double x = winwidth / 1.5;
	double y = winheight - h / 1.5;
	double w = winwidth / 5; // �ؼ����


	// ���Ǿۻ�����
	if (button(GenUIID(0), x, y - 2 * h, w, h, "���Ǿۻ�"))
	{
		int result = MessageBox(NULL, "���Ǿۻᡱ�������㷺�����������Ĵ󽭺�����֮һ�����������������׼��������д˾֣�ֻ�Ǿ������в��죺���С�����ի��Ϸ�������Ϊ�����ǹ�������������бࡷ����֮Ϊ������ͬ�족����Ԩ�����������Ϊ�������ײʡ������ڴ˾�ͼ���к��˫��������ö���ӣ��ʾ���������ԡ����ǡ���֮�����ֹ�˼���ɣ������ķ���էһ�����췽����ʤ������̯ǰ�ġ�����ţ����������ʤ���У���������˵�Ȧ�ף��ʽ������˶��Դ˾�Ϊı���ķ�����", "��ֽ���", MB_OKCANCEL);
		if (result == 1)
		{
			*mode = 1;
		}
		else if (result == 2)
		{
			return;
		}
	}
	// ��򾽵������
	if (button(GenUIID(0), x, y - 4 * h, w, h, "��򾽵��"))
	{
		int result = MessageBox(NULL, "����򾽵���������䵥ȱ���˫��һ���Ĳо֣�ԭ�����߰�˫������Ϊ���е���������������С������Ϊ�ж�������������С����򾡣�����ض��ľ��ƣ�˫��������С��ǣ�ƣ������������ڷ�����������һС������ر任ʿ���λ�ã���ս�ɺͣ���������ս��ǿ��һ�����Ͳо֡���򾽵����������ô����ı�����������ի��Ϸ�ס��С���򾽵�������뱾����ͬ��������", "��ֽ���", MB_OKCANCEL);
		if (result == 1)
		{
			*mode = 2;
		}
		else if (result == 2)
		{
			return;
		}
	}
	// Ұ���������
	if (button(GenUIID(0), x, y - 6 * h, w, h, "Ұ�����"))
	{
		int result = MessageBox(NULL, "��Ұ�����Ǵ��͵������ž�֮һ���롰���Ǿۻᡱ������򾽵��������ǧ����С�������������Ϊ�Ĵ󽭺��ž֣���仯ʮ�ָ��Ӻ���¡���������˫�����˫����ĵ��Ͳо֣�ʵ�ü�ֵ�ܴ�����о��˾ֵ����ֺܶࡣԭ��Ϊ���Ⱥͣ������о�����Ϊ�˾�������α仯��ֻҪ�ڷ��߳����ţ�����Ӧ�Ǻ��Ⱥ�ʤ��", "��ֽ���", MB_OKCANCEL);
		if (result == 1)
		{
			*mode = 3;
		}
		else if (result == 2)
		{
			return;
		}
	}
	// ǧ���������
	if (button(GenUIID(0), x, y - 8 * h, w, h, "ǧ�����"))
	{
		int result = MessageBox(NULL, "��ǧ����С����β������һ����ս�������������ƪ�����䵥�������ݺᣬ��Ϊ����ǹ���ơ����˾ֵ���һ�ص��ǣ�˫����������У������������䣩�ͽ���˧��ʿ���ˣ������ࣩ�����ܸ������ܣ���ַ��Ӹ��ԵĹ���ս����������ν������ʿ���������иգ����������������ء��������о��о��еĽ��š�ͣ�ţ����ţ��ĺò��ϡ�", "��ֽ���", MB_OKCANCEL);
		if (result == 1)
		{
			*mode = 4;
		}
		else if (result == 2)
		{
			return;
		}
	}
	// �˳��ԾֻطŰ�ť
	if (button(GenUIID(0), x, y - 10 * h, w, h, "�˳���������"))
	{
		int result = MessageBox(NULL, "��ȷ��Ҫ�˳���������������?", "Tips", MB_OKCANCEL);
		if (result == 1)
		{
			*manual = 0;
		}
		else if (result == 2)
		{
			return;
		}
	}
		
}
