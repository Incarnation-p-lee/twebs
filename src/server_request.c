/*-----------------------------------*/
/*Author Incarnation.p Lee           */
/*Data   7-15-13                     */
/*Mannul Server the client request.  */
/*-----------------------------------*/
/*-------------Revision--------------*/
/*DATE    WHO     WHAT               */
/*071513  pli     Created            */
/*-----------------------------------*/
void
server_static(int fd, char *filename, int size)
{
  int fd_src;
  char *src;
  char buf[MAX_BUF];
  char filetype[MAX_LINE];

  get_filetype(filename, filetype);
  sprintf(buf, "HTTP/1.0 200 OK\r\n");
  sprintf(buf, "%sContent-type: %s\r\n", buf, filetype);
  sprintf(buf, "%sContent-length: %d\r\n\r\n", buf, size);

  system_write(fd, buf, strlen(buf));

  fd_src = open(filename, O_RDONLY, 0);
  fprintf(stdout, "request %s\n", filename);
  if(-1 == fd_src)
    client_error_handle(fd, filename, 
      "404", "Not Found", 
      "Tiny can't find this file."); 

  src = mmap(0, size, PROT_READ, MAP_PRIVATE, fd_src, 0);
  if(NULL == src)
    error_handle("mmap");

  system_write(fd, src, size);
  
  fprintf(stdout, "Sent %s.\n", filename);
  close(fd_src);
  munmap(src, size);

  return;
}


void
server_dynamic(int fd, char *filen, 
  char *cgiv)
{
  return;
}


static void
get_filetype(char *filename, char *filetype)
{
  assert(NULL != filename);

  if(strstr(filename, ".html"))
    strcpy(filetype, "text/html");
  else if(strstr(filename, ".gig"))
    strcpy(filetype, "image/gif");
  else if(strstr(filename, ".jpg"))
    strcpy(filetype, "image/jpg");
  else
    strcpy(filetype, "text/plain");
   
  return;
}
