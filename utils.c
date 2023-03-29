#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "utils.h"

int get_digit_count(int val)

{
    return (int)log10(val) + 1;
}

void swap_int(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}

void trim(char *str)
{
    int l = strlen(str);
    if (str[l - 1] == '\n')
    {
        str[l - 1] = 0;
    }
}

void parse_monster(monster_s *monster, char *csv_line)
{
    char *token = strtok(csv_line, ",");

    int attr = 0;

    while (token)
    {
        switch (attr)
        {
        case 0:
            strcpy(monster->name, token);
            break;
        case 1:
            strcpy(monster->type, token);
            break;
        case 2:
            monster->hp = atoi(token);
            break;
        case 3:
            monster->ac = atoi(token);
            break;
        case 4:
            monster->str = atoi(token);
            break;
        case 5:
            monster->dex = atoi(token);
            break;
        case 6:
            monster->con = atoi(token);
            break;
        }
        attr++;
        token = strtok(NULL, ",");
    }
}

/*
 * Loads all monsters from a CSV file into memory.
 * Allocates memory pointed to by `*monsters_ptr`
 *
 * Args
 * ----
 *  monster_s **monsters_ptr - A double pointer to `monster_s`.
 *      Dereferencing this once (`*monsters_ptr`) returns the value to where the
 *      allocated memory should be stored. That is, you should assign the result
 *      of an allocation call to `*monsters_ptr`.
 *
 *  FILE *fp - A file pointer representing an open CSV file.
 *
 * Return
 * ------
 *  Returns an `int` representing the number of monsters loaded.
 */

int load_monster_csv(monster_s **monsters_ptr, FILE *fp)
{
    char buffer[MAX_LEN] = {0};
    int num_read = 0;

    while (fgets(buffer, MAX_LEN, fp))
    {

        trim(buffer);

        monster_s *monster = malloc(sizeof(monster_s));

        // Parse the CSV line and store the data into the new monster entry
        parse_monster(monster, buffer);

        *monsters_ptr = realloc(*monsters_ptr, (num_read + 1) * sizeof(monster_s));
        // reallocates the memory for the monsters array to support one more entry
        // adds the new monster structure to the end of the monsters array by assigning the value of monster to the next element of the array
        (*monsters_ptr)[num_read] = *monster;
        num_read++;
        free(monster);
        // Complete the function by parsing the csv line and storing the data into each monster_s entry.
        // For each item, you will need to reallocate the data to support 1 more.
    }

    

    return num_read;
}

void print_monsters(monster_s *monsters, int num_monsters)
{
    int max_name = 0, max_type = 0, max_hp = 0, max_ac = 0, max_str = 0, max_dex = 0, max_con = 0;
    
    
    for (int i = 0; i < num_monsters; i++)
    { 
        int len_name = strlen(monsters[i].name);
        int len_type = strlen(monsters[i].type);
        int len_hp = get_digit_count(monsters[i].hp);
        int len_ac = get_digit_count(monsters[i].ac);
        int len_str = get_digit_count(monsters[i].str);
        int len_dex = get_digit_count(monsters[i].dex);
        int len_con = get_digit_count(monsters[i].con);

        if (len_name > max_name)
            max_name = len_name;
        if (len_type > max_type)
            max_type = len_type;
        if (len_hp > max_hp)
            max_hp = len_hp;
        if (len_ac > max_ac)
            max_ac = len_ac;
        if (len_str > max_str)
            max_str = len_str;
        if (len_dex > max_dex)
            max_dex = len_dex;
        if (len_con > max_con)
            max_con = len_con;
            
    }
    printf("| %-*s | %-*s | %*s | %-*s | %-*s | %-*s | %-*s |\n", max_name, "NAME", max_type, "TYPE", max_hp, "HP",
               max_ac, "AC", max_str, "STR", max_dex, "DEX", max_con, "CON");

    printf("| %.*s | %.*s | %.*s | %.*s | %.*s | %.*s | %.*s |\n",
           max_name + 2, "--------------------",
           max_type+ 2, "--------",
           max_hp + 2, "---",
           max_ac + 2, "--",
           max_str + 2, "---",
           max_dex + 2, "---",
           max_con + 2, "---");
    
    for (int i = 0; i < num_monsters; i++)
    {  
        printf("| %-*s | %-*s | %*d | %*d | %*d | %*d | %*d |\n", max_name, monsters[i].name, max_type, monsters[i].type, max_hp, monsters[i].hp,
               max_ac, monsters[i].ac, max_str+1, monsters[i].str, max_dex+2, monsters[i].dex, max_con+1, monsters[i].con);
    }
}