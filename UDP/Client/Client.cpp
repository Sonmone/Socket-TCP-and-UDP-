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

	 SOCKET sockClient=socket(AF_INET,SOCK_DGRAM,0); 
	 SOCKADDR_IN addrClient;  addrClient.sin_addr.S_un.S_addr=inet_addr("127.0.0.1"); 
	 addrClient.sin_family=AF_INET;  addrClient.sin_port=htons(6000);  
	 char recvBuf[100]; 
	 char sendBuf[100]; 
	 char tempBuf[200];  
	 int len=sizeof(SOCKADDR);
	 while(1) 
	 {   printf("please input:\n");  
	     gets(sendBuf); 
         sendto(sockClient,sendBuf,sizeof(sendBuf)+1,0,(sockaddr*)&addrClient,len);  
		 recvfrom(sockClient,recvBuf,sizeof(recvBuf),0,(sockaddr*)&addrClient,&len); 

		 if('q'==recvBuf[0])  
		 {    sendto(sockClient,"q",sizeof("q")+1,0,(sockaddr*)&addrClient,len);    printf("chat end!\n");    break;   }  

		 /*s*/printf(/*tempBuf,*/"%s say:%s\n",inet_ntoa(addrClient.sin_addr),recvBuf);  
		 //printf("%s\n",tempBuf);
	 }   

	 closesocket(sockClient); 
	 WSACleanup(); 
}