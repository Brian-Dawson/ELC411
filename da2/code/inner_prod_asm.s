    .syntax unified
    .text


    .global inner_prod_asm
    .func inner_prod_asm, inner_prod_asm
    .thumb_func
inner_prod_asm:
    // r0 = h; r1 = x; r2= n; r3 = sum; r4= i; 
    push {r4, r5, r6, r7}
    mov r3, #0 // sum = 0
    mov r4, #0 // i = 0
    loop: 
        cmp r4, r2 //comparing r4(i) and r2(n)
        bge continue //if i >= n go to continue
        ldrsh r5, [r0],#2  //Loading the value of h then post incrementing by 2 (2bytes)
        ldrsh r6, [r1],#2 //Loading the value of h then post incrementing by 2 (2bytes) 
        mul r7, r5, r6 //temp = h[i]*x[i]
        add r3, r3, r7 //sum = sum + temp
        add r4, r4, #1 //i++
        b loop //branch back to loop
    continue :
        asr r0, r3, #16
        pop {r4,r5,r6,r7}
        bx lr

.endfunc
.end



