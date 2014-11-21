#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MAX_MEM_POOL = 428;
char* memoryPool = NULL;
char* currentStartAddr = 0;

void error_message(){
    printf("\nError: Incorrect input argument.\n\nUsage: <this executable> <printable ASCII string>\n\n");
}

char* getBuffer(int size){
    if(memoryPool == NULL){
        memoryPool = (char*)malloc(sizeof(char)*MAX_MEM_POOL);
        currentStartAddr = memoryPool;
    }
    if(currentStartAddr >= memoryPool+MAX_MEM_POOL){
        printf("\nError: Local memory pool overflow.");
    }
    char* retAddr = currentStartAddr;
    currentStartAddr = currentStartAddr + size;
    return retAddr;
}

void ascii_helper(char* username)
{
	int i;
	for(i = 0; i < strlen(username); i++)
	{
//		printf("%d", (int)username[i]);
		if(	((int)username[i] > 126) || ((int)username[i] < 32))
		{
			error_message();
			exit(0);
		}	 
	}
}

void declare_variable(char **inputName, char **destName, char **titleString, char **destTitleString, char *username){
    *inputName = getBuffer(10);
    printf("argv_decVar = %s\n", username);
	
	if((strlen(username) > 10) || (strlen(username) < 1) )						//added this
	{
		error_message();
		exit(0);
	}	
	
	ascii_helper(username);
	strncpy(*inputName, username, 10);											//added this
    *destName = getBuffer(10);
    *titleString = getBuffer(16);
    *destTitleString = getBuffer(16);
}

void name_relocate(char *inputName, char *destName){
    strncpy(destName, inputName, 10); 
}

void title_relocate(char *titleString, char *destTitleString){
    titleString = "Your Name =";
    strncpy(destTitleString, titleString, 10);
}

void data_relocate(char *inputName, char *destName, char *titleString, char *destTitleString){
    name_relocate(inputName, destName);
    title_relocate(titleString,destTitleString);
}

void print_data(char *destName, char *destTitleString){
    printf("\n\n%s",destTitleString);
    printf("%s", destName);
    printf("\n\n");
}

char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        error_message();
        exit(0);
    }

    char *inputName;
    char *destName;
    char *titleString;
    char *destTitleString;

//    for(int i = 1; i < argc; i++)
//    {
//    	argv[1] = argv[i]
//    }
	int i = 1;
    char* agv1 = argv[i];
	char* agv2 = argv[i+1];
    char* s = concat(agv1, agv2);
    printf("argv_main = %s\n", s);

    declare_variable(&inputName, &destName, &titleString, &destTitleString, /*argv[1]*/ s);
    data_relocate(inputName, destName, titleString, destTitleString);    
    print_data(destName, destTitleString);

	free(s);//deallocate the string
    return 0;
}
