#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "queue_utils.h"




int main() {
    srand(time(NULL)); // seed random number generator

    init_queue(); // initialize the queue

    read_monsters_from_csv("monster.csv"); // read monster data from CSV file

    int choice;
    do {
        printf("Select an option:\n");
        printf("1. Add monsters\n");
        printf("2. Roll initiative\n");
        printf("3. Next turn\n");
        printf("4. View current order\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_monsters();
                break;
            case 2:
                roll_initiative();
                break;
            case 3:
                next_turn();
                break;
            case 4:
                view_current_order();
                break;
            case 5:
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 5);

    free_queue(); // free memory used by the queue

    return 0;
}

void add_monster(monster_s **iniOrder, int *iniNum, int result, monster_s *monsters) {
    int choice;
    char input[2]; // increase size to 2 to allow for null terminator
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
            for (int i = 0; i < *iniNum; i++) {
                if (iniOrder[i] == &monsters[choice - 1]) {
                    alreadyChosen = 1;
                    break;
                }
            }
            if (alreadyChosen) {
                printf("Monster already chosen. Please select another monster.\n");
            } else {
                iniOrder[*iniNum] = &monsters[choice - 1];
                (*iniNum)++;
            }
        }
    }
}
void roll_initiative() {
    // Check if initiative has already been rolled
    if (initiative_rolled()) {
        printf("Initiative has already been rolled. Roll again? (y/n): ");
        char answer;
        scanf(" %c", &answer);
        if (answer != 'y' && answer != 'Y') {
            return;
        }
    }

    // Roll initiative for each monster in the order
    monster_s* monster;
    while ((monster = dequeue()) != NULL) {
        int initiative = rand() % 20 + 1;
        printf("%s rolls %d for initiative.\n", monster->name, initiative);
        monster->dex = initiative;
        enqueue(monster);
    }
}


  
    monster_s **iniOrder = (monster_s **)malloc(result * sizeof(monster_s *));

    int iniNum = 0; // number of monsters selected by the use

    int choice;
    char input[2]; // increase size to 2 to allow for null terminator
    
    
    while (1)
    {
        printf("(C) Continue\n");
        printf("What monster do you want to add?\n Select corresponding number or enter 'C' to continue: \n");

        scanf("%s", input);

        if (strcmp(input, "C") == 0 || strcmp(input, "c") == 0)
        {
            break;
        }

        choice = atoi(input);

        if (choice < 1 || choice > result)
        {
            printf("Invalid selection. Please enter a number between 1 and %d or 'C' to continue.\n", result);
        }
        else
        {
            int alreadyChosen = 0;
            for (int i = 0; i < iniNum; i++)
            {
                if (iniOrder[i] == &monsters[choice - 1])
                {
                    alreadyChosen = 1;
                    break;
                }
            }
            if (alreadyChosen)
            {
                printf("Monster already chosen. Please select another monster.\n");
            }
            else
            {
                iniOrder[iniNum] = &monsters[choice - 1];
                iniNum++;
            }
        }
    }
    printf("Initiative Order:\n");
    for (int i = 0; i < iniNum; i++)
    {
        printf("%s\n", iniOrder[i]->name);
    }

    
    
    return 0;