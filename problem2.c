#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Program being used: %s", argv[0]);
        return 1;
    }

    FILE *fptr;
    fptr = fopen(argv[1], "r");
    if (fptr == NULL)
    {
        printf("Could not open the file.");
        return 1;
    }

    monster_s *monsters = NULL; // dynamically allocating memory

    int num_monsters = load_monster_csv(&monsters, fptr);

    for (int i = 0; i < num_monsters; i++)
    {
        printf("%s (%s), %d HP, %d AC, %d STR, %d DEX, %d CON\n", monsters[i].name, monsters[i].type, monsters[i].hp, monsters[i].ac, monsters[i].str, monsters[i].dex, monsters[i].con);
    }

    // loading monsters from the csv file
    free(monsters);

    fclose(fptr);

    // TODO: Verify command line arguments.
    // TODO: Attempt to open a CSV file given by the command line arguments.
    // TODO: Load all the data with `load_monsters_csv`.
    // TODO: Print the data to verify that it was loaded.
    // TODO: Be sure to free any allocated memory.......

    return 0;
}
