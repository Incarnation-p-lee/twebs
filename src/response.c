/*-----------------------------------*/
/*Author Incarnation.p Lee           */
/*Data   7-14-13                     */
/*Mannul Response the http GET       */
/*-----------------------------------*/
/*-------------Revision--------------*/
/*DATE    WHO     WHAT               */
/*071413  pli     Created            */
/*-----------------------------------*/
void
response(int fd)
{
  char buf[MAX_LINE];
  char method[MAX_LINE];
  char uri[MAX_LINE];
  char version[MAX_LINE];
  char filen[MAX_LINE];
  char cgiv[MAX_LINE];
  int is_static;
  struct sys_bio bio;
  struct stat sbuf;

  system_init(&bio, fd);
  system_readline(&bio, buf, MAX_LINE);
  sscanf(buf, "%s %s %s", method,
    uri, version);

  if(strcmp(method, "GET"))
  {
    client_error_handle(fd, method, 
      "501", "Not Implemented", 
      "Tiny can't implement this method."); 
    return;
  }
  
  /*-tiny web ignore any info of */
  /*-http header.                */
  read_request_head(&bio);

  is_static = uri_parser(uri, 
    filen, cgiv); 

#if 0
  if(!strstr(filen, "./favicon.ico"))
    client_error_handle(fd, filen, "404", "Not Found", 
      "Tiny can't find this file."); 
#else
/*
  if(!strstr(filen, "./favicon.ico"))
    return;
*/
#endif
     

  if(stat(filen, &sbuf) < 0)
    client_error_handle(fd, filen, "404", "Not Found", 
      "Tiny can't find this file."); 

  if(is_static)
  {
    if(!sbuf.st_mode)
    {
			client_error_handle(fd, filen, 
				"403", "Access Deny", 
				"You have no right."); 
      return;
    }
    server_static(fd, filen, sbuf.st_size);
  }
  else
  {
    if(sbuf.st_mode)
    {
			client_error_handle(fd, filen, 
				"403", "Unknown Cgifile", 
				"Can not find the CGI."); 
      return;
    }
    server_dynamic(fd, filen, cgiv);
  }
  
  return;
}


static void
read_request_head(struct sys_bio *bio)
{
  char buf[MAX_LINE];

  system_readline(bio, buf, MAX_LINE);
  while(strcmp(buf,"\r\n"))
  {
		if(!system_readline(bio, buf, MAX_LINE))
      break;
  }
  return;
}

