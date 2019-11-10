#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
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
    int randNum=0;
    int *buff=&randNum;
    read(randomDataFile, buff, sizeof(int));
    printf("%d\n",randNum);
    randos[i]=randNum;
  }
  close(randomDataFile);
  int fileToWriteTo = open("fileToWriteTo.txt", O_WRONLY|O_TRUNC);
  if(fileToWriteTo<0){
    fileToWriteTo = open("fileToWriteTo.txt",O_WRONLY|O_CREAT,0640);
  }
  write(fileToWriteTo, &randos, 10*sizeof(int));
  close(fileToWriteTo);
  int fileToReadFrom = open("fileToWriteTo.txt", O_RDONLY);
  int *randos2;
  read(fileToReadFrom, randos2, 10*sizeof(int));
  for(i=0;i<10;i++){
    printf("Read %d from random file, and %d from file I made\n",randos[i],randos2[i]);
  }
  return 0;
}
