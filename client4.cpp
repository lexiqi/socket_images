#include <stdio.h>
 #include <errno.h>
 #include <string.h>
 #include <netdb.h>
 #include <sys/types.h>
 #include <netinet/in.h>
 #include <sys/socket.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <arpa/inet.h>
 #include <netdb.h>
#include<fstream>
using namespace std;

void error(const char *);
std::ifstream::pos_type filesize(const char* filename);

 #define MAXLINE 4096

void sendData(int sockfd,char *path)
{
     FILE *fq;
     int len;
     int size;
     
     if( ( fq = fopen(path,"rb") ) == NULL ){
         printf("File open.\n");
         close(sockfd);
         exit(1);
     }
     size=filesize(path);
     // printf("%d\n",sizeof(size));
     fseek(fq,0,SEEK_SET);
     write(sockfd,&size,sizeof(size));
     char  buffer[size];
     bzero(buffer,sizeof(buffer));
     while(!feof(fq)){
         len = fread(buffer, 1, sizeof(buffer), fq);
         if(len != write(sockfd, buffer, len)){
             printf("write.\n");
             break;
         }
     }
     fclose(fq);
         printf("send success!\n");
         //printf("%d\n",len);

}
 
 int main(int argc, char** argv){
     int   sockfd;
     struct sockaddr_in  servaddr;
   
 
    if( argc != 2){
         printf("usage: ./client <ipaddress>\n");
         return 0;
     }
 
     if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
         printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
         return 0;
     }
 
     memset(&servaddr, 0, sizeof(servaddr));
     servaddr.sin_family = AF_INET;
     servaddr.sin_port = htons(7676);
     if( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
         printf("inet_pton error for %s\n",argv[1]);
         return 0;
     }
 
     if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
         printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
         return 0;
     }
     char path1[]="./test1.jpg";
     sendData(sockfd,path1);
     sleep(1);
     char path2[]="./test2.jpg";
     sendData(sockfd,path2);


      
     close(sockfd);

 
     return 0;
 }
std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}
