#include "project.h"
#include <stdio.h>
#include <string.h>

#define NVIC_CPUID_BASE_ADDR 0xe000ed00 
//revision [3:0]
#define revision_lft_idx 3
#define revision_rgt_idx 0
//partno [15:4]
#define partno_lft_idx 15
#define partno_rgt_idx 4
//constant [19:16]
#define constant_lft_idx 19
#define constant_rgt_idx 16
//variant [23:20]
#define variant_lft_idx 23
#define variant_rgt_idx 20
//implementer [31:24]
#define implementer_lft_idx 31
#define implementer_rgt_idx 24

void bubble_sort(char *str);
uint32_t get_bits(uint32_t regval, int lft_idx, int rgt_idx);

int main(void)
{
    char test_str[] = "Brian Dawson"; //string to be reversed
    bubble_sort(test_str); 
    
    //access register via its address here... Hardware needed to test
    //declare a pointer my_req_ptr and set it equal to register of NVIC_CPUID_BASE_ADDR
    uint32_t volatile * my_req_ptr = (uint32_t *) NVIC_CPUID_BASE_ADDR;
    //get value in the register
    uint32 reg_val = *my_req_ptr;
    uint32_t revision = get_bits(reg_val, revision_lft_idx, revision_rgt_idx);
    uint32_t partno = get_bits(reg_val, partno_lft_idx, partno_rgt_idx);
    uint32_t constant = get_bits(reg_val, constant_lft_idx, constant_rgt_idx);
    uint32_t variant = get_bits(reg_val, variant_lft_idx, variant_rgt_idx);
    uint32_t implementer = get_bits(reg_val, implementer_lft_idx, implementer_rgt_idx);
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

void bubble_sort(char *str)
{
    int stringLength,i,k;
    for (stringLength = 0; str[stringLength] != '\0'; stringLength++) {} //calculates string length
    char *currentChar, *nextChar, temp;
    currentChar = str; //copying str pointer to currentChar
    nextChar = str; //copying str pointer to nextChar
    nextChar++; //moving nextChar pointer to second character in str
    for (k = 1; k < stringLength; k++) //defines the number of iterations of bubble sort. Will be stringLength-1 iterations
    {
        for (i = 0; i < stringLength - k; i++) 
        //i< stringLength - k because each iteration puts the largest value last. This means one less comparison is needed each iteration
        {
            if (str[i] > str[i + 1]) //if the currentChar is greater than the char right after it then switch them
            {
                temp = *nextChar; //save nextChar into temp
                *nextChar = *currentChar; //set nextChar = currentChar
                *currentChar = temp; //make currentChar equal to temp(original nextChar)
            }//end if (str[i] > str[i + 1])
            nextChar++; //moving nextChar to right one character
            currentChar++; //moving current char to the right one character
        }//end for (i = 0; i < stringLength; i++)
        for (i = 0; i < stringLength - k; i++) //same for loop as above to reset pointer locations
        {
            nextChar--; //moving nextChar back to second character
            currentChar--; //moving current char back to first character
        }//end for (i = 0; i < stringLength - k; i++)
    }//end for (k = 0; k < stringLength - 1; k++)
}//end void bubble_sort(char *str)

uint32_t get_bits(uint32_t regval, int lft_idx, int rgt_idx)
{
    uint32_t bufferVal = 0; //bufferVal will be used to create a binary value of 111... with lft_idx many 1s 
    int i;
    regval = regval >> rgt_idx; //shifts right by rgt_idx bits
    int nbits = lft_idx - rgt_idx + 1;
    for (i = 0; i < nbits; i++)
    {
        bufferVal = (bufferVal << 1) + 1; //shift right by 1 bit then add 1 (add an additional 1)
    }//end for (i = 0; i < nbits; i++)
    regval = bufferVal & regval; //cuts off all of the bits past the lft_idx point
    return(regval);
}//end uint32_t get_bits(uint32_t regval, int lft_idx, int rgt_idx)