
#include "wordstat.h"



/*MAIN STRUCTURE*/
struct charnode{
	int occurcount;
	int varcount;
	struct varnode* variations;
	struct nextarray* next;
};

/*COMPARE*/
struct varnode{
	char fileName[40];
	int fileOccurCount;
	struct wordnode* thisvar;
	struct varnode* next;
};


/*STORES WORD*/
struct wordnode{
	char word[40];
	struct wordnode* next;

};

/*STORES WORD*/
struct nextarray{
	struct charnode* next[36];
};

/*CHECKS OCCURANCES OF WORDS*/
int processStr(struct wordnode* a, struct wordnode* b)
{
    int i;
    struct wordnode* pointera;
    struct wordnode* pointerb;
    i=0;
    pointera=a;
    pointerb=b;
    
	while( pointera->word[i] != '\0' || pointerb->word[i] != '\0')
	{
		if(i==40)
		{
			i=0;
			pointera=pointera->next;
			pointerb=pointerb->next;
		}
		if (pointera->word[i] != pointerb->word[i])
		{
			return 0;
		}
		i++;
	}
    return 1;
}

/*RECURSIVE TREE PRINT*/
void printResult(struct charnode* head)
{
    char c;
    char fc;
    int i;
    int f;
    int j;
    struct wordnode* pointer;
    struct wordnode* varpointer;
    struct varnode*	nextVarPointer;
 
    if(head==NULL)
	{
		return;
	}
	if(head->occurcount!=0)
	{
		/*Before anything print out list*/
		fprintf(stdout, "%s" , "<list> ");
		/*sets the wordnode type pointer to the beginning of the word*/
		pointer=head->variations->thisvar;
		/*sets the char c to the beginning of the word*/
		c=pointer->word[0];
		/*Sets counter to 0*/
		i=0;

		/*While the character is not a null character*/
		while (c!='\0')
		{
			/*print out that character*/
			fprintf(stdout, "%c" , tolower(c));
			/*increment counter*/
			i++;


			/*if counter is equal to 40*/
			if(i==40)
			{
				/*reset counter*/
				i=0;
				/*points to the next wordnode*/
				pointer=pointer->next;
			}
			/*set char c equal to the next char*/
			c=pointer->word[i];
		}

		fprintf(stdout, "\n");

		nextVarPointer=head->variations->next;

		while(nextVarPointer!=0)
		{
			varpointer=nextVarPointer->thisvar;
			fc=varpointer->word[0];
			j=0;

			while (fc!='\0')
			{
				fprintf(stdout, "%c", fc);
				j++;

			if(j==40)
			{
				j=0;
				varpointer=varpointer->next;
			}

			fc=varpointer->word[j];
		}
		fprintf(stdout, " %i ", nextVarPointer->fileOccurCount);
		nextVarPointer=nextVarPointer->next;
		}
        fprintf(stdout, "\n%s\n" , "</list>");

	}
	if (head->next != NULL)
	{
		for (i=0;i<36;i++)
		{
			f=i+26;
			if(f>35)
			{
				f=f-36;
			}
			
			if(head->next->next[f] != NULL)
			{	
				
				printResult(head->next->next[f]);
			}
		}
	}
    
}




struct charnode* newcharnode(){
	struct charnode* node = (struct charnode*)malloc(sizeof(struct charnode));
	if (node ==NULL)
	{
		fprintf (stderr, "out of memory");
	}
	memset(node, 0, sizeof(struct charnode));
    
	node->occurcount=0;
	node->varcount=0;
	node->variations=NULL;
	node->next=NULL;
    
    return node;
}

/*STORE VARIATIONS*/
struct varnode* newvarnode(){
	struct varnode* node = (struct varnode*)malloc(sizeof(struct varnode));
	if (node ==NULL)
	{
		fprintf (stderr, "out of memory");
	}
	memset(node, 0, sizeof(struct varnode));


    node->fileOccurCount=1;
	node->thisvar=NULL;
	node->next=NULL;
    
    return node;
}


struct nextarray* newnextarray(){
    int count;
	struct nextarray* array = (struct nextarray*)malloc(sizeof(struct nextarray));
	if (array ==NULL)
	{
		fprintf (stderr, "out of memory");
        
	}
	memset(array, 0, sizeof(struct nextarray));
    
	for(count=0;count<36;count++)
	{
		array->next[count]=NULL;
	}
    return array;
}


struct wordnode* newwordnode(){
    int count;
	struct wordnode* node = (struct wordnode*)malloc(sizeof(struct wordnode));
	if (node ==NULL)
	{
		fprintf (stderr, "out of memory");
	}
	memset(node, 0, sizeof(struct wordnode));
    
	node->next=NULL;
	for (count=0;count<40;count++)
	{
		node->word[count]='\0';
	}
    
    return node;
}

void freecharnode(struct charnode* current){
	if (current->variations != NULL)
	{
		freevarnode(current->variations);
	}
	if(current->next !=NULL)
	{
		freenextarray(current->next);
	}
    free(current);
}

void freevarnode(struct varnode* current){
	if(current->thisvar !=NULL)
	{
		freewordnode(current->thisvar);
	}
	if(current->next != NULL)
	{
		freevarnode(current->next);
	}
    free (current);
}

void freewordnode(struct wordnode* current){
	if(current->next!=NULL)
	{
		freewordnode(current->next);
	}
    free (current);
}

void freenextarray(struct nextarray* current){
    int i;
	if(current->next != NULL)
	{
		for(i=0;i<36;i++)
		{
			if(current->next[i]!=NULL)
			{
				freecharnode(current->next[i]);
			}
		}
	}
    free(current);
}












