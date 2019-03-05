/******************************************************************
 * Projecto:                Primera Práctica de SSOO II
 *
 * Nombre del programa:     PB.c
 *
 * Autor:                   Pablo Rodríguez Solera
 *
 * Fecha de creación:       18/02/2019
 *
 * Proposito:               Copiar examen al directorio del alumno.
 *
 * ****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

FILE *openFile(char *file_name[]){
  FILE *f = NULL;
  f = fopen (file_name, "r" );
  if (f == NULL) {
    fprintf(stderr,"Error opening the file %s\n", file_name);
    exit (1);
  }

  return f;
}

int copyExam(FILE *f){
  char buf[1024] = "";
  char *dni_token = "";
  char *exam_type_token = "";
  char command[512];
  while (fgets(buf, sizeof(buf), f)){
    dni_token = strtok(buf, " ");
    exam_type_token = strtok(NULL , " ");
    strcat(exam_type_token,".pdf");
    snprintf(command, sizeof command, "/bin/cp  %s %s", exam_type_token, dni_token);
    system(command);
  }
   return(0);
}

int main(int argc, char const *argv[]) {

  FILE *f = NULL;
  char file_name[] = "estudiantes.txt";
  f = openFile(file_name);
  copyExam(f);

	fclose (f);
  return 0;
}
