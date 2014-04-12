#include <stdio.h>
#include <stdlib.h>
 int main(void)
   {
      FILE *fp;
      char input[1024];
      printf("Enter the data to be written ");
      gets(input); 
      fp = fopen("/proc/osproject", "w"); // The proc file open is performed in write mode
      if (fp == NULL) {
      printf("I couldn't open/proc/osproject for writing.\n");
      exit(0);
      }
      fprintf(fp, "%s", input); // The input data is written into the proc file
      return 0;
   }
