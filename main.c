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

int ParseCourses(char myText[], char myCourses[MAX_COURSES][21], int myGrades[MAX_COURSES], int i);

int ParseCourse(char courseText[], char courseDest[], int *gradeDest);

int ParseString(char myText[], char name[], int i, char splitter);

int ParseStringWithSpaces(char myText[], char name[], int i, char splitter);

void MaxStudStats();

void AllStats();

void PrintMenu();

void PrintStatsMenu();

void ParseTextAndUpsert();

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
                break;
            case 1:
                if (howManyStudents > MAX_STUDENTS) {
                    printf("Error: there is no more space.\n");
                }
                ParseTextAndUpsert();
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
Function name: ParseTextAndUosert
Input : no input.
Output: no ouput.
Function operation: this function calls the help of other function to parse the input text into different arrays.
after the text is parsed the function will call other functions to check if the student already exists.
if the student exists, then he will be updated. if he is new, he will be inserted.
*/
void ParseTextAndUpsert() {
    // helper arrays.
    char firstN[21] = {'\0'};
    char lastN[21] = {'\0'};
    char myCourses[5][21] = {'\0'};
    int myGrades[5] = {0};
    // if the students array is full.
    if (howManyStudents >= MAX_STUDENTS) {
        printf("Error: there is no more space.\n");
        return;
    }
    int currentIndex = 0;
    // array in size of 200, with one extra room for the \0.
    char input[201];
    // gets the text from the user.
    fgets(input, 201, stdin);
    // goes over the spaces to get to the index where the letters starts.
    while (input[currentIndex] == ' ') {
        currentIndex++;
    }
    // activates the ParseString function. the function will return the index in the array that the first name starts
    // if the input is valid, else it will return -1, which will indicate to print out error.
    currentIndex = ParseString(input, firstN, currentIndex, ' ');
    if (currentIndex == -1) {
        printf("Error: invalid name or grade.\n");
        return;
    }
    // ignores the spaces before the last name.
    while (input[currentIndex] == ' ') {
        currentIndex++;
    }
    // activates the ParseStringWithSpaces function. the function will return the index in the array
    // that the last name ends which is ':' if the input is valid, else it will return -1,
    // which will indicate to print out error.
    currentIndex = ParseStringWithSpaces(input, lastN, currentIndex, ':');
    if (currentIndex == -1) {
        printf("Error: invalid name or grade.\n");
        return;
    }
    // because we stop on ':'.
    currentIndex++;
    // activates the ParseCourses function. if the function returns -1, it means the input is not valid,
    // error will be printed to the screen.
    currentIndex = ParseCourses(input, myCourses, myGrades, currentIndex);
    if (currentIndex == -1) {
        printf("Error: invalid name or grade.\n");
        return;
    }
    // activates the IndexToUpdate function, which returns index or -1.
    int index = IndexToUpdate(firstN[21], lastN[21]);
    if (index != -1) {
        UpdateStudent(index, firstN[21], lastN[21], myCourses[MAX_COURSES][21],
                      myGrades[MAX_COURSES]);
    } else {
        printf("Student %c%s %s%c added.\n", '"', firstN, lastN, '"');
    }
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
            // checks if the string is over 20 chars.
            if (j >= 21) {
                return -1;
            }
        }
            // if the string conatins other chars then letters.
        else {
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
            // checks if the string is over 20 chars.
            if (j >= 21) {
                return -1;
            }
        }
            // if the input is invalid (other chars then letters or spaces).
        else {
            return -1;
        }
    }
    // returns the index of the splitter.
    return i;
}

/*
Function name: ParseCourse.
Input: array of chars to hold the array of course name, array of chars to hold the filtered course,
int pointer for the grade.
Output: int(-1 or index).
Function operation: this function parses the course to an array that will hold his name, and to an array that will
hold his grade. the function will validate the courseText, be checking that the name consists only letters and spaces,
and the grade consists only digits, and is in range of 0-100. if the function founds that the courseText isn't valid,
it will return -1 which will be later used to print out error.
*/
int ParseCourse(char courseText[], char courseDest[], int *gradeDest) {
    int flagForCourseName = 0;
    int currentIndex = 0;
    // ignores the spaces before the course name.
    while (courseText[currentIndex] == ' ') {
        currentIndex++;
    }
    // index to the place in the courseText where the course name starts
    int nameStart = currentIndex;
    // checks that until the splitter ',' the course name consists only letters and spaces.
    while (courseText[currentIndex] != ',') {
        if ((courseText[currentIndex] >= 'a' && courseText[currentIndex] <= 'z') ||
            (courseText[currentIndex] >= 'A' && courseText[currentIndex] <= 'Z') ||
            courseText[currentIndex] == ' ') {
        } else {
            return -1;
        }
        // checks for atleast one letter.
        if ((courseText[currentIndex] >= 'a' && courseText[currentIndex] <= 'z') ||
            (courseText[currentIndex] >= 'A' && courseText[currentIndex] <= 'Z')) {
            // changes the value of the flag if it found atleast ont letter.
            flagForCourseName = 1;
        }
        // increments the index until the splitter.
        currentIndex++;
    }
    // if the value of the flag didnt change to 1, it means there are no letters in the course name-invalid input.
    if (flagForCourseName == 0) {
        return -1;
    }
    // activates the ParseStringWithSpaces function. if the input is valid, the function will return the undex
    // that it stoped on. else it will return -1, which will be used to print out error.
    currentIndex = ParseStringWithSpaces(courseText, courseDest, nameStart, ',');
    if (currentIndex == -1) {
        return -1;
    }
    // because it stops on ','.
    currentIndex++;
    // ignores spaces before the grade.
    while (courseText[currentIndex] == ' ') {
        currentIndex++;
    }
    // it means that there are no digits in the grade, so the input is invalid.
    if (courseText[currentIndex] == ';') {
        return -1;
    }
    // indicate the place where the grade starts.
    int startGradeIndex = currentIndex;
    // goes the array until it gets something that is different then a digit.
    while (courseText[currentIndex] >= '0' && courseText[currentIndex] <= '9') {
        currentIndex++;
    }
    // indicate where the grade ends.
    int endGradeIndex = currentIndex;
    int grade = 0;
    // goes over the digits and places the value in the grade vriable.
    for (int j = startGradeIndex; j < endGradeIndex; j++) {
        //converts to int value.
        grade *= 10;
        grade += (int) (courseText[j] - '0');
    }
    // checks that the grade is in range.
    if (grade < 0 || grade > 100) {
        return -1;
    }
    // places the grade in the the place where the *gradeDest points to.
    *gradeDest = grade;
    // because it stops on ';'
    currentIndex++;
    return currentIndex;
}


/*
Function name: ParseCourses.
Input: array of chars which will hold the course + grade text, array of chars which will hold
the extraced courses names, and array of ints which wiill hold the grades of the courses.
Output: int (-1 or index);
Function operaation: this function will parse the user input into a text that will hold only the courses and
their grades. then the function will call the ParseCourse function, so eventully we will get the courses
seperated from the grades, and will be placed in the helper arrays in the ParseTextAndUpsert function.
*/
int ParseCourses(char myText[], char myCourses[MAX_COURSES][21], int myGrades[MAX_COURSES], int i) {
    int courseIndex = 0;
    // in case the user enters '\n' after the ':'.
    if (myText[i] == '\n') {
        return -1;
    }
    // check until the user input \n or that there are over 5 courses.
    while ((myText[i] != '\n') && (courseIndex < MAX_COURSES)) {
        // new array to hold the course + grade text.
        char course[201] = {'\0'};
        int j = 0;
        // goes over the the user input from the index the function recieved, which is the index where the course
        // name starts, and places it in the course array.
        while (myText[i] != ';') {
            course[j] = myText[i];
            i++;
            j++;
            // in case the user didnt enter the ';' at the end.
            if (myText[i] == '\0') {
                return -1;
            }
        }
        // activated the ParseCourse function and places the result in the "result" variable.
        int result = ParseCourse(course, myCourses[courseIndex], &myGrades[courseIndex]);
        // if ParseCourse returned -1, then the input isnt valid and error will be printed.
        if (result == -1) {
            return -1;
        }
        // if after all the stages the function didnt exit, it means one course added.
        courseIndex++;
        i++;
    }
    return i;
}

/*
Function name: IndexToUpdate.
Input: array of chars to hold first name, array of chars to hold last name.
Output: int-index.
Function operation: this function recieves student's first and last name, and will check if that student is already
listed. if the student is listed the function will return the index of that student in the first and last names
arrays to use it for update, else the function will return 0 to use it later to insert the new student.
*/
int IndexToUpdate(char first[], char last[]) {
    // goes over the students.
    for (int i = 0; i < howManyStudents; i++) {
        // checks if the student already exists.
        if ((strcmp(firstName[i], first) == 0) && (strcmp(lastName[i], last) == 0)) {
            // returns index of the student if he exitst.
            return i;
        }
    }
    // if the student doesnt exist.
    return -1;
}

/*
Function name: UpdateStudent.
Input: int-index of the student, array of chars to hold first name, array of chars to hold last name,
2d array of chars to hold the courses names, and array of int's to hold the courses grades.
Output: no output.
Function operation:

*/
void UpdateStudent(int studentIndex, char first[21], char last[21], char myCourses[MAX_COURSES][21],
                   int myGrades[MAX_COURSES]) {
    // goes over the student courses.
    for (int i = 0; i < MAX_COURSES; i++) {
        // flag.
        int found = 0;
        for (int j = 0; j < MAX_COURSES; j++) {
            // check for similiar courses
            if (strcmp(courses[studentIndex][MAX_COURSES][21], myCourses[j][21]) == 0) {
                // updates the grade of the similar course.
                strcpy(grades[studentIndex][i], myGrades[j]);
                // if the course is already exist, then the flag value will change.
                found = 1;
            }
        }
        // if the course is not in the courses list of the students.
        if (found == 0) {
            int howManyCourses = 0;
            // checks how many courses the student have
            while ((courses[studentIndex][howManyCourses] != "") && (howManyCourses <= 5)) {
                howManyCourses++;
            }
            strcpy(courses[studentIndex][howManyCourses][21], myCourses[i]);
            strcpy(grades[studentIndex][howManyCourses], myGrades[i]);
        }
    }
    printf("Student %c%s %s%c updated.\n", '"', first, last, '"');
}

void InsertStud(int numberOfStud, char) {

}

/*
Function name: DeleteStud.
Input: none.
Output: none.
Function operation: this function gets from the user a student name that he wish to delete.
the function will call other function to extract the first and last name, and will go over the students list
and will delete the student by moving the entire list of students and their courses until the desired student will
be out of the list.
*/
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
            for (int g = 0; g < MAX_COURSES; g++) {
                while (g != '\0') {
                    grades[j][g] = grades[j][g + 1];
                }
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
    // gets the operation from the user.
    scanf("%c", &secondOp);
    // gets the \n.
    scanf("%c", &dummy);
    // switch case for the statistics menu.
    switch (secondOp) {
        // prints the student with the max average grade.
        case 'a':
            PrintMaxAverageGrade();
            break;
            // prints the student with the max grade.
        case 'b':
            PrintMaxMaxGrade();
            break;
            // prints the student with the max calculated min grade.
        case 'c':
            PrintMaxMinGrade();
            break;
            // prints the student with the max sum of grades.
        case 'd':
            PrintMaxSumGrades();
            break;
            // prints the student with the max number of courses.
        case 'e':
            PrintMaxNumCourses();
            break;
            // exits.
        case '0':
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
the function will print each student with the chosen statistic to be shown. the students will be printed out sorted.
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
        // print all students with their average grade.
        case 'a':
            PrintAllAverageGrade();
            break;
            // prints all students with their max grade.
        case 'b':
            PrintAllMaxGrade();
            break;
            // prints all students with thier min grade.
        case 'c':
            PrintAllMingrade();
            break;
            // prints all students with thier sum of grades.
        case 'd':
            PrintAllSumGrades();
            break;
            // prints all students with thier number of courses.
        case 'e':
            PrintAllNumCourses();
            break;
        case '0':
            // exits.
            return;
            break;
    }
}

/*
Function name: PrintMaxAverageGrade.
Input: none.
Output: none.
Function operation: this function prints the students with the max calculated average grade.
the function will go over the list of students and thier courses, and will calcule each student average grade.
then the function will compare the average grades sof the students, and will print the one with the higest average.
*/
void PrintMaxAverageGrade() {
    int count = 0;
    // initialzing variable to the minimum.
    int maxAverage = 0;
    int studentIndex = 0;
    // goes over the list of students.
    for (int i = 0; i < howManyStudents; i++) {
        int sum = 0;
        int average = 0;
        // goes over the list of courses for each student.
        for (int j = 0; j < MAX_COURSES; j++) {
            while (j != '\0') {
                // summing the courses grades.
                sum += grades[i][j];
                // counting the courses.
                count++;
            }
        }
        average = sum / count;
        if (maxAverage < average) {
            // replace the current average with the average that is higher.
            maxAverage = average;
            // saves the student index with the max calculated average..
            studentIndex = i;
        }
            // if there are 2 students with the same average grade, then the student that comes first in the lexcography
            // order will be saved.
        else if (maxAverage == average) {
            // checks the first names.
            if (strcmp(firstName[i], firstName[studentIndex]) < 0) {
                studentIndex = i;
            }
                // if the sudents also have the same first names, then we will check their last names.
            else if (strcmp(firstName[i], firstName[studentIndex]) == 0) {
                if (strcmp(lastName[i], lastName[studentIndex]) < 0) {
                    studentIndex = i;
                }
            }
        }
    }
    printf("%s %s, %d\n", firstName[studentIndex], lastName[studentIndex], maxAverage);
}

/*
Function name: PrintMaxMaxGrade.
Input: none.
Output: none.
Function operation: this function goes over the list of students and thier courses, and will print the student
with the higest grade in one course.
*/
void PrintMaxMaxGrade() {
    int maxGrade = 0;
    int studentIndex = 0;
    // initializing variable to the minimum.
    int maxMax = 0;
    // goes over the list of students.
    for (int i = 0; i < howManyStudents; i++) {
        // goes over thte list of the students courses.
        for (int j = 0; j < MAX_COURSES; j++) {
            while (j != '\0') {
                // compare the students max grade.
                if (maxGrade < grades[i][j]) {
                    // places the new max grade in the maxGrade variable.
                    maxGrade = grades[i][j];
                }
            }
        }
        // compare to see which grade is higher.
        if (maxMax < maxGrade) {
            // replace the current max grade with the grade that is higher.
            maxMax = maxGrade;
            // saves the student index with the max calculated grade.
            studentIndex = i;
        }
            // if two students have the same highest grade, then the student that comes first in lexicographic order
            // in the first names, will be printed.
        else if (maxMax == maxGrade) {
            if (strcmp(firstName[i], firstName[studentIndex]) < 0) {
                studentIndex = i;
            }
                // if the sudents also have the same first names, then we will check their last names.
            else if (strcmp(firstName[i], firstName[studentIndex]) == 0) {
                if (strcmp(lastName[i], lastName[studentIndex]) < 0) {
                    studentIndex = i;
                }
            }
        }
    }
    printf("%s %s, %d\n", firstName[studentIndex], lastName[studentIndex], maxMax);
}

/*
Function name: PrintMaxMinGrade.
Input: none.
Output: none.
Function operation: this function goes over the students list and thier courses, and will print the student
with the max calculated min grade.
*/
void PrintMaxMinGrade() {
    // initialize to the min amount.
    int maxMin = 0;
    // initialize to the max amount.
    int minGrade = 100;
    int studentIndex = 0;
    // goes over the students list.
    for (int i = 0; i < howManyStudents; i++) {
        // goes over the students courses.
        for (int j = 0; j < MAX_COURSES; j++) {
            while (j != '\0') {
                // compare the min grades.
                if (minGrade > grades[i][j]) {
                    // if the students grade is lower then the minGrade variable, then the minGrade will be reinitialize.
                    minGrade = grades[i][j];
                }
            }
        }
        // checks if the current student min grade is higher then the former min grade.
        if (maxMin < minGrade) {
            // reinitialize the msxMin variable to the new max calculated min grade.
            maxMin = minGrade;
            // saves the student index.
            studentIndex = i;
        }
            // if two students have the same min grade, then the student that comes first in lexicographic order
            // in the first names, will be printed.
        else if (maxMin == minGrade) {
            if (strcmp(firstName[i], firstName[studentIndex]) < 0) {
                studentIndex = i;
            }
                // if the sudents also have the same first names, then we will check their last names.
            else if (strcmp(lastName[i], lastName[studentIndex]) < 0) {
                studentIndex = i;
            }
        }
    }
    printf("%s %s, %d\n", firstName[studentIndex], lastName[studentIndex], maxMin);
}

/*
Function name: PrintMaxSumGrades.
Input: none.
Output: none.
Function operation: this funciton goes over the list of students and thier courses, and will print the student
with the maximum sum of grades.
*/
void PrintMaxSumGrades() {
    // initialize to the minimum.
    int sum = 0;
    int maxSum = 0;
    int studentIndex = 0;
    // goes over the students.
    for (int i = 0; i < howManyStudents; i++) {
        // goes over the courses.
        for (int j = 0; j < MAX_COURSES; j++) {
            while (j != '\0') {
                // summing the grades of the student.
                sum += grades[i][j];
            }
        }
        // compares the highes sum so far with the current sum.
        if (maxSum < sum) {
            // if the current sum is higher, then the maxSum variable will be reinitialize to the current sum.
            maxSum = sum;
            // saves the student place.
            studentIndex = i;
        }
            // if two students have the same highest sum of grades, then the student that comes first in
            // lexicographic order in the first names, will be printed.
        else if (maxSum == sum) {
            if (strcmp(firstName[i], firstName[studentIndex]) < 0) {
                studentIndex = i;
            }
                // if the sudents also have the same first names, then we will check their last names.
            else if (strcmp(lastName[i], lastName[studentIndex]) < 0) {
                studentIndex = i;
            }
        }
    }
    printf("%s %s, %d\n", firstName[studentIndex], lastName[studentIndex], maxSum);
}

/*
Function name: PrintMaxNumCourses.
Input: none.
Output: none.
Function operation: this funciton goes over the students list and thier grades wand will print the student with
the highest number of courses.
*/
void PrintMaxNumCourses() {
    // initialize to the minimum.
    int count = 0;
    int maxCount = 0;
    int studentIndex = 0;
    // goes over the students.
    for (int i = 0; i < howManyStudents; i++) {
        // goes over the students courses.
        for (int j = 0; j < MAX_COURSES; j++) {
            while (j != '\0') {
                count++;
            }
        }
        // compares the max number of courses so far, with the current number of courses.
        if (maxCount < count) {
            // if the current number of courses is higher, the maxCount variable will be reinitialize.
            maxCount = count;
            // saves the student index
            studentIndex = i;
        }
            // if two students have the same highest num of courses, then the student that comes first in
            // lexicographic order in the first names, will be printed.
        else if (maxCount == count) {
            if (strcmp(firstName[i], firstName[studentIndex]) < 0) {
                studentIndex = i;
            }
                // if the sudents also have the same first names, then we will check their last names.
            else if (strcmp(lastName[i], lastName[studentIndex]) < 0) {
                studentIndex = i;
            }
        }
    }
    printf("%s %s, %d\n", firstName[studentIndex], lastName[studentIndex], maxCount);
}

/*
Function name: PrintAllAverageGrade.
Input: none.
Output: none.
Function operation: this function prints all the students with their avarage grade.
*/
void PrintAllAverageGrade() {
    // initialize to minimum.
    int count = 0;
    int sum = 0;
    int average = 0;
    // goes over the students.
    for (int i = 0; i < howManyStudents; i++) {
        // goes over the student's courses.
        for (int j = 0; j < MAX_COURSES; j++) {
            while (j != 0) {
                sum += grades[i][j];
                count++;
            }
        }
        average = sum / count;
        printf("%s %s, %d\n", firstName[i], lastName[i], average);
    }
}

/*
Function name: PrintAllSumGrades.
Input: none.
Output: none.
Function operation: this function prints all the students with their sum of grades.
*/
void PrintAllSumGrades() {
    // initialize to minimum.
    int sum = 0;
    // goes over the students.
    for (int i = 0; i < howManyStudents; i++) {
        // goes over the students courses.
        for (int j = 0; j < MAX_COURSES; j++) {
            while (j != '\0') {
                // summing the student's grades.
                sum += grades[i][j];
            }
        }
        printf("%s %s, %d\n", firstName[i], lastName[i], sum);
    }
}

/*
Function name: PrintAllNumCourses.
Input: none.
Output: none.
Function operation: this function prints the students with thier number of courses.
*/
void PrintAllNumCourses() {
    // initialize to minimum.
    int count = 0;
    // goes over the students.
    for (int i = 0; i < howManyStudents; i++) {
        // goes over the student's courses.
        for (int j = 0; j < MAX_COURSES; j++) {
            while (j != '\0') {
                count++;
            }
        }
        printf("%s %s, %d\n", firstName[i], lastName[i], count);
    }
}

/*
Function name: PrintAllMingrade.
Input: none.
Output: none.
Fjunciton operation: this function prints all the students with their minimum grade.
*/
void PrintAllMingrade() {
    // initialize to maximum.
    int minGrade = 100;
    // goes over the students.
    for (int i = 0; i < howManyStudents; i++) {
        // goes over the student's courses.
        for (int j = 0; j < MAX_COURSES; j++) {
            while (j != '\0') {
                // compare the min grade so far with the current min grade.
                if (minGrade > grades[i][j]) {
                    // if the current min grade is lower then the minGrade variable, then the variable will
                    // reintialize to the current min grade value.
                    minGrade = grades[i][j];
                }
                printf("%s %s, %d\n", firstName[i], lastName[i], minGrade);
            }
        }
    }
}

/*
Function name: PrintAllMaxGrade.
Input: none.
Output: none.
Function operation: this function prints all the students with their maximum grade.
*/
void PrintAllMaxGrade() {
    // initialize to minimum.
    int maxGrade = 0;
    // goes over ths students.
    for (int i = 0; i < howManyStudents; i++) {
        // goes over the student's courses
        for (int j = 0; j < MAX_COURSES; j++) {
            while (j != '\0') {
                if (maxGrade < grades[i][j]) {
                    maxGrade = grades[i][j];
                }
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
