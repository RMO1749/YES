#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"

int comp_name(const void *a, const void *b)
{
    monster_s *typea = (monster_s *)a;
    monster_s *typeb = (monster_s *)b;
    return strcmp(typea->name, typeb->name);
}
int comp_hp(const void *a, const void *b)
{
    monster_s *typea = (monster_s *)a;
    monster_s *typeb = (monster_s *)b;

    if (typea->hp < typeb->hp)
    {
        return 1;
    }
    else if (typea->hp > typeb->hp)
    {
        return -1;
    }
    else if ( typea->hp == typeb->hp)
    {
        return 0;
    }
}int comp_ac(const void *a, const void *b)
{
    monster_s *typea = (monster_s *)a;
    monster_s *typeb = (monster_s *)b;

    if (typea->ac < typeb->ac)
    {
        return 1;
    }
    else if (typea->ac > typeb->ac)
    {
        return -1;
    }
    else if ( typea->ac == typeb->ac)
    {
        return 0;
    }
}
int comp_stat(const void *a, const void *b)
{
    monster_s *ma = (monster_s *)a;
    monster_s *mb = (monster_s *)b;

    int sum_a = ma->str + ma->dex + ma->con;
    int sum_b = mb->str + mb->dex + mb->con;

    if (sum_a < sum_b)
    {
        return 1;
    }
    else if (sum_a > sum_b)
    {
        return -1;
    }
    else if ( sum_a == sum_b)
    {
        return 0;
    }
}


void show_menu()
{
    printf("--------------------------\n");
    printf("|      MONSTER LIST      |\n");
    printf("--------------------------\n");
    printf("| 1. Filter by name      |\n");
    printf("| 2. Filter by HP        |\n");
    printf("| 3. Filter by AC        |\n");
    printf("| 4. Filter by stats     |\n");
    printf("| 5. Exit                |\n");
    printf("--------------------------\n");
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Program being used: %s", argv[0]);
        return 1;
    }

    char filename[MAX_LEN];
    strncpy(filename, argv[1], MAX_LEN - 1); // adding the "-1" to max_len here so we do not cpy actual stirng itself.
    filename[MAX_LEN - 1] = '\0';            // for handling file correctly, we need to include the null pointer to terminate the program.

    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open the file.");
        return 1;
    }

    monster_s *monsters = NULL;
    int result = load_monster_csv(&monsters, fp);
    if (result != 6) // I changed this to 6 becausd there are 6 monsters.
    {
        printf("Error loading monsters from file '%s'\n", filename);
        fclose(fp);
        return 1;
    }
    

    // Run menu loop
    int choice = 0;
    while (choice != EXIT_CHOICE)
    {
        show_menu();
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            qsort(monsters, result, sizeof(monster_s), comp_name);
            print_monsters(monsters, result);
            // TODO: Implement name filtering
            // TODO: Filter by name and print
            break;
        case 2:
            qsort(monsters, result, sizeof(monster_s), comp_hp);
            print_monsters(monsters, result); // TODO: Implement HP filtering
            // TODO: Filter by HP and print
            break;
        case 3:
            qsort(monsters, result, sizeof(monster_s), comp_ac);
            print_monsters(monsters, result); // TODO: Implement AC filtering
            // TODO: Filter by AC and print
            break;
        case 4:
            qsort(monsters, result, sizeof(monster_s), comp_stat);
            print_monsters(monsters, result);// TODO: Implement stats filtering
            // TODO: Filter by stats and print
            break;
        case 5:
            if (fp)
            {
                fclose(fp);
            }
            break;
        }
    }
    free(monsters);

    return 0;
}
