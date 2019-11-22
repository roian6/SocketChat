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
	printf("|               말해뭐해               |\n");
	printf("|             Chat Program             |\n");
	printf("----------------------------------------\n");
	printf("              서버 만들기                \n");
	printf("              서버 들어가기              \n");
	printf("              종료                      \n");

	while (key != ENTER) {
		if (cursor < 0)// 커서가 위로 너무 올라갈때
			cursor = 2;
		cursor %= 3; // 나머지 연산 0, 1, 2 중 하나
		gotoxy(11, cursor + 4); printf("▷");
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
			printf("서버를 열 포트를 입력하세요: ");
			scanf("%s", &port);
			printf(concat(port, "번 포트에 서버가 실행중입니다...\n"));
			system(concat("server.exe ", port));
			break;
		case 1:
			system("cls");
			printf("접속할 포트를 입력하세요: ");
			scanf("%s", &port);
			printf("닉네임을 입력하세요: ");
			scanf("%s", &name);
			printf(concat(name, "님, 환영합니다!\n"));
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

void cursorView(char show)//커서숨기기
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}