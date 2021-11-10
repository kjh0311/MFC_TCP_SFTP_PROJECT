#include "pch.h"
#include "CTcpConnector.h"

static const int TIMEOUT_USEC = 100000;


bool CTcpConnector::Connect(char* host, int port)
{
	bool result = true;
	int recval;

	TIMEVAL Timeout;
	Timeout.tv_sec = 0;
	Timeout.tv_usec = TIMEOUT_USEC;
	
	//윈도우 소켓(원속) 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("WSAStartup Error\n");
		result = false;
	}

	//소켓 확인(connect)
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		printf("socket() Error\n");
		result = false;
	}

	//연결 확인
	SOCKADDR_IN clientAddr;

	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(port);
	inet_pton(AF_INET, host, &(clientAddr.sin_addr.S_un.S_addr));

	//set the socket in non-blocking
	unsigned long iMode = 1;
	int iResult = ioctlsocket(clientSocket, FIONBIO, &iMode);
	if (iResult != NO_ERROR)
	{
		printf("ioctlsocket failed with error: %ld\n", iResult);
	}

	recval = connect(clientSocket, (SOCKADDR *)&clientAddr, sizeof(clientAddr));
	if (recval == SOCKET_ERROR)
	{
		printf("connect() Error\n");
		result = false;
	}

	fd_set Write, Err;
	FD_ZERO(&Write);
	FD_ZERO(&Err);
	FD_SET(clientSocket, &Write);
	FD_SET(clientSocket, &Err);

	// check if the socket is ready
	select(0, NULL, &Write, &Err, &Timeout);
	if (FD_ISSET(clientSocket, &Write))
	{
		result = true;
	}

	closesocket(clientSocket);
	WSACleanup();

	return result;
}
