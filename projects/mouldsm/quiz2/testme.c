#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const char range[] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'};

/* This function generates a random char and returns it.*/
/* reall we want this to generate 9 characters...*/
char inputChar() {
  int max = sizeof(range)/sizeof(range[0]); /*because ascii is beautiful */
  //printf("max is %d\n", max);
  int rando = rand() % (max + 1);
  //printf("rando was %d\n",rando); 
  return (char)(range[rando]);
}
/* I need ATLEAST 96!/(96-9)! =  iterations to ensure exit status is achieved for "c"... */
/* for "s" we need 26!/(25-7)! = */
/* holy crap independent events, (96!/(96-9)!)*(26!/(26-7)!) = 1559819890146044259532800000 */
/* that is unrealistic, so lets do something */
char *inputString() {
  /* so we are going to limit to just lowercase */
  /* which means tc max is 25!/(25-6)! = 127512000 which is 1/2 an int so we guud */
  int max = 25;
  char str[6] = {93,93,93,93,93,'\0'};
  char *str_ptr = str;
  int i = 0;
  for(i=0;i<5;i++) {
    str[i] = (char) ((rand() % (max+1)) + 97);
  }
  return str_ptr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
