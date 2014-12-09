
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>




/*
PARAMETERS: VOID

RETURNS: Charnode Pointer

FUNCTION: Create new char node main structure to store wordnodes, varnodes, and newnextarray's
*/
struct charnode* newcharnode();
/*
PARAMETERS: VOID

RETURNS: Varnode Pointer

FUNCTION: Create new var node main structure to store wordnodes
*/
struct varnode* newvarnode();
/*
PARAMETERS: VOID

RETURNS: newnextarray pointer

FUNCTION: Create new nextarray structure node main structure to store an array of characters
*/
struct nextarray* newnextarray();
/*
PARAMETERS: VOID

RETURNS: wordnode pointer

FUNCTION: Create new char node main structure to store wordnodes
*/
struct wordnode* newwordnode();
/*
PARAMETERS: 
	head = Charnode head of the tree structure

RETURNS: Int

FUNCTION: Recursively print thorugh the binary tree structure the formated list of all words and files they occur in
*/
int process(char* fileName, struct charnode *head);
/*
PARAMETERS: 
	head = Charnode head of the tree structure

RETURNS: Void

FUNCTION: Recursively print thorugh the binary tree structure the formated list of all words and files they occur in
*/
void printResult(struct charnode* head);
/*
PARAMETERS: 
	a = Wordnode pointer to a word you want to compare to b
	b = Wordnode pointer to a word you want to compare to a

RETURNS: int indicator to if the nodes match or not

FUNCTION: Acts like the strcmp(), if the strings in the wordnodes do not match retun 0 else return 1
*/
int compare(struct wordnode* a, struct wordnode* b);
/*
PARAMETERS: 
	current= charnode pointer to the current charnode to free

RETURNS: Void

FUNCTION: Dynamically free memory

*********NOTE: WHEN USING MAIN THIS IS THE ONLY FUNCTION YOU NEED TO CALL TO FREE THE ENTIRE STRUCUTRE******
*/
void freecharnode(struct charnode* current);
/*
PARAMETERS: 
	current= varnode pointer to the current charnode to free

RETURNS: Void

FUNCTION: Dynamically free memory

*/
void freevarnode(struct varnode* current);
/*
PARAMETERS: 
	current= freevarnode pointer to the current charnode to free

RETURNS: Void

FUNCTION: Dynamically free memory
*/
void freewordnode(struct wordnode* current);
/*
PARAMETERS: 
	current= freenextarray pointer to the current charnode to free

RETURNS: Void

FUNCTION: Dynamically free memory
*/
void freenextarray(struct nextarray* current);

























