#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<vector>
#include<arpa/inet.h>
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
/*
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
*/

 //   portno = atoi(argv[2]);
	portno=5000;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname("192.168.1.100");
//	server=127.0.0.1;

string line;

    //if (server == NULL) {
     //   fprintf(stderr,"ERROR, no such host\n");
      //  exit(0);
    //}

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr("192.168.1.100");// AF_INET;
    //bcopy((char *)server->h_addr, 
         //(char *)&serv_addr.sin_addr.s_addr,
         //server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
 //   printf("Please enter the message: ");
    bzero(buffer,256);

//File handling
ifstream myfile("temp2.txt");
	if(myfile.is_open()){
		while(getline(myfile,line)){
			cout<<line<<endl;
			//tab2[i++]=line;
			strncpy(buffer, line.c_str(), sizeof(buffer));
			buffer[sizeof(buffer) - 1] = 0;
			}
		myfile.close();		
		
	}
	else{
		cout<<"\nUnable to open file";
	}

//

//    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);

    n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
int lenght=strlen(buffer);
char temp[100];
cout<<endl<<"hello"<<endl;
string temp_string;
string start_application;
string stop_application;
string cmd_stop="./stopscript.sh ";
int z=0;
string cmd="./programscript.sh ";
	for(int i=0;i<lenght;i++){
		if(buffer[i]==','){
			cout<<endl<<buffer[i+1]<<endl;
			if(buffer[i+1]=='C'){
				i++;
				while(buffer[++i]!='%'){
					temp[z++]=buffer[i];
					//cout<<"this character"<<temp[z];			
					}
				temp[z]='\0';
				start_application=(string)temp;
				bzero(temp,100);	
				z=0;
				start_application+=" ";
				cout<<endl<<"Application sent now is: "<<start_application;
				cmd+=start_application;
				}	
			else if(buffer[i+1]=='D'){
				i++;
				cout<<"Reached here"<<endl;
				while(buffer[++i]!='%'){
					temp[z++]=buffer[i];
					}
				temp[z]='\0';
				stop_application=(string)temp;
				bzero(temp,100);
				z=0;
				stop_application+=" ";
				cout<<endl<<"Application sent to stop: "<<stop_application;
				cmd_stop+=stop_application;
				}
			}
		}			
cout<<endl<<"To start program shell script: "<<cmd.c_str();
				system(cmd.c_str());
cout<<endl<<"To stop program shell script: "<<cmd_stop.c_str();
				system(cmd_stop.c_str());

				
/*
	string cmd="./programscript.sh ";
	string temp=(string)buffer;
	cmd+=temp;
	system(cmd.c_str());
*/
    close(sockfd);
    return 0;
}
