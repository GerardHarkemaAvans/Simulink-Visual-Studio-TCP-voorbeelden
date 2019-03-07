#pragma once
#include <winsock2.h>
#include <Ws2tcpip.h>

class tcpClient {

public:
	tcpClient();
	tcpClient(const char * ip_address, unsigned int port);

	int connectToServer(const char  *ip_address, unsigned int port);
	int sendToServer(const char * buf, int len);
	int receiveFromServer(char * buf, int len);
	int isConnectedToServer(void);
	int disconnectFromServer(void);

protected:
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct sockaddr_in clientService;
	int connected = 0;

};