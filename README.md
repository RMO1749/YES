# CSE 1320 Assignment 3
Covers dynamic memory allocation, qsort, stacks, and queues.

## Problem 1

**Part 1**

Create a file named `problem1.c` with a comparison function `int compare_int(const void *elem1, const void *elem2);`
The comparison function, when used with `qsort`, should sort integers in ascending order with a slight twist: all odd numbers must come before any even number.

**Part 2**

In `main`, prompt the user to enter an integer representing the size of an array of integers. Allocate memory for the array and have the user enter the values for the array. Once the values are read, use `qsort` to sort the data using the comparison function you defined in part 1.

Print the values of the array before AND after the call to `qsort` in the format shown in the example run.

```
Enter the size of the array: 10
Enter 10 values: 10 2 3 8 5 9 1 4 7 6
10 2 3 8 5 9 1 4 7 6
1 3 5 7 9 2 4 6 8 10
```

## Problem 2

Create a new `monster_s` `struct` which contains the attributes of a monster.

```
typedef struct {
    char name[MAX_STR];
    char type[MAX_STR];
    int hp;
    int ac;
    int str;
    int dex;
    int con;
} monster_s;
```

Add this to `utils.h`.

**Part 1**

Modify the parameter list for `main` in `problem2.c` so that it accepts command line arguments. The program should accept a single argument: a file name for a CSV file. Your program should verify that the user entered the required number of command line arguments. Load the file with the given file name and verify that the file is open.

**Part 2**

Complete `load_monster_csv` in `utils.c` which accepts the following arguments:
- `monster_s **monsters` - a pointer-to-`monster_s`, this will be your array.
- `FILE *fp` - a file pointer referencing an open file of CSV data.

The function returns an `int` representing the number of monsters read from the file. The code in this function is only partially complete. Follow the comments to complete the function.

**Part 3**

Verify that your function works by printing out the monsters in the format used from assignment 1.

`"%s (%s), %d HP, %d AC, %d STR, %d DEX, %d CON\n"`

## Problem 3

Create a function `print_monsters` in `utils.c` which takes as input a pointer-to-`monster_s` and an `int` representing the number of monsters. Print the monster's data to `stdout` following the example run below. Don't forget to declare the function in `utils.h`. The function should display the data as seen below.

```
| NAME                 | TYPE     | HP  | AC | STR | DEX | CON |
| -------------------- | -------- | --- | -- | --- | --- | --- |
| Acolyte              | HUMANOID | 9   | 10 | 5   | 5   | 5   |
| Adult Black Dragon   | DRAGON   | 195 | 19 | 11  | 7   | 10  |
| Goblin               | HUMANOID | 7   | 15 | 4   | 7   | 5   |
| Gold Dragon Wyrmling | DRAGON   | 60  | 17 | 9   | 7   | 8   |
| Bearded Devil        | FIEND    | 52  | 13 | 8   | 7   | 7   |
| Rakshasa             | FIEND    | 110 | 16 | 7   | 8   | 9   |
```

The formatting is important here. The hyphens between the name and stats should be the same length as the string above it.

Write a program in a file named `problem4.c` that accepts a file name from the command line and attempts to open it. If it is successful, display the contents of each monster using `print_monster`.

**HINT:** You will need to loop through your data first and get the maximum length for each attribute. This will be simple for strings by using `strlen`. The `int` data will require a different approach. Math functions like `log10` will be useful here. Use sub-specifiers to control the length.

## Problem 4

Write a program that soirts monsters based on each of their properties, depending on the user's choice.

**Part 1**

Use `problem4.c` as a starting point to implement your program. Follow the `TODO`s so that the program accepts a file name from the command line and attempts to open it. If opened, parse the CSV data using `load_monster_csv`. You can assume that the user will give a valid CSV file (if the file exists). Your program should exit if the file does not exist.

**Part 2**

Implement 4 comparison functions that will sort the data that is loaded. For each one, call the sort and print the sorted data using `print_monsters`. These are organized in the `switch` statement in `problem5.c`. The comparisons should be implemented as follows:
1. Sort by name alphabetically.
2. Sort by HP from greatest to lowest (at the bottom).
3. Sort by AC from greatest to lowest (at the bottom).
4. Sort by stats from greatest to lowest (at the bottom). This is done by summing up `str`, `dex`, and `con` and using that value in your comparisons.

**When exiting the program, make sure you free all memory that was allocated!**

## Problem 5

In most table top RPG rule sets, combat order is managed by having all combatants roll to consider their position in the initiative order. Those with a higher roll will go before those with a lower roll.

Create a program with the following features

## Add Monster

Using the `monster_s` struct from problem 2, load the monsters from the CSV file into an array. Create a second dynamic array of pointers to `monster_s` that will be used to manage the initiative order.

Present the user with a list of monsters and allow them to select one to add to the initiative order. They should be able to add as many monsters as they want. If they select a monster that is already in the initiative order, print an error message and ask them to select another monster. Include an option to continue when they are done adding monsters.

**Example**
```
(1) Goblin
(2) Acolyte
(3) Adult Black Dragon
(4) Gold Dragon Wyrmling
(5) Bearded Devil
(6) Rakshasa
(C) Continue
```

**BONUS**

If there are more than 10 monsters, print the monsters in groups of 10. Include two prompts to allow the user to select between groups of monsters.

**Example**
```
(1) Goblin
(2) Acolyte
(3) Adult Black Dragon
(4) Gold Dragon Wyrmling
(5) Bearded Devil
(6) Rakshasa
(7) Adult Green Dragon
(8) Beholder
(9) Lich
(0) Cult Fanatic
(N) Next
(P) Previous
(C) Continue
```

Once the user has selected all of the monsters they want to add, print the current list.

## Roll Initiative

Use the list of monsters added from the first option to roll initiative for each monster. This will involve using the `rand` function to generate a random number between 1 and 20 for each monster.

Create a queue based on the rolls of each monster. The ordering is based on their roll. If two or more creatures roll the same value, you can choose the relative ordering.

If the user runs this command after already calculating initiative, warn the user that they are about to re-roll. If they confirm, roll initiative as normal. If they decline, go back to the main menu.

**Example**
```
1. Add Monsters
2. Roll Initiative
3. Next Turn
4. View Current Order
> 2
Goblin rolled a 20.
Adult Black Dragon rolled an 18.
Cult Fanatic rolled an 18.
Lich rolled a 17.
Beholder rolled a 12.
Rakshasa rolled a 9.
Bearded Devil rolled a 2.
```

## Next Turn

Option 3 will process a turn in the current ordering. This involves dequeuing the front of the queue and printing a message indicating who is going. Additionally, write a function named `peek` that looks at the next monster in the queue, **but does not remove them**. Use that to notify who is up next.

**Example**
```
1. Add Monsters
2. Roll Initiative
3. Next Turn
4. View Current Order
> 3
Goblin's Turn!
Cult Fanatic is next.
```

## View Current Order

Print the current ordering with the current monster at the top of the output. The original ordering number should be printed next to the monster's name.

**Example**
```
1. Add Monsters
2. Roll Initiative
3. Next Turn
4. View Current Order
> 4
3. Adult Black Dragon
4. Lich
5. Beholder
6. Rakshasa
7. Bearded Devil
1. Goblin
2. Cult Fanatic
```

## Requirements
- Each monster should be represented by a `struct` that is dynamically allocated.
- All logic for the main program should be in `monster_initiative.c`.
- Implement the menu as requested. It does not have to look exactly like the example run.
- Implement the 4 sub-items as defined above.
- All queue functions should be declared and defined in separate files. For example, they will be in `queue_utils.(c|h)`.
- Free all memory before exiting the program.