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
  char * data;
  fd = open("storyf", O_RDWR | O_APPEND);
  key_t key = ftok(".", 'R');
 
  struct sembuf up = {.sem_num=0, .sem_op=1, .sem_flg=SEM_UNDO};
  struct sembuf down = {.sem_num=0, .sem_op=-1, .sem_flg=SEM_UNDO};
  
  shmid = shmget(key, 200, 0644);
  data = shmat(shmid, (void *) 0, 0);
  semid = semget(key, 1, 0644);
  
  if(data[1]){
    printf("This was the last line added:\n");
    printf("%s\n", &data[3]);
  }
  else{
    printf("And so a new story begins...\n");
  }

  printf("Continue the story!: ");

  char user_in[200];
  fgets(user_in, 200, stdin);
  int size = strlen(user_in);

  semop(semid, &down, 1);
  data[0] = size;
  data[1] += size;
  strcpy(&data[3], user_in);
  write(fd, user_in, size);
  semop(semid, &up, 1);
   
}
