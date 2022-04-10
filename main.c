#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include "Personas.h"

#define MAXPERSONAS 150

void category(Persona* personas, int cont, char *, FILE *, char *);

int main(int argc, char *argv[]) {
    FILE* fpin;
    fpin = fopen(argv[1], "r");
    if (fpin == NULL) return 1;

    char row[MAXPERSONAS];
    char *token;
    int cont = 0;

    // para sacar la primera línea
    fgets(row, MAXPERSONAS, fpin);
    Persona  *personas = (Persona *) malloc(sizeof(Persona));


    while (feof(fpin) != true) {
        fgets(row, MAXPERSONAS, fpin);
        Persona  *unaPersona = (Persona *) malloc(sizeof(Persona));

        // Para conseguir el nombre
        token = strtok(row, ",");
        strcpy(unaPersona -> name, token);

        // Para conseguir la categoría de peligrosidad
        token = strtok(NULL, ",");
        unaPersona -> dangerCategory = strtol(token, (char **) NULL, 0);

        // Para conseguir la probabilidad de ataque
        token = strtok(NULL, ",");
        token = strtok(token, "\n");
        if (token != NULL) {
            unaPersona -> attackProb = strtold(token, (char **) NULL);
        }
        else unaPersona -> attackProb = -1;  // asignamos un -1 para la gente que no tiene probabilidad de ataque para diferenciar

        personas[cont] = *unaPersona;
        cont++;
    }

    category(personas, cont, argv[2], fpin, argv[3]);


    fclose(fpin);
    return 0;
}


void category(Persona *personas, int cont, char* num_lista, FILE * fpin, char* arch_out) {

    FILE* fpout;
    fpout = fopen(arch_out, "w+");
    if (fpout == NULL) perror("Opening file");
    long int danger_category;


    for (int i = 0; i < cont; i++) {
        danger_category = personas[i].dangerCategory;

        }

    fclose(fpout);
}