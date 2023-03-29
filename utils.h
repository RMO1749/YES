#ifndef UTILS_H_
#define UTILS_H_
#include <stdio.h>

#define MAX_MONSTERS 32
#define MAX_LEN 128
#define MAX_STR 128

#define FILTER_NAME 1
#define FILTER_HP 2
#define FILTER_AC 3
#define FILTER_STATS 4
#define EXIT_CHOICE 5


typedef struct  {
    char name[MAX_STR];
    char type[MAX_STR];
    int hp;
    int ac;
    int str;
    int dex;
    int con;
    int initiative;
} monster_s;


void swap_int(int, int);
void trim(char *); 
int load_monster_csv(monster_s **, FILE *);
void print_monsters(monster_s *, int);

#endif
