#include "stdafx.h"  // Dummy to make it compiling
#include "tcpClient.h"
#include <iostream>
#include <stdio.h>

//#define DBG_MESSAGE

using namespace std;

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")


tcpClient::tcpClient() {

}
tcpClient::tcpClient(const char * ip_address, unsigned int port) {
	this->connectToServer(ip_address, port);
}

int tcpClient::connectToServer(const char * ip_address, unsigned int port) {
	int iResult;

	//----------------------
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
#if defined DBG_MESSAGE
		cout << "WSAStartup failed with error: " << iResult << endl;
#endif
		return iResult;
	}
#if defined DBG_MESSAGE
	cout << "WSAStartup: Oke\n";
#endif

	//----------------------
	// Create a SOCKET for connecting to server
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET) {
#if defined DBG_MESSAGE
		cout << "socket failed with error: " << WSAGetLastError() << endl;
#endif
		WSACleanup();
		return SOCKET_ERROR;
	}
#if defined DBG_MESSAGE
	cout << "Create socket Oke" << endl;
#endif


	//----------------------
	// The sockaddr_in structure specifies the address family,
	// IP address, and port of the server to be connected to.
	clientService.sin_family = AF_INET;
	inet_pton(AF_INET, ip_address, &clientService.sin_addr.s_addr);
//	clientService.sin_port = htons(TELNET_PORT);
	clientService.sin_port = htons(port);

	//----------------------
	// Connect to server.
	iResult = connect(this->ConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService));
	if (iResult == SOCKET_ERROR) {
#if defined DBG_MESSAGE
		cout << "Connect failed with error: " << WSAGetLastError() << endl;
#endif
		closesocket(this->ConnectSocket);
		WSACleanup();
		return SOCKET_ERROR;
	}
#if defined DBG_MESSAGE
	cout << "Connect Oke" << endl;
#endif
	this->connected = ~0;
	return NO_ERROR;
}

int tcpClient::sendToServer(const char * buf, int len) {

	if (this->connected) {
		int iResult;
		//	memcpy(sendbuf, buf, len);
		iResult = send(this->ConnectSocket, buf, len, 0);
		//		iResult = send(ConnectSocket, data, sizeof(data), 0);
		if (iResult == SOCKET_ERROR) {
#if defined DBG_MESSAGE
			cout << "send failed with error: " << WSAGetLastError() << endl;
#endif
			closesocket(ConnectSocket);
			WSACleanup();
			return SOCKET_ERROR;
		}
#if defined DBG_MESSAGE
		cout << "Bytes Sent: " << iResult << endl;
#endif
		return iResult;
	}
	else return SOCKET_ERROR;
}

int tcpClient::receiveFromServer(char * buf, int len) {
	
	if (this->connected) {
		int iResult;
		iResult = recv(ConnectSocket, buf, len, 0);

		if (iResult < 0)
		{
#if defined DBG_MESSAGE
			cout << "receive failed with error: " << WSAGetLastError() << endl;
#endif
			return iResult;
		}
#if defined DBG_MESSAGE
		buf[len] = '\0';
		cout << "Bytes received: " << iResult << endl;
		cout << buf << endl;
#endif
		return iResult;
	}
	else return SOCKET_ERROR;
}
int tcpClient::isConnectedToServer(void) {
	return this->connected;
}

int tcpClient::disconnectFromServer(void) {
	// shutdown the connection since no more data will be sent
	int iResult;

	this->connected = 0;

	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
#if defined DBG_MESSAGE
		cout << "shutdown failed with error: " << WSAGetLastError() << endl;
#endif
		closesocket(ConnectSocket);
		WSACleanup();
		return iResult;
	}


	// close the socket
	iResult = closesocket(ConnectSocket);
	if (iResult == SOCKET_ERROR) {
#if defined DBG_MESSAGE
		cout << "close failed with error: " << WSAGetLastError() << endl;
#endif
		WSACleanup();
		return iResult;
	}

	WSACleanup();
	return NO_ERROR;
}
