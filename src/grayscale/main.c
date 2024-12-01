/*
Reign Elaiza Larraquel & Atasha Dominique Pidlaoan
S14
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "c_comparison.c"

// Declare the external assembly function
extern void imgCvtGrayInttoFloat(size_t size, const uint8_t* input, float* output);


int main() {

    struct timespec tspec_before, tspec_after;
    long long total_sec_c = 0, total_nsec_c = 0;
    long long total_sec_asm = 0, total_nsec_asm = 0;
    // Seed random number generator
    srand((unsigned int)time(NULL));
    
    char choose;
    printf("Choose Number: \n 1: Manual Input Mode \n 2: Performance Testing Mode\n\n");
    printf("Answer: ");
    scanf_s(" %c", &choose);
    printf("-------------------------------------------------\n\n");

    if (choose == '1') {
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

        // Arrays to store the converted pixel values (separate for C and assembly)
        float* imgFloatAsm = (float*)malloc(size * sizeof(float)); // For assembly conversion
        if (imgFloatAsm == NULL) {
            printf("Memory allocation failed!\n");
            free(imgInt); // Free previously allocated memory
            return 1;
        }

        float* imgFloatC = (float*)malloc(size * sizeof(float)); // For C conversion
        if (imgFloatC == NULL) {
            printf("Memory allocation failed!\n");
            free(imgInt);
            free(imgFloatAsm); // Free previously allocated memory
            return 1;
        }

        char choice;
        // Ask the user if they want to input pixel values or generate them automatically
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
            

            // Generate random pixel values between 0 and 255
            printf("Generating random pixel values:\n");
            for (size_t i = 0; i < size; i++) {
                imgInt[i] = rand() % 256;  // Random value between 0 and 255
            }
        }
        else {
            printf("Invalid choice! Exiting program.\n");
            free(imgInt);
            free(imgFloatAsm);
            free(imgFloatC);
            return 1;   
        }

        // Call the assembly function to convert the image and store it in imgFloatAsm
        imgCvtGrayInttoFloat(size, imgInt, imgFloatAsm);

        // Call the C function to convert the image and store it in imgFloatC
        c_imgCvtGrayInttoFloat(size, imgInt, imgFloatC);
        
        // Print the input and output arrays
        printf("\nInput imgInt (integer values):\n");
        for (size_t i = 0; i < size; i++) {
            printf("%u ", imgInt[i]);
            if ((i + 1) % width == 0) printf("\n");
        }

        // Print the converted float values using assembly
        printf("\nConverted imgFloatAsm (float values using assembly):\n");
        for (size_t i = 0; i < size; i++) {
            printf("%.2f ", imgFloatAsm[i]);  // Display float values with 2 decimal places
            if ((i + 1) % width == 0) printf("\n");
        }

        // Print the converted float values using the C function
        printf("\nConverted imgFloatC (float values using C function):\n");
        for (size_t i = 0; i < size; i++) {
            printf("%.2f ", imgFloatC[i]);  // Display float values with 2 decimal places
            if ((i + 1) % width == 0) printf("\n");
        }

        // Free allocated memory
        free(imgInt);
        free(imgFloatAsm);
        free(imgFloatC);

        return 0;

    } else if (choose == '2') {
        
        printf("\nSection 1: Correctness Check\n\n"); 
        size_t width, height;
        
        for(int i = 0; i < 3; i++) {

            printf("[TEST No.: %d]\n", i + 1);

            width = (rand() % 10) + 1;
            height = (rand() % 10) + 1;

            size_t size = width * height;
            
            uint8_t* imgInt = (uint8_t*)malloc(size * sizeof(uint8_t));
            float* imgFloatAsm = (float*)malloc(size * sizeof(float)); // For assembly conversion
            float* imgFloatC = (float*)malloc(size * sizeof(float)); // For C conversion


            for (int i = 0; i < size; i++) imgInt[i] = rand() % 256;
            
            imgCvtGrayInttoFloat(size, imgInt, imgFloatAsm);
            c_imgCvtGrayInttoFloat(size, imgInt, imgFloatC);

            // Print the input and output arrays
            printf("\nInput imgInt (integer values):\n");
            for (size_t i = 0; i < size; i++) {
                printf("%u ", imgInt[i]);
                if ((i + 1) % width == 0) printf("\n");
            }

            // Print the converted float values using assembly
            printf("\nConverted imgFloatAsm (float values using assembly):\n");
            for (size_t i = 0; i < size; i++) {
                printf("%.2f ", imgFloatAsm[i]);  // Display float values with 2 decimal places
                if ((i + 1) % width == 0) printf("\n");
            }

            // Print the converted float values using the C function
            printf("\nConverted imgFloatC (float values using C function):\n");
            for (size_t i = 0; i < size; i++) {
                printf("%.2f ", imgFloatC[i]);  // Display float values with 2 decimal places
                if ((i + 1) % width == 0) printf("\n");
            }

            for (size_t i = 0; i < size; i++) {
                if(imgFloatC[i] != imgFloatAsm[i]) printf("FAIL");

            }

            printf("\nTEST RUN %d PASS\n", i+1);
            printf("-------------------------------------------------\n\n");

        }
         

        printf("\nSection 2: Performance Testing\n\n");

        

        for (int i = 1; i <= 3; i++)
        {
            width = 1;
            height = 1;

            for (int i = 0; i < i; i++) {
                width *= 10;
                height *= 10;
            }

            size_t size = width * height;
            
            uint8_t* imgInt = (uint8_t*)malloc(size * sizeof(uint8_t));
            float* imgFloatAsm = (float*)malloc(size * sizeof(float)); // For assembly conversion
            float* imgFloatC = (float*)malloc(size * sizeof(float)); // For C conversion
           

            for (int i = 0; i < 30; i++) {

                if (i < 9) {
                    printf("Iteration 0%d:  ", i + 1);
                }
                else {
                    printf("Iteration %d:  ", i + 1);
                }
                

                for (int k = 0; k > size; i++) imgInt[i] = rand() % 256;
                
                timespec_get(&tspec_before, TIME_UTC);
                imgCvtGrayInttoFloat(size, imgInt, imgFloatAsm);
                timespec_get(&tspec_after, TIME_UTC);

                long sec_asm = tspec_after.tv_sec - tspec_before.tv_sec;
                long nsec_asm = tspec_after.tv_nsec - tspec_before.tv_nsec;
                if (nsec_asm < 0) { // Normalize if nsec part is negative
                    sec_asm--;
                    nsec_asm += 1000000000L;
                }
                total_sec_asm += sec_asm;
                total_nsec_asm += nsec_asm;
                printf("ASM Kernel Time: %ld.%09ld seconds   |", sec_asm, nsec_asm);

                timespec_get(&tspec_before, TIME_UTC);
                c_imgCvtGrayInttoFloat(size, imgInt, imgFloatC);
                timespec_get(&tspec_after, TIME_UTC);
                long sec_c = tspec_after.tv_sec - tspec_before.tv_sec;
                long nsec_c = tspec_after.tv_nsec - tspec_before.tv_nsec;
                if (nsec_c < 0) { // Normalize if nsec part is negative
                    sec_c--;
                    nsec_c += 1000000000L;
                }
                total_sec_c += sec_c;
                total_nsec_c += nsec_c;
                printf("   C Kernel Time: %ld.%09ld seconds\n", sec_c, nsec_c);

            }

            long double average_time_c = (total_sec_c + total_nsec_c / 1e9) / 30.000000000;
            long double average_time_asm = (total_sec_asm + total_nsec_asm / 1e9) / 30.000000000;

            printf("\nAverage C Kernel Time (size %d): %0.9Lf seconds\n", (int)width, average_time_c);
            printf("Average ASM Kernel Time(size %d): %0.9lf seconds\n", (int)width, average_time_asm);
            printf("--------------------------------------------------------------------------------------------------\n\n");
        }
        


    } else {
        printf("Invalid choice! Exiting program.\n");
        return 0;
    }

    
}
