#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <errno.h>

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
			      (Linux-specific) */
};

struct sembuf up = {.sem_num=0, .sem_op=1, .sem_flg=SEM_UNDO};
struct sembuf down = {.sem_num=0, .sem_op=-1, .sem_flg=SEM_UNDO};

int main(int argc, char * argv[]){
  key_t key;
  int shmid, semid, fd;
  int * data;
  key = ftok(".", 'R');

  if(argc>1){
    if(!strcmp(argv[1], "-c")){
      shmid = shmget(key, 200, 0644 | IPC_CREAT);
      data = shmat(shmid, (void *)0, 0);
      data[0] = 0;
      data[1] = 0;
      semid  = semget(key, 1, 0644 | IPC_CREAT);
      union semun semdata;
      semdata.val=1;
      semctl(semid, 0, SETVAL, semdata);
      open("storyf", O_RDWR | O_CREAT | O_TRUNC, 0666);
    }
    if(!strcmp(argv[1], "-r")){
      semid  = semget(key, 1, 0644);
      shmid = shmget(key, 200, 0644);
      data = shmat(shmid, (void *)0, 0);
      semop(semid, &down, 1);
      fd = open("storyf", O_RDWR);
      char string[10000];
      read(fd, string, 10000);
      printf("%s\n", string);
      close(fd);
      remove("storyf");
      shmdt(data);
      shmctl(shmid, IPC_RMID, NULL);
      semctl(semid, 0, IPC_RMID, 0);
    }
    if(!strcmp(argv[1], "-v")){
      fd = open("storyf", O_RDONLY);;
      char string[10000];
      read(fd, string, 10000);
      printf("%s\n", string);
      close(fd);
    }
  }

      

}
