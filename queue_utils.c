#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include "queue_utils.h"


void sort_queue(Node** head, Node** rear) {
    if (*head == NULL) {
        return;
    }

    int swapped;
    Node* ptr1 = *head;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (ptr1->data.initiative < ptr1->next->data.initiative) {
                monster_s temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void print_queues(Node** head) {
    Node* current = *head;

    while (current != NULL) {
        printf("%s (%d)\n", current->data.name, current->data.initiative);
        current = current->next;
    }
}

// Dequeue function
monster_s dequeue(Node **head, Node **rear) {
    monster_s val = (*rear)->data;
    if(*head == *rear) {
        free(*rear);
        *head = NULL;
        *rear = NULL;
    } else {
        Node *prev = (*rear)->prev;
        prev->next = NULL;
        free(*rear);
        *rear = prev;
    }
    return val;
}

void enqueue(monster_s data, Node** head, Node** rear) {
    Node *newNode = calloc(1, sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = *rear;
    if (*head == NULL) {
        *head = newNode;
    }
    else {
        (*rear)->next = newNode;
    }
    *rear = newNode;
}

void roll_initiative(Node** head, Node** rear) {
    // Check if there are monsters in the queue

    if (head == NULL) {
        printf("There are no monsters in the queue.\n");
        return;
    }
    
    // Check if initiative has already been rolled
    if (*head != NULL && (*head)->data.initiative != 0) {
        printf("Initiative has already been rolled. Do you want to reroll? (Y/N): ");
        char response;
        scanf(" %c", &response);
        if (response == 'N' || response == 'n') {
            return;
        }
    }
    
    // Roll initiative for each monster
    Node* curr = *head;
    while (curr != NULL) {
        curr->data.initiative = rand() % 20 + 1;
        curr = curr->next;
    }
    
    // Sort the queue based on the initiative rolls
    sort_queue(head, rear);
    
    // Print the new initiative order
    printf("Initiative rolled!\n");
    print_queues(head);
} 


void print_queue(Node* head, int min_hp, int max_hp) {
    if (head == NULL) {printf("what?");
        printf("\nQueue is empty!\n");
        return;
    }
    printf("\nQueue contains:\n");
    while (head != NULL) {
        if (head->data.hp >= min_hp && head->data.hp <= max_hp) {
            printf("Monster %s: HP %d\n", head->data.name, head->data.hp);
        }
        head = head->next;
    }
}

void peek(Node* head) {
    if (head == NULL) {
        printf("\nQueue is empty!\n");
        return;
    }
    printf("\nPeeked monster: %s\n", head->data.name);
}


void add_monster(Node **head, Node **rear, int result, monster_s *monsters) {
    int choice;
    printf("huh");
    char input[2];
    while (1) {
        printf("(C) Continue\n");
        printf("What monster do you want to add?\n Select corresponding number or enter 'C' to continue: \n");
        scanf("%s", input);

        if (strcmp(input, "C") == 0 || strcmp(input, "c") == 0) {
            break;
        }
    
        choice = atoi(input);

        if (choice < 1 || choice > result) {
            printf("Invalid selection. Please enter a number between 1 and %d or 'C' to continue.\n", result);
        } else {
            int alreadyChosen = 0;
            Node *curr = *head;
            while (curr != NULL) {
                if (curr->data.name == monsters[choice-1].name) {
                    alreadyChosen = 1;
                    break;
                }
                curr = curr->next;
            }
            if (alreadyChosen) {
                printf("Monster already chosen. Please select another monster.\n");
            } else {
                enqueue(monsters[choice-1], head, rear);
            }
        }
    }
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
