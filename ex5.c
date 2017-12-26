/***************
*Student name: Gil Kagan
*Student ID: 315233221
*Course Exercise Group: 89110-06
Exercise name: ex5.c
****************/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// constants to present the maximum number of students and courses throughout the assignment.
#define MAX_STUDENTS 50
#define MAX_COURSES 5

int IndexToUpdate(char first[], char last[]);

void UpdateStudent(int studentIndex, char first[21], char last[21], char myCourses[MAX_COURSES][21],
                   int myGrades[MAX_COURSES]);

int ParseCourses(char myText[], char myCourses[MAX_COURSES][21], char myGrades[MAX_COURSES], int i);

int ParseCourse(char courseText[], char courseDest[], int *gradeDest);

int ParseString(char myText[], char name[], int i, char splitter);

int ParseStringWithSpaces(char myText[], char name[], int i, char splitter);

void MaxStudStats();

void AllStats();

void PrintMenu();

void PrintStatsMenu();

void UpsertStudent();

void DeleteStud();

void PrintMaxAverageGrade();

void PrintMaxMaxGrade();

void PrintMaxMinGrade();

void PrintMaxSumGrades();

void PrintMaxNumCourses();

void PrintAllAverageGrade();

void PrintAllSumGrades();

void PrintAllNumCourses();

void PrintAllMingrade();

void PrintAllMaxGrade();

// arrays for the assignment.
char firstName[MAX_STUDENTS][21] = {'\0'};
char lastName[MAX_STUDENTS][21] = {'\0'};
char courses[MAX_STUDENTS][MAX_COURSES][21] = {'\0'};
int grades[MAX_STUDENTS][MAX_COURSES] = {0};

int howManyStudents = 0;
int howManyCourses = 0;

// main function for the assignment
void main() {
    char dummy;
    // executes the menu function, to print the menu to the screen.
    PrintMenu();
    // loop to ask for operation from the user until he enters 0.
    while (1) {
        int op;
        // gets the operation from the user.
        scanf("%d", &op);
        // gets the \n.
        scanf("%c", &dummy);
        // each case is a different operation that the menu allowes the user to choose from.
        switch (op) {
            case 0:
                // Exit.
                return;
            case 1:
                if (howManyStudents > MAX_STUDENTS) {
                    printf("Error: there is no more space.\n");
                }
                UpsertStudent();
                break;
            case 2:
                DeleteStud();
                break;
            case 3:
                MaxStudStats();
                break;
            case 4:
                AllStats();
                break;
            case 5:
                PrintMenu();
                break;
            default:
                // in case the user input something that doesnt fit to the menu.
                printf("Error: unrecognized operation.\n");
                break;
        }
        printf("Select the next operation(insert 5 for complete menu).\n");
    }
}

/*
Function name: PrintMenu.
Input: no input.
Output: void - no output.
Function operation: this function prints to the screen the menu for the students grades management system.
*/
void PrintMenu() {
    printf("Please select the operation:\n");
    printf("	0. Exit.\n");
    printf("	1. Insert or update student grade.\n");
    printf("	2. Delete student information.\n");
    printf("	3. Print the student with maximal computed grade.\n");
    printf("	4. Print all the student with their computed grades.\n");
    printf("	5. Print the menu.\n");

}

/*
Function name: PrintStatsMenu.
Input: no input.
Output: no output.
Function operation: this function prints to the screen the aggregation mathods for operation 3 and 4 in the menu.
*/
void PrintStatsMenu() {
    printf("Please select the aggregation method:\n");
    printf("	a. Average grade.\n");
    printf("	b. Maximal grade.\n");
    printf("	c. Minimal grade.\n");
    printf("	d. Sum.\n");
    printf("	e. Count.\n");
    printf("	0. Return the main menu.\n");
}

/*
Function name: UpsertStudent.
Input : no input.
Output: no ouput.
Function operation:
*/
void UpsertStudent() {
    // helper arrays.
    char firstN[21] = {'\0'};
    char lastN[21] = {'\0'};
    char myCourses[5][21] = {'\0'};
    int myGrades[5] = {0};
    if (howManyStudents >= 50) {
        printf("Error: there is no more space.\n");
        return;
    }
    int currentIndex = 0;
    // array in size of 200, with one extra room for the \0.
    char input[201];
    fgets(input, 201, stdin);
    // goes over the spaces to get to the index where the letters starts.
    while (input[currentIndex] == ' ') {
        currentIndex++;
    }
    // the index in the array that the first name starts.
    currentIndex = ParseString(input, firstN, currentIndex, ' ');
    if (currentIndex == -1) {
        printf("Error: invalid name or grade.\n");
        return;
    }
    while (input[currentIndex] == ' ') {
        currentIndex++;
    }
    // increments the 'i' by 1 to flag the place where the last name starts in the input array-after the space between
    // the end of the first name to the last name.
    currentIndex = ParseStringWithSpaces(input, lastN, currentIndex, ':');
    if (currentIndex == -1) {
        printf("Error: invalid name or grade.\n");
        return;
    }
    //because we stop on ':'.
    currentIndex++;
    currentIndex = ParseCourses(input, courses, grades, currentIndex);
    if (currentIndex == -1) {
        printf("Error: invalid name or grade.\n");
        return;
    }
    // if all the actions succeded, it means the student added seccesfully.
    howManyStudents++;
    printf("Student %c%s %s%c added.\n", '"', firstN, lastN, '"');
}

/*
Function name: ParseString.
Input: array of chars, array of chars, int i (index), char splitter (index to stop).
Output: int (-1 or i- index).
Function operation: this function parses a string of several words, into an array the will hold one word.
the function will also check that the string is is valid- only letters.
if it the function founds that the string isnt valid, it will return -1 which will later be used to print out error.
if the string is over 20 chars, the function will return -1 aswell.
if everything is valid, the function will return the index of the splitter.
*/
int ParseString(char myText[], char name[], int i, char splitter) {
    int j = 0;
    // checks until the splitter sign.
    while (myText[i] != splitter) {
        // checks that the the input is valid - only letters.
        if ((myText[i] >= 'a' && myText[i] <= 'z') || (myText[i] >= 'A' && myText[i] <= 'Z')) {
            // if the string is valid, the function will put the string into a new array to be used later.
            name[j] = myText[i];
            i++;
            j++;
            if (j >= 21) {
                return -1;
            }
        } else {
            return -1;
        }
    }
    // returns index.
    return i;
}

/*
Function name: Parse StringWithSpaces.
Input: array of chars, array of chars, int index, char splitter (index to stop).
Output: int (-1 of index).
Function operation: this function parses a string with spaces into a different array to save it for later use.
the function will also check for the validity of the string- thats is not over 21 chars, and that is hold only
letters ans spaces and not other chars. if the string isnt valid, the function will return -1, which will be used
later to pribnt out error. if its all valid, the function will return the index of the splitter.
*/
int ParseStringWithSpaces(char myText[], char name[], int i, char splitter) {
    int j = 0;
    // the loop will exit when the index recheas the splitter.
    while (myText[i] != splitter) {
        // checks that the input is valid.
        if ((myText[i] >= 'a' && myText[i] <= 'z') || (myText[i] >= 'A' && myText[i] <= 'Z') || myText[i] == ' ') {
            // puts the string into a new array.
            name[j] = myText[i];
            i++;
            j++;
            if (j >= 21) {
                return -1;
            }
        } else {
            return -1;
        }
    }
    // returns the index of the splitter.
    return i;
}

/*
Function name: ParseCourse.
Input: array of chars to hold the array of course + grade, array of chars to hold the filtered course, int pointer
to place

*/
int ParseCourse(char courseText[], char courseDest[], int *gradeDest) {
    int currentIndex = 0;
    while (courseText[currentIndex] == ' ') {
        currentIndex++;
    }
    int nameStart = currentIndex;
    while (courseText[currentIndex] != ',' && courseText[currentIndex] != '\0') {
        // checks that the input is valid - only letters and spaces.
        if ((courseText[currentIndex] >= 'a' && courseText[currentIndex] <= 'z') ||
            (courseText[currentIndex] >= 'A' && courseText[currentIndex] <= 'Z') ||
            courseText[currentIndex] == ' ') {
            currentIndex++;
        } else {
            return -1;
        }
    }
    if (courseText[currentIndex] == ',') {
        currentIndex = ParseStringWithSpaces(courseText, courseDest, nameStart, ',');
        if (currentIndex == -1) {
            return -1;
        }
        currentIndex++;
        while (courseText[currentIndex] == ' ' && courseText[currentIndex] != '\0') {
            currentIndex++;
        }
        if (courseText[currentIndex] == '\0') {
            return -1;
        }
        int startGradeIndex = currentIndex;
        while (courseText[currentIndex] >= '0' && courseText[currentIndex] <= '9') {
            currentIndex++;
        }
        int endGradeIndex = currentIndex;
        int grade = 0;
        int length = endGradeIndex - startGradeIndex;
        for (int j = startGradeIndex; j < endGradeIndex; j++) {
            //converts to int value.
            grade *= 10;
            grade += (int) (courseText[j] - '0');
        }
        if (grade < 0 || grade > 100) {
            return -1;
        }
        gradeDest = &grade;
        while (courseText[currentIndex] == ' ' && courseText[currentIndex] != '\0') {
            currentIndex++;
        }
        if (courseText[currentIndex] != '\0') {
            return -1;
        }
    } else {
        return -1;
    }
    return currentIndex;
}


int ParseCourses(char myText[], char myCourses[MAX_COURSES][21], char myGrades[MAX_COURSES], int i) {
    int courseIndex = 0;
    while ((myText[i] != '\n') && (courseIndex < MAX_COURSES)) {
        char course[201] = {'\0'};
        int j = 0;
        while (myText[i] != ';') {
            // //checks that atleast one time there is a number for the grade, or letter for the course name.
            //if ((myText[i] >= 'a' && myText[i] <= 'z') ||
            //	(myText[i] >= 'a' && myText[i] <= 'z') ||
            //	(myText[i] == ' ') || (myText[i] == ',') || (myText[i] <= '9') || (myText[i] >= '0')){
            course[j] = myText[i];
            i++;
            j++;
            /*}
            else
            {
            return -1;
            }*/
        }
        int result = ParseCourse(course, myCourses[courseIndex], &myGrades[courseIndex]);
        if (result == -1) {
            return -1;
        }
        courseIndex++;
    }
    return i;
}


//updatestudent(studentindex, first, last, courses, grades);


int IndexToUpdate(char first[], char last[]) {
    for (int i = 0; i < howManyStudents; i++) {
        if ((strcmp(firstName[i], first) == 0) && (strcmp(lastName[i], last) == 0)) {
            // if the strings are equal, it means the new input is already a signed student,
            // so it will return the index of that student in the students list, to use if for update.
            return i;
        }
    }
}


void UpdateStudent(int studentIndex, char first[21], char last[21], char myCourses[MAX_COURSES][21],
                   int myGrades[MAX_COURSES]) {
    for (int i = 0; i < MAX_COURSES; i++) {
        int found = 0;
        for (int j = 0; j < MAX_COURSES; j++) {
            // check for similiar courses
            if (strcmp(courses[studentIndex], myCourses[j]) == 0) {
                grades[studentIndex][i] = myGrades[j];
                found = 1;
            }
        }
        if (found == 0) {
            int howManyCourses = 0;
            // checks how many courses the student have
            while ((courses[studentIndex][howManyCourses] != "") && (howManyCourses <= 5)) {
                howManyCourses++;
            }
            strcpy(courses[studentIndex][howManyCourses], myCourses[i]);
            strcpy(grades[studentIndex][howManyCourses], myGrades[i]);
        }
    }
    printf("Student %c%s %s%c updated.\n", '"', first, last, '"');
}

void DeleteStud() {
    char delInput[201];
    fgets(delInput, 201, stdin);
    char delFirstN[21] = {'\0'};
    char delLastN[21] = {'\0'};
    int i = 0;
    // flag
    int delIndex = -1;
    // goes over the spaces to get to the index where the letters starts.
    while (delInput[i] == ' ') {
        i++;
    }
    i = ParseString(delInput, delFirstN, i, ' ');
    if (i == -1) {
        printf("Error: invalid name.\n");
        return;
    }
    while (delInput[i] == ' ') {
        i++;
    }
    i = ParseStringWithSpaces(delInput, delLastN, i, '\n');
    if (i == -1) {
        printf("Error: invalid name.\n");
        return;
    }
    for (int k = 0; k < howManyStudents; k++) {
        // check if the student is in the array.
        if ((strcmp(firstName[k], delFirstN) == 0) && (strcmp(lastName[k], delLastN) == 0)) {
            delIndex = k;
        }
    }
    // if the value of delIndex didnt changed , then the student is not not in the array.
    if (delIndex == -1) {
        printf("Error: student name does not exist.\n");
        return;
    } else {
        // to delete the student from the array, we decrease the place of each student from the place that is after
        // the place of the student that we want to delete, by replacing the student that we want to delete from
        // the array with the student after him. in that way we can delete the student from the array.
        for (int j = delIndex; j < howManyStudents; j++) {
            firstName[j][21] = firstName[j + 1][21];
        }
        for (int j = delIndex; j < howManyStudents; j++) {
            lastName[j][21] = lastName[j + 1][21];
        }
        for (int j = delIndex; j < howManyStudents; j++) {
            for (int g = 0; g < howManyCourses; g++) {
                grades[j][g] = grades[j][g + 1];
            }
        }
        printf("Student %c%s %s%c deleted.\n", '"', firstName[delIndex], lastName[delIndex], '"');
    }
}

/*
Function name: MaxStudStats.
Input: no input.
Output: no output.
Function operation: this function prints the statistics menu for assignment 3, and asks the user for operation.
The function will print the student with the max calculated statistics from one of the following:
Average grade, max grade, min grade, sum of grades and number of courses.
*/
void MaxStudStats() {
    char secondOp;
    char dummy;
    // if there are no students in the list yet, the function will exit with error.
    if (howManyStudents == 0) {
        printf("Error: there are no students.\n");
        return;
    }
    // prints the stats menu.
    PrintStatsMenu();
    // gets the peration from the user.
    scanf("%c", &secondOp);
    // gets the \n.
    scanf("%c", &dummy);
    // switch case for the statistics menu.
    switch (secondOp) {
        case 'a':
            PrintMaxAverageGrade();
            break;
        case 'b':
            PrintMaxMaxGrade();
            break;
        case 'c':
            PrintMaxMinGrade();
            break;
        case 'd':
            PrintMaxSumGrades();
            break;
        case 'e':
            PrintMaxNumCourses();
            break;
        case '0':
            // exits.
            return;
            break;
    }
}// end of function.

/*
Function name: AllStats.
Input: no input.
Output: no output.
Function operation: Function operation: this function prints the statistics menu for assignment 4,
and asks the user for operation.
the function will print each student with the chosen statistic to be shown. the students will be printed out sorted
*/
void AllStats() {
    char secondOp;
    char dummy;
    // if there arent any students yet, the function will exit with error.
    if (howManyStudents == 0) {
        printf("Error: there are no students.\n");
        return;
    }
    PrintStatsMenu();
    // gets the operation from the user,
    scanf("%c", &secondOp);
    // gets the /n.
    scanf("%c", &dummy);
    switch (secondOp) {
        case 'a':
            PrintAllAverageGrade();
            break;
        case 'b':
            PrintAllMaxGrade();
            break;
        case 'c':
            PrintAllMingrade();
            break;
        case 'd':
            PrintAllSumGrades();
            break;
        case 'e':
            PrintAllNumCourses();
            break;
        case '0':
            // exit.
            return;
            break;
    }
}

void PrintMaxAverageGrade() {
    int count = 0;
    int maxAverage = 0;
    int studentIndex = 0;
    for (int i = 0; i < howManyStudents; i++) {
        int sum = 0;
        int average = 0;
        for (int j = 0; j < howManyCourses; j++) {
            sum += grades[i][j];
            count++;
        }
        average = sum / count;
        if (maxAverage < average) {/// need to fix this code
            // replace the current average with the average that is higher.
            maxAverage = average;
            // saves the tudent index with the max calculated average..
            studentIndex = i;
        } else if (maxAverage == average) {
            if (strcmp(firstName[i], firstName[studentIndex]) < 0) {
                studentIndex = i;
            }
        }
    }
    printf("%s %s, %d\n", firstName[studentIndex], lastName[studentIndex], maxAverage);
}

void PrintMaxMaxGrade() {
    int maxGrade = 0;
    int studentIndex = 0;
    int maxMax = 0;
    for (int i = 0; i < howManyStudents; i++) {
        for (int j = 0; j < howManyCourses; j++) {
            if (maxGrade < grades[i][j]) {
                maxGrade = grades[i][j];
            }
        }
        if (maxMax < maxGrade) {
            // replace the current max grade with the grade that is higher.
            maxMax = maxGrade;
            // saves the student index with the max calculated grade.
            studentIndex = i;
        } else if (maxMax == maxGrade) {
            if (strcmp(firstName[i], firstName[studentIndex]) < 0) {
                studentIndex = i;
            }
        }
    }
    printf("%s %s, %d\n", firstName[studentIndex], lastName[studentIndex], maxMax);
}

void PrintMaxMinGrade() {
    int maxMin = 100;
    int minGrade = 100;
    int studentIndex = 0;
    for (int i = 0; i < howManyStudents; i++) {
        for (int j = 0; j < howManyCourses; j++) {
            if (minGrade > grades[i][j]) {
                minGrade = grades[i][j];
            }
        }
        if (maxMin > minGrade) {
            maxMin = minGrade;
            studentIndex = i;
        } else if (maxMin == minGrade) {
            if (strcmp(firstName[i], firstName[studentIndex]) < 0) {
                studentIndex = i;
            }
        }
    }
    printf("%s %s, %d\n", firstName[studentIndex], lastName[studentIndex], maxMin);
}

void PrintMaxSumGrades() {
    int sum = 0;
    int studentIndex = 0;
    int maxSum = 0;
    for (int i = 0; i < howManyStudents; i++) {
        for (int j = 0; j < howManyCourses; j++) {
            sum += grades[i][j];
        }
        if (maxSum < sum) {
            maxSum = sum;
            studentIndex = i;
        } else if (maxSum == sum) {
            if (strcmp(firstName[i], firstName[studentIndex]) < 0) {
                studentIndex = i;
            }
        }
    }
    printf("%s %s, %d\n", firstName[studentIndex], lastName[studentIndex], maxSum);
}

void PrintMaxNumCourses() {
    int count = 0;
    int studentIndex = 0;
    int maxCount = 0;
    for (int i = 0; i < howManyStudents; i++) {
        for (int j = 0; j < howManyCourses; j++) {
            count++;
        }
        if (maxCount < count) {
            maxCount = count;
            studentIndex = i;
        } else if (maxCount == count) {
            if (strcmp(firstName[i], firstName[studentIndex]) < 0) {
                studentIndex = i;
            }
        }
    }
    printf("%s %s, %d\n", firstName[studentIndex], lastName[studentIndex], maxCount);
}

void PrintAllAverageGrade() {
    int count = 0;
    int sum = 0;
    int average = 0;
    for (int i = 0; i < howManyStudents; i++) {
        for (int j = 0; j < howManyCourses; j++) {
            sum += grades[i][j];
            count++;
        }
        average = sum / count;
        printf("%s %s, %d\n", firstName[i], lastName[i], average);
    }
}

void PrintAllSumGrades() {
    int sum = 0;
    for (int i = 0; i < howManyStudents; i++) {
        for (int j = 0; j < howManyCourses; j++) {
            sum += grades[i][j];
        }
        printf("%s %s, %d\n", firstName[i], lastName[i], sum);
    }
}

void PrintAllNumCourses() {
    int count = 0;
    for (int i = 0; i < howManyStudents; i++) {
        for (int j = 0; j < howManyCourses; j++) {
            count++;
        }
        printf("%s %s, %d\n", firstName[i], lastName[i], count);
    }
}

void PrintAllMingrade() {
    int minGrade = 100;
    for (int i = 0; i < howManyStudents; i++) {
        for (int j = 0; j < howManyCourses; j++) {
            if (minGrade > grades[i][j]) {
                minGrade = grades[i][j];
            }
            printf("%s %s, %d\n", firstName[i], lastName[i], minGrade);
        }
    }
}

void PrintAllMaxGrade() {
    int maxGrade = 0;
    for (int i = 0; i < howManyStudents; i++) {
        for (int j = 0; j < howManyCourses; j++) {
            if (maxGrade < grades[i][j]) {
                maxGrade = grades[i][j];
            }
            printf("%s %s, %d\n", firstName[i], lastName[i], maxGrade);
        }
    }
}

void Sort() {
    char temp[21] = {'\0'};
    for (int i = 0; i < howManyStudents - 1; i++) {
        for (int j = i + 1; j < howManyStudents; j++) {
            if (strcmp(firstName[i], firstName[j]) > 0) {
                strcpy(temp, firstName[i]);
                strcpy(firstName[i], firstName[j]);
                strcpy(firstName[j], temp);
            }
        }
    }
}









//void main_old() {
//	// executes the menu function, to print the menu to the screen.
//	int op;
//
//	PrintMenu();
//	char dummy;
//	// loop to ask for operation from the user until he enters 0.
//	do {
//		char secondOp;
//
//
//		scanf("%d", &op);
//		// each case is a different operation that the menu allowes the user to choose from.
//		switch (op) {
//		case 0:
//			break;
//		case 1:
//			UpsertStudent();
//			break;
//		case 2:
//			scanf("%c", &dummy);
//
//			DeleteStud();
//			break;
//		case 3:
//			if (howManyStudents == 0) {
//				printf("Error: there are no students.\n");
//				break;
//			}
//			else {
//				PrintStatsMenu();
//			}
//			scanf("%c", &secondOp);
//			scanf("%c", &dummy);
//			switch (secondOp) {
//			case 'a':
//				break;
//			case 'b':
//
//				break;
//			case 'c':
//
//				break;
//			case 'd':
//
//				break;
//			case 'e':
//
//				break;
//			case '0':
//				PrintMenu();
//				break;
//			}
//			break;
//		case 4:
//			if (howManyStudents == 0) {
//				printf("Error: there are no students.\n");
//				break;
//			}
//			else {
//				PrintStatsMenu();
//			}
//			scanf("%c", &secondOp);
//			scanf("%c", &dummy);
//			switch (secondOp) {
//			case 'a':
//				PrintAllAverageGrade();
//				break;
//			case 'b':
//				PrintAllMaxGrade();
//				break;
//			case 'c':
//				PrintAllMingrade();
//				break;
//			case 'd':
//				PrintAllSumGrade();
//				break;
//			case 'e':
//				PrintAllNumCourses();
//				break;
//			case '0':
//				PrintMenu();
//				break;
//			}
//			break;
//		case 5:
//			PrintMenu();
//			break;
//			// in case the user input something that doesnt fit to the menu.
//		default:
//			printf("Error: unrecognized operation.\n");
//			break;
//		}
//		printf("Select the next opertaion(insert 5 for complete menu).\n");
//	} while (op != 0);
//}

//currentIndex++;
//int startLastNameIndex = currentIndex;
//// the last name ends when the string reaches ':'.
//while (input[currentIndex] != ':') {
//	// checks that the input is valid - only letters and spaces.
//	if ((input[currentIndex] >= 'a' && input[currentIndex] <= 'z') || (input[currentIndex] >= 'A' && input[currentIndex] <= 'Z') || input[currentIndex] == ' ') {
//		currentIndex++;
//	}
//	else {
//		printf("Error: invalid name or grade.\n");
//		return;
//	}
//}
//// the index when the last name ends in the input array.
//int endLastNameIndex = currentIndex;
//int j = 0;
//// reinitialize  
//int length = endLastNameIndex - startLastNameIndex;
//// checks if the length is valid.
//if (length > 20) {
//	printf("Error: invalid name or grade.\n");
//	return;
//}
//// in case the length is valid.
//else {
//	// loop to place the string in the new array.
//	for (; startLastNameIndex <= endLastNameIndex; startLastNameIndex++) {
//		lastN[j] = input[startLastNameIndex];
//		j++;
//	}
//}
// the currnt i is one character before ':', so we need to get to the place in the input array that 
// is right after the ':' mark, where should be space.



//int startFirstNameIndex = i;
//while (input[i] != ' ') {
//	// checks that the the input is valid - only letters.
//	if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) {
//		i++;
//	}
//	else {
//		printf("Error: invalid name or grade.\n");
//		return;
//	}
//}
//// the index in the array that the first name ends.
//int endFirstNameIndex = i;
//// if the length of the string until the index when the first name ends is bigger then 20, 
//// then the input isnt valid.
//int length = endFirstNameIndex - startFirstNameIndex;
//if (length > 20) {
//	printf("Error: invalid name or grade.\n");
//	return;
//}
//// the input is valid.
//else {
//	int j = 0;
//	// this loop runs in the input array from the index in the array that the first name starts, until it ends
//	// and puts the chars in a new array to hold only the first name for later use.
//	for (; startFirstNameIndex <= endFirstNameIndex; startFirstNameIndex++) {
//		firstN[j] = input[startFirstNameIndex];
//		j++;
//	}
//}
//// increments to one place after the first name ends, where should be space.
//i++;
/*currentIndex = lastIndex;*/
// goes over the spaces to get to the index where the letters starts.



//int n = 0;
//int counterGrade = n;
//while ((input[currentIndex] != '\n') || howManyCourses <= 5) {
//	// goes over the spaces to get to the index where the letters starts.
//	if (input[currentIndex] == ' ') {
//		while (input[currentIndex] == ' ') {
//			currentIndex++;
//		}
//	}
//	currentIndex++;
//	// gets to the index where the name of the course starts.
//	currentIndex++;
//	int startCourseNameIndex = currentIndex;
//	while (input[currentIndex] != ',') {
//		// checks that the input is valid - only letters and spaces.
//		if ((input[currentIndex] >= 'a' && input[currentIndex] <= 'z') || (input[currentIndex] >= 'A' && input[currentIndex] <= 'Z') ||
//			input[currentIndex] == ' ') {
//			currentIndex++;
//		}
//		else {
//			printf("Error: invalid name or grade.\n");
//			return;
//		}
//	}
//	int endCourseNameIndex = currentIndex;
//	int j = 0;
//	// reinitialize to count 
//	int length = endCourseNameIndex - startCourseNameIndex;
//	if (length > 20) {
//		printf("Error: invalid name or grade.\n");
//		return;
//	}
//	for (; startCourseNameIndex <= endCourseNameIndex; startCourseNameIndex++) {
//		myCourses[n][j] = input[startCourseNameIndex];
//		j++;
//	}
//	n++;
//	// gets to the index where the grade should start.
//	currentIndex += 2;
//	if (input[currentIndex] == ' ') {
//		while (input[currentIndex] == ' ') {
//			currentIndex++;
//		}
//	}
//	int startGradeIndex = currentIndex;
//	// exits from loop when the index reaches ';'.
//	while (input[currentIndex] != ';') {
//		// checks if the input is valid.
//		if (input[currentIndex] < '0' || input[currentIndex] > '9' || input[currentIndex] == ' ') {
//			printf("Error: invalid name or grade.\n");
//			return;
//		}
//		// the input is valid.
//		else {
//			currentIndex++;
//		}
//	}
//	int endGradeIndex = currentIndex;
//	int grade = 0;
//	int length = endGradeIndex - startGradeIndex;
//	for (int j = 0; j <= length; j++) {
//		// converts to int value.
//		grade += (int)((input[currentIndex] - '0') *pow(10, length - j - 1));
//	}
//	// checks if the grade is valid (0-100).
//	if ((grade < 0) || (grade > 100)) {
//		printf("Error: invalid name or grade.\n");
//		return;
//	}
//	else {
//		// puts the grade in the array.
//		myGrades[n] = grade;
//		n++;