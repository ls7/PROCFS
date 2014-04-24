#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 int main(void)
   {

      FILE *filePtr;
      char msg[1024];
      int msgLen; 
      printf("Enter message to be sent ");
      gets(msg); 
      filePtr = fopen("/proc/my_proc_file", "w");
      if (filePtr == NULL) {
      printf("I couldn't open/proc/my_proc_file for writing.\n");
      exit(0);
      }
      msgLen = strlen(msg);

      if(msgLen>1024)
      printf("You have exceeded the buffer size\n");
	
      fprintf(filePtr, "%s", msg); 
      return 0;
   }
