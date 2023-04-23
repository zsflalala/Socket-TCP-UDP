#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
 
int main()
{
    //创建一个套接字，并检测是否创建成功
    int sockSer = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockSer == -1)
        perror("socket");
 
    struct sockaddr_in addrSer;  //创建一个记录地址信息的结构体
    addrSer.sin_family = AF_INET;    //使用AF_INET协议族
    addrSer.sin_port = htons(5050);     //设置地址结构体中的端口号
    addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");  //设置通信ip
 
    //将套接字地址与所创建的套接字号联系起来，并检测是否绑定成功
    socklen_t addrlen = sizeof(struct sockaddr);
    int res = bind(sockSer,(struct sockaddr*)&addrSer, addrlen);
    if(res == -1)
        perror("bind");
 
    char sendbuf[256];    //申请一个发送数据缓存区
    char recvbuf[256];    //申请一个接收数据缓存区
    struct sockaddr_in addrCli;
    while(1)
    {
        recvfrom(sockSer,recvbuf,256,0,(struct  sockaddr*)&addrCli, &addrlen);     //从指定地址接收客户端数据
        printf("Cli:>%s\n",recvbuf);
 
        printf("Ser:>");
        scanf("%s",sendbuf);
        sendto(sockSer,sendbuf,strlen(sendbuf)+1,0,(struct sockaddr*)&addrCli, addrlen);    //向客户端发送数据
    }
    return 0;
}