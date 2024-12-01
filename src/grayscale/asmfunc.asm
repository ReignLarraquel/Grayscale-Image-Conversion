section .text
global imgCvtGrayInttoFloat ; Expose the symbol to C code

imgCvtGrayInttoFloat:
    ; Parameters: RCX = size (number of pixels), RDX = input pointer, R8 = output pointer

    ; Push used registers to the stack
    push rdi
    push rsi

    ; Load constant 255.0 into xmm1 for normalization
    mov rax, 255
    cvtsi2ss xmm1, rax    ; xmm1 = 255.0f (divisor)

    ; Set up the loop with a counter
    xor rsi, rsi          ; rsi = 0 (i = 0)

.loop:
    ; Check if we have processed all pixels (i >= size)
    cmp rsi, rcx
    jge .done

    ; Load a pixel from input array
    movzx rax, byte [rdx + rsi]   ; rax = input[i]

    ; Convert the pixel value into a float
    cvtsi2ss xmm0, rax             ; xmm0 = (float)input[i]

    ; Normalize the value by dividing by 255.0
    divss xmm0, xmm1               ; xmm0 = xmm0 / 255.0f

    ; Store the result in the output array
    movss [r8 + rsi * 4], xmm0     ; output[i] = xmm0

    ; Increment the loop counter
    inc rsi

    ; Repeat the loop
    jmp .loop

.done:
    ; Restore registers before returning
    pop rsi
    pop rdi

    ret
