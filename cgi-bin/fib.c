//
// Created by Hang Gong on 2/16/18.
//
#include "csapp.h"


int fibb(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibb(n - 1) + fibb(n - 2);
    }
}


void fib(int fd, char *args) {
    char st[MAXLINE], content[MAXLINE], header[MAXLINE];
    int n = 0;
    int ans = 0;

    /* Extract the argument */
    strncpy(st, args, MAXLINE);
    n = atoi(st);
    ans = fibb(n);



    /* Make the response body */
    snprintf(content, MAXLINE, "Welcome to add.com: ");
    snprintf(content, MAXLINE, "%sTHE Internet addition portal.\r\n<p>", content);
    snprintf(content, MAXLINE, "%sThe %d fibonacci number is: %d\r\n<p>",
             content, n, ans);
    snprintf(content, MAXLINE, "%sThanks for visiting!\r\n", content);
    size_t len = strlen(content);

    // Make response header
    snprintf(header, MAXLINE, "Connection: close\r\n");
    snprintf(header, MAXLINE, "%sContent-length: %d\r\n", header, (int)len);
    snprintf(header, MAXLINE, "%sContent-type: text/html\r\n\r\n", header);

    // write response
    rio_writen(fd, header, strlen(header));
    rio_writen(fd, content, len);
}
