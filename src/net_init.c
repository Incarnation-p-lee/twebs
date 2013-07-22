/*-----------------------------------*/
/*Author Incarnation.p Lee           */
/*Data   7-14-13                     */
/*Mannul initial the network         */
/*-----------------------------------*/
/*-------------Revision--------------*/
/*DATE    WHO     WHAT               */
/*071413  pli     Created            */
/*-----------------------------------*/
int
open_fd_listen(int port)
{
  int fd_listen;
  int optval;
  struct sockaddr_in server_addr;

  fd_listen = socket(AF_INET,
    SOCK_STREAM, 0);
  if(fd_listen < 0)
    error_handle("socket");

  optval = 1;
  if(0 != setsockopt(fd_listen, 
    SOL_SOCKET, SO_REUSEADDR,
    (const void *)&optval, 
    sizeof(int)))
    error_handle("setsockopt");

  memset(&server_addr, 0, 
    sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = 
    htonl(INADDR_ANY);
  server_addr.sin_port = htons(port);
  
  if(bind(fd_listen, 
   (struct sockaddr*)&server_addr,
   sizeof(server_addr)) < 0)
    error_handle("bind");
    
  if(listen(fd_listen, 
    LISTEN_COUNT) < 0)
    error_handle("listen");

  return fd_listen;
}
