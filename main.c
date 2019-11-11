#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
int randNum(){
  int randomDataFile = open("/dev/random", O_RDONLY);
  if(randomDataFile<0){
    printf("%d\n",randomDataFile);
    printf("%s\n",strerror(errno));
    return randomDataFile;
  }
  int randNum=0;

  if(read(randomDataFile, &randNum, sizeof(int))<0){
    printf("%s\n",strerror(errno));
    return 0;
  }
  close(randomDataFile);
  return randNum;
}

int main(){
  printf("hi\n");
  int randos[10];
  int i;
  for(i=0;i<10;i++){
    randos[i]=randNum();
    printf("Generated %d \n",randos[i]);
  }

  int fileToWriteTo = open("fileToWriteTo.txt", O_WRONLY|O_TRUNC);

  if(fileToWriteTo<0){
    fileToWriteTo = open("fileToWriteTo.txt",O_WRONLY|O_CREAT|O_EXCL,0640);
  }
  if(write(fileToWriteTo, &randos, 10*sizeof(int))<0){
    printf("%s\n",strerror(errno));
    return errno;
  }
  if(close(fileToWriteTo)<0){
    printf("%s\n",strerror(errno));
    return errno;
  }
  int fileToReadFrom = open("fileToWriteTo.txt", O_RDONLY);
  int randos2[10];

  if(read(fileToReadFrom, &randos2, 10*sizeof(int))<0){
    printf("%s\n",strerror(errno));
    return errno;
  }
  //printf("Got here \n");

  for(i=0;i<10;i++){
    printf("Read %d from random file, and %d from file I made\n",randos[i],randos2[i]);
  }
  return 0;
}
