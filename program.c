/* Emoticon message cleanser:
*
* 
*Code Written by
Kushal Jaiswal
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define STAGE_NUM_ONE 1							/* stage numbers */ 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5
#define STAGE_HEADER "Stage %d\n==========\n"	/* stage header format string */

#define MAX_MSG_LENGTH 280						/* maximum message length */
#define MAX_NUM_MSGS 100						/* maximum number of messages */
#define MAX_EMTCN_LENGTH 50						/* maximum emot. line length */
#define MAX_NUM_EMTCN 50						/* maximum number of emot. */

typedef char msg_t[MAX_MSG_LENGTH+1];			/* a message */
typedef char emtcn_t[MAX_EMTCN_LENGTH+1];		/* an emoticon */

/****************************************************************/

/* function prototypes */
void read_one_msg(msg_t one_msg, int max_len);
void print_stage_header(int stage_num);
int count_tokens(msg_t one_msg);
void stage_one(msg_t one_msg);
void stage_two(msg_t msgs[], int *num_msgs);
void stage_three(msg_t msgs[], int num_msgs);
void stage_four(emtcn_t emtcns[], int *num_emtcns);
void stage_five(msg_t msgs[], int num_msgs, emtcn_t emtcns[], int num_emtcns);

/* add your own function prototypes here */
int search(char *emoticon, emtcn_t emtcns[]);

/****************************************************************/

/* main function controls all the action, do NOT modify this function */

int
main(int argc, char *argv[]) {
	/* to hold all input messages */
	msg_t msgs[MAX_NUM_MSGS];	
	/* to hold the number of input messages */
	int num_msgs = 0;	
	/* to hold all input emoticons in the dictionary */
	emtcn_t emtcns[MAX_NUM_EMTCN];
	/* to hold the number of emoticons in the dictionary */
	int num_emtcns = 0;	
	
	/* stage 1: reading the first message */
	stage_one(msgs[num_msgs]); 
	num_msgs++;
	
	/* stage 2: removing alphanumeric characters */
	stage_two(msgs, &num_msgs);
	
	/* stage 3: removing extra commas */ 
	stage_three(msgs, num_msgs);
	
	/* stage 4: reading the dictionary and finding the longest emoticon */
	stage_four(emtcns, &num_emtcns);
	
	/* stage 5: removing invalid emoticons with the help of the dictionary */
	stage_five(msgs, num_msgs, emtcns, num_emtcns);
	
	/* all done; take some rest */
	return 0;
}

/* read a line of input into one_msg */

void
read_one_msg(msg_t one_msg, int max_len) { /* reads one line of the message */
	int i = 0, c;
	while (((c = getchar()) != EOF) && (c != '\n') && (c != '\r')) {
		if (i < max_len) {
			one_msg[i++] = c;
		} else {
			printf("Invalid input line, toooooooo long.\n");
			exit(EXIT_FAILURE);
		}
	}
	one_msg[i] = '\0'; /* null character put to terminate string */
}

/* print stage header given stage number */

void 
print_stage_header(int stage_num) {
	printf(STAGE_HEADER, stage_num);
}

/****************************************************************/

/* scan a message and count the number of tokens (separated by commas) in it */

int 
count_tokens(msg_t one_msg) {
	/* counts the number of tokens in the first message */
	int token = 0;
	int i = 0;
	while(one_msg[i] != '\0') {
		if(one_msg[i] == ',')
			token++;
		i++;
	}
	token += 1; /* tokens is 1 more than the total commas */
	return token;
}
/* function to check if the given emoticon is valid or not  */

int search( char *emoticon, emtcn_t emtcns[]) {
	for (int i = 0; i < 50; i++) {
		int j = 0;
		int x = 0;
		int count = 0;
		
		while(emoticon[x] != '\0') {  
			if(emtcns[i][j++] == emoticon[x]) { /* if the emoticon is in the 
                                                   dictionary */
             count++;
         }
         x++;
     }
        
        if (count == x) { /* if the number of characters in 
                             each match are the same */
           return 1;
        }	
    }
 	return 0;
}

/* stage 1: reading the first message */

void 
stage_one(msg_t one_msg) {
	/* add code for stage 1 */
	/* print stage header */
	print_stage_header(STAGE_NUM_ONE);
	
	/* read the first message */
	read_one_msg(one_msg, MAX_MSG_LENGTH);
	/* count and print the number of tokens */
	printf("Number of tokens: %d\n\n", count_tokens(one_msg));
}

/* stage 2: removing alphanumeric characters */

void 
stage_two(msg_t msgs[], int *num_msgs) {
	/* add code for stage 2 */
	/* print stage header */
	print_stage_header(STAGE_NUM_TWO);
	
	while(*num_msgs < MAX_NUM_MSGS) {
		/* reading each message */
		read_one_msg(msgs[*num_msgs], MAX_MSG_LENGTH);
		if( msgs[*num_msgs][0] == '#' && msgs[*num_msgs][1] == '#'
			&& msgs[*num_msgs][2] == '#' && msgs[*num_msgs][3] == '\0' ) {
			break;
		} /* check if the separating line is reached or not */
		else {
			*num_msgs += 1; /* the total number of lines in the message 
                               is passed*/ 
		}
	}
	
	if(*num_msgs == MAX_NUM_MSGS){ /* if the separating line is the last 
                                      line(#100) */
		msg_t dump; /* a temporary array is created storing 
                       the separating line */
		read_one_msg(dump, MAX_MSG_LENGTH);
	}
	
	for(int i = 0; i < *num_msgs; i++) {
		int a, b;
		a = 0;
		b = 0;
        
		while(msgs[i][a] != '\0') {
			char c = msgs[i][a++];
			if(isalnum(c) != 0) {
				continue;
			}
			else{
				msgs[i][b++] = c; /* refitting only the emoticons 
									 in the array */
			}
		}
        
		msgs[i][b] = '\0';
		printf("%s\n", msgs[i]);
	}
	printf("\n");
}

/* stage 3: removing extra commas */ 

void 
stage_three(msg_t msgs[], int num_msgs) {
	/* add code for stage 3 */
	/* print stage header */
	print_stage_header(STAGE_NUM_THREE);
	for(int i = 0; i < num_msgs; i++) {
		int updatedcolumn = 0;
		int length = strlen(msgs[i]); /* finding the total characters 
                                         in each line */
		
		for(int j = 0;j < length; j++) {
		
        if(j == 0 && msgs[i][j] == ',') { /* leading comma */
			continue;
		}
		else if(msgs[i][j] == ',' && msgs[i][j-1] == ',') { /* consecutive 
                                                               comma */
			continue;
		}
		else {
			int count = 0;
			for(int k = j+1; k < length ; k++) {
				if(msgs[i][k] != ',') {
					count++;
				}
			}
			
            if(msgs[i][j] == ',' && count == 0) {
                continue;
            }
            else {
                msgs[i][updatedcolumn++] = msgs[i][j];
            }
            }
        }
		
		msgs[i][updatedcolumn] = '\0';
		printf("%s\n", msgs[i]);
    }
    
	printf("\n");	
}

/* stage 4: reading the dictionary and finding the longest emoticon */ 

void stage_four(emtcn_t emtcns[], int *num_emtcns) {
	/* add code for stage 4 */
	/* print stage header */
	print_stage_header(STAGE_NUM_FOUR);
	
	while(*num_emtcns < MAX_NUM_EMTCN) {
		read_one_msg(emtcns[*num_emtcns], MAX_EMTCN_LENGTH); /* read each line 
																of emoticons */
		if(emtcns[*num_emtcns][0] == '\0') { /* reads till the end of 
                                                the text */
			break;*num_emtcns += 1;
		}
		else {
			*num_emtcns += 1;
        }
	}
	
	printf("Emoticon total: %d\n", *num_emtcns);
    
	int max = -1, index = 0; /* initialize max with -1 to find the longest
                                emoticon */
	
	for(int i = 0; i < *num_emtcns; i++) {
		int x = 0;
		/* finding length of emoticon */
		while(emtcns[i][x++] != ',');
		x--;
		if(x > max) {
			max = x;
			index = i; /* position of the longest emoticon */
		}
	}
	
	printf("Longest: ");
	int x = 0;
	
	while(emtcns[index][x] != ',') {
		printf("%c", emtcns[index][x]);
		x++;
	}
	
	printf("\n");
	printf("Length: %d\n", max);
	printf("\n");
}

/* stage 5: removing invalid emoticons with the help of the dictionary */

void
stage_five(msg_t msgs[], int num_msgs, emtcn_t emtcns[], int num_emtcns) {
     /* add code for stage 5  */
     /* print stage header */
     print_stage_header(STAGE_NUM_FIVE);
     for(int i = 0; i < num_emtcns; i++) {
     	 int old_col=0;
     	 int new_col=0;
     	 while(emtcns[i][old_col] != ',') { /* the array stores only the valid 
     	 	 								   emoticons now */
     	 	 emtcns[i][new_col]=emtcns[i][old_col];
     	 	 new_col++;
     	 	 old_col++;
     	 }
     	 emtcns[i][new_col] = '\0';
     }
     
     char emoticon[MAX_EMTCN_LENGTH];
     
     for(int i = 0; i < num_msgs; i++) {  
         int col, check, index, line_check;
         col = 0, check = 0, index = 0, line_check = 0;
         
         while(msgs[i][col] != '\0') {
             if (msgs[i][col] != ',') { /* puts each emoticon from msgs into a 
                                           new array */
                 emoticon[index++] = msgs[i][col];
                 col++;  
             }
             else {
             	 emoticon[index] = '\0'; /* terminating the array having the
                                            emoticon */
				 index = 0;
                 check = search(emoticon, emtcns);
                 
                 if (check == 1) { /* if emoticon is a valid one */
                     if(line_check == 0) { 
                     	 printf("%s", emoticon);
                     }
                     else {
                     	 printf(",%s", emoticon);  
                     }
                     line_check++;
                 }
                 else {
                 	 printf(","); /* if not a valid emoticon just put the 
                                     comma */
                 }
                 
                 col += 1;
                 continue;   
             }
         } 
         
     /* we do the last emoticon separately because at the end there is \0 so it 
     	does not enter the while loop */
	
	 emoticon[index] = '\0';
	 index = 0;
	 check = search(emoticon, emtcns);
     
	 if (check == 1) {
	 	 if(line_check == 0) {
              printf("%s", emoticon);
          }
          else {
              printf(",%s", emoticon); 	 
          }
          line_check++; 
	 }
	 else if(line_check != 0) { /* comma printed only if the line contains     
                                 atleast one valid emoticon and then invalids */
	 	 printf(",");
	 }
	 
     col += 1;
     
	 if(line_check != 0) { /* if the line just contains invalid emoticons or   
                              end of a valid line is reached */ 
	 	 printf("\n");
	 }
	}
}
	
	
	
	

     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
