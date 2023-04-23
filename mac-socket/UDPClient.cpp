#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
 
#define BUFFER_SIZE 1024
 
int main()
{
    //创建一个套接字，并检测是否创建成功
    int sockCli = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockCli == -1){
        perror("socket");
    }
    struct sockaddr_in addrSer;  //创建一个记录地址信息的结构体
    addrSer.sin_family = AF_INET;    //使用AF_INET协议族
    addrSer.sin_port = htons(5050);     //设置地址结构体中的端口号
    addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");  //设置通信ip
    socklen_t addrlen = sizeof(struct sockaddr);
 
 
    char sendbuf[256];    //申请一个发送数据缓存区
    char recvbuf[256];    //申请一个接收数据缓存区
 
    while(1){
        //向客户端发送数据
        printf("Cli:>");
        scanf("%s",sendbuf);
        sendto(sockCli, sendbuf, strlen(sendbuf)+1, 0, (struct sockaddr*)&addrSer, addrlen);
        //接收来自客户端的数据
        recvfrom(sockCli, recvbuf, BUFFER_SIZE, 0, (struct sockaddr*)&addrSer, &addrlen);
        printf("Ser:>%s\n", recvbuf);
 
    }
 
    return 0;
}