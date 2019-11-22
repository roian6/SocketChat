#include <stdio.h>
#include <WinSock2.h>
#include <Windows.h>
#include <conio.h>
#include <string.h>

#define UP 72
#define DOWN 80
#define ENTER 13

char* concat(const char *s1, const char *s2);
void gotoxy(int x, int y);
void cursorView(char show);

int menu, cursor = 0;
char key = NULL;
char name[100], ip[100], port[100];

int main(void){
	cursorView(0);
	printf("----------------------------------------\n");
	printf("|               ���ع���               |\n");
	printf("|             Chat Program             |\n");
	printf("----------------------------------------\n");
	printf("              ���� �����                \n");
	printf("              ���� ����              \n");
	printf("              ����                      \n");

	while (key != ENTER) {
		if (cursor < 0)// Ŀ���� ���� �ʹ� �ö󰥶�
			cursor = 2;
		cursor %= 3; // ������ ���� 0, 1, 2 �� �ϳ�
		gotoxy(11, cursor + 4); printf("��");
		key = getch();
		if(key == -32 || key == 224)
			key = getch();
		switch (key) {
		case UP:
			gotoxy(11, cursor + 4); printf("  ");
			cursor--;
			break;
		case DOWN:
			gotoxy(11, cursor + 4); printf("  ");
			cursor++;
			break;
		}
	}

	switch (cursor) {
		case 0:
			system("cls");
			printf("������ �� ��Ʈ�� �Է��ϼ���: ");
			scanf("%s", &port);
			printf(concat(port, "�� ��Ʈ�� ������ �������Դϴ�...\n"));
			system(concat("server.exe ", port));
			break;
		case 1:
			system("cls");
			printf("������ ��Ʈ�� �Է��ϼ���: ");
			scanf("%s", &port);
			printf("�г����� �Է��ϼ���: ");
			scanf("%s", &name);
			printf(concat(name, "��, ȯ���մϴ�!\n"));
			system(concat(concat(concat("client.exe 127.0.0.1 ", port), " ") ,name));
			break;
		case 2:
			break;
	}
}



char* concat(const char *s1, const char *s2)
{
	const size_t len1 = strlen(s1);
	const size_t len2 = strlen(s2);
	char *result = malloc(len1 + len2 + 1); // +1 for the null-terminator
	// in real code you would check for errors in malloc here
	memcpy(result, s1, len1);
	memcpy(result + len1, s2, len2 + 1); // +1 to copy the null-terminator
	return result;
}

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void cursorView(char show)//Ŀ�������
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}