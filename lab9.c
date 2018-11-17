#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_QUESTIONS 11
#define CHARACTERS_IN_NAME 256
#define ERROR_INPUT 'e'
#define PRIME_PROGRAMMER "Trong Garson"

void display_startup_banner ();
int read_name_file(FILE *names_file, char name[CHARACTERS_IN_NAME],int *id);
int read_omr_file(FILE *omr_file, int *id, char answers[NUMBER_OF_QUESTIONS]);
double calculate_grades(char answers[NUMBER_OF_QUESTIONS], char answer_key[NUMBER_OF_QUESTIONS]);
void print_combined_file(FILE *combined_file, int id, char name[CHARACTERS_IN_NAME], char answers[NUMBER_OF_QUESTIONS], double grade);

int main ()
{
	display_startup_banner ();

	FILE *name_file = fopen("test_taker_names.txt","r");
	FILE *omr_file = fopen("newomr.txt","r");
	FILE *combined_file = fopen("full_data.csv","w");

	int student_id=0;
	char answer_key[NUMBER_OF_QUESTIONS]={0};
	char student_answers[NUMBER_OF_QUESTIONS]={0};
	char student_name[CHARACTERS_IN_NAME]={0};

	read_omr_file(omr_file,&student_id,answer_key);
	while(read_omr_file(omr_file,&student_id, student_answers)){
		read_name_file(name_file, student_name, &student_id);
		double grade=calculate_grades(student_answers,answer_key);
		print_combined_file(combined_file, student_id,student_name, student_answers, grade);
	}
}

/*
 * Function:	display_startup_banner
 * Description:	Prints out the programmer's name, date and time of compilation
 * Author:	Trong Garson
 * Date:	November 7, 2018
 * Input:	None
 * Output:	None
 * Globals:	prime_programmer, date and time
 * Returns:	None
 */
void display_startup_banner (){
	printf("MERGING OMR FORM AND STUDENT DATA PROGRAM WRITTEN IN C\n\n");
	printf("Program written by %s.\n", PRIME_PROGRAMMER);
	printf("Program compiled on %s at %s\n\n", __DATE__,__TIME__);

	return;
}

/*
 * Function:	read_name_file
 * Description:	reads the names from the file
 * Author:	Trong Garson
 * Date:	November 7, 2018
 * Input:	Names file
 * Output:	name, id
 * Globals:	CHARACTERS_IN_NAME
 * Returns:	1 for success, 0 for failure
 */


int read_name_file(FILE *names_file, char name[CHARACTERS_IN_NAME],int *id){
	fscanf(names_file, "%d", id);
	fgets(name, CHARACTERS_IN_NAME, names_file);
	int length = strlen(name);
	name[length - 1] = 0; // get rid of the newline character that fgets reads
	return 1;
}

/*
 * Function:	read_omr_file
 * Description:	reads the omr file
 * Author:	Trong Garson
 * Date:	November 7, 2018
 * Input:	omr_file
 * Output:	id, answers
 * Globals:	prime_programmer, date and time
 * Returns:	1 for success and 0 for failure
 */

int read_omr_file(FILE *omr_file, int *id, char answers[NUMBER_OF_QUESTIONS]){
	int read = fscanf(omr_file, "%d", id);
	if(read != 1) { return 0; } // if we failed to read an id, quit
	int i;
	for(i=0; i<NUMBER_OF_QUESTIONS; ++i){
		read = fscanf(omr_file, "%c", &answers[i]);
		if(read != 1) { return 0; }
	}
	return 1;
}

/*
 * Function:	calculate_grades
 * Description:	calculates the grades for the student
 * Author:	Trong Garson
 * Date:	November 7, 2018
 * Input:	answer, answer_key
 * Output:	None
 * Globals:	NUMBER_OF_QUESTIONS, ERROR_INPUT
 * Returns:	grades-percent correct
 */

double calculate_grades(char answers[NUMBER_OF_QUESTIONS], char answer_key[NUMBER_OF_QUESTIONS]){
	double correct = 0;
	int i;
	for(i = 0; i < NUMBER_OF_QUESTIONS; i++){
		if(answers[i] == ERROR_INPUT) {
			printf("Encountered an input error -- treating as correct\n");
			correct++;
		} else if (answers[i] == answer_key[i]) {
			correct++;
		}
	}

	return (100.0 * correct) / NUMBER_OF_QUESTIONS;
}

/*
 * Function:	print_combined_file
 * Description:	Prints out the combined file with the omr and the name file
 * Author:	Trong Garson
 * Date:	November 7, 2018
 * Input:	id, name, combined_file, answers
 * Output:	None
 * Globals:	CHARACTERS_IN_NAME, NUMBER_OF_QUESTIONS
 * Returns:	None
 */

void print_combined_file(FILE *combined_file, int id, char name[CHARACTERS_IN_NAME], char answers[NUMBER_OF_QUESTIONS], double grade){
	fprintf(combined_file, "%05d, ", id);
	fprintf(combined_file, "%s, ", name);
	int i;
	for(i = 0; i < NUMBER_OF_QUESTIONS; i++){
		fprintf(combined_file, "%c, ", answers[i]);
	}
	fprintf(combined_file, "%3.0lf%%\n", grade);
}



