/*-----------------------------------*/
/*Author Incarnation.p Lee           */
/*Data   7-14-13                     */
/*Mannul handle the error.           */
/*-----------------------------------*/
/*-------------Revision--------------*/
/*DATE    WHO     WHAT               */
/*071413  pli     Created            */
/*-----------------------------------*/
void
error_handle(const char *message)
{
  char *unknown = "Unknown location.";

  if(NULL == message)
    message = unknown;
   
  fprintf(stdout, "break at %s\n", 
    message);
  fprintf(stdout, "%02d =>%s\n",
    errno, strerror(errno));

  exit(1);
}
