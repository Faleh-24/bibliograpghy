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
    printf("\n");
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

            printf("Enter the required author \n");
            fgetchar();
            scanf("%[^\n]", userentry);
            searchByAuthor(userentry);
            break;
        case 3:
            int year;
            printf("Enter the required year \n");
            scanf("%d",&year);
            searchByYear(year);

            break;
        case 4:
            int year1;
            int year2;
            printf("Enter year1 \n");
            scanf("%d",&year1);
            printf("Enter year2 \n");
            scanf("%d",&year2);
            searchByRangeYear(year1,year2);
            break;
        case 5:
            get_entery_type();
            break;
        case 6:
            sort_Authors();
            break;
        case 7:
            detect_duplication();
            break;
        case 8:
            get_missing_info_from_entry();
            break;
        case 9:
            show_uwe_harvard_style();
            break;
        case 10:
            char typechoice [LEN];
            char authorchoice [LEN];
            char titlechoice [LEN];
            int yearchoice;
            printf("Enter type (inproceedings or techReport or article or  misc  \n");
            fgetchar();
            scanf("%[^\n]", typechoice);
            printf("Enter Author name \n");
            fgetchar();
            scanf("%[^\n]", authorchoice);
            printf("Enter Title of entry  \n");
            fgetchar();
            scanf("%[^\n]", titlechoice);
            printf("Enter year of enrty (0 if there is no year) ");
            scanf("%d",&yearchoice);

            add_bibliography(typechoice , titlechoice , authorchoice , yearchoice);
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


void searchByYear(int year)
{
    for(int i=0 ; i < count ; i++ )
    {
        if(biblio[i].material_year == year    )
        {
            printf("Title : %s , Author : %s , Type : %s , Year : %d "
                   ,
                   biblio[i].material_title ,biblio[i].material_author ,biblio[i].material_type ,biblio[i].material_year);
        }

    }
}
void searchByRangeYear(int year1,int year2)
{
    for(int i=0 ; i < count ; i++ )
    {
        if(biblio[i].material_year >= year1 && biblio[i].material_year <= year2  )
        {
            printf("Title : %s , Author : %s , Type : %s , Year : %d \n\n",
                   biblio[i].material_title ,biblio[i].material_author ,biblio[i].material_type ,biblio[i].material_year);
        }

    }




}

void get_entery_type()
{
    int inproceedings_count=0;
    int article_count=0;
    int misc_count=0;
    int techreport_count=0;
    for ( int i=0 ; i < count ; i++)
    {
       if ( strstr (biblio[i].material_type ,"inproceedings") )
       {
           inproceedings_count++;
       }
       else if ( strstr (biblio[i].material_type ,"article") )
       {
           article_count++;
       }
       else if ( strstr (biblio[i].material_type ,"misc") )
       {
           misc_count++;
       }
       else if ( strstr (biblio[i].material_type ,"techReport") )
       {
           techreport_count++;
       }

    }
    printf("Inproceedings : %d \n ",inproceedings_count);
    printf("Articles : %d \n ",article_count);
    printf("TechReport : %d \n ",techreport_count);
    printf("Misc : %d \n ",misc_count);


}

void detect_duplication()
{
    for ( int i=0 ; i <count-1 ; i++)
    {

        for (int j = i+1 ; j < count ; j++)
        {
            if (strstr(biblio[i].material_type , biblio[j].material_type ) &&
                    strstr(biblio[i].material_title , biblio[j].material_title ) &&
                            strstr(biblio[i].material_author , biblio[j].material_author) &&
                            biblio[i].material_year==biblio[j].material_year
                            )
            {

                printf("DUPLICATION FOUND \n Title : %s , Author : %s , Type : %s , Year : %d \n\n",
                       biblio[i].material_title ,biblio[i].material_author ,biblio[i].material_type ,biblio[i].material_year);
            }
        }
    }

}

void get_missing_info_from_entry()
{
  for(int i = 0 ; i < count ; i++)
  {
      if ( biblio[i].material_year <=0 )
      {
          printf("Missing year info for this entry : \n");
          printf("Title : %s , Author : %s , Type : %s , Year : %d \n\n",
                 biblio[i].material_title ,biblio[i].material_author ,biblio[i].material_type,biblio[i].material_year);
      }
      if ( biblio[i].material_author[0] == '\0' )
      {
          printf("Missing author info for this entry : \n");
          printf("Title : %s , Author : %s , Type : %s , Year : %d \n\n",
                 biblio[i].material_title ,biblio[i].material_author ,biblio[i].material_type,biblio[i].material_year);
      }
      if ( biblio[i].material_title[0] == '\0' )
      {
          printf("Missing title info for this entry : \n");
          printf("Title : %s , Author : %s , Type : %s , Year : %d \n\n",
                 biblio[i].material_title ,biblio[i].material_author ,biblio[i].material_type,biblio[i].material_year);
      }
      if ( biblio[i].material_type[0] == '\0' )
      {
          printf("Missing type info for this entry : \n");
          printf("Title : %s , Author : %s , Type : %s , Year : %d \n\n",
                 biblio[i].material_title ,biblio[i].material_author ,biblio[i].material_type,biblio[i].material_year);
      }

  }


}

void add_bibliography(char *type , char *title , char * author , int year)
{
    FILE *file = fopen("bibliography.txt", "a");
    if (!file) {
        perror("File open failed file is not exist");
        return ;
    }
    fprintf(file , "@%s{,\n",type);
    fprintf(file , "author = {%s},\n",author);
    fprintf(file , "title = {%s},\n",title);
    fprintf(file , "year = {%d}\n",year);
    fprintf(file , "}\n\n");
    fclose(file);
    printf("file updated successfully \n");

}

void show_uwe_harvard_style()
{
    int userentry;
    for(int i = 0 ; i < count ; i++)
    {
        printf("%d- %s \n",i,biblio[i].material_title);
    }
    printf("choose which title for you Harvard reference \n");
    scanf("%d",&userentry );
    if(userentry < 0 || userentry >=count)
    {
        printf("you have entered wrong number \n");

    }
    else
    {
        printf("\n %s. (%d) %s.\n",biblio[userentry].material_author,biblio[userentry].material_year,biblio[userentry].material_title);

    }

}
void sort_Authors() {
    Data copy [100];
    Data temp;

    for (int i = 0; i < count; i++) {
        copy[i] = biblio[i];
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(copy[j].material_author, copy[j + 1].material_author) > 0) {
                temp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = temp;
            }
        }
    }

    printf("Sorted Authors:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", copy[i].material_author);
    }
}