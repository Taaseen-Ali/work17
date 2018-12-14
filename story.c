#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
			      (Linux-specific) */
};

int main(int argc, char * argv[]){
  key_t key;
  int shmid, semid, fd;
  char * data;
  key = ftok("file", 'R');
  struct sembuf up = {.sem_num=0, .sem_op=1, .sem_flg=SEM_UNDO};
  struct sembuf down = {.sem_num=0, .sem_op=-1, .sem_flg=SEM_UNDO};
  
  if(argc > 1){
    if(strcmp(argv[1], "-c")){
      shmid = shmget(key, 200, 0644 | IPC_CREAT);
      data = shmat(shmid, (void *)0, 0);
      semid  = semget(key, 1, IPC_CREAT);
      semctl(semid, 0, SETVAL, 1);
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
      

