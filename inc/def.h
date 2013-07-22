#ifndef DEFINITION_H
#define DEFINITION_H

/*- ALL MARCO DEFINES               */
#define LISTEN_COUNT         1024
#define MAX_LINE             1024
#define MAX_BUF              10240
#define INTERNAL_BUF_SIZE    2048
#define NUL                  (char)0



/*- ALL STRUCTURE DEFINES           */
typedef struct sys_bio{
  int fd;
  int rest;
  char *current;
  char iobuffer[INTERNAL_BUF_SIZE];
}System_bio;



#endif
