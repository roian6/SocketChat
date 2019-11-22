#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>

#define BUF_SIZE 100
#define NAME_SIZE 20

#pragma comment(lib, "ws2_32.lib")

unsigned WINAPI SendMsg(void* arg);//������ �����Լ�
unsigned WINAPI RecvMsg(void* arg);//������ �����Լ�
void ErrorHandling(char* msg);

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];

int main(int argc, char* argv[]){
	WSADATA wsaData;
	SOCKET sock;
	SOCKADDR_IN serverAddr;
	HANDLE sendThread, recvThread;
	if (argc != 4){
		printf("Usage : %s <IP> <port> <name>\n", argv[0]);
		exit(1);
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)// ������ ������ ����Ѵٰ� �ü���� �˸�
		ErrorHandling("WSAStartup() error!");

	sprintf(name, "[%s]", argv[3]);
	sock = socket(PF_INET, SOCK_STREAM, 0);//������ �ϳ� �����Ѵ�.

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
	serverAddr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)//������ �����Ѵ�.
		ErrorHandling("connect() error");

	//���ӿ� �����ϸ� �� �� �Ʒ��� ����ȴ�.
	send(sock, name, strlen(name), 0);

	sendThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&sock, 0, NULL);//�޽��� ���ۿ� �����尡 ����ȴ�.
	recvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&sock, 0, NULL);//�޽��� ���ſ� �����尡 ����ȴ�.

	WaitForSingleObject(sendThread, INFINITE);//���ۿ� �����尡 �����ɶ����� ��ٸ���./
	WaitForSingleObject(recvThread, INFINITE);//���ſ� �����尡 �����ɶ����� ��ٸ���.
	//Ŭ���̾�Ʈ�� ���Ḧ �õ��Ѵٸ� ���� �Ʒ��� ����ȴ�.
	closesocket(sock);//������ �����Ѵ�.
	WSACleanup();//������ ���� ��������� �ü���� �˸���.
	return 0;
}

unsigned WINAPI SendMsg(void* arg){//���ۿ� �������Լ�
	SOCKET sock = *((SOCKET*)arg);//������ ������ �����Ѵ�.
	char nameMsg[NAME_SIZE + BUF_SIZE];
	while (1){//�ݺ�
		fgets(msg, BUF_SIZE, stdin);//�Է��� �޴´�.
		if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")){//q�� �Է��ϸ� �����Ѵ�.
			closesocket(sock);
			exit(0);
		}
		sprintf(nameMsg, "%s %s", name, msg);//nameMsg�� �޽����� �����Ѵ�.
		send(sock, nameMsg, strlen(nameMsg), 0);//nameMsg�� �������� �����Ѵ�.
	}
	return 0;
}

unsigned WINAPI RecvMsg(void* arg){
	SOCKET sock = *((SOCKET*)arg);//������ ������ �����Ѵ�.
	char nameMsg[NAME_SIZE + BUF_SIZE];
	int strLen;
	while (1){//�ݺ�
		strLen = recv(sock, nameMsg, NAME_SIZE + BUF_SIZE - 1, 0);//�����κ��� �޽����� �����Ѵ�.
		if (strLen == -1)
			return -1;
		nameMsg[strLen] = 0;//���ڿ��� ���� �˸��� ���� ����
		fputs(nameMsg, stdout);//�ڽ��� �ֿܼ� ���� �޽����� ����Ѵ�.
	}
	return 0;
}

void ErrorHandling(char* msg){
	fputs(msg, stderr);

	fputc('\n', stderr);
	exit(1);
}