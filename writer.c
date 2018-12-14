#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){
  int fd, semid, shmid;
  int * data;
  fd = open("story.txt", O_CREAT);
  
  struct sembuf up = {.sem_num=0, .sem_op=1, .sem_flg=SEM_UNDO};
  struct sembuf down = {.sem_num=0, .sem_op=-1, .sem_flg=SEM_UNDO};

  key_t key = ftok("file", 'R');
  shmid = shmget(key, 200, 0644);
  data = shmat(shmid, (void *) 0, 0);
  semid = semget(key, 1, 0644);
  printf("This was the last line added:\n");

  lseek(fd, -1*(data[1]), SEEK_END);
  char * string;
  read(fd, string, data[1]);
  printf("%s\n", string);

  printf("Continue the story!:\n");
  fgets(string, 200, stdin);
  printf("%d\n", sizeof(*string));
  
}
