//
// Created by User on 02/07/2025.
//

#include "bibliography.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

Data biblio [limit];
int count;

int starts_with(const char *line, const char *prefix) {
    return strncmp(line, prefix, strlen(prefix)) == 0;
}

void trim(char *str) {
    // Remove leading and trailing whitespace
    char *end;
    while (isspace((unsigned char)*str)) str++;
    end = str + strlen(str) - 1;
    while (end > str && (isspace((unsigned char)*end) || *end == '}')) end--;
    *(end + 1) = '\0';
}

void extract_value(const char *line, char *dest, size_t size) {
    const char *start = strchr(line, '{');
    if (!start) {
        dest[0] = '\0';
        return;
    }
    start++;  // Move past '{'
    const char *end = strchr(start, '}');
    if (!end) end = start + strlen(start);  // In case of missing '}'

    size_t len = end - start;
    if (len >= size) len = size - 1;
    strncpy(dest, start, len);
    dest[len] = '\0';
}


int extract_year(const char *line) {
    char temp[LEN];
    extract_value(line, temp, LEN);
    return (int)strtol(temp, NULL, 10);
}

int readBiblioGraphyData( ) {
    FILE *file = fopen("bibliography.txt", "r");
    if (!file) {
        perror("File open failed");
        return 0;
    }

    char line[limit];
    int i = -1;

    while (fgets(line, sizeof(line), file)) {
        // Remove leading whitespace
        char *trimmed = line;
        while (isspace(*trimmed)) trimmed++;

        if (trimmed[0] == '@') {
            i++;
            if (i >= limit) break;
            sscanf(trimmed, "@%[^'{']", biblio[i].material_type);
            biblio[i].material_author[0] = '\0';
            biblio[i].material_title[0] = '\0';
            biblio[i].material_year = 0;
        } else if (strncmp(trimmed, "author", 6) == 0) {
            extract_value(trimmed, biblio[i].material_author, LEN);
        } else if (strncmp(trimmed, "title", 5) == 0) {
            extract_value(trimmed, biblio[i].material_title, LEN);
        } else if (strncmp(trimmed, "year", 4) == 0) {
            biblio[i].material_year = extract_year(trimmed);
        }
    }

    fclose(file);
    count = i + 1;
    return count;
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

void checkEntry(int userEntry) {
    switch (userEntry) {
        case 1:
            char userentry[LEN];
            printf("Enter the required title \n");
            fgetchar();
            scanf("%[^\n]", userentry);
            searchByTitle(userentry);
            break;
        case 2:

            printf("Search by required author \n");
            fgetchar();
            scanf("%[^\n]", userentry);
            searchByAuthor(userentry);
            break;
        case 3:
            printf("Search by title /n");
            break;
        case 4:
            printf("Search by title /n");
            break;
        case 5:
            printf("Search by title /n");
            break;
        case 6:
            printf("Search by title /n");
            break;
        case 7:
            printf("Search by title /n");
            break;
        case 8:
            printf("Search by title /n");
            break;
        case 9:
            printf("Search by title /n");
            break;
        case 10:
            printf("Search by title /n");
            break;
    }

}
void searchByTitle(char * chosenTitle)
{

    for(int i=0 ; i < count ; i++ )
    {
        if(strstr (biblio[i].material_title ,chosenTitle  )  )
        {
            printf("Title : %s , Author : %s , Type : %s , Year : %d ",
                   biblio[i].material_title ,biblio[i].material_author ,biblio[i].material_type ,biblio[i].material_year);
        }

    }
}


void searchByAuthor(char * chosenAuthor)
{
    for(int i=0 ; i < count ; i++ )
    {
        if(strstr (biblio[i].material_author ,chosenAuthor  )  )
        {
            printf("Title : %s , Author : %s , Type : %s , Year : %d ",
                   biblio[i].material_title ,biblio[i].material_author ,biblio[i].material_type ,biblio[i].material_year);
        }

    }
}


