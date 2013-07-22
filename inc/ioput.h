#ifndef IOPUT_H
#define IOPUT_H


/*- external linkage function */
void
system_init(struct sys_bio *, int);
int
system_write(int, char *, int);
int
system_readline(struct sys_bio *, char *,
  int);


/*- static linkage function   */
static int
system_readbuf(struct sys_bio *, char *, int);

#endif
