#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#define BufLen 1024
#define port 1234

int main()
{
  // ��ʼ��DLL
  WSAData wsadata;
  int iResult = WSAStartup(MAKEWORD(2, 2), &wsadata);
  printf("IP����󳤶�:%hu\n", wsadata.iMaxUdpDg);
  if (iResult != NO_ERROR) //NO_ERRORֵΪ0
  {
    printf("WSAStartupfailedwitherror:%ld\n", iResult);
    return 1;
  }
  
  // �����׽��� (socket)
  SOCKET servSock = socket(PF_INET, SOCK_STREAM, 0);
  if (servSock == INVALID_SOCKET)
  {
    printf("socketfailedwitherror:%d\n", WSAGetLastError());
    //��ֹdll��ʹ��
    WSACleanup();
    return 1;
  }

  // ׼��ͨ�ŵ�ַ
  struct sockaddr_in saddr;
  memset(&saddr, 0, sizeof(saddr));
  saddr.sin_family = AF_INET;              //IPV4Э��
  saddr.sin_port = htons(1234);            //�˿�  host to network short  �����ֽ���ת�����ֽ��� ���������Ϊshort
  saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // �󶨵�ַ��socket��bind��
  if (bind(servSock, (sockaddr *)&saddr, sizeof(saddr)) == SOCKET_ERROR)
  {
    printf("bindfailedwitherror:%ld\n", WSAGetLastError());
    closesocket(servSock);
    WSACleanup();
    return 1;
  }

  // ���� (listen)
  if (listen(servSock, 20) == SOCKET_ERROR) /*�������������Ϊ20  �����������ʱ���Ͳ��ٽ����µ����� ���ڿͻ��˻��յ� WSAECONNREFUSED ����*/
  {
    printf("bindfailedwitherror:%ld\n", WSAGetLastError());
    closesocket(servSock);
    WSACleanup();
    return 1;
  };

  // �ȴ��ͻ������� (accept)
  int nSize = sizeof(SOCKADDR);
  struct sockaddr_in clntAddr; //���ڽ��ܿͻ��˵�ַ��Ϣ
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

  // �շ����� (recv & send)
  char RecvBuf[BufLen];
  char SendBuf[BufLen];
  while(true)
  {
      // �������� (recv)
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

      // �������� (send)
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

  // �˳� 
  closesocket(clienSock);
  closesocket(servSock);
  WSACleanup();
  system("pause");
  return 0;
}
