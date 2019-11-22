# 프로그래밍 보고서

### 팀원

10422 정윤하, 10423 정찬효

### 프로젝트 이름

말해 뭐해 (C언어 소켓 채팅 프로그램)

### 프로젝트 소개

"말해 뭐해"는 C언어를 이용해 개발한 소켓 채팅 프로그램입니다. 사용자는 프로그램을 통해 간단한 조작 만으로 채팅 서버를 열 수 있으며, 같은 네트워크 안에 있다면 누구나 채팅에 참여하여 대화를 나눌 수 있습니다.

### 주요 기능

- 소켓 서버 기능 - 프로그램을 실행하고 포트를 입력하면 해당 포트에 서버를 열 수 있으며, 이후에 해당 서버에 접속한 유저의 정보를 볼 수 있습니다.
- 채팅 클라이언트 기능 - 자신의 IP와 접속할 포트, 그리고 닉네임을 입력하면 해당 서버에 접속하여 다른 유저들과 대화를 나눌 수 있습니다.

### 기술 설명

```
//클라이언트 주요 함수

unsigned WINAPI SendMsg(void* arg){//전송용 쓰레드함수
	SOCKET sock = *((SOCKET*)arg);//서버용 소켓을 전달한다.
	char nameMsg[NAME_SIZE + BUF_SIZE];
	while (1){//반복
		fgets(msg, BUF_SIZE, stdin);//입력을 받는다.
		if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")){//q를 입력하면 종료한다.
			closesocket(sock);
			exit(0);
		}
		sprintf(nameMsg, "%s %s", name, msg);//nameMsg에 메시지를 전달한다.
		send(sock, nameMsg, strlen(nameMsg), 0);//nameMsg를 서버에게 전송한다.
	}
	return 0;
}

unsigned WINAPI RecvMsg(void* arg){
	SOCKET sock = *((SOCKET*)arg);//서버용 소켓을 전달한다.
	char nameMsg[NAME_SIZE + BUF_SIZE];
	int strLen;
	while (1){//반복
		strLen = recv(sock, nameMsg, NAME_SIZE + BUF_SIZE - 1, 0);//서버로부터 메시지를 수신한다.
		if (strLen == -1)
			return -1;
		nameMsg[strLen] = 0;//문자열의 끝을 알리기 위해 설정
		fputs(nameMsg, stdout);//자신의 콘솔에 받은 메시지를 출력한다.
	}
	return 0;
}
```

```
//서버 주요 함수

void SendMsg(char* msg, int len){ //메시지를 모든 클라이언트에게 보낸다.
	int i;
	WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
	for (i = 0; i<clientCount; i++)//클라이언트 개수만큼
		send(clientSocks[i], msg, len, 0);//클라이언트들에게 메시지를 전달한다.
	ReleaseMutex(hMutex);//뮤텍스 중지
}
```

### 사용 방법

#### 서버 열기

1. 프로그램 실행 후 `서버 만들기` 선택
2. 서버를 열 포트 입력
3. 서버가 만들어지면, 해당 서버에 접속하는 유저의 정보를 볼 수 있음.

#### 서버 접속하기

1. 프로그램 실행 후 `서버 들어가기` 선택
2. 자신의 IP 입력(cmd에서 `ipconfig` 실행 후 IPv4 주소 입력)
3. 닉네임 입력
4. 채팅 시작하기

### 유의 사항

간혹 PC에 따라 msvcr120d.dll이 없다는 오류가 발생할 수 있는데, 함께 첨부한 msvcr120d.dll 파일을 `C:\Windows\SysWOW64` 폴더 안에 넣고 프로그램을 다시 시작하면 해결할 수 있습니다.

(컴퓨터 9실 학생 PC에서는 아무 오류 없이 정상 작동하는 것을 확인했습니다.)
