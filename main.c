#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include "Personas.h"

#define MAXPERSONAS 200
#define MAXCHAR 1000

const char* PERSON_FORMAT_OUT = "%s,%ld,%Lf\n";


void sort_words(Persona* personas, int count, char *);
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

        //unaPersona -> category = 0;  // agregamos una columna de ceros para un posterior ordenamiento

        personas[cont] = *unaPersona;
        cont++;
    }

    category(personas, cont, argv[2], fpin, argv[3]);

    fclose(fpin);
    return 0;
}


void category(Persona *personas, int cont, char* num_lista, FILE * fpin, char* arch_out) {
    //sort_words(personas, cont, arch_out);

    FILE* fpout;
    fpout = fopen(arch_out, "w+");
    if (fpout == NULL) perror("Opening file");
    int i = 5;

    while (i != 0) {
        for (int j = 0; j < cont; j++) {
            long int danger_category = personas[j].dangerCategory;
            if (danger_category == i) {
                fprintf(fpout, PERSON_FORMAT_OUT, personas[j].name, personas[j].dangerCategory, personas[j].attackProb);
            }
        }
        i--;
    }

    fclose(fpout);

    //long int danger_category;

    //for (int i = 0; i < cont; i++) {
        //if (personas[i].dangerCategory <= 2 && personas[i].attackProb == (long double) -1) {
        //    personas[i].category = 1;
        //    fprintf(fpout, PERSON_FORMAT_OUT, personas[i].name, personas[i].dangerCategory, personas[i].attackProb,
        //            personas[i].category);

    //    fprintf(fpout, PERSON_FORMAT_OUT, personas[i].name, personas[i].dangerCategory, personas[i].attackProb,
    //                personas[i].category);
    //}

}

void sort_words(Persona* personas, int count, char* arch_out) {
    FILE *fpout;
    fpout = fopen(arch_out, "w+");
    if (fpout == NULL) perror("Opening file");
    char temp[100];
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (strcmp(personas[i].name, personas[j].name) < 0) {

                strcpy(temp, personas[i].name);
                strcpy(personas[i].name, personas[j].name);
                strcpy(personas[j].name, temp);
            }
        }
    }
    for (int i = 0; i < count; i++) {
        fprintf(fpout, PERSON_FORMAT_OUT, personas[i].name, personas[i].dangerCategory, personas[i].attackProb);
    }
}

