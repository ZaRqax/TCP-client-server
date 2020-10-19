#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mutex>
#include <string.h>



using namespace std;


void client();
void server();

int checksum(string s);
const char * str_to_c(string s);
string cpp_to_c(char * str){
        return string(str);
}

//this PC - 10.0.1.132
//another PC - 10.0.1.139 

int main()
{

    cout <<"Starting Programm..\n";
    thread serv_thr(server);
    serv_thr.join();
     
	// thread thread_of_server(server);

	 //thread_of_server.join();

return 0;
}
const char * str_to_c(string s){
    const char  * c_str = s.c_str();
    return c_str;
}

void server(){

int sock, listener,temp;
    char buff[1024]; unsigned int sz;
    struct sockaddr_in addr;
    listener = socket(AF_INET, SOCK_STREAM, 0);
    int reusee = 1;
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (const char*)&reusee, sizeof(reusee)) < 0)
    perror("setsockopt(SO_REUSEADDR) failed");
    #ifdef SO_REUSEPORT
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEPORT, (const char*)&reusee, sizeof(reusee)) < 0)
    perror("setsockopt(SO_REUSEPORT) failed");
    #endif
    if (listener < 0)
    {
        perror("socket");
        exit(1);
    }
   // printf("%s\n", "Binding server \n");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);// от хоста  в сеть 
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");//inet_addr("10.0.1.132");//htonl(INADDR_ANY);    //htonl(INADDR_ANY);// unigned long 
 //   printf("%s\n", "bind server" );
    if (bind(listener, (struct sockaddr *) &addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }
   else{
       printf("%s\n", "bind is successfull " );
   }
   printf("%s\n", "start listener\n" );
    if (listen(listener, 1) == -1 ){//Функция устанавливает сокет в режим прослушивания ,указываем число установленых соединений для данного совекта
        perror(" listener");
      //  close(listener);
        exit(2);
    }
     sock = 0;
     string s;
     cout <<"Желаете установить соединение ?(yes/no)"<<endl;
     cin >> s;
     if (s == "yes") {

     printf("%s\n", "start.. \n" );
     sz = sizeof(&addr);
    
     thread thread_of_client(client);
     sock = accept(listener, (struct sockaddr *) &addr, &sz);  //принятие соеденения
          printf("%s", "Дескриптор сокета: ");
      if (sock < 1){
            perror("socket");
            exit(1);
            temp = 0;
         } 
        int reuse = 1;
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");
        #ifdef SO_REUSEPORT
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse, sizeof(reuse)) < 0)
        perror("setsockopt(SO_REUSEPORT) failed");
        #endif
         printf("%s\n", "stop \n" );

        printf("%s", "Дескриптор сокета: ");
        printf("%d\n", sock );
        //char check[];
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
     thread_of_client.join();
     
}
       close(listener);
  
}	
void client(){
   // global.lock();
   // global.lock();
    printf("%s\n","Thread   were launched...");
	int sock1; //char msg[];
	int reuse = 1;
	//thread th(server);
	//sleep(4);
    struct sockaddr_in addr1;

    sock1 = socket(AF_INET, SOCK_STREAM, 0);
    if (sock1 < 0)
    {
        perror("socket");
        exit(1);
    }
    printf("%s\n", "bind client" );
    addr1.sin_family = AF_INET; 
    addr1.sin_port = htons(3425); // (Host TO Network Short)
    addr1.sin_addr.s_addr = inet_addr("127.0.0.1");//htonl(INADDR_LOOPBACK); // inet_addr("10.0.1.139");// htonl(INADDR_LOOPBACK); //inet_addr("10.0.1.190"); // Host TO Network Long //inet_addr
    printf("%s\n", "connect client" );
    if (connect(sock1, (struct sockaddr *)&addr1, sizeof(addr1)) < 0)
    {
        perror("connect");
    }

    // thread start_server(server);
    

	if (setsockopt(sock1, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0)
	perror("setsockopt(SO_REUSEADDR) failed");
	#ifdef SO_REUSEPORT
	if (setsockopt(sock1, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse, sizeof(reuse)) < 0)
	
	perror("setsockopt(SO_REUSEPORT) failed");
	#endif
 	printf("%s\n", "client connected" );
    	
  //    global.unlock();
    string msga;
    while(1)
    {
        cin >>  msga; 
        msga += "/" + to_string(checksum(msga));
        send(sock1,str_to_c(msga),sizeof(msga),0);
   // scanf("%s",msg);
   // send(sock1,msg,sizeof(msg),0);
    if(msga== "break"){break;}
    }

	
    close(sock1);
        //start_server.join();

}
int checksum(string s ){
    int sum=0;
    for (int i = 0; i < s.length(); i++){
        sum +=static_cast<int>(s.at(i));
    }
    return sum;
    }