#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue_utils.h"
#include <time.h>
#include <stdbool.h>

#include "utils.h"

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Program being used: %s", argv[0]);
        return 1;
    }

    char filename[MAX_LEN];
    strncpy(filename, argv[1], MAX_LEN - 1);
    filename[MAX_LEN - 1] = '\0';

    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open the file.");
        return 1;
    }

    monster_s *monsters = NULL;

    int result = load_monster_csv(&monsters, fp);
    if (result != 6)
    {
        printf("Error loading monsters from file '%s'\n", filename);
        fclose(fp);
        return 1;
    }

    printf("Monsters:\n");
    for (int i = 0; i < result; i++)
    {
        printf("(%d) %s\n", i + 1, monsters[i].name);
    }
    int choice;
    Node **head = NULL;
    Node **rear = NULL;

    monster_s **iniOrder = (monster_s **)malloc(result * sizeof(monster_s *));

    bool initiative_rolled = false; // Changed here
    do
    {
        printf("Select an option:\n");
        printf("1. Add monsters\n");
        printf("2. Roll initiative\n");
        printf("3. Next turn\n");
        printf("4. View current order\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice); 

        
        switch (choice) // Removed initiative_rolled from the switch statement
        {
        case 1:
            printf("Adding monsters...\n");
            add_monster(head, rear, result, monsters);

            printf("Monsters added successfully.\n");
            break;
        case 2:
         if (initiative_rolled) {
            printf("Initiative has already been rolled. Are you sure you want to roll again? (y/n)\n");
            char response;
            scanf(" %c", &response);
            if (response != 'y') {
                break;
            }
        } 
            roll_initiative(head, rear);
            initiative_rolled = true;
            printf("Initiative has been rolled.\n");
            break;

            case 3:
            if (!initiative_rolled) // Changed here
            {
                printf("Initiative has not been rolled yet.\n");
                break;
            }
            printf("Next up: ");
            peek(*head);
            break;
        case 4:
            printf("Current initiative order:\n");
            print_queue(*head, 0, INT_MAX); // Changed here
            printf("\n");
            break;

        case 5:
            free(monsters); // Changed here
            printf("Exiting program...\n");
            exit(0);
            break;
        default:
            printf("Invalid selection\n");
            break;
        }

    } while (choice != 5);

    fclose(fp);

    return 0;
}
