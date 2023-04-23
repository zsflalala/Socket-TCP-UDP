#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#define BufLen 1024
#define port 1234

int main(){
    // 初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // 创建套接字
    SOCKET clienSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    // 准备通信地址
    struct sockaddr_in sockAddr;
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(port);

    // 连接服务器
    connect(clienSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    printf("you have connected the server!\n");
    
    // 收发数据
    char SendBuf[BufLen];        // 发送数据缓冲区
    char RecvBuf[BufLen];        // 接受数据缓冲区
    while(true){
        // 发送数据
        printf("client:");
        scanf("%s",SendBuf);
        send(clienSock, SendBuf, BufLen, 0);
        if(strcmp(SendBuf,"exit") == 0)
        {
        	break;
		}
	
        // 接收数据
        ZeroMemory(RecvBuf, BufLen); // 缓冲区清零
        recv(clienSock, SendBuf, BufLen, 0);
        printf("server:%s\n",SendBuf);
    }
    printf("\nExit successfully! Bye!\n");

    //关闭套接字
    closesocket(clienSock);

    //终止使用 DLL
    WSACleanup();

    system("pause");
    return 0;
}
