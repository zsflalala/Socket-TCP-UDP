//客户端
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
    SOCKET ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // 客户端套接字由操作系统分配端口
    if (INVALID_SOCKET == ClientSocket)                             // INVALID_SOCKET 无效套接字
    {
        closesocket(ClientSocket);
        WSACleanup();
        return false;
    }

    // 3 准备通信地址
    sockaddr_in ServerAddr; // 服务器地址
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(1234);
    ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int ServerAddr_len = sizeof(ServerAddr);

    // 4 发送数据 (sendto)

    char SendBuf[BufLen]; // 发送数据缓冲区

    cout << "请输入小写字符串:" << endl;
    cin >> SendBuf;
    cout << "准备发送数据报给服务器..." << endl;

    if (SOCKET_ERROR == sendto(ClientSocket, SendBuf, BufLen, 0, (SOCKADDR *)&ServerAddr, ServerAddr_len)) // SOCKET_ERROR = -1
    {
        closesocket(ClientSocket);
        WSACleanup();
        return false;
    }
    cout << "客户端发送消息成功!" << endl
         << endl;

    // 5 接收数据(recvfrom)

    char RecvBuf[BufLen];        // 接受数据缓冲区
    ZeroMemory(RecvBuf, BufLen); // 缓冲区清零

    cout << "准备接收来自服务器的数据报..." << endl;
    if (SOCKET_ERROR == recvfrom(ClientSocket, RecvBuf, BufLen, 0, (SOCKADDR *)&ServerAddr, &ServerAddr_len)) // SOCKET_ERROR = -1
    {
        closesocket(ClientSocket);
        WSACleanup();
        return false;
    }
    cout << "客户端接收消息成功!" << endl
         << endl;
    cout << "服务器消息为:" << endl;
    cout << RecvBuf << endl
         << endl;

    // 6 准备退出

    cout << "准备退出..." << endl;
    closesocket(ClientSocket);
    WSACleanup();
    system("pause");
    return 0;
}