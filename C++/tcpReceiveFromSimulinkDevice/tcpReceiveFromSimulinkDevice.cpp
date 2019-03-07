/**
	\file TcpReceiveFromSimulinkDevice.cpp
	\brief Voorbeeld programma om gegevens uit een Arduino simulink-model te ontvangen 
	door middel van het tcp/ip protocol
	\author Gerard Harkema
	\date 6 maart 2019
	\remarks Gebuik dit programma samen met het ReceiveFromTcpServer.xls simulink model
*/

#include "stdafx.h"
#include "../tcpClientLibrary/tcpClient.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>

using namespace std;

/*! IP_ADDRESS: Ip address van het simulink model in de Arduino
*/
#define IP_ADDRESS  "192.168.2.87"
/*! PORT: poortnummer van het simulink model in de Arduino
*/
#define PORT 25000

/** RECEIVE_DATA: Definitie van de data-structuur die ontvangen wordt van det simulink model
Deze moet overeenkomen met de "Data size"van het simulink blok
*/
typedef struct {
	double Value1;
	double Value2;
}RECEIVE_DATA;

tcpClient theTcpReceiveClient(IP_ADDRESS, PORT);

int main() {

	int iResult;
	RECEIVE_DATA data;
	char rcvbuf[sizeof(data) + 1];

	//	theTcpReceiveClient.connectToServer(IP_ADDRESS, PORT);

	do {
		iResult = theTcpReceiveClient.receiveFromServer(rcvbuf, sizeof(data) + 1);
		if (iResult == SOCKET_ERROR) {
			cout << "receive failed with error" << endl;
			while (cin.get() != '\n');
			cin.get();
			return 1;
		}
		cout << "Bytes Received: " << iResult << endl;

		memcpy(&data, &rcvbuf, sizeof(data));
		cout << "Receiving " << data.Value1 << " , " << data.Value2 << endl;
	} while (!_kbhit());

	theTcpReceiveClient.disconnectFromServer();
	cout << "Disconnected from server" << endl;


	while (cin.get() != '\n');
	cin.get();
	return 0;
}


