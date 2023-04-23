//�ͻ���
#include <WINSOCK2.H>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#define port 1234   // �˿ں�
#define BufLen 1024 // ��������С
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
    SOCKET ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == ClientSocket)
    {
        closesocket(ClientSocket);
        WSACleanup();
        return false;
    }

    // 3 ׼��ͨ�ŵ�ַ
    sockaddr_in ServerAddr; // ��������ַ
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(port);
    ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 4 ���ӷ����� (connect)

    cout << "׼�����ӷ�����..." << endl;
    if (SOCKET_ERROR == connect(ClientSocket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr)))
    {
        closesocket(ClientSocket);
        WSACleanup();
        return false;
    }
    cout << "���ӳɹ�!" << endl
         << endl;

    // 5 �������� (send)
    char SendBuf[BufLen]; // �������ݻ�����

    cout << "������Сд�ַ���:" << endl;
    cin >> SendBuf;
    cout << "׼���������ݱ���������..." << endl;

    if (SOCKET_ERROR == send(ClientSocket, SendBuf, BufLen, 0))
    {
        closesocket(ClientSocket);
        WSACleanup();
        return false;
    }
    cout << "�ͻ��˷�����Ϣ�ɹ�!" << endl
         << endl;

    // 6 �������� (recv)

    char RecvBuf[BufLen];        // �������ݻ�����
    ZeroMemory(RecvBuf, BufLen); // ����������

    cout << "׼���������Է����������ݱ�..." << endl;
    if (SOCKET_ERROR == recv(ClientSocket, RecvBuf, BufLen, 0))
    {
        closesocket(ClientSocket);
        WSACleanup();
        return false;
    }
    cout << "�ͻ��˽�����Ϣ�ɹ�!" << endl
         << endl;
    cout << "��������ϢΪ:" << endl;
    cout << RecvBuf << endl
         << endl;

    // 7 ׼���˳�

    cout << "׼���˳�..." << endl;
    closesocket(ClientSocket);
    WSACleanup();
    system("pause");
    return 0;
}
