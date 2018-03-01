//
// Created by Hang Gong on 2/16/18.
//
#include "csapp.h"


void mul(int fd, char *args) {
    char *p;
    char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE], header[MAXLINE];
    int n1=0, n2=0;

    /* Extract the two arguments */
    p = strchr(args, '&');
    *p = '\0';
    strncpy(arg1, args, MAXLINE);
    strncpy(arg2, p+1, MAXLINE);
    n1 = atoi(arg1);
    n2 = atoi(arg2);

    /* Make the response body */
    snprintf(content, MAXLINE,
             "Welcome, this is Multiplier portal.\r\n"
                     "<p>The answer is: %d * %d = %d\r\n"
                     "<p>Thanks for visiting!\r\n",
             n1, n2, n1*n2);
    size_t len = strlen(content);

    // Make response header
    snprintf(header, MAXLINE, "Connection: close\r\n");
    snprintf(header, MAXLINE, "%sContent-length: %d\r\n", header, (int)len);
    snprintf(header, MAXLINE, "%sContent-type: text/html\r\n\r\n", header);

    // write response
    rio_writen(fd, header, strlen(header));
    rio_writen(fd, content, len);
}
