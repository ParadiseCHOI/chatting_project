//https://kevinthegrey.tistory.com/26 참고함

#include <iostream>
//#include "stdafx.h"
#include <stdio.h> //c++에서 c문법을 가져다 쓰며 구현
#include <WinSock2.h> //소켓 통신을 위한 헤더 파일
#pragma comment(lib, "ws2_32") //소켓 통신을 위한 lib 파일

#define PORT 4578 //PORT를 사용할 때는 예약된 포트를 제외하고 사용해야 한다.
#define PACKET_SIZE 1024 //패킷 사이즈 지정

int main()
{
	WSADATA wsaData; //Windows의 소켓 초기화 정보를 저장하기 위한 구조체. 이미 선언되어 있다.
	WSAStartup(MAKEWORD(2, 2), &wsaData); //(소켓 버전, WSADATA 구조체 주소) 이 함수를 가장 먼저 호출.
	//이 함수를 통해 Windows에게 어느 소켓을 활용할 것인지 알려준다.
	//2.2 버전을 사용할 것이기 때문에 MAKEWORD()를 사용해 2.2로 만들어 전달한다.

	SOCKET hListen; //소켓 구조체 생성
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); 
	//PF_INET은 IPv4를 사용한다는 것, SOCK_STREAM은 연결지향형 소켓, IPPROTO_TCP는 TCP 프로토콜 사용.

	SOCKADDR_IN	tListenAddr = {}; //hListen 소켓에 할당할 주소 정보 구조체 선언
	tListenAddr.sin_family = AF_INET; //반드시 AF_INET이어야 한다고 reference에 명시됨.
	tListenAddr.sin_port = htons(PORT); //PORT 번호는 2바이트 안에서 표현할 수 있는 숫자로 정해야 한다. 
	//htons(host to network short), 이 함수를 거치면 무조건 Big-endian 방식으로 데이터를 변환하여 설정한다.
	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY); //서버는 현재 작동되는 컴퓨터의 IP 주소로 설정해 줘야 한다.
	//현재 서버를 따로 두지 않고 구현할 것이기 때문이다. INADDR_ANY는 현재 동작되는 컴퓨터의 IP주소로 설정하는 것이다.
	//s_addr은 IPv4 인터넷 주소를 의미한다. htonl(long)도 htons(short)와 마찬가지. 자료형만 다름.
	
	bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr)); 
	//bind(소켓, 소켓 구성 요소 구조체의 주소, 그 구조체의 크기);
	//bind 함수는 소켓에 주소 정보를 연결한다. Listen 소켓의 역할은 접속 승인 뿐이다.
	//(SOCKADDR* 타입 형변환)
	listen(hListen, SOMAXCONN);
	//listen 함수는 연결을 수신하는 상태로 소켓의 상태를 변경한다.(대기 상태로 만들어 준다.)
	//SOMAXCONN은 한꺼번에 요청 가능한 최대 접속승인 수를 의미한다.

	SOCKADDR_IN tClntAddr = {}; //accept할 클라이언트 측 주소 정보 구조체 생성
	int iClntSize = sizeof(tClntAddr);
	SOCKET hClient = accept(hListen, (SOCKADDR*)&tClntAddr, &iClntSize);
	//accept함수를 이용해 접속 요청을 수락. 이 함수는 동기화된 방식으로 동작된다.
	//동기화된 방식이란 요청을 마무리 하기 전까지 계속 대기상태에 놓여 요청이 들어오기 전까지 이 함수는 빠져나오지 않는다.
	//접속 요청을 승인하면 연결된 소켓이 만들어져 return 되는데, 이것을 통해 통신해야 한다.

	char cBuffer[PACKET_SIZE] = {};
	//클라이언트측 정보를 수신하기 위해 기존에 정의해둔 패킷 크기만큼 버퍼를 생성.
	recv(hClient, cBuffer, PACKET_SIZE, 0);
	//recv함수는 대상 소켓으로부터 보내온 정보를 받아주는 역할을 한다.
	//보내준 데이터가 없으면 여기서 받을 때까지 대기 상태에 있게 된다.
	//flag를 활성화시키지 않을 것이기 때문에 0을 지정한다.
	printf("Recv Msg: %s\n", cBuffer);

	char cMsg[] = "Server Send";
	send(hClient, cMsg, strlen(cMsg), 0);
	//recv와 같은 맥락으로 서버가 메세지를 클라이언트측에 전달한다.
	closesocket(hClient); //클라이언트 소켓을 닫는다.
	closesocket(hListen); //서버의 listen 소켓을 닫는다.

	WSACleanup(); //소켓을 활용하는 것은 WSAStartup 함수와 WSACleanup 함수 사이에 작성해야 한다.
	//생성자와 소멸자 개념. WSAStartup을 하면서 지정한 내용을 지워준다.
	return 0;
}