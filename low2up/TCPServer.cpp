//������
#include <WINSOCK2.H> //socket ͷ�ļ�
#include <iostream>
#pragma comment(lib, "WS2_32.lib") // �ӻ������� -lWS2_32
#define port 4010                  // �˿ں�
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

    SOCKET LinkSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // �������׽���
    if (INVALID_SOCKET == LinkSocket)                             // INVALID_SOCKET ��Ч�׽���
    {
        closesocket(LinkSocket);
        WSACleanup();
        return false;
    }

    // 3 ׼��ͨ�ŵ�ַ
    sockaddr_in ServerAddr; // ��������ַ
    ServerAddr.sin_family = AF_INET;
    // ServerAddr.sin_port = htons(port);
    // ServerAddr.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY ������õ�ַ
    ServerAddr.sin_port = htons(1234);
    ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int ServerAddr_len = sizeof(ServerAddr);

    // 4 �󶨵�ַ��socket��bind��
    if (SOCKET_ERROR == bind(LinkSocket, (SOCKADDR *)&ServerAddr, ServerAddr_len))
    {
        closesocket(LinkSocket);
        WSACleanup();
        return false;
    }

    //5 ���� (listen)
    if (SOCKET_ERROR == listen(LinkSocket, SOMAXCONN))
    {
        closesocket(LinkSocket);
        WSACleanup();
        return false;
    }

    // 6 �ȴ��ͻ������ӣ�accpet��
    sockaddr_in ClientAddr;

    int ClientAddr_len = sizeof(ClientAddr);

    cout << "�ȴ��ͻ���������..." << endl;
    SOCKET ServerSocket = accept(LinkSocket, (SOCKADDR *)&ClientAddr, &ClientAddr_len);
    if (INVALID_SOCKET == ServerSocket)
    {
        closesocket(ServerSocket);
        closesocket(LinkSocket);
        WSACleanup();
        return false;
    }
    cout << "�ͻ������ӳɹ�!" << endl
         << endl;

    // 7 �������� (recv)

    char RecvBuf[BufLen];
    ZeroMemory(RecvBuf, BufLen);

    cout << "׼���������Կͻ�������..." << endl;

    if (SOCKET_ERROR == recv(ServerSocket, RecvBuf, BufLen, 0))
    {
        closesocket(ServerSocket);
        closesocket(LinkSocket);
        WSACleanup();
        return false;
    }
    cout << "������������Ϣ�ɹ�!" << endl
         << endl;

    // 8 �������� (send)

    char SendBuf[BufLen];

    char *p = RecvBuf, *q = SendBuf;
    while (*p != '\0')
        *q++ = *p++ - 'a' + 'A';

    cout << "׼���������ݱ����ͻ���..." << endl;
    if (SOCKET_ERROR == send(ServerSocket, SendBuf, BufLen, 0))
    {
        closesocket(ServerSocket);
        closesocket(LinkSocket);
        WSACleanup();
        return false;
    }
    cout << "������������Ϣ�ɹ�!" << endl
         << endl;

    // 9 ׼���˳�
    cout << "׼���˳�..." << endl;
    closesocket(ServerSocket);
    closesocket(LinkSocket);
    WSACleanup();
    system("pause");
    return 0;
}
