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

#endif //FALEH_BIBLIOGRAPHY_H
