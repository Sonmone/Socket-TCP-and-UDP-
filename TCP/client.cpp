
#include <WINSOCK2.H>   
#include <stdio.h>  

#define SERVER_ADDRESS "127.0.0.1"                     //��������IP��ַ      
#define PORT           5150                           //�������Ķ˿ں�      
#define MSGSIZE        1024                           //�շ��������Ĵ�С      
#pragma comment(lib, "ws2_32.lib")                    // ��ʾ�׽������ӿ�  
   
int main()      
{      
    WSADATA wsaData;       
    SOCKET sClient;      
    SOCKADDR_IN server;   
	
    //�շ�������      
    char SendMessage[MSGSIZE]; 
	char ReceiveMessage[MSGSIZE];

       
    int ret;                           //�ɹ������ֽڵĸ���   
	int nResult;                       //��������ֵ���鿴�����Ƿ�ɹ�
                   
        
    WSAStartup(0x0202, &wsaData);       // Initialize Windows socket library  
                   
    // �����ͻ����׽���      
    sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INETָ��ʹ��TCP/IPЭ���壻      
                                                         //SOCK_STREAM, IPPROTO_TCP����ָ��ʹ��TCPЭ��   
	
    // ָ��Զ�̷������ĵ�ַ��Ϣ(�˿ںš�IP��ַ��)      
    memset(&server, 0, sizeof(SOCKADDR_IN)); //�Ƚ������ַ��server��Ϊȫ0      
    server.sin_family = PF_INET; //������ַ��ʽ��TCP/IP��ַ��ʽ      
    server.sin_port = htons(PORT); //ָ�����ӷ������Ķ˿ںţ�htons()���� converts values between the host and network byte order      
    server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS); //ָ�����ӷ�������IP��ַ      
                                                        //�ṹSOCKADDR_IN��sin_addr�ֶ����ڱ���IP��ַ��sin_addr�ֶ�Ҳ��һ���ṹ�壬sin_addr.s_addr�������ձ���IP��ַ      
                                                        //inet_addr()���ڽ� �����"127.0.0.1"�ַ���ת��ΪIP��ַ��ʽ      
    //�����ղ�ָ���ķ�������      
    nResult = connect(sClient, ( sockaddr *) &server, sizeof(SOCKADDR_IN)); //���Ӻ������sClient��ʹ���������     

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
          
        send(sClient, SendMessage, strlen(SendMessage), 0); //sClientָ�����ĸ����ӷ��ͣ� SendMessageָ�����������ݵı����ַ ��strlen(SendMessage)ָ�����ݳ���      
	    ret = recv(sClient, ReceiveMessage, MSGSIZE, 0);                                                                   //server������Զ�̷������ĵ�ַ��Ϣ      
        printf ("%s",ReceiveMessage);
		if(strcmp (ReceiveMessage,"�Ѵ����������,���ش�\n") == 0)
			break;
	}      

    Sleep(3000);           
    // �ͷ����Ӻͽ��н�������      
    closesocket(sClient);      
    WSACleanup();  
    return 0;      
}  