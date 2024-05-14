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

// time == 00  is ok
// time == 123 is error
// time == -12 is error
int8_t  is24hors(const char *argv) {
    size_t len = strlen(argv);

    if (len == 0 || 2 < len) {
        printf("len, %s, %zu\n", argv, len);
        return(-1);
    }

    if (!isdigit(argv[TENS_PLACE]) || !isdigit(argv[ONES_PLACE])) {
        printf("len, %c, %zu\n", argv[TENS_PLACE], len);
        return(-1);
    }
    
    int time = atoi(argv);
    
    if (time < 0 || 23 < time) {
        return(-1);
    }

    return time;
}

int8_t  has_the_time_from_start_time_to_end_time(char **argv) {
    int8_t  theTime = is24hors(argv[THE_TIME]);

    if (theTime == -1) {
        fprintf(stderr, "error: the time: time is 0 to 23 \n");
        return(EXIT_FAILURE);
    }

    int8_t  startTime = is24hors(argv[START_TIME]);

    if (startTime == -1) {
        fprintf(stderr, "error: start time: time is 0 to 23 \n");
        return(EXIT_FAILURE);
    }

    int8_t  endTime = is24hors(argv[END_TIME]);

    if (endTime == -1) {
        fprintf(stderr, "error: end time: time is 0 to 23 \n");
        return(EXIT_FAILURE);
    }

    if (startTime == endTime) {
        if (startTime == theTime) {
            printf("\x1b[32mthe time is included from start time to end time \n\x1b[39m");
            return(EXIT_SUCCESS);
        }
        else if (startTime != theTime) {
            fprintf(stderr, "\x1b[31mthe time is not included from start time to end time \n\x1b[39m");
            return(EXIT_FAILURE);
        }
    }

    if (startTime <= theTime && theTime < endTime) {
        printf("\x1b[32mthe time is included from start time to end time \n\x1b[39m");
        return(EXIT_SUCCESS);
    }
    fprintf(stderr, "\x1b[31mthe time is not included from start time to end time \n\x1b[39m");
    return(EXIT_FAILURE);
}

int main(int argc, char **argv) {

    if (argc != 4) {
        fprintf(stderr, "usege: ./hastime the_time start_time end_time \n");
        return (1);
    }

    return(has_the_time_from_start_time_to_end_time(argv));
}