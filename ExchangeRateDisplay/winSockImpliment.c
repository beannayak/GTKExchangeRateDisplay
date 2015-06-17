#include <winsock.h>
#include <winsock2.h> 
#pragma comment(lib,"ws2_32.lib") //Winsock Library

typedef int socklen_t;

struct addrinfo
{
  int ai_flags;                 /* Input flags.  */
  int ai_family;                /* Protocol family for socket.  */
  int ai_socktype;              /* Socket type.  */
  int ai_protocol;              /* Protocol for socket.  */
  socklen_t ai_addrlen;         /* Length of socket address.  */
  struct sockaddr *ai_addr;     /* Socket address for socket.  */
  char *ai_canonname;           /* Canonical name for service location.  */
  struct addrinfo *ai_next;     /* Pointer to next in list.  */
};
 
char* GetHostNameOrIP (char* sHost)
{
	IN_ADDR inaddr;
	inaddr.S_un.S_addr = inet_addr(sHost);
	
	if( inaddr.S_un.S_addr == INADDR_NONE) //if sHost is name and not IP
	{
		HOSTENT* phostent = gethostbyname( sHost);
		if( phostent == 0)
			return 0;

		if( sizeof(inaddr) != phostent->h_length)
			return NULL; // error something wrong,

		inaddr.S_un.S_addr = *((unsigned long*) phostent->h_addr);

		return strdup( inet_ntoa(inaddr));
	}
	else // sHost is probably a valid IP
	{
		HOSTENT* phostent = gethostbyaddr( (const char*)&inaddr,sizeof(IN_ADDR), AF_INET);
		if( phostent == NULL)
			return NULL;
		return strdup(phostent->h_name);
	}

	return NULL;
}

SOCKET open_socket(char *host,char *port) {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;


    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
     
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
  
    int portNum = atoi(port);
    server.sin_addr.s_addr = inet_addr(GetHostNameOrIP(host));
    server.sin_family = AF_INET;
    server.sin_port = htons (portNum);
 
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    return s;
}

int say(int socket_c, char *msg) {
	int result = send(socket_c, msg, strlen(msg), 0);
	if (result == -1)
		printf("Error talking to server - %s", strerror(errno));
	return result;
}
