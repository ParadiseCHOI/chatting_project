//https://kevinthegrey.tistory.com/26 참고함

#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32")

#define PORT	4578
#define PACKET_SIZE 1024
#define SERVER_IP	"192.168.xx.xxx"

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hSocket;
	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tAddr = {};
	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(PORT);
	tAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	connect(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr)); //클라이언트에서는 bind 대신 connect 함수를 사용
	//connect함수는 지정된 소켓에 연결을 설정. 서버에 연결하기 위해 connect 함수를 사용.

	char	cMsg[] = "Client Send";
	send(hSocket, cMsg, strlen(cMsg), 0);

	char	cBuffer[PACKET_SIZE] = {};
	recv(hSocket, cBuffer, PACKET_SIZE, 0);

	printf("Recv Msg : %s\n", cBuffer);

	closesocket(hSocket);

	WSACleanup();
}
