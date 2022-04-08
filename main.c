#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include "Personas.h"

#define MAXCHAR 150

int main(int argc, char *argv[]) {
    FILE* fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        return 1;
    }

    char row[MAXCHAR];
    char *token;
    int cont = 0;

    // para sacar la primera línea
    fgets(row, MAXCHAR, fp);
    Persona  *personas = (Persona *) malloc(sizeof(Persona));


    while (feof(fp) != true) {
        fgets(row, MAXCHAR, fp);

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
        else unaPersona -> attackProb = 0;


        personas[cont] = *unaPersona;
        cont++;
    }

    printf("%s", personas[5].name);

    return 0;
}
