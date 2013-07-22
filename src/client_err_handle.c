/*-----------------------------------*/
/*Author Incarnation.p Lee           */
/*Data   7-14-13                     */
/*Mannul handle client unknown       */
/*       request.                    */
/*-----------------------------------*/
/*-------------Revision--------------*/
/*DATE    WHO     WHAT               */
/*071413  pli     Created            */
/*-----------------------------------*/
void
client_error_handle(int fd, 
  char *reason, char *errnum,
  char *shortmsg, char *longmsg)
{

  char buf[MAX_LINE];
  char body[MAX_BUF];

  sprintf(body, "<html><title>Tiny Error</title>");
  sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
  sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
  sprintf(body, "%s<p>%s: %s\r\n", body, reason, longmsg);
  sprintf(body, "%s<hr><em>" "Tiny Web Server</em>\r\n", body);

  sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
  system_write(fd, buf, strlen(buf));
  sprintf(buf, "Conten-type: text/html\r\n"); 
  system_write(fd, buf, strlen(buf));
  sprintf(buf, "Conten-length: %d\r\n\r\n", strlen(body)); 
  system_write(fd, buf, strlen(buf));
  system_write(fd, body, strlen(body));
 
  return;
}

