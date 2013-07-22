/*-----------------------------------*/
/*Author Incarnation.p Lee           */
/*Data   7-15-13                     */
/*Mannul parser the uri link         */
/*-----------------------------------*/
/*-------------Revision--------------*/
/*DATE    WHO     WHAT               */
/*071413  pli     Created            */
/*-----------------------------------*/
int
uri_parser(char *uri, char *filename, 
  char *cgiargv)
{
  char *parse; 

  if(!strstr(uri, "cgi-bin")) 
  { /* static */
    strcpy(cgiargv, "");
    strcpy(filename, ".");
    strcat(filename, "/files");
    strcat(filename, uri);
    if('/' == uri[strlen(uri) - 1])
      strcat(filename, "index.html");

    return 1;
  }
  else
  { /* dynamic */
    parse = index(uri, '?');
    if(NULL != parse)
    {
      strcpy(cgiargv, parse + 1);
      *parse = NUL;
    }
    else
      strcpy(cgiargv, "");

    strcpy(filename, ".");
    strcat(filename, uri);
    return 0;
  }
}
