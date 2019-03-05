/******************************************************************
 * Projecto:                Primera Práctica de SSOO II
 *
 * Nombre del programa:     PA.c
 *
 * Autor:                   Pablo Rodríguez Solera
 *
 * Fecha de creación:       18/02/2019
 *
 * Proposito:               Crear los directorios de los alumnos.
 *
 * ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

FILE *openFile(char *file_name[]){
  FILE *f = NULL;
  f = fopen (file_name, "r" );
  if (f == NULL) {
    fprintf(stderr,"Error opening the file %s\n", file_name);
    exit (1);
  }

  return f;
}

int createDirectories(FILE *f){
  char buf[1024];

  while (fgets(buf, sizeof(buf), f) != NULL){
    strtok(buf, " ");
    mkdir(buf,0777);
  }
  return 0;
}

int main(int argc, char const *argv[]) {

  FILE *f = NULL;
  char file_name[] = "estudiantes.txt";
  f = openFile(file_name);
  createDirectories(f);

	fclose (f);
  return 0;
}
