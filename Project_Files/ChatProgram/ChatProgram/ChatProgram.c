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
	printf("���ϴ� �۾��� �����ϼ���\n1: ���� ���� 2: ���� �����ϱ� 3: ����\n");	
	scanf("%d", &menu);

	switch (menu) {
		case 1:
			printf("������ �� ��Ʈ�� �Է��ϼ���: ");
			scanf("%s", &port);
			printf(concat(port, "�� ��Ʈ�� ������ �������Դϴ�...\n"));
			system(concat("server.exe ", port));
			break;
		case 2:
			printf("������ ��Ʈ�� �Է��ϼ���: ");
			scanf("%s", &port);
			printf("�г����� �Է��ϼ���: ");
			scanf("%s", &name);
			printf(concat(name, "��, ȯ���մϴ�!\n"));
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