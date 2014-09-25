//Ivaness Christle Chiong      CS350-01
//CS350, Fall 2014
//Lab 03 -- File I/O; Bit Operations
//Instructor: James Sasaki
//
//Illinois Institute of Technology
//

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
  printf("CS 350 Lab 3 for %s\n\n", "Ivaness Christle Chiong | CS350-01");

  // We print out the command line that we were executed with.
  // argc has the number of words on the command line and argv[0], ...
  // contain the different words. The name of the command (e.g. a.out) 
  // is the initial word. The file will also be specified on the command line
  // as the second word (e.g. myfile.dat).

  printf("The command line had %d part(s)\n", argc);
  int i;
  for(i = 0; i < argc ; i++)
    printf("argv[%d] = %s\n", i, argv[i]);

  // In this part, we will open a file for input, read from it,
  // process it, then close it. In case fopen did not succeed, 
  // print an error message saying so and quit the program using 
  // "return 1."

  char *filename = "myfile.dat";    // file to read from
  FILE *in_file;
  
  in_file = fopen(filename, "r");
  if(in_file == NULL) {
    printf("\nOops! Couldn't open %s for reading. Please try again. \n\n", filename); // error message
    return 1; 
  }

  // Read a sequence of numbers from the file.
  // nbr_read = # of items read by fscanf; if zero, read failed.
  // Repeatedly read and process three integers and use fscanf to 
  // read the three integers. These three integers represent 
  // one in hex as 'hex', and two in decimal form named as 
  // 'r_bit' as the right-bit, and 'l_bit' as the left-bit.

  int nbr_read, hex, r_bit, l_bit;
  nbr_read = fscanf(in_file, "%x %d %d \n", &hex, &r_bit, &l_bit);

  while(nbr_read > 0) {
    nbr_read = fscanf(in_file, "%x %d %d \n", &hex, &r_bit, &l_bit);
  }

  int k = (l_bit-r_bit) + 1; // the length of the selected bits
  printf("\nValue:   %#x = %d \n", hex, hex);
  int mask = ((1 << k) - 1) << r_bit; // the mask

  int bit_and = hex & mask;    // applying the bitwise AND operation to get the desired value
  int actual_val = (bit_and >> r_bit); // the actual value of the selected bits 
  printf("Mask:  %#010x, bits %d:%d = %x\n", mask, r_bit, l_bit, actual_val);   // printing the mask

  int bits_set = hex | mask; // using the OR bit operation to get the value when we set hex[r_bit:l_bit] to all 1s.
  printf("Bits set:   %#x\n", bits_set);

  int cleared = bits_set ^ mask; // using the bits_set and the mask, we use the XOR bit operation to get the value when we set hex[r_bit:l_bit] to all 0s.
  printf("Cleared:   %#x\n", cleared);

  int flipped = hex ^ mask; // using XOR bit operation to the hex and the mask to get the value when we flip bits hex[r_bit:l_bit]
  printf("Flipped:   %#x\n\n", flipped);

  int close_err = fclose(in_file); // yields false if the close succeeded
  return 0;

}
