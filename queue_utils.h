#ifndef QUEUE_UTILS_H_
#define QUEUE_UTILS_H


#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define MAX_MONSTERS 32
#define MAX_LEN 128
#define MAX_STR 128



typedef struct node Node;
    struct node {
        monster_s data;
        Node *prev;
        Node *next;
    };

monster_s dequeue(Node **, Node **);
int load_monster_csv(monster_s **, FILE *);
void enqueue(monster_s , Node **, Node **);
void print_queue(Node *, int, int);
void peek(Node *);
void add_monster(Node **, Node **, int , monster_s *);
void roll_initiative(Node ** , Node **);


#endif 
