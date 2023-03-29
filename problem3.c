#include <stdio.h>
#include <stdlib.h>
#include "utils.h"




int main(int argc, char **argv) {
    if(argc != 2)
    {
         printf("Program being used: %s", argv[0]);
         return 1;
    }
  
    FILE *fptr;
    fptr = fopen(argv[1], "r");
    if(fptr == NULL)
    {
        printf("Could not open the file.");
        return 1;
    }

    monster_s *monsters = NULL; //dynamically allocating memory

    int num_monsters = load_monster_csv(&monsters,fptr); 
    
     print_monsters(monsters, num_monsters);

    //loading monsters from the csv file
    free(monsters);
    
    fclose(fptr);

    return 0;
}
