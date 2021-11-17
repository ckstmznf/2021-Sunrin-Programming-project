#pragma once
#include <stdio.h>
#include <conio.h>
// #define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment( lib, "ws2_32.lib")
#include <WinSock2.h>

#define IPADDR "127.0.0.1"

void main() {
	WSADATA wsdata;
	int iRes = WSAStartup( MAKEWORD( 0x02, 0x02 ), &wsdata );
	if ( ERROR_SUCCESS != iRes ) return;

	SOCKET hSocket;
	hSocket = socket( PF_INET, SOCK_STREAM, 0 );
	if ( INVALID_SOCKET == hSocket ) return;
	
	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(IPADDR);
	servAddr.sin_port = htons( 1234 );
	iRes = connect( hSocket, (LPSOCKADDR)&servAddr, sizeof( servAddr ) );
	
	while(1) {
		char cBuff = _getch();
		
		
		printf("%c", cBuff);
		send( hSocket, &cBuff, sizeof(cBuff), 0 );
		
		if ( 0x1b == cBuff ) {
			printf("EXIT\n");
			break;
		}
	}
	
	closesocket( hSocket );
	WSACleanup();
}