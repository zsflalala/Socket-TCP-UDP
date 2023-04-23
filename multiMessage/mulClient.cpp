#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#define BufLen 1024
#define port 1234

int main(){
    // ��ʼ��DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // �����׽���
    SOCKET clienSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    // ׼��ͨ�ŵ�ַ
    struct sockaddr_in sockAddr;
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(port);

    // ���ӷ�����
    connect(clienSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    printf("you have connected the server!\n");
    
    // �շ�����
    char SendBuf[BufLen];        // �������ݻ�����
    char RecvBuf[BufLen];        // �������ݻ�����
    while(true){
        // ��������
        printf("client:");
        scanf("%s",SendBuf);
        send(clienSock, SendBuf, BufLen, 0);
        if(strcmp(SendBuf,"exit") == 0)
        {
        	break;
		}
	
        // ��������
        ZeroMemory(RecvBuf, BufLen); // ����������
        recv(clienSock, SendBuf, BufLen, 0);
        printf("server:%s\n",SendBuf);
    }
    printf("\nExit successfully! Bye!\n");

    //�ر��׽���
    closesocket(clienSock);

    //��ֹʹ�� DLL
    WSACleanup();

    system("pause");
    return 0;
}
