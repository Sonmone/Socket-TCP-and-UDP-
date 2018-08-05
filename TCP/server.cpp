
#include <WINSOCK2.H>   
#include <stdio.h>     
                    
#define PORT           5150    
#define MSGSIZE        1024    
#pragma comment(lib, "ws2_32.lib")      

DWORD WINAPI SendRecvThread(LPVOID lparam); 
                   
int main()      
{      
    WSADATA wsaData;      
    SOCKET sListen;      
    SOCKET sClient;      
    SOCKADDR_IN local;      
    SOCKADDR_IN client;      
    
    int iaddrSize = sizeof(SOCKADDR_IN);      
    WSAStartup(0x0202, &wsaData);      
                   
    sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);      
                   
    local.sin_family = AF_INET;      
    local.sin_port = htons(PORT);      
    local.sin_addr.s_addr = htonl(INADDR_ANY);      
    bind(sListen, (struct sockaddr *) &local, sizeof(SOCKADDR_IN));      
                   
    listen(sListen, 5);      
                   
   
    while (1)
	{   
		sClient = accept(sListen, (struct sockaddr *) &client, &iaddrSize);      
              
       
		if (sClient == INVALID_SOCKET)
			printf("accept failed: %d\n", WSAGetLastError()); 
		else
            printf("Accepted client:%s  port is %d\n", inet_ntoa(client.sin_addr),ntohs(client.sin_port));

		DWORD   dwThreadId;  
        HANDLE  h; 
		h=CreateThread(NULL,NULL,SendRecvThread,(LPVOID)sClient,0,&dwThreadId);    //dwThreadId是线程号。。
        if(h == NULL)    
        {    
            printf("CreatThread AnswerThread() failed\n");    
        }    
        else    
        {    
            printf("CreateThread OK\n ThreadId is %d\n",dwThreadId);    
        }    
		
    }  
	


    return 0; 
	
  }  




DWORD WINAPI SendRecvThread(LPVOID lparam)
{    
    SOCKET ClientSocket=(SOCKET)(LPVOID)lparam;   
    
    char RecvMessage[MSGSIZE]; 
	char sendbuf1 [MSGSIZE];
	strcpy(sendbuf1,"The message is received !\n") ;
    char sendbuf2 [MSGSIZE] ;
	strcpy(sendbuf2,"已达最大传输数据,请重传\n") ;
    int ret;     //成功接收字节的个数  
	int sum = 0;   // 成功接收字节的总数

    while(1)
	{
        ret = recv(ClientSocket, RecvMessage, MSGSIZE, 0); 
      	sum = sum + ret;
        RecvMessage[ret] = '\0';      
        printf("Received [%d bytes] : Thread[%d] says '%s'\n",ret,GetCurrentThreadId(),RecvMessage); 
	    if (sum >= 20)
			break;
	    send(ClientSocket,sendbuf1,sizeof(sendbuf1),0);
	}


    send(ClientSocket,sendbuf2,sizeof(sendbuf2),0);  
	closesocket(ClientSocket);      
	printf("线程%d已停止\n",GetCurrentThreadId());
	return 0;
}













