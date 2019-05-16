//use local time class in c library 


#include <stdio.h>
#include <libsocket/libinetsocket.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // Connect to http://quotesondesign.com
    int fd = create_inet_stream_socket("quotesondesign.com", "80", LIBSOCKET_IPv4, 0);
    if (fd == -1)
    {
        printf("Can't connect to service");
        exit(1);
    }
    
    // Open the socket number (fd) as a FILE
    FILE *f = fdopen(fd, "rb+");
    
    // Send GET request to web server
    fprintf(f, "GET /wp-json/posts?filter[orderby]=rand HTTP/1.0\n");
    fprintf(f, "Host: quotesondesign.com\n");
    fprintf(f, "\n");
    
    char line[1000];
    while (fgets(line, 1000, f) != NULL)
    {
        // The quote is between <p> and <\/p> tags. Search for them.
        char * start = strstr(line, "<p>");
        if (start == NULL)
            continue;   // Not interested in lines that don't have <p>
        char * end = strstr(line, "<\\/p>");
        *end = '\0';
        
        printf("%s", start+3);
    }
    fclose(f);
}