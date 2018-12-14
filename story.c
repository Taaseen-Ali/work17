#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char * argv[]){
  key_t key;
  int shmid, semid, fd;
  char * data;
  key = ftok("file", 'R');

  if(argc > 1){
    if(strcmp(argv[1], "-c")){
      shmid = shmget(key, 200, 0644 | IPC_CREAT);
      data = shmat(shmid, (void *)0, 0);
      semid  = semget(key, 1, IPC_CREAT);
      fd = open("story.txt", O_CREAT | O_TRUNC);
    }
    if(strcmp(argv[1], "-r")){
      //stuff
    }
    if(strcmp(argv[1], "-v")){
      //stuff
    }
  }
}
      

