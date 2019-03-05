/******************************************************************
 * Projecto:                Primera Práctica de SSOO II
 *
 * Nombre del programa:     PA.c
 *
 * Autor:                   Pablo Rodríguez Solera
 *
 * Fecha de creación:       18/02/2019
 *
 * Proposito:               Limpiar directorio.
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

int removeDirectories(FILE *f){
  char *dni_token = "";
  char buf[1024];
  char command[1024];
  while (fgets(buf, sizeof(buf), f) != NULL){
    dni_token=strtok(buf, " ");
    snprintf(command, sizeof command, "rm -r %s",dni_token);
    if(system(command) == -1){
      fprintf(stderr,"Error al eliminar el directorio del alumno: %s\n",dni_token);
    }
  }
  return 0;
}

int main(int argc, char const *argv[]) {

  FILE *f = NULL;
  char file_name[] = "estudiantes.txt";
  f = openFile(file_name);
  removeDirectories(f);

	fclose (f);
  return 0;
}
