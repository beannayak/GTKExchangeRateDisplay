#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <myString.h>
#include <stdlib.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void download(char *url, char* fileName) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(fileName,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        fclose(fp);
    }
}

void getDate(char *year, char *month, int *dayCount){
    char urlString[255];
    long unsigned int size;
    char string[65535];
    FILE *myFile;

    strCpy ("http://www.nepcal.com/index.php?y=", urlString);
    strCat (urlString, year);
    strCat (urlString, "&m=");
    strCat (urlString, month);

    /********* Download and check for internet connection using CURL ***********/
    download (urlString,"./a.html");
    
    myFile = fopen ("./a.html", "rb");
	fseek(myFile, 0L, SEEK_END);
	size = ftell(myFile);
	if (size == 0){
		printf ("Check Your Internet Connection....\n");
		return;
	}
	fclose(myFile);
    /***************************************************************************/
    

    /************************ Check for the date and return English date ********/
    char **firstSplit;
    int firstSplitLength;
    char **secondSplit;
    int secondSplitLength;
    char buffer[2];
    int x, y;
    char counting;
    char start = 0;
    char nextLineCheck = 0;
    char checkOnceA = 1;
    char checkOnceB = 1;
    char *retYear;
    int retDay;
    char firstNonFadedCheck = 0;

    myFile = fopen("./a.html", "r");
    //printf ("{");
    while (fgets (buffer, sizeof (buffer), myFile) != NULL){
		if (buffer[0] != '\n'){
			string [x] = buffer[0];
		} else {
			string[x] = '\0';

            /***** Your code here *******/
            if (indexOfWithStart(string, "class=\"mheadn_h\"",0)>=0 || indexOfWithStart(string, "class=\"mheadn\"",0)>=0) {
                if (start){
                    printf ("%d, ", counting);
                }
                counting = 0;
                start = 1;
            }

            if (nextLineCheck){
                if (indexOfWithStart(string, "&", 0)<0){
                    counting++;
                } 
nextLineCheck = 0;
            }

            if (start) {
                if (indexOfWithStart(string, "class=\"day_container_h \"", 0)>=0 || indexOfWithStart(string, "class=\"day_container_h holiday_h\"", 0)>=0 || indexOfWithStart(string, "class=\"day_container \"", 0)>=0 || indexOfWithStart(string, "class=\"day_container holiday\"", 0)>=0){
                    nextLineCheck = 1;
                    firstNonFadedCheck = 1;
                }
            }

            if (checkOnceA && indexOfWithStart(string, "mheade_h", 0) >= 0) {
                firstSplit = split (string, ">", &firstSplitLength);
                secondSplit = split (firstSplit[1], "<", &secondSplitLength);
                freeSplitedString(firstSplit, firstSplitLength);
                firstSplit = split (secondSplit[0], " ", &firstSplitLength);
                retYear = malloc (length(firstSplit[1]) + 1);
                strCpy (firstSplit[1], retYear);
                freeSplitedString(firstSplit, firstSplitLength);
                freeSplitedString(secondSplit, secondSplitLength);
                checkOnceA = 0;
            }
            if (checkOnceB && indexOfWithStart(string, "dayvale_h", 0) >= 0 && firstNonFadedCheck){
                firstSplit = split (string, ">", &firstSplitLength);
                secondSplit = split (firstSplit[1], "<", &secondSplitLength);
                retDay = toInteger(secondSplit[0]);
                freeSplitedString(firstSplit, firstSplitLength);
                freeSplitedString(secondSplit, secondSplitLength);
                checkOnceB = 0;
            }
            /****************************/
            x = -1;
		}
		x++;
	}
    printf ("%d, %s, %d\n", counting, retYear, retDay);
    free (retYear);
	fclose(myFile);  

    remove ("./a.html");
    /*********************************************************************************/
}

int main(int argc, char **argv){
    int dayCount;
    char a[6];
    int y;
    char **yearSplit;
    int yearSplitLength;
    int yearStart = 2071;    
    int yearEnd = 1974;
    
    if (argc >= 4){
        if ( equals(argv[1], "-r")){
            yearStart = toInteger(argv[2]);
            yearEnd = toInteger(argv[3]);
        }
    } else if (argc >= 3){
        if (equals(argv[1], "-f")){
            yearStart = toInteger(argv[2]);
        } else if (equals(argv[1], "-o")){
            yearStart = toInteger(argv[2]);
            yearEnd = yearStart;
        }    
    } 

    for (y=yearStart; y>=yearEnd; y--){
        sprintf (a, "%d", y);
        getDate (a, "1", &dayCount);
    }
    return 0;
}

