#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
 #include <arpa/inet.h>

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define BAD_MESSAGE         -13
#define SUCCESS               0
#define CLOSE                -1



int main()
{
    char buff[1024]; unsigned int sz;
    int sock, listener,temp;
    struct sockaddr_in addr;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);// от хоста  в сеть 
    addr.sin_addr.s_addr = inet_addr("10.0.1.132");     //htonl(INADDR_ANY);// unsigned long 
    
    if (bind(listener, (struct sockaddr *) &addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }
    
    if (listen(listener, 1) == -1 ){//Функция устанавливает сокет в режим прослушивания ,указываем число установленых соединений для данного совекта
        perror(" listener");
        close(listener);
        exit(2);
    }
      sock = 0;
      temp =1;
    while(temp)
    {
        
         sz = sizeof(addr);
         sock = accept(listener, (struct sockaddr *) &addr, &sz );  //принятие соединения
         if (sock < 1){
            temp = 0;
         } 
        printf("%s", "Дескриптор сокета: ");
        printf("%d\n", sock );
         
    while (1)
    {
        sz = recv (sock, &buff , 1024 ,0);  
        printf("%s","Принято:  ");
        printf("%s\n", buff);     
        if (buff[0] == '!'){
            break;   
            temp =0;    
        }
       
    }
        close(sock);  
       close(listener);


    }
        
    
    return 0;
}




