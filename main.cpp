#pragma warning(suppress : 4996)
#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Interface.h"


// ќпределимс€ с номером порта и другими константами.
#define PORT    5555
#define BUFLEN  512

// ƒве вспомогательные функции дл€ чтени€/записи (см. ниже)
int   readFromClient(int fd, char* buf);
void  writeToClient(int fd, char* buf);
vector<int> q;
auto* cc = new Controller(true);
int  main(void)
{
	int     i, err, opt = 1;
	int     sock, new_sock;
	fd_set  active_set, read_set;
	struct  sockaddr_in  addr;
	struct  sockaddr_in  client;
	char    buf[BUFLEN];
	socklen_t  size;
	stringstream ss;
	int er = 0;
	// »нициализаци€ windows sockets
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("WSAStartup failed\n");
		return 1;
	}

	// —оздаем TCP сокет дл€ приема запросов на соединение
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("Server: cannot create socket");
		exit(EXIT_FAILURE);
	}
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

	// «аполн€ем адресную структуру и
	// св€зываем сокет с любым адресом
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	err = bind(sock, (struct sockaddr*) & addr, sizeof(addr));
	if (err < 0) {
		perror("Server: cannot bind socket");
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	// —оздаем очередь на 3 вход€щих запроса соединени€
	err = listen(sock, 3);
	if (err < 0) {
		perror("Server: listen queue failure");
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	// ѕодготавливаем множества дескрипторов каналов ввода-вывода.
	// ƒл€ простоты не вычисл€ем максимальное значение дескриптора,
	// а далее будем провер€ть все дескрипторы вплоть до максимально
	// возможного значени€ FD_SETSIZE.
	FD_ZERO(&active_set);
	FD_SET(sock, &active_set);

	// ќсновной бесконечный цикл проверки состо€ни€ сокетов
	while (1) {
		// ѕроверим, не по€вились ли данные в каком-либо сокете.
		// ¬ нашем варианте ждем до фактического по€влени€ данных.
		read_set = active_set;
		if (select(FD_SETSIZE, &read_set, NULL, NULL, NULL) < 0) {
			perror("Server: select  failure");
			WSACleanup();
			exit(EXIT_FAILURE);
		}
		// fd_set в windows устроена немного иначе - как массив дескрипторов
		// ƒанные по€вились. ѕроверим в каком сокете.
		for (int j = 0; j < read_set.fd_count; j++) {
			i = read_set.fd_array[j];
			if (FD_ISSET(i, &read_set)) {
				if (i == sock) {
					// пришел запрос на новое соединение
					size = sizeof(client);
					new_sock = accept(sock, (struct sockaddr*) & client, &size);
					if (new_sock < 0) {
						perror("accept");
						WSACleanup();
						exit(EXIT_FAILURE);
					}
					fprintf(stdout, "Server: connect from host %s, port %hu.\n",
						inet_ntoa(client.sin_addr),
						ntohs(client.sin_port));
					FD_SET(new_sock, &active_set);
				}
				else {
					// пришли данные в уже существующем соединени
					err = readFromClient(i, buf);
					if (err < 0) {
						// ошибка или конец данных
						closesocket(i);
						FD_CLR(i, &active_set);
					}
					else {
						// а если это команда закончить работу?
						if (strstr(buf, "stop")) {
							closesocket(i);
							FD_CLR(i, &active_set);
						}
						else {
							// данные прочитаны нормально
							writeToClient(i, buf);
						}
					}
				}
			}
		}
	}
	WSACleanup();
}

int  readFromClient(int fd, char* buf)
{
	int  nbytes;
		nbytes = recv(fd, buf, BUFLEN, 0);
		q.push_back(atoi(buf));
		cout << "\n";
		cout << "\n";
		cout << (q[q.size() - 1]);
		cout << "\n";
		cout << "\n";
		if (q[q.size() - 1] == 1000)
		{
			if (q[0] == 1)
			{
				cc->buff.generate_cloud(q[1]/100, q[2] / 100, q[3] , q[4] , q[5] );
			}
			else if (q[0] == 2)
			{
				cc->buff.gen(q[1]);
			}
			else if (q[0] == 3)
			{
				cc->unload();
			}
			else if (q[0] == 4)
			{			
			}
			else if (q[0] == 5)
			{
				cc->Kmc(q[1], q[2]);
			}
			else if (q[0] == 6)
			{
				cc->FOREL(q[1] / 100, q[2]);
			}
			else if (q[0] == 7)
			{
				cc->Km(q[1]);
			}
			else if (q[0] == 8)
			{
				cc->Em("Em.txt",q[1]);
			}
			else if (q[0] == 9)
			{
				cc->DBSCAN(q[1] *0.01, q[2]);
			}
			else if (q[0] == 10)
			{
				cc->IER();
			}
			else if (q[0] == 11)
			{
				cc->inter(0,0);
			}
			else if (q[0] == 12)
			{
				cc->tree("tree.txt",30);
			}
			q.clear();
		}
	if (nbytes < 0) {
		// ошибка чтени€
		perror("Server: read failure");
		return -1;
	}
	else if (nbytes == 0) {
		// больше нет данных
		return -1;
	}
	else {
		// есть данные
		//fprintf(stdout, "Server got message: %s\n", buf);
		return 0;
	}
}
void  writeToClient(int fd, char* buf)
{
	int  nbytes;
	unsigned char* s;

	for (s = (unsigned char*)buf; *s; s++) *s = toupper(*s);
	nbytes = send(fd, buf, strlen(buf) + 1, 0);
	fprintf(stdout, "Write back: %s\nnbytes=%d\n", buf, nbytes);

	if (nbytes < 0) {
		perror("Server: write failure");
	}
}