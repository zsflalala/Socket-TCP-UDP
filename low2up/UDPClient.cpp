//�ͻ���
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
    SOCKET ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // �ͻ����׽����ɲ���ϵͳ����˿�
    if (INVALID_SOCKET == ClientSocket)                             // INVALID_SOCKET ��Ч�׽���
    {
        closesocket(ClientSocket);
        WSACleanup();
        return false;
    }

    // 3 ׼��ͨ�ŵ�ַ
    sockaddr_in ServerAddr; // ��������ַ
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(1234);
    ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int ServerAddr_len = sizeof(ServerAddr);

    // 4 �������� (sendto)

    char SendBuf[BufLen]; // �������ݻ�����

    cout << "������Сд�ַ���:" << endl;
    cin >> SendBuf;
    cout << "׼���������ݱ���������..." << endl;

    if (SOCKET_ERROR == sendto(ClientSocket, SendBuf, BufLen, 0, (SOCKADDR *)&ServerAddr, ServerAddr_len)) // SOCKET_ERROR = -1
    {
        closesocket(ClientSocket);
        WSACleanup();
        return false;
    }
    cout << "�ͻ��˷�����Ϣ�ɹ�!" << endl
         << endl;

    // 5 ��������(recvfrom)

    char RecvBuf[BufLen];        // �������ݻ�����
    ZeroMemory(RecvBuf, BufLen); // ����������

    cout << "׼���������Է����������ݱ�..." << endl;
    if (SOCKET_ERROR == recvfrom(ClientSocket, RecvBuf, BufLen, 0, (SOCKADDR *)&ServerAddr, &ServerAddr_len)) // SOCKET_ERROR = -1
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

    // 6 ׼���˳�

    cout << "׼���˳�..." << endl;
    closesocket(ClientSocket);
    WSACleanup();
    system("pause");
    return 0;
}