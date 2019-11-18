#include <stdio.h>
#include <WinSock2.h>
#include <Windows.h>
#include <conio.h>
#include <string.h>

char* concat(const char *s1, const char *s2);

int menu;
char name[100], ip[100], port[100];

int main(void){
	printf("Chat Program\n");
	printf("원하는 작업을 선택하세요\n1: 서버 열기 2: 서버 접속하기 3: 종료\n");	
	scanf("%d", &menu);

	switch (menu) {
		case 1:
			printf("서버를 열 포트를 입력하세요: ");
			scanf("%s", &port);
			printf(concat(port, "번 포트에 서버가 실행중입니다...\n"));
			system(concat("server.exe ", port));
			break;
		case 2:
			printf("접속할 포트를 입력하세요: ");
			scanf("%s", &port);
			printf("닉네임을 입력하세요: ");
			scanf("%s", &name);
			printf(concat(name, "님, 환영합니다!\n"));
			system(concat(concat(concat("client.exe 127.0.0.1 ", port), " ") ,name));
			break;
		case 3:
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