#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// Declare the external assembly function
extern void imgCvtGrayInttoFloat(size_t size, const uint8_t* input, float* output);

int main() {
    size_t width, height;

    // Prompt the user for image dimensions (width and height)
    printf("Enter image width: ");
    scanf_s("%zu", &width);

    printf("Enter image height: ");
    scanf_s("%zu", &height);

    // Calculate the number of pixels (size of the input array)
    size_t size = width * height;

    // Dynamically allocate memory for the input and output arrays
    uint8_t* imgInt = (uint8_t*)malloc(size * sizeof(uint8_t));
    if (imgInt == NULL) {
        printf("Memory allocation failed!\n");
        return 1; // Exit with error if allocation fails
    }

    float* imgFloat = (float*)malloc(size * sizeof(float));
    if (imgFloat == NULL) {
        printf("Memory allocation failed!\n");
        free(imgInt); // Free previously allocated memory
        return 1; // Exit with error if allocation fails
    }

    // Ask the user if they want to input pixel values or generate them automatically
    char choice;
    printf("Do you want to input pixel values manually (m) or generate them randomly (r)? ");
    scanf_s(" %c", &choice); // Notice the space before %c to consume any extra newline

    if (choice == 'm' || choice == 'M') {
        // Prompt the user to input the grayscale pixel values
        printf("Enter the grayscale pixel values (0-255) row by row:\n");
        for (size_t i = 0; i < size; i++) {
            printf("Pixel %zu: ", i + 1);
            scanf_s("%hhu", &imgInt[i]);  // Input as unsigned 8-bit integer
        }
    }
    else if (choice == 'r' || choice == 'R') {
        // Seed the random number generator
        srand((unsigned int)time(NULL));

        // Generate random pixel values between 0 and 255
        printf("Generating random pixel values:\n");
        for (size_t i = 0; i < size; i++) {
            imgInt[i] = rand() % 256;  // Random value between 0 and 255
        }
    }
    else {
        printf("Invalid choice! Exiting program.\n");
        free(imgInt);
        free(imgFloat);
        return 1;
    }

    // Call the assembly function to convert the image
    imgCvtGrayInttoFloat(size, imgInt, imgFloat);

    // Print the input and output arrays
    printf("\nInput imgInt (integer values):\n");
    for (size_t i = 0; i < size; i++) {
        printf("%u ", imgInt[i]);
        if ((i + 1) % width == 0) printf("\n");
    }

    printf("\nConverted imgFloat (float values):\n");
    for (size_t i = 0; i < size; i++) {
        printf("%.2f ", imgFloat[i]);  // Display float values with 2 decimal places
        if ((i + 1) % width == 0) printf("\n");
    }

    // Free allocated memory
    free(imgInt);
    free(imgFloat);

    return 0;
}
