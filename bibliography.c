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

void getUserMenu()
{
    int userentry;

    printf("1- Search by title \n");
    printf("2- Search by Author \n");
    printf("3- Search by year \n");
    printf("4- Search by range of year \n");
    printf("5- print entry type   \n");
    printf("6- 0rganised alphabetically Authors on screen \n");
    printf("7- check duplicate entries  \n");
    printf("8- check missing information in an entry \n");
    printf("9- show UWE Harvard reference \n");
    printf("10- add bibliography entries  \n");
    printf("enter operation number from above (1 to 10 )\n");

    scanf("%d",&userentry);

    if (userentry <1 || userentry >10)
    {
        printf("Enter correct number");
    }
    else
    {
        checkEntry(userentry);
    }

}

void checkEntry(int userEntry)
{
    switch (userEntry) {
        case 1:
            char userentry[len];
            printf("Enter the required title");
            scanf("%s",userentry);
            searchByTitle(userentry);
        break;
        case 2: printf("Search by author pressed /n");
        break;
        case 3: printf("Search by title /n");
            break;
        case 4: printf("Search by title /n");
            break;
        case 5: printf("Search by title /n");
            break;
        case 6: printf("Search by title /n");
            break;
        case 7: printf("Search by title /n");
            break;
        case 8: printf("Search by title /n");
            break;
        case 9: printf("Search by title /n");
            break;
        case 10: printf("Search by title /n");
            break;
    }
}

void searchByTitle(char * chosenTitle)
{
    printf("You are searching for : %s" ,chosenTitle);
}
