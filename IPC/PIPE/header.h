#include <stdio.h>
#include <sys/types.h>	// next 3 for stat()
#include <sys/stat.h>
#include <unistd.h>	//pipe

#include <sys/ipc.h>

#include <sys/msg.h>	//message Q

#include <string.h>

#include <fcntl.h>	//open()	

#include <signal.h>	//SIGINT

#include <stdlib.h> //atoi()

#include <dirent.h>	//DIR and readdir(), opendir()

#include <sys/shm.h>	//for shared memory	

#include <sys/sem.h>	//for shemaphore

#include <pthread.h>	//for threads
