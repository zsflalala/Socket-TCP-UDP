//������
#include <WINSOCK2.H> //socket ͷ�ļ�
#include <iostream>
#pragma comment(lib, "WS2_32.lib") // �ӻ������� -lWS2_32
#define port 4000                  // �˿ں�
#define BufLen 1024                // ��������С
using namespace std;
int main()
{
    WSADATA wsaData;

    // 1 ���ò���ʼ��windows socket(WSAStartup)
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)) //�ɹ�����0
    {
        return false;
    }

    // 2 �����׽���(socket)
    SOCKET ServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // �������׽���
    if (INVALID_SOCKET == ServerSocket)                             // INVALID_SOCKET ��Ч�׽���
    {
        closesocket(ServerSocket);
        WSACleanup();
        return false;
    }

    // 3 ׼��ͨ�ŵ�ַ
    sockaddr_in ServerAddr; // ��������ַ

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(1234);
    ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int ServerAddr_len = sizeof(ServerAddr);

    // 4 �󶨵�ַ��socket��bind��
    if (SOCKET_ERROR == bind(ServerSocket, (SOCKADDR *)&ServerAddr, ServerAddr_len))
    {
        closesocket(ServerSocket);
        WSACleanup();
        return false;
    }

    // 5 ��������(recvfrom)

    char RecvBuf[BufLen];
    ZeroMemory(RecvBuf, BufLen);

    sockaddr_in ClientAddr;
    int ClientAddr_len = sizeof(ClientAddr);

    cout << "׼���������Կͻ�������..." << endl;

    if (SOCKET_ERROR == recvfrom(ServerSocket, RecvBuf, BufLen, 0, (SOCKADDR *)&ClientAddr, &ClientAddr_len))
    {
        closesocket(ServerSocket);
        WSACleanup();
        return false;
    }
    cout << "������������Ϣ�ɹ�!" << endl
         << endl;

    // 6 ��������(sendto)

    char SendBuf[BufLen];
    char *p = RecvBuf, *q = SendBuf;
    while (*p != '\0')
        *q++ = *p++ - 'a' + 'A';

    cout << "׼���������ݱ����ͻ���..." << endl;
    if (SOCKET_ERROR == sendto(ServerSocket, SendBuf, BufLen, 0, (SOCKADDR *)&ClientAddr, ClientAddr_len))
    {
        closesocket(ServerSocket);
        WSACleanup();
        return false;
    }
    cout << "������������Ϣ�ɹ�!" << endl
         << endl;

    // 7 ׼���˳�
    cout << "׼���˳�..." << endl;
    closesocket(ServerSocket);
    WSACleanup();
    system("pause");
    return 0;
}