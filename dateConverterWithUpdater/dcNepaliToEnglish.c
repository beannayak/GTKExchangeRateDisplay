#include <stdio.h>
#include <myString.h>

char *readLine(FILE *myFile){
    char buffer[3000] = {0};
	char *string = NULL;

    fscanf(myFile, "%[^'\n']s", buffer);
	if (!feof(myFile) ){
        string = (char *) malloc(length(buffer) + 1);
        strCpy (buffer, string);
        fseek (myFile, 1, SEEK_CUR); 
	}
    
    return string;
}

int myToInteger(char *number){
    int count = 0;
    int value = 0;
    while (number[count] != '\0'){
        if (number[count] >= 48 && number[count] <= 57){
            value = value * 10 + (number[count]-48);
        }
        count++;
    }
    return value;
}

int **putToArray(int *myDataLength){
    char *string;
    int **myData;
    int lineCount = 0;
    FILE *myFile = fopen("./DateInfo.dat", "r");
    char **splitedString;
    int splitedStringLength;    
    int x;

    /******** First parse *************************/
    while ((string = readLine (myFile)) != NULL){
        if (!equals(string, "\0") && !(equals(string, "\r\0"))) {
            lineCount++;
        }
        free (string);
    }
    *myDataLength = lineCount;
    fclose(myFile);
    /**********************************************/

    /****************** Initilize double pointer array ****************/
    myData = (int **) malloc ((sizeof(int*)) * (lineCount) + 1);
    for (x=0; x<lineCount; x++){
        myData[x] = (int *) malloc (sizeof (int) * 14);
    }
    /******************************************************************/

    /*******************Fill the array ********************************/
    lineCount = 0;
    myFile = fopen("./DateInfo.dat", "r");
    while ((string = readLine (myFile)) != NULL){
        if (!equals(string, "\0") && !(equals(string, "\r\0"))) {
            splitedString = split(string, ",", &splitedStringLength);
            for (x=0; x<14; x++){
                myData[lineCount][x] = myToInteger(splitedString[x]);
            }
            freeSplitedString(splitedString, splitedStringLength);
        }
        lineCount++;
        free (string);
    }
    fclose(myFile);
    /******************************************************************/

    return myData;
}

int isLeapYear(int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

int main(int argc, char **argv){
    int **data;
    int dataLength;
    int checkYear, x, y;
    char breakCondition = 0;   
    int englishDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char *englishMonthsName[] = {"January", "Feburary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int year, month, day;
    int retYear, retMonth, retDay;
    int dayCount;
    int counter;
    int subVal, monthCounter;

    if (argc < 4){
        printf ("Enter your date in system arguments.\n");
        exit(0);
    }

    data = putToArray(&dataLength);
    for (x=0; x<dataLength; x++){
        for (y=0; y<14;y++){
            if (data[x][y] == 2013){
                checkYear = 2070 + x;
                //printf ("year: %d \n", checkYear);
                breakCondition = 1;
                break;
            }
        }
        if (breakCondition){
            break;
        }
    }

    sscanf (argv[1], "%d", &year);
    sscanf (argv[2], "%d", &month);
    sscanf (argv[3], "%d", &day);

    year = checkYear - year;
    retYear = data[year][12];
    if (isLeapYear(retYear)){
        englishDays[1] = 29;
    } else {
        englishDays[1] = 28;
    }

    dayCount = 0;
    for (counter=0; counter<month-1; counter++){
        dayCount += data[year][counter];
    }
    dayCount += day;

    subVal = englishDays[3] - data[year][13];
    monthCounter = 3;
    while (1){
        dayCount -= subVal;
        monthCounter++;
        if (monthCounter == 12) {
            monthCounter = 0;
            retYear += 1;
            if (isLeapYear(retYear)){
                englishDays[1] = 29;
            } else {
                englishDays[1] = 28;
            }
        }
        if (dayCount > englishDays[monthCounter]){
            subVal = englishDays[monthCounter];
        } else {
            dayCount -= 1;
            if (dayCount == 0) {
                monthCounter -- ;
                if (monthCounter == -1){
                    monthCounter = 11;
                    retYear -= 1;
                }
                retDay = englishDays[monthCounter];
            } else {
                retDay = dayCount;
            }
            break;
        }
    }

    retMonth = monthCounter;
    if (retDay < 0) {
        retMonth -= 1;
        retDay = englishDays[retMonth] + retDay;
    } 
    printf ("%d %s %d\n", retYear, englishMonthsName[retMonth], retDay);
    return 0;
}
