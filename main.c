/*-----------------------------------*/
/*Author Incarnation.p Lee           */
/*Data   7-13-13                     */
/*Mannul Tiny web server             */
/*-----------------------------------*/
/*-------------Revision--------------*/
/*DATE    WHO     WHAT               */
/*071313  pli     Create project     */
/*-----------------------------------*/

#include "include.h"
#include "def.h"
#include "var.h"
#include "external.h"


int
main(int argc, char **argv)
{
  int fd_listen;
  int fd_connected;
  int port;
  socklen_t client_len;
  struct sockaddr_in client_addr;

  if(2 != argc)
  {
    fprintf(stderr, "Usage %s <port>\n", 
      argv[0]);
    exit(1);
  }
  
  port = atoi(argv[1]);
  fd_listen = open_fd_listen(port);
  client_len = sizeof(client_addr);

  while(1)
  {
    fd_connected = accept(fd_listen, 
      (struct sockaddr*)&client_addr, 
      &client_len);
    fprintf(stdout, "client connected..\n");
    response(fd_connected);
    close(fd_connected);
  }

  return EXIT_SUCCESS;
}
