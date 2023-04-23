#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#define BufLen 1024
#define port 1234

int main()
{
  // 初始化DLL
  WSAData wsadata;
  int iResult = WSAStartup(MAKEWORD(2, 2), &wsadata);
  printf("IP包最大长度:%hu\n", wsadata.iMaxUdpDg);
  if (iResult != NO_ERROR) //NO_ERROR值为0
  {
    printf("WSAStartupfailedwitherror:%ld\n", iResult);
    return 1;
  }
  
  // 创建套接字 (socket)
  SOCKET servSock = socket(PF_INET, SOCK_STREAM, 0);
  if (servSock == INVALID_SOCKET)
  {
    printf("socketfailedwitherror:%d\n", WSAGetLastError());
    //终止dll的使用
    WSACleanup();
    return 1;
  }

  // 准备通信地址
  struct sockaddr_in saddr;
  memset(&saddr, 0, sizeof(saddr));
  saddr.sin_family = AF_INET;              //IPV4协议
  saddr.sin_port = htons(1234);            //端口  host to network short  主机字节序转网络字节序 传入的类型为short
  saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // 绑定地址与socket（bind）
  if (bind(servSock, (sockaddr *)&saddr, sizeof(saddr)) == SOCKET_ERROR)
  {
    printf("bindfailedwitherror:%ld\n", WSAGetLastError());
    closesocket(servSock);
    WSACleanup();
    return 1;
  }

  // 监听 (listen)
  if (listen(servSock, 20) == SOCKET_ERROR) /*设请求队列上限为20  当请求队列满时，就不再接收新的请求 对于客户端会收到 WSAECONNREFUSED 错误。*/
  {
    printf("bindfailedwitherror:%ld\n", WSAGetLastError());
    closesocket(servSock);
    WSACleanup();
    return 1;
  };

  // 等待客户端连接 (accept)
  int nSize = sizeof(SOCKADDR);
  struct sockaddr_in clntAddr; //用于接受客户端地址信息
  memset(&clntAddr, 0, sizeof(clntAddr));
  printf("Waiting for client to connect...\n");
  SOCKET clienSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
  if (clienSock == INVALID_SOCKET)
  {
    printf("accept failed with error:%ld\n", WSAGetLastError());
    closesocket(servSock);
    WSACleanup();
    return 1;
  }
  else
  {
    printf("client:%s:%hu  have connected;socket=%d\n", inet_ntoa(clntAddr.sin_addr), ntohs(clntAddr.sin_port), clienSock); 

  }  
  printf("Waiting for client to send message...\n");

  // 收发数据 (recv & send)
  char RecvBuf[BufLen];
  char SendBuf[BufLen];
  while(true)
  {
      // 接收数据 (recv)
      ZeroMemory(RecvBuf,BufLen);
      if (SOCKET_ERROR == recv(clienSock, RecvBuf, BufLen, 0))
      {
            closesocket(clienSock);
            closesocket(servSock);
            WSACleanup();
            printf("get recv error");
            system("pause");
            return false;
      }
      printf("client:%s\n",RecvBuf);
      if(strcmp(RecvBuf,"exit") == 0)
      {
        break;
      }

      // 发送数据 (send)
      ZeroMemory(SendBuf,BufLen);
      printf("server:");
      scanf("%s",SendBuf);
      if (SOCKET_ERROR == send(clienSock, SendBuf, BufLen, 0))
      {
        closesocket(clienSock);
        closesocket(servSock);
        WSACleanup();
        printf("get send error");
        system("pause");
        return false;
      }
      
  }
  printf("\nClient have disconnected.\n");

  // 退出 
  closesocket(clienSock);
  closesocket(servSock);
  WSACleanup();
  system("pause");
  return 0;
}
