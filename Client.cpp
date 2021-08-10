#include<iostream>
#include<string>
#include<WS2tcpip.h>

using namespace std;


#pragma comment(lib , "ws2_32.lib")
void main()
{
	string ipAddress = "127.0.0.1"; //IP address of the server
	int port = 54000; //Listening port on the server

	//Initialize Winsock
	WSADATA data;

	WORD ver = MAKEWORD(2, 2);

	int wsRes = WSAStartup(ver, &data);

	if (wsRes != 0)
	{
		cerr << "cant star winsock" << wsRes << endl;
		return;
	}

	//create a socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	//addrs Family_ IP version 4
	if (sock == INVALID_SOCKET)
	{
		cerr << " cant create socket, ERR" << WSAGetLastError() << endl;
		return;
	}

	//Fill in hint struct
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	//connect to server
	//The connect function establishes a connection to a specified socket.
	//sock: A descriptor identifying an unconnected socket.
	//hint: A pointer to the sockaddr structure to which the connection should be established.
	int connRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connRes == SOCKET_ERROR)
	{
		cerr << "cant connet to server " << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
	}


	char buf[4096];
	string userInput;

	do
	{
		cout << "> ";

		getline(cin, userInput);

		if (userInput.size() > 0)
		{
			//Send the text
			int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendRes != SOCKET_ERROR)
			{
				//Wait for the response
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0)
				{
					//Echo response to console
					cout << "Server >" << string(buf, 0, bytesReceived) << endl;
				}
			}
		}

	} while (userInput.size() != 0);

		//Gracefully close down everything
	closesocket(sock);
	//The closesocket function closes an existing socket.
	WSACleanup();
	//The WSACleanup function terminates use of the Winsock 2 DLL (Ws2_32.dll).
}