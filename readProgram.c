#include<stdio.h>
#include<stdlib.h>
main()
{
   char ch;
   FILE *filePtr;
   filePtr = fopen("/proc/my_proc_file","r");
    if( filePtr == NULL )
   {
      printf("Error while opening the file.\n");

   }
    else
   {   
    
     printf("Received message is :- \n");
     while( ( ch = fgetc(filePtr) ) != EOF )
     printf("%c",ch);
     fclose(filePtr);
     printf("\n");
   }
 return 0;
}
