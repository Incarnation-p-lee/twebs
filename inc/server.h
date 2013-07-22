#ifndef SERVER_H
#define SERVER_H



extern void
system_init(struct sys_bio *, int);
extern int
system_write(int, char *, int);
extern int
system_readline(struct sys_bio *, char *, int);
extern void
client_error_handle(int fd, char *reason, char *errnum,
  char *shortmsg, char *longmsg);
extern int
uri_parser(char *, char *, char *);
extern void
error_handle(char *);
  



void
response(int);
void
server_static(int, char *, int);
void
server_dynamic(int, char *, char *);



static void
read_request_head(struct sys_bio *);
static void
get_filetype(char *, char *);

#endif
