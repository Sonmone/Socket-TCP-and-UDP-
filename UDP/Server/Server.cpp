#include<Winsock2.h>
#include<stdio.h>  
#pragma comment(lib,"ws2_32.lib")
void main() 
 { 
	WORD wVersionRequested;
    WSADATA wsaData;  

   int err; 
   wVersionRequested = MAKEWORD( 1, 1 ); 
   err = WSAStartup( wVersionRequested, &wsaData );

   if ( err != 0 ) 
   {   return;  }  
   
   if ( LOBYTE( wsaData.wVersion ) != 1 ||         HIBYTE( wsaData.wVersion ) != 1 ) 
   {   WSACleanup( );   return;   }   

   SOCKET sockSrv=socket(AF_INET,SOCK_DGRAM,0); 
   SOCKADDR_IN addrSrv;  addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY); 
   addrSrv.sin_family=AF_INET;  addrSrv.sin_port=htons(6000);  
   bind(sockSrv,(sockaddr*)&addrSrv,sizeof(sockaddr)); 
   SOCKADDR_IN addrClient;  int len=sizeof(SOCKADDR);  
   char recvBuf[100]; 
   char sendBuf[100];
   char tempBuf[100];  

   while(1) 
   {   recvfrom(sockSrv,recvBuf,100,0,(sockaddr*)&addrClient,&len); 


       if('q'==recvBuf[0])  
	   {    
		   sendto(sockSrv,"q",strlen("q")+1,0,(sockaddr*)&addrClient,len);    printf("chat end!\n");    break;   
	   }  

       /*s*/printf(/*tempBuf,*/"%s say:%s \n",inet_ntoa(addrClient.sin_addr),recvBuf);   
      // printf("%s\n",tempBuf);   
       printf("please Input:\n"); 
       gets(sendBuf);   //读取一行数据 
       sendto(sockSrv,sendBuf,strlen(sendBuf)+1,0,(sockaddr*)&addrClient,len);  
   }  


   closesocket(sockSrv); 
   WSACleanup(); 
 }