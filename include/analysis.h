#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

double words_per_min(char *text, double time){
    int words = 0;
    int i = 0;
    while(text[i] != '\0'){
        if(isspace(text[i])){
            words++;
        }
        i++;
    }
    return words/time;
}

double calculate_accuracy(char *text, char *input){
    int i = 0;
    int correct = 0;
    int total = 0;
    while(text[i] != '\0'){
        if(text[i] == input[i]){
            correct++;
        }
        total++;
        i++;
    }
    return (double)correct/total;
}

