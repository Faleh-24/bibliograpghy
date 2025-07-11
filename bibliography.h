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
void searchByYear(int year);
void searchByAuthor(char * chosenAuthor);
void searchByRangeYear(int year1,int year2);
void get_entery_type();
void detect_duplication();
void get_missing_info_from_entry();
void add_bibliography(char *type , char *title , char * author , int year);
#endif //FALEH_BIBLIOGRAPHY_H
