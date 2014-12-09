

#include "wordstat.h"
#include "wordstat.c"



/* GLOBAL VARIABLE FOR MAIN FILE*/

    struct wordnode* pointer; /*POINTS TO WORD POS.*/
    struct wordnode* filePointer; /*POINTS TO WORD FILE POINTER.*/
    struct wordnode* word; /*STORES WORD*/
    struct wordnode* currentFile; /*Stores filename*/
    struct charnode* pos; /*POSITION IN TREE*/
    struct varnode* test; /* TEST VARIATION*/
    struct varnode* lag; /*SOMETIMES YOU NEED A LAG*/
    int i; /*COUNTER*/
    int j; /*COUNTER*/
    struct charnode* head;/*charnode type pointer to head*/
    FILE* thefile;/*file pointer to the file we want to open*/
    char c;/*This will be set to the characters we read in*/
    char *fileName; /*the file name we read in*/
    char *writeToFileName; /*The file name we write to*/
    DIR* dp; /*Directory pointer to traverse through*/
 	FILE* fp;/*File pointer fp */
 	int flag=0;/*Flag for the file*/

/* FUNCTIONS IN MAIN*/

 /*
PARAMETERS: 
	fileName = the name of the file passed in by dTraverse to read in and add to the tree
	head = A charnode pointer type to the head of the tree we want to add these words and filenames to

FUNCTION: Open a single file and read it in, tokenize it, create a wordnode of the character being read in
		  and compare it to all other words in the tree, if there isn't a match we insert this one into the tree
		  with a pointer to a var node which holds the name of the file this word was contained in. If there is a match
		  we do an iteration through the linked list of varnodes to go through the file names and if there is a match we
		  increment the count for this file it was found in, else we add this varnode as a new one to the end of the list
*/
int process(char* fileName, struct charnode *head);

 /*
PARAMETERS: 
	file = The name of the file we want to read or directory we want to crawl through and open all files within the direcotry

FUNCTION: Checks if input is with a dircectory or a file, if it is a file call the process functions and check for other files
or directories. If there are any files we process these before opening any subdirectories and processing the files contained in there
*/
void dTraverse(char* file );

/**************************************Function Implementation*******************************/

void dTraverse(char* file ){


	DIR * dir = opendir( file );
	if( !dir )	// if dir is not a valid directorery
	{
		// check if dirName is a file name.
		process(file, head);
		//fclose(file);
	}
	else{
		struct dirent *dptr;

		while( (dptr= readdir(dir)) )
		{
		if( !strcmp( dptr->d_name, "." ) || !strcmp( dptr->d_name, ".." ) )
				continue;

		size_t dirLen = strlen(file);
		char * location = malloc( dirLen + strlen(dptr->d_name) + 1 );	
		strncpy( location, file, dirLen );
			location[ dirLen ] = '/';
			location[ dirLen+1 ] =  '\0'; 
			strcat(location, dptr->d_name );
			 dTraverse(location);
			 free(location);
			 flag=1;

		}
}
}


int process (char* fileName, struct charnode *head){

    /*sets the file name*/
    fileName=fileName;

    /*BEFORE OPENING FILE, STORE CURRENT FILE NAME IN A WORD NODE*/
   
    if(fileName != NULL)
    {
    	currentFile = newwordnode();
    	filePointer = currentFile;
    	i=0;

    	while (fileName[i]!= 0)
    	{
    		if(i==39)
    		{
    			filePointer->next = newwordnode();
    		}
    		if(i == 40)
    		{
    			filePointer=filePointer->next;
    			i=0;
    		}
    		filePointer->word[i]=fileName[i];
    		i++;

    	}

    }

	thefile = fopen(fileName,"r");

	if (thefile == NULL)
	{
		fprintf (stderr, "CANNOT READ IN FILE, PLEASE CHECK NAME AND TRY AGAIN \n");
		fprintf (stderr, "%s\n", fileName);
		/*fprintf (stderr, "%s\n", argv[1]);*/
		return 0;
	}
	c=fgetc(thefile);
	/*Retreive File name and store in a wordnode*/
	while (c != EOF)
	{
		/*RETREIVE WORD*/
		if (isalpha(c)!=0)
		{
			word = newwordnode();
			pointer=word;
			i=0;
			while(isalnum(c)!=0)
			{
				if(i==39)
				{
					pointer->next = newwordnode();
				}
				if(i==40)
				{
					pointer=pointer->next;
					i=0;
				}
                pointer->word[i]=c;
                i++;
				c=fgetc(thefile);
			}

			/*ADDS WORD TO TREE*/
			c=word->word[0];
			pointer=word;
			pos=head;
			i=0;
			while (c!='\0')
			{
				if (pos->next==NULL)
				{
					pos->next=newnextarray();
				}
				if (isalpha(c)!=0)
				{
					if(pos->next->next[tolower(c)-'a']==NULL)
					{
						pos->next->next[tolower(c)-'a']=newcharnode();
					}
					pos = pos->next->next[tolower(c)-'a'];
				}
				if (isdigit(c)!=0)
				{
					if(pos->next->next[tolower(c)-'0'+26]==NULL)
					{
						pos->next->next[tolower(c)-'0'+26]=newcharnode();
					}
					pos = pos->next->next[tolower(c)-'0'+26];
				}
				i++;
				if(i==40)
				{
					i=0;
					pointer=pointer->next;
				}
				c=pointer->word[i];
			}
			pos->occurcount++;
			
			/* SEARCH AND CREATE VARIATIONS */
			if(pos->variations==NULL)
			{
				pos->variations=newvarnode();
				pos->variations->thisvar=word;
				pos->variations->next=newvarnode();
				pos->variations->next->thisvar=filePointer;
				pos->variations->next->fileOccurCount++;
				 
			}else
			{
				test=pos->variations->next;
				i=0;
				while(test != NULL)
				{
					lag=test;
					currentFile=test->thisvar;
					if(processStr(currentFile,filePointer)==1)
					{
						i=1;
						pos->variations->next->fileOccurCount++;
						
						break;
					}
					test=test->next;
				}
				if(i==0)
				{
					lag->next=newvarnode();
					lag->next->thisvar=filePointer;
					
				}
			}
		}
		c=fgetc(thefile);
	}
	/*EOF IN*/
	i=fclose(thefile);
	if (i!=0)
	{
		fprintf(stderr, "FILE CLOSE FAILURE");
	}


    
    
    return 0;
}
/******************************************MAIN************************************/

int main (int argc, char **argv)
{

    
   
	if (argc != 3)
	{
		fprintf (stderr, "THIS PROGRAM REQUIRES TWO ARGUMENTS. Please try again. Type -h for more information.\n");
		return 0;
	}
	/*If the -h option is used*/
	if (strcmp(argv[1], "-h") == 0)
	{
		fprintf (stdout, "\n When using indexer, follow the command with an arguement\nwhere the first argument is either the name of the file that you want to write your data to,\nWhen used with a valid file name or direcotry name for the second argument, \nall the unique words in the file in lexicographical order,\nalong with the total number of times each word appears in each file\nshould be printed to a file but\nI couldn't get it to print to a file so\n it just fucking prints on the screen\n thats all I got.Try it out!\n");
		return 0;
	}

	char *fileName =argv[2]; //directory or filename 
	
	head=newcharnode();
	dTraverse(fileName); //go through directories

	/*PRINT AND FREE */
	printResult(head);
	freecharnode(head);

	return 1;
}


