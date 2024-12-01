# Grayscale-Image-Conversion

This project implements a program that converts grayscale image pixel values from integer format (0-255) to float format (0.0-1.0). The conversion is performed using both assembly language (for performance comparison) and C. The program provides two modes:

1. Manual Input Mode: Users can manually enter pixel values.
2. Random Pixel Generation Mode: The program generates random pixel values for performance testing or demonstration.

The program compares the performance of converting an image using both assembly and C, and it outputs the results for both conversions.



## Authors

- Reign Elaiza Larraquel ([@ReignLarraquel](https://www.github.com/ReignLarraquel))
- Atasha Dominique Pidlaoan ([@tshlaine](https://www.github.com/tshlaine))

Last modified: 12/02/2024


## How To Run

To deploy this project run the following in your Terminal/CMD:

```bash
  nasm -f win64 asmfunc.asm -o asmfunc.obj
```

```bash
  gcc -c main.c -o main.obj -m64
```

```bash
  gcc main.obj asmfunc.obj -o main.exe -m64
```

```bash
  main.exe
```


## Usage/Examples

**Input:** height, width, integer pixel values
```
Height: 3 
Width: 4

Integer Pixel Values:
64,  89,  114, 84
140, 166, 191, 84
216, 242, 38,  84
```

**Output:** Single Float pixel values

```

0.25 0.35 0.45 0.33
0.55 0.65 0.75 0.33
0.85 0.95 0.15 0.33
```

## Sample Output
![image](https://github.com/user-attachments/assets/dded628c-a78d-435b-9aca-01c7dd9782e7)


## Analysis of Execution Time and Code Output
Before proceeding with any further analysis, the initial step is to verify if the outputs of the C and assembly kernels match. This is done by comparing the results of the first 3 elements of the output arrays. The comparison is performed as follows:
### Test No. 1
**Results:** Pass
![image](https://github.com/user-attachments/assets/5a221eda-2ad3-471e-b925-da8a0833221b)

### Test No. 2
**Results:** Pass
![image](https://github.com/user-attachments/assets/445c01c1-d0a8-477b-81c5-97fc7eb42e53)

### Test No. 3
**Results:** Pass
![image](https://github.com/user-attachments/assets/13f9145e-e478-43df-ab9e-397af4e3c730)

### Summary:
All tests had the same outputs for C and Assembly kernels, thus results in all tests passing.

| Test  | Pass/Fail |
|-------|-----------|
|   1   |    Pass   |
|   2   |    Pass   |
|   3   |    Pass   |
|       |    Pass   |

## Performance Testing

### Test No. 1
**Average C Kernel Time (size 10):** 0.000001013 seconds

**Average ASM Kernel Time (size 10):** 0.000000760 seconds
![image](https://github.com/user-attachments/assets/425065ee-0b29-49bb-8671-4740ff134465)

### Test No. 2
**Average C Kernel Time (size 10):** 0.000067763 seconds

**Average ASM Kernel Time (size 10):** 0.000054880 seconds
![image](https://github.com/user-attachments/assets/52d80175-45fe-4d7a-af1d-0f68db44c266)

### Test No. 3
**Average C Kernel Time (size 10):** 0.007467243 seconds

**Average ASM Kernel Time (size 10):** 0.005723887 seconds
![image](https://github.com/user-attachments/assets/4da15359-7ce5-4172-a50a-a30882d54b1d)



| x86-64  | C |
| ------------- | ------------- |
| ![image](https://github.com/user-attachments/assets/9ba700c3-ed9f-42aa-a807-e786f49feded) | ![image](https://github.com/user-attachments/assets/9923cfcc-1620-4568-97fa-c8bc462bac7c)  |

## Conclusion
Based on the results from the kernel timing tests, it is evident that the assembly implementation is faster than the C implementation. The time measurements for both the C kernel and the assembly kernel show a clear performance advantage for the assembly-based solution.

## Demo

