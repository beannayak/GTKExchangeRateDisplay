#include <stdio.h>
#include <stdlib.h>
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
    int englishDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char *nepaliMonthsName[] = {"Baishakh", "Jestha", "Ashar", "Shrawan", "Bhadra", "Ashwin", "Kartik", "Mangshir", "Poush", "Magh", "Falgun", "Chaitra" };
    int checkYear, x, y;
    int year, month, day;
    int retYear, retMonth, retDay;
    int counter;
    int dayCount;
    char forward;
    char breakCondition = 0;
 
    if (argc < 4){
        printf ("Enter your date in system arguments.\n");
        exit(0);
    }
   
    data = putToArray(&dataLength);
    for (x=0; x<dataLength; x++){
        for (y=0; y<14;y++){
            if (data[x][y] == 2013){
                checkYear = 2070 + x;
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
    
    if (isLeapYear(year)){
        englishDays[1] = 29;
    } else {
        englishDays[1] = 28;
    }

    for (counter=0; counter<dataLength; counter++){
        if (data[counter][12] == year){
            retYear = checkYear - counter;
        }
    }     

    if (month >= 4){
        if (month != 4){
            dayCount = englishDays[3] - data[checkYear - retYear][13];
            for (counter=4; counter < (month-1); counter++){
                dayCount += englishDays[counter];
            }
            dayCount += day;    
            forward = 1;
        } else {
            if (day > data[checkYear - retYear][13]){
                forward = 1;
                dayCount = day - data[checkYear - retYear][13];
            } else {
                forward = 0;
                dayCount = data[checkYear - retYear][13] - day;
            }
        }
    } else {
        dayCount = data[checkYear - retYear][13];
        for (counter=(month); counter<3; counter++){
            dayCount += englishDays[counter];
        }
        dayCount += englishDays[month-1] - day;
        forward = 0;
    }

    int monthCount = 0;    
    if (forward){
        while (1){
            if (data[checkYear - retYear][monthCount] < dayCount){
                dayCount -= data[checkYear - retYear][monthCount];
                monthCount ++;
            } else {
                retMonth = monthCount;
                retDay = dayCount + 1;
                break;
            }
        }
    } else {
        monthCount = 11;
        retYear -= 1;
        while (1){
            //printf ("data[%d][%d] = %d and dayCount = %d\n", retYear, monthCount, data[2071 - retYear][monthCount], dayCount);
            if (data[checkYear - retYear][monthCount] < dayCount){
                dayCount -= data[checkYear - retYear][monthCount];
                monthCount --;
            } else {
                dayCount = data[checkYear - retYear][monthCount] - dayCount;
                retDay = dayCount + 1;
                if (retDay > data[checkYear - retYear][monthCount]){
                    retDay = retDay - data[checkYear - retYear][monthCount];
                    monthCount++;
                    if (monthCount == 12){
                        retYear += 1;
                        monthCount = 0;
                    }
                }
                retMonth = monthCount;
                break;
            }
        }
    }

    printf ("BS. is: %d %s %d\n", retYear, nepaliMonthsName[retMonth], retDay);
    return 0;
}

