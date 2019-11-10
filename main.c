#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int rngesus(int randomDataFile){
  int randNum=0;
  int *buff=&randNum;
  if(read(randomDataFile, buff, sizeof(int))<0){
    printf("%s\n",strerror(errno));
  }
  return randNum;
}

int main(){
  int randomDataFile = open("/dev/random", O_RDONLY);
  if(randomDataFile<0){
    printf("%d\n",randomDataFile);
    printf("%s\n",strerror(errno));
    return randomDataFile;
  }
  int randos[10];
  int i;
  for(i=0;i<10;i++){
    randos[i]=rngesus(randomDataFile);
  }
  if(close(randomDataFile)<0){
    printf("%s\n",strerror(errno));
    return errno;
  }

  int fileToWriteTo = open("fileToWriteTo.txt", O_WRONLY|O_TRUNC);
  if(fileToWriteTo<0){
    fileToWriteTo = open("fileToWriteTo.txt",O_WRONLY|O_CREAT,0640);
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
  int *randos2;
  if(read(fileToReadFrom, randos2, 10*sizeof(int))<0){
    printf("%s\n",strerror(errno));
    return errno;
  }
  for(i=0;i<10;i++){
    printf("%d: ",i);
    printf("Read %d from random file, and %d from file I made\n",randos[i],randos2[i]);
  }
  //printf("made it here %d \n",errno);
  return close(fileToReadFrom);
}
