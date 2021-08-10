#include <iostream>

#include <WS2tcpip.h> //winsock header file


#pragma comment (lib, "ws2_32.lib")

using namespace std;

void main()
{
	//Initialize winsock
	WSADATA wsData;

	//version 2.2

	WORD ver = MAKEWORD(2, 2);

	//The WSAStartup function initiates use of the Winsock DLL by a process.
	//wVersionA pointer to the WSADATA data structure that is to receive details of the Windows Sockets implementation.Required
	//
	int wsOk = WSAStartup(ver, &wsData);

	if (wsOk != 0)
	{
		cerr << "can't initialize winsock" << endl;
		return;
	}

	//create a socket
	//AF_INET :The address family specification //The Internet Protocol version 4 (IPv4) address family.
	//AF_INET6: The Internet Protocol version 6 (IPv6) address family.
	//SOCK_STREAM: A socket type that provides sequenced, reliable, two-way, connection-based byte streams with
	//an OOB data transmission mechanism. This socket type uses the Transmission Control Protocol (TCP)
	//for the Internet address family (AF_INET or AF_INET6).
	// SOCK_DGRAM: A socket type that supports datagrams, which are connectionless, unreliable buffers
	// of a fixed(typically small) maximum length.This socket type uses the User Datagram Protocol(UDP)
	// for the Internet address family(AF_INET or AF_INET6).

	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);

	if (listening == INVALID_SOCKET)
	{
		cerr << "cant create socket" << endl;
		return;
	}

	//bind the socket an ip address and port to socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; //inet_addr(localIP)

	//The bind function associates a local address with a socket.
	bind(listening, (sockaddr *)&hint, sizeof(hint));

	//Tell winsock the socket is listening
	//The listen function places a socket in a state in which it is listening for an incoming connection.
	listen(listening, SOMAXCONN);

	//Wait for connection

	sockaddr_in client;
	int clientSize = sizeof(client);

	//The accept function permits an incoming connection attempt on a socket.
	//If no error occurs, accept returns a value of type SOCKET that is a descriptor for the new socket.
	//This returned value is a handle for the socket on which the actual connection is made.
	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];
	char service[NI_MAXHOST];

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXHOST, 0) == 0)
	{
		cout << host << "connected on port " << service << endl;
	}
	else
	{
	}

	closesocket(listening);

	char buf[4096];

	while (true)
	{
		ZeroMemory(buf, 4096);

		//Wait for client to send data
		//The recv function receives data from a connected socket or a bound connectionless socket.
		int bytesReceived = recv(clientSocket, buf, 4096, 0);

		if (bytesReceived == SOCKET_ERROR)
		{
			cerr << "Error in recv()" << endl;
			break;
		}

		if (bytesReceived == 0)
		{
			cout << "client disconnected " << endl;
			break;
		}

		cout << string(buf, 0, bytesReceived) << endl;

		//echo message back to client
		//The sendto function sends data to a specific destination.
		send(clientSocket, buf, bytesReceived + 1, 0);

		

	}

	//close the socket

	closesocket(clientSocket);


	WSACleanup();

	return;
}

