#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char line[6000];

void error(char *msg) {
	printf("%s - %s.\n", msg, strerror(errno));
}

int main(int argc , char *argv[])
{
    char *message , server_reply[2000];
    int recv_size;
 
    SOCKET s;
    s = open_socket("www.nepcal.com", "80");
 
    //Send some data
    message = "GET / HTTP/1.1\r\n";
    say(s, message);
	message = "Host: www.nepcal.com\r\n\r\n";
	say(s, message);
 
    //Add a NULL terminating character to make it a proper string before printing
	FILE *myfile = fopen("a.html", "w");
    char rec[255];
	int bytesrecv = recv(s, rec, 254, 0);
	//printf("Downloading data...\n");
	while (bytesrecv) {
		if (bytesrecv < 0)
			error("Cannot read from server.");
			rec[bytesrecv] = '\0';
			fprintf(myfile, "%s", rec);
			//printf("%s", rec);
			
			bytesrecv = recv(s, rec, 254, 0);
			if (strstr(rec, "converterFields")) {
				fprintf(myfile, "%s", rec);
				break;		
			}
		}
	fclose(myfile);
    return 0;
}

