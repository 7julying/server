#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib") //socket编程需要引用该库

using namespace std;
#define BUF_SIZE 512

int main()
{
	WSADATA wsd;
	SOCKET sHost;
	SOCKADDR_IN servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	char buf[BUF_SIZE];
	int retVal;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("WSAStartup failed!\n");
		return -1;
	}
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		printf("socket failed!\n");
		WSACleanup();
		return -1;
	}
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("10.99.12.18");
	servAddr.sin_port = htons((short)4999);
	int nServAddlen = sizeof(servAddr);
	retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
	if (SOCKET_ERROR == retVal)
	{
		printf("connect failed!\n");
		closesocket(sHost);
		WSACleanup();
		return -1;
	}
	while (1)
	{
		ZeroMemory(buf, BUF_SIZE);
		strcpy(buf, "MYTCP");
		retVal = send(sHost, buf, strlen(buf), 0);
		if (SOCKET_ERROR == retVal)
		{
			printf("send failed!\n");
			closesocket(sHost);
			WSACleanup();
			return -1;
		}
	}
	closesocket(sHost);
	WSACleanup();
	return 0;
}
