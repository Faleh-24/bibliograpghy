//
// Created by User on 02/07/2025.
//

#include "bibliography.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Data biblio [limit];
int count;
void extractField(const char* line, char* output) {
    const char* open = strchr(line, '{');
    const char* close = strrchr(line, '}');

    if (open && close && close > open) {
        int length = close - open - 1;
        strncpy(output, open + 1, length);
        output[length] = '\0';
    } else {
        strcpy(output, "");
    }
}
void readBiblioGraphyData() {
    FILE* file = fopen("bibliography.txt", "r");
    if (!file) {

    }

    char line[len];
    char value[len];
    int stage = 0;

    while (fgets(line, sizeof(line), file)) {
        if (stage == 0) {
            extractField(line, value);
            strcpy(biblio[count].material_title, value);
        } else if (stage == 1) {
            extractField(line, value);
            strcpy(biblio[count].material_author, value);
        } else if (stage == 2) {
            extractField(line, value);
            biblio[count].material_year = atoi(value);
        } else if (stage == 3) {
            extractField(line, value);
            strcpy(biblio[count].material_type, value);
            count++;
        }

        stage = (stage + 1) % 4;
    }

    fclose(file);
    printf("file read succesfully .\n" );
}
