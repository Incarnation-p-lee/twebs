#ifndef HANDLER_H
#define HANDLER_H


extern int
system_write(int, char *, int);



void
client_error_handle(int fd, 
  char *reason, char *errnum,
  char *shortmsg, char *longmsg);
void
error_handle(const char*);

#endif
