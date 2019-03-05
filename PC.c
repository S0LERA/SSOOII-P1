/******************************************************************
 * Projecto:                Primera Práctica de SSOO II
 *
 * Nombre del programa:     PA.c
 *
 * Autor:                   Pablo Rodríguez Solera
 *
 * Fecha de creación:       18/02/2019
 *
 * Proposito:               Crear los archivos de la nota del alumno.
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

int makeGrade(FILE *f){
  int avg_grade =0;
  int n_students=0;
  char buf[1024] = "";
  char *dni_token = "";
  char *exam_type_token = "";
  char *grade_token = "";
  int grade1 = 0;
  int grade_needed = 0;
  char buf2[1024];
  FILE *f2;
  while (fgets(buf, sizeof(buf), f)){
    dni_token = strtok(buf, " ");
    exam_type_token = strtok(NULL , " ");
    grade_token = strtok(NULL , " ");
    grade1 = atoi(grade_token);
    grade_needed = 10 - grade1;
    snprintf(buf2, sizeof buf2, "La nota que debes obtener en este nuevo examen para superar la prueba es %i.",grade_needed);
    strcat(dni_token,"/Nota.txt");
	  f2 = fopen(dni_token, "wb");
    fputs(buf2, f2);
    fclose(f2);
    avg_grade = avg_grade + grade1;
    n_students = n_students +1;
}
   avg_grade = avg_grade/n_students;
   return(avg_grade);
}

int main(int argc, char *argv[]) {

  FILE *f = NULL;
  char file_name[] = "estudiantes.txt";
  int avg_grade=0;
  char msg[1024];

  f = openFile(file_name);
  avg_grade = makeGrade(f);
  sprintf(msg,"%d",avg_grade);
  write(atoi(argv[1]),msg,strlen(msg)+1);
	fclose (f);
  return 0;
}
