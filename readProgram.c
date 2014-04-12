#include<stdio.h>
#include<stdlib.h>
main()
{
   char ch;
   FILE *fp;
   fp = fopen("/proc/osproject","r"); // read mode
    if( fp == NULL )
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
   
 printf("The contents of file are :- \n");
 while( ( ch = fgetc(fp) ) != EOF )//Until end of file, the characters are fetched
 printf("%c",ch);
 fclose(fp);// File closure
 printf("\n");
 return 0;
}
