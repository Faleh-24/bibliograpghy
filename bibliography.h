//
// Created by User on 02/07/2025.
//

#ifndef FALEH_BIBLIOGRAPHY_H
#define FALEH_BIBLIOGRAPHY_H

#define limit 100
#define LEN 500
typedef struct
{
    char material_type[LEN];
    char material_title[LEN];
    char material_author[LEN];
    int material_year;
}Data;




//functions
int readBiblioGraphyData( );
void getUserMenu();
void checkEntry(int userEntry);
void searchByTitle(char * chosenTitle);
void searchByAuthor(char * chosenAuthor);

#endif //FALEH_BIBLIOGRAPHY_H
