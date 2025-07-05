//
// Created by User on 02/07/2025.
//

#ifndef FALEH_BIBLIOGRAPHY_H
#define FALEH_BIBLIOGRAPHY_H

#define limit 100
#define len 500
typedef struct
{
    char material_type[len];
    char material_title[len];
    char material_author[len];
    int material_year;
}Data;




//functions
void extractField(const char* line, char* output);
void readBiblioGraphyData();
void getUserMenu();
void checkEntry(int userEntry);
void searchByTitle(char * chosenTitle);

#endif //FALEH_BIBLIOGRAPHY_H
