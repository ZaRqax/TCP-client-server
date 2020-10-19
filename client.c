#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    int sock; char msg[1024];
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket");
        exit(1);
    }
    addr.sin_family = AF_INET; 
    addr.sin_port = htons(3425); // (Host TO Network Short)
    addr.sin_addr.s_addr =inet_addr("10.0.10.253"); // Host TO Network Long //inet_addr

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2); 
    }

   while(1)
   {
   	printf("%s\n","Ваше сообщение: " );
    scanf("%s",msg);
    send(sock,msg,sizeof(msg),0);
    if(msg[0]== '!'){break;
    }
    }
    close(sock);
    return 0;
}
