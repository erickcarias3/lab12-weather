#include <stdio.h>
#include <libsocket/libinetsocket.h>
#include <stdlib.h>
#include <string.h>
 



void printInfo( FILE *file ){
    
    char line[5000];
    char * start = NULL;
    char * end = NULL;
    while(fgets(line, 5000, file) != NULL)
    {   
        if (line[0] == '{'){
            start = strstr(line, "place");
            end = strstr(line, "us}");
            //printf("%s \n" , result);
            break;
            
        }
    }
    while(*start != *end ){
        printf("%s\n" , start);
    }
    /*for(int i = 0; i < 5000 ; i++){
        if(line[i] == ',')
            line[i] = '\0';
    }
    */
    
    printf("%s \n ",line);
}



int main(int argc, char *argv[1])
{
    // Connect to http://quotesondesign.com
    int fd = create_inet_stream_socket("api.aerisapi.com", "80", LIBSOCKET_IPv4, 0);
    if (fd == -1)
    {
        printf("Can't connect to service");
        exit(1);
    }
    
    // Open the socket number (fd) as a FILE
    FILE *f = fdopen(fd, "rb+");
    
    char request[100]; 
    char * clientId = "wQhXMMnxoRV4HNKoRLZrL";
    char * clientSecret = "rUOW0GEyf5bT9JhUzro2WQAuUpj3A7nFHgVCRGEK";
    // Send GET request to web server
    sprintf(request, "/observations/%s?client_id=%s&client_secret=%s" , argv[1] , clientId , clientSecret);
    
    fprintf(f, "GET %s HTTP/1.0\n", request);
    fprintf(f, "Host: api.aerisapi.com\n");
    fprintf(f, "\n");
    

    printInfo(f);
   
 
    fclose(f);
}