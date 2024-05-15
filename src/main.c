#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define TENS_PLACE 0
#define ONES_PLACE 1

#define THE_TIME   1
#define START_TIME 2
#define END_TIME   3

// time == 0   is ok
// time == 00  is ok
// time == 123 is error
// time == -12 is error
int8_t  is24hors(const char *timeStr, const char *timeName) {
    size_t len = strlen(timeStr);

    switch (len)
    {
        case 0: // timeStr is empty string
            fprintf(stderr, "error: %s is empty string\n", timeName);
            return(-1);
        case 1: // timeStr is one character like "1", "+" or ...
            if (!isdigit(timeStr[0])) {
                
                fprintf(stderr, "error: %s is not number\n", timeName);
                return(-1);
            }
            break;
        case 2: // timeStr is two characters like "00", "1a" or ...
            if (!isdigit(timeStr[TENS_PLACE]) || !isdigit(timeStr[ONES_PLACE])) {
                fprintf(stderr, "error: %s is not number\n", timeName);
                return(-1);
            }
            break;
        default: // timeStr is over two characters like "-12", "123" or ...
            fprintf(stderr, "error: %s is not 0 to 23 number\n", timeName);
            return(-1);
    }
    
    int timeNum = atoi(timeStr);

    if (timeNum < 0 || 23 < timeNum) {
        return(-1);
    }

    return timeNum;
}

int8_t  has_the_time_from_start_time_to_end_time(char **argv) {
    int8_t  theTime = is24hors(argv[THE_TIME], "the time");

    if (theTime == -1) {
        return(EXIT_FAILURE);
    }

    int8_t  start = is24hors(argv[START_TIME], "start");

    if (start == -1) {
        return(EXIT_FAILURE);
    }

    int8_t  end = is24hors(argv[END_TIME], "end");

    if (end == -1) {
        return(EXIT_FAILURE);
    }

    if (end < start) {
        fprintf(stderr, "\x1b[31mend is biger than start \n\x1b[39m");
        return(EXIT_FAILURE);
    }

    if (start == end) {
        if (start == theTime) {
            printf("\x1b[32mthe time is included from start to end \n\x1b[39m");
            return(EXIT_SUCCESS);
        }
        else if (start != theTime) {
            fprintf(stderr, "\x1b[31mthe time is out of from start to end \n\x1b[39m");
            return(EXIT_FAILURE);
        }
    }

    if (start <= theTime && theTime < end) {
        printf("\x1b[32mthe time is included from start to end \n\x1b[39m");
        return(EXIT_SUCCESS);
    }
    fprintf(stderr, "\x1b[31mthe time is out of from start to end \n\x1b[39m");
    return(EXIT_FAILURE);
}

int main(int argc, char **argv) {

    if (argc != 4) {
        fprintf(stderr, "usege: ./hastime the time start end \n");
        return (1);
    }

    return(has_the_time_from_start_time_to_end_time(argv));
}