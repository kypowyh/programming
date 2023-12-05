#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")

// од клиента

int main(){

	while (1) {

		const char SERVER_IP[] = "127.0.0.1"; // указываем адрем
		const short SERVER_PORT_NUM = 6379; // указываем порт

		int erStat;

		struct in_addr ip_to_num;
		inet_pton(AF_INET, SERVER_IP, &ip_to_num); // ip адрес в числовой формат 


		WSADATA wsData;
		erStat = WSAStartup(MAKEWORD(2, 2), &wsData); // вызов сокетов

		if (erStat != 0) { // обработка ошибок 
			printf("Error WinSock version initializaion #\n");
			WSAGetLastError();
			return 1;
		}
		else
			printf("WinSock initialization is OK\n");

		SOCKET ClientSock = socket(AF_INET, SOCK_STREAM, 0); // инициализаци€ сокета 

		if (ClientSock == INVALID_SOCKET) { // обработка ошибок 
			printf("Error initialization socket # \n");
			WSAGetLastError();
			closesocket(ClientSock);
			WSACleanup();
		}
		else
			printf("Client socket initialization is OK\n");

		// заполнение информации о сервере

		struct sockaddr_in servInfo;

		ZeroMemory(&servInfo, sizeof(servInfo));

		servInfo.sin_family = AF_INET;
		servInfo.sin_addr = ip_to_num;
		servInfo.sin_port = htons(SERVER_PORT_NUM);

		erStat = connect(ClientSock, (struct sockaddr*)&servInfo, sizeof(servInfo)); // попытка коннекта 

		if (erStat != 0) { // обработка ошибки 
			printf("Connection to Server is FAILED. Error! \n");
			WSAGetLastError();
			closesocket(ClientSock);
			WSACleanup();
			return 1;
		}
		else
			printf("Connection established SUCCESSFULLY. Ready to send a message to Server\n");

		char requestBuffer[100]; // строка дл€ хранени€ запроса

		char responseBuffer[100];

		printf("Enter query: ");
		fgets(requestBuffer, 100, stdin); // ввод строки с клавиатуры 

		size_t len = strcspn(requestBuffer, "\n");
		if (len < sizeof(requestBuffer)) {
			requestBuffer[len] = '\0';
		}

		erStat = send(ClientSock, requestBuffer, strlen(requestBuffer), 0); // отправка запроса 

		if (erStat == SOCKET_ERROR) { // обработка ошибок 
			printf("Error #%d\n", WSAGetLastError());
		}
		else {
			printf("Successfully!\n"); // успех
		}

		// ѕолучение и вывод результата от сервера
		erStat = recv(ClientSock, responseBuffer, sizeof(responseBuffer) - 1, 0);
		if (erStat > 0) {
			responseBuffer[erStat] = '\0';
			printf("Server answer: %s\n", responseBuffer);
		}
		else if (erStat == 0) {
			printf("Connection closed by server\n");
		}
		else {
			printf("Error #%d\n", WSAGetLastError());
		}

		closesocket(ClientSock);
		WSACleanup();
	}

	//getchar();

	return 0;
}