
#include <WINSOCK2.H>   
#include <stdio.h>  

#define SERVER_ADDRESS "127.0.0.1"                     //服务器端IP地址      
#define PORT           5150                           //服务器的端口号      
#define MSGSIZE        1024                           //收发缓冲区的大小      
#pragma comment(lib, "ws2_32.lib")                    // 显示套接字链接库  
   
int main()      
{      
    WSADATA wsaData;       
    SOCKET sClient;      
    SOCKADDR_IN server;   
	
    //收发缓冲区      
    char SendMessage[MSGSIZE]; 
	char ReceiveMessage[MSGSIZE];

       
    int ret;                           //成功接收字节的个数   
	int nResult;                       //函数返回值，查看调用是否成功
                   
        
    WSAStartup(0x0202, &wsaData);       // Initialize Windows socket library  
                   
    // 创建客户端套节字      
    sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INET指明使用TCP/IP协议族；      
                                                         //SOCK_STREAM, IPPROTO_TCP具体指明使用TCP协议   
	
    // 指明远程服务器的地址信息(端口号、IP地址等)      
    memset(&server, 0, sizeof(SOCKADDR_IN)); //先将保存地址的server置为全0      
    server.sin_family = PF_INET; //声明地址格式是TCP/IP地址格式      
    server.sin_port = htons(PORT); //指明连接服务器的端口号，htons()用于 converts values between the host and network byte order      
    server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS); //指明连接服务器的IP地址      
                                                        //结构SOCKADDR_IN的sin_addr字段用于保存IP地址，sin_addr字段也是一个结构体，sin_addr.s_addr用于最终保存IP地址      
                                                        //inet_addr()用于将 形如的"127.0.0.1"字符串转换为IP地址格式      
    //连到刚才指明的服务器上      
    nResult = connect(sClient, ( sockaddr *) &server, sizeof(SOCKADDR_IN)); //连接后可以用sClient来使用这个连接     

    if(nResult==SOCKET_ERROR)  
	{  
          printf("connect failed with error: %d\n",WSAGetLastError());  
    }  
    else  
    {  
       printf("Connection is ok\n");  
    }  
    
	while (1)
	{    
	    printf("Send:");      
        gets(SendMessage);  
          
        send(sClient, SendMessage, strlen(SendMessage), 0); //sClient指明用哪个连接发送； SendMessage指明待发送数据的保存地址 ；strlen(SendMessage)指明数据长度      
	    ret = recv(sClient, ReceiveMessage, MSGSIZE, 0);                                                                   //server保存了远程服务器的地址信息      
        printf ("%s",ReceiveMessage);
		if(strcmp (ReceiveMessage,"已达最大传输数据,请重传\n") == 0)
			break;
	}      

    Sleep(3000);           
    // 释放连接和进行结束工作      
    closesocket(sClient);      
    WSACleanup();  
    return 0;      
}  