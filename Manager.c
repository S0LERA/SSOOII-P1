/******************************************************************
 * Projecto:                Primera Práctica de SSOO II
 *
 * Nombre del programa:     Manager.c
 *
 * Autor:                   Pablo Rodríguez Solera
 *
 * Fecha de creación:       18/02/2019
 *
 * Proposito:               Gestión  y sincronización de los procesos
 														relacionados con el desarrollo de la práctica
 *
 * Historial de revisión:
 *
 * Fecha        Autor       Ref         Revisión
 * 03/03/2019   Pablo   		1           Funciones printLog y createLog
 *																			creadas
 * 04/03/2019		Pablo				2						Variables renombradas
 *
 * ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define NUM_SONS 4
#define PA 0
#define PB 1
#define PC 2
#define PD 4
#define READ 0

pid_t g_sons_matrix[NUM_SONS];


void handler(int sig){

  printLog("[MANAGER] A Ctrl+C interruption occurred, killing the children processes...");
  for(int i = 0; i < NUM_SONS;i++){
    if(g_sons_matrix[i] != 0){
      if(kill(g_sons_matrix[i],SIGKILL) == -1){
        fprintf(stderr,"[MANAGER] Error removing children\n");
        printLog("[MANAGER] Error removing children");
      }
    }
  }
  printLog("[MANAGER] Childrens killed succesfully");
  printLog("[MANAGER] Removing the program files...");
  pid_t pid;
  int 	status;
  pid = fork();
  g_sons_matrix[PD] = pid;
  if(pid == -1){
    fprintf(stderr,"[MANAGER] Error creating the children that remove the  program files.");
    printLog("[MANAGER] Error creating the children that remove the  program files.");
    exit(1);
  }else if(pid == 0){
    if(execlp("./PD", "./PD",NULL) == -1){
      fprintf(stderr,"[MANAGER] Error executing the children that remove the  program files.");
      printLog("[MANAGER] Error executing the children that remove the  program files.");
      exit(1);
    }
  }else{
    waitpid(pid,&status,0);
    printLog("[MANAGER] Files removed succesfully");
  }
  exit(EXIT_SUCCESS);
}


int createLog(){
  FILE *log;
  log = fopen("log.txt", "wb");
  if (log == NULL) {
    fprintf(stderr,"[MANAGER] Error creating the log.\n");
    exit (1);
  }
  fputs("******** Log of the system ********\n",log);
  fclose(log);
  return EXIT_SUCCESS;
}

int printLog(char str[]){
  FILE *log;
  log = fopen("log.txt", "a");
  if (log == NULL) {
    fprintf(stderr,"[MANAGER] Error opening the log.\n");
    exit (1);
  }
  if(fprintf(log,"\n%s",str) == -1){
    fprintf(stderr,"[MANAGER] Error writing in the log.\n");
    exit (1);
  }
  fclose(log);
  return EXIT_SUCCESS;
}

int createDirectories(){
  pid_t pid;
  int 	status;
  pid = fork();
  g_sons_matrix[PA] = pid;
  if(pid == -1){
    fprintf(stderr,"[MANAGER] Error creating the children that creates the students directories");
    printLog("[MANAGER] Error creating the children that creates the students directories");
    exit(1);
  }else if(pid == 0){
    if(execlp("./PA", "./PA",NULL) == -1){
      fprintf(stderr,"[MANAGER] Error executing the children that creates the students directories");
      printLog("[MANAGER] Error executing the children that creates the students directories");
      exit(1);
    }
  }else{
    waitpid(pid,&status,0);
    printLog("[MANAGER] Directories created succesfully");
  }
  return EXIT_SUCCESS;
}

int copyExams(){
  pid_t pid;
  int 	status;
  pid = fork();
  g_sons_matrix[PB] = pid;
  if(pid == -1){
    fprintf(stderr,"[MANAGER] Error creating the children that copy the exam");
    printLog("[MANAGER] Error creating the children that copy the exam");
    exit(1);
  }else if(pid == 0){
    if(execlp("./PB", "./PB",NULL) == -1){
      fprintf(stderr,"[MANAGER] Error executing the children that copy the exam");
      printLog("[MANAGER] Error executing the children that copy the exam");
      exit(1);
    }
  }else{
    makeGradefile();
    waitpid(pid,&status,0);
    printLog("[MANAGER] Exams copied succesfully");
  }
  return EXIT_SUCCESS;
}

int makeGradefile(){
  pid_t pid;
  int 	status,pipe_c[2];
  pipe(pipe_c);
  char wr_pipe_c[256];
  sprintf(wr_pipe_c,"%d",pipe_c[1]);
	char log_return[1024];

  pid = fork();
  g_sons_matrix[PC] = pid;
  if(pid == -1){
    fprintf(stderr,"[MANAGER] Error creating the children that make the grade file");
    printLog("[MANAGER] Error creating the children that make the grade file");
    exit(1);
  }else if(pid == 0){
    if(execlp("./PC","./PC",wr_pipe_c,NULL) == -1){
      fprintf(stderr,"[MANAGER] Error executing the children that make the grade file");
      printLog("[MANAGER] Error executing the children that make the grade file");
      exit(1);
    }
  }else{
    waitpid(pid,&status,0);
    read(pipe_c[READ],wr_pipe_c,sizeof(wr_pipe_c));
    printLog("[MANAGER] Grade file succesfully created for all the students");
		sprintf(log_return,"%s %s","[MANAGER] The average mark of the students is",wr_pipe_c);
    printLog(log_return);
  }
  return EXIT_SUCCESS;
}

int mainF(){
  signal(SIGINT,handler);
  createLog();
  createDirectories();
  copyExams();
  printLog("[MANAGER] End of the program.");
  return EXIT_SUCCESS;
}
int main(){
 mainF();
}
