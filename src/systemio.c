/*-----------------------------------*/
/*Author Incarnation.p Lee           */
/*Data   7-14-13                     */
/*Mannul System input and output     */
/*-----------------------------------*/
/*-------------Revision--------------*/
/*DATE    WHO     WHAT               */
/*071413  pli     Created            */
/*-----------------------------------*/
void
system_init(struct sys_bio *bio,
  int fd)
{
  assert(NULL != bio);

  bio->fd = fd;
  bio->current = 0;
  bio->rest = 0;
  memset(bio->iobuffer, 0,
    INTERNAL_BUF_SIZE);

  return;
}

int
system_readline(struct sys_bio *bio,
  char *buf, int maxlen)
{
  char c;  
  int n;
  int rc;

  n = 1;
  while(n < maxlen)
  {
    rc = system_readbuf(bio, &c, 1);
    if(1 == rc)
    {
      *buf++ = c;
      if('\n' == c)
        break;
    }
    else if(0 == rc)
    {
      if(1 == n)
        return 0;
      else
        break;
    }
    else
      return -1;
  }
  *buf = NUL;
  
  return n;
}

static int
system_readbuf(struct sys_bio *bio,
  char *buf, int len)
{
  int read_size; 

  while(bio->rest <= 0)
  {
    bio->rest = read(bio->fd, 
      bio->iobuffer, 
      sizeof(bio->iobuffer));
    
    if(bio->rest < 0)
    {
      if(EINTR != errno)
        return -1;
    }
    else if(0 == bio->rest)
      return 0;
    else
      bio->current = bio->iobuffer;
  }

  read_size = len > bio->rest? 
    bio->rest: len;
  
  memcpy(buf, bio->current, read_size);
  bio->rest -= read_size;
  bio->current += read_size;

  return read_size;
}

/*--------------------------------------------------*/
/*-When write buf, client may close the connection.-*/
/*-Then next write you may receive EPIPE.          -*/
/*-Handle the signal EPIPE, make server works well.-*/
/*--------------------------------------------------*/
int 
system_write(int fd, char *buf, int len)
{
  int write_size;

  while(len > 0)
  {
    write_size = write(fd, buf, len);
    if(0 >= write_size)
    {
      if(EINTR != errno)
        write_size = 0;
      else
        return -1;
    }
		len -= write_size;
		buf += write_size;
  }
  
  return len;
}
