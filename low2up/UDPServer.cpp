//服务器
#include <WINSOCK2.H> //socket 头文件
#include <iostream>
#pragma comment(lib, "WS2_32.lib") // 加环境配置 -lWS2_32
#define port 4000                  // 端口号
#define BufLen 1024                // 缓冲区大小
using namespace std;
int main()
{
    WSADATA wsaData;

    // 1 启用并初始化windows socket(WSAStartup)
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)) //成功返回0
    {
        return false;
    }

    // 2 创建套接字(socket)
    SOCKET ServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // 服务器套接字
    if (INVALID_SOCKET == ServerSocket)                             // INVALID_SOCKET 无效套接字
    {
        closesocket(ServerSocket);
        WSACleanup();
        return false;
    }

    // 3 准备通信地址
    sockaddr_in ServerAddr; // 服务器地址

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(1234);
    ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int ServerAddr_len = sizeof(ServerAddr);

    // 4 绑定地址与socket（bind）
    if (SOCKET_ERROR == bind(ServerSocket, (SOCKADDR *)&ServerAddr, ServerAddr_len))
    {
        closesocket(ServerSocket);
        WSACleanup();
        return false;
    }

    // 5 接收数据(recvfrom)

    char RecvBuf[BufLen];
    ZeroMemory(RecvBuf, BufLen);

    sockaddr_in ClientAddr;
    int ClientAddr_len = sizeof(ClientAddr);

    cout << "准备接收来自客户端数据..." << endl;

    if (SOCKET_ERROR == recvfrom(ServerSocket, RecvBuf, BufLen, 0, (SOCKADDR *)&ClientAddr, &ClientAddr_len))
    {
        closesocket(ServerSocket);
        WSACleanup();
        return false;
    }
    cout << "服务器接收消息成功!" << endl
         << endl;

    // 6 发送数据(sendto)

    char SendBuf[BufLen];
    char *p = RecvBuf, *q = SendBuf;
    while (*p != '\0')
        *q++ = *p++ - 'a' + 'A';

    cout << "准备发送数据报给客户端..." << endl;
    if (SOCKET_ERROR == sendto(ServerSocket, SendBuf, BufLen, 0, (SOCKADDR *)&ClientAddr, ClientAddr_len))
    {
        closesocket(ServerSocket);
        WSACleanup();
        return false;
    }
    cout << "服务器发送消息成功!" << endl
         << endl;

    // 7 准备退出
    cout << "准备退出..." << endl;
    closesocket(ServerSocket);
    WSACleanup();
    system("pause");
    return 0;
}