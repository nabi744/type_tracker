//
// Created by john on 24. 11. 21.
//

#ifndef TYPE_TRACKER_STRUCTURE_H
#define TYPE_TRACKER_STRUCTURE_H

typedef struct{
    char filename[100];
    float wpm;
    float accuracy_avg;
    float frequency_avg;
    float accuracy[26];
    float frequency[26];
} test;


typedef struct{
    test* history;
    int num_tests;
} user;


#endif //TYPE_TRACKER_STRUCTURE_H
