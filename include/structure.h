//
// Created by john on 24. 11. 21.
//

#ifndef TYPE_TRACKER_STRUCTURE_H
#define TYPE_TRACKER_STRUCTURE_H

typedef {

    test* history;
} user;

typedef {
    char filename[100];
    float wpm;
    float accuracy_avg;
    float frequency_avg;
    float accuracy[26];
    float frequency[26];
} test;

#endif //TYPE_TRACKER_STRUCTURE_H
