#pragma once
/*! 
\file tcpClient.h
\brief Interface(.h) van de TCP/IP library voor TCP/IP communicatie met een Arduino Simulink model
\author Gerard Harkema
\date 6 maart 2019
*/
#include <winsock2.h>
#include <Ws2tcpip.h>

class tcpClient {

public:
	/*! Default constructor, maakt nog geen verbinding met het Arduino Simulink model.

	*/
	tcpClient();

	/*! \brief Verbinding maken met de TCP/IP server in het Arduino Simulink model.\n

	\param ip_address	Ip address van TCP/IP server in her Arduino Simulink model
	\param port			Poortnummer van TCP/IP server in her Arduino Simulink model
	\return				0: bij succes\n
						<> 0: als er een fout is opgetreden.
	*/
	tcpClient(const char * ip_address, unsigned int port);
	
	/*! \brief Verbinding maken met de TCP/IP server in het Arduino Simulink model.\n

	\param ip_address	Ip address van TCP/IP server in her Arduino Simulink model
	\param port			Poortnummer van TCP/IP server in her Arduino Simulink model
	\return				0: bij succes\n
						<> 0: als er een fout is opgetreden.
	*/
	int connectToServer(const char  *ip_address, unsigned int port);

	/*! \brief Bericht verzenden naar het Arduino Simulink model.

	\param buf	pointer naar het te verzenden bericht
	\param len			lengte van het bericht in bytes
	\return				>=0: aantal verzonden bytes\n
						<0: fout bij het verzenden
	*/
	int sendToServer(const char * buf, int len);

	/*! \brief Bericht ontvangen van het Arduino Simulink model.

	\param buf	pointer naar het te ontvangen bericht
	\param len			maximale lengte van het te ontvangen bericht in bytes
	\return				>=0: aantal ontvangen bytes in het bericht/n
						<0: fout bij het verzenden
	*/	
	int receiveFromServer(char * buf, int len);

	/*! \brief Opvragen van de status van de verbinding

	\return				0: niet verbonden\n
						<>0: Verbonden
	*/	
	int isConnectedToServer(void);

	/*! \brief Verbinding verbreken met het Arduino Simulink model

	\return				0: bij succes\n
						<>0: als er een fout is opgetreden.
	*/	
	int disconnectFromServer(void);

	//! DOXYS_OFF
protected:
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct sockaddr_in clientService;
	int connected = 0;

	//! DOXYS_ON

};