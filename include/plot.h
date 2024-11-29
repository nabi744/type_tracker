#ifndef PLOT_H
#define PLOT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "gnuplot_i.h"
#include "stb_image.h"
#include "stb_image_write.h"

typedef struct {
    char key;
    int x;
    int y;
    int width;
    int height;
} KeyPosition;

enum plot_mode {
    accuracy,
    frequency
};

const KeyPosition key_positions[26] = {
    {'A', 360, 280, 122, 117},
    {'B', 870, 543, 122, 117},
    {'C', 598, 543, 122, 117},
    {'D', 632, 280, 122, 117},
    {'E', 429, 149, 122, 117},
    {'F', 768, 280, 122, 117},
    {'G', 904, 280, 122, 117},
    {'H', 1040, 280, 121, 116},
    {'I', 1107, 149, 121, 116},
    {'J', 1175, 280, 122, 116},
    {'K', 1311, 279, 121, 117},
    {'L', 1446, 279, 122, 117},
    {'M', 1142, 542, 122, 117},
    {'N', 1006, 542, 122, 118},
    {'O', 1242, 149, 122, 116},
    {'P', 1378, 149, 121, 116},
    {'Q', 157, 149, 123, 118},
    {'R', 565, 149, 121, 117},
    {'S', 497, 280, 121, 117},
    {'T', 700, 149, 122, 117},
    {'U', 972, 149, 121, 117},
    {'V', 734, 543, 122, 117},
    {'W', 293, 149, 122, 117},
    {'X', 462, 542, 122, 119},
    {'Y', 836, 149, 121, 117},
    {'Z', 326, 543, 122, 118}
};

void plot_heatmap(test *analyze_test, enum plot_mode mode) {
    float *metrics = malloc(sizeof(float) * 26);

    // Choose the plot_mode of the heatmap
    switch (mode) {
        case accuracy:
            memcpy(metrics, analyze_test->accuracy, sizeof(analyze_test->accuracy));
            break;
        case frequency:
            memcpy(metrics, analyze_test->frequency, sizeof(analyze_test->accuracy));
            break;
        default:
            printf("Wrong Enum\n");
            break;
    }

    // Plot the heatmap
    int width, height, channels;
    unsigned char *img = stbi_load("../res/img/keyboard.png", &width, &height, &channels, 0);
    if (img == NULL) {
        printf("Error in loading the image\n");
        exit(1);
    }

    // Create a copy of the image to modify
    unsigned char *output_img = malloc(width * height * channels);
    memcpy(output_img, img, width * height * channels);

    // Find the maximum usage value for normalization
    float max_usage = 100.0f;

    // Overlay the heatmap
    for (int i = 0; i < 26; i++) {
        KeyPosition kp = key_positions[i];
        float usage = metrics[i];

        // Normalize the usage value to [0, 1]
        float intensity = usage / max_usage;

        // Define the heatmap color (e.g., red intensity)
        unsigned char heatmap_color[3] = {
            (unsigned char)(255 * intensity), // Red channel
            0,                                // Green channel
            0                                 // Blue channel
        };

        // Overlay the heatmap color onto the key area
        for (int y = kp.y; y < kp.y + kp.height; y++) {
            for (int x = kp.x; x < kp.x + kp.width; x++) {
                int idx = (y * width + x) * channels;
                // Simple alpha blending
                float alpha = 0.5f; // Heatmap transparency
                for (int c = 0; c < 3; c++) { // Assuming RGB
                    output_img[idx + c] = (unsigned char)(
                        alpha * heatmap_color[c] + (1 - alpha) * output_img[idx + c]
                    );
                }
            }
        }
    }

    // Save the output image
    if (!stbi_write_png("../res/img/keyboard_heatmap.png", width, height, channels, output_img, width * channels)) {
        printf("Error in writing the image\n");
    }

    // Free memory
    stbi_image_free(img);
    free(output_img);
}

void plot_user_history(user *analyze_user) {
    int num_tests = analyze_user->num_tests;
    test *tests = analyze_user->history;

    if (num_tests <= 0) {
        printf("No tests available to plot.\n");
        return;
    }

    gnuplot_ctrl *gp = gnuplot_init();
    if (!gp) {
        fprintf(stderr, "Error: Unable to initialize Gnuplot.\n");
        return;
    }

    FILE *data_file = fopen("../data/tmp/plot_data.txt", "w");
    if (!data_file) {
        fprintf(stderr, "Error: Unable to create data file.\n");
        gnuplot_close(gp);
        return;
    }

    for (int i = 0; i < num_tests; i++) {
        fprintf(data_file, "%d %f %f\n", i + 1, tests[i].accuracy_avg, tests[i].frequency_avg);
    }
    fclose(data_file);

    gnuplot_cmd(gp,
                "set terminal png size 800,600; "
                "set output '../res/img/user_test_graph.png'; "
                "set xlabel 'Test Index'; "
                "set ylabel 'Value'; "
                "set title 'Accuracy and Frequency Averages'; "
                "plot '../data/tmp/plot_data.txt' using 1:2 with lines title 'Accuracy Avg', "
                "'../data/tmp/plot_data.txt' using 1:3 with lines title 'Frequency Avg'");

    gnuplot_close(gp);
    printf("Plot saved to '../res/img/user_test_graph.png'\n");
}

#endif // PLOT_H