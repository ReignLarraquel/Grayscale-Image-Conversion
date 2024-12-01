#include <stdint.h>

void c_imgCvtGrayInttoFloat(size_t size, uint8_t* inputPixels, float* outputPixels) {
    // Iterate through each pixel in the input array
    for (size_t i = 0; i < size; i++) {
        // Convert the integer pixel value to a float and normalize it by dividing by 255.0
        outputPixels[i] = (float)inputPixels[i] / 255.0f;
    }
}
