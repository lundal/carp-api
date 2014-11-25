/*
 *
 *
 *
 *
 * Kjetil Aamodt, 2005
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void readDMASums(int n);
void printSums(int n, FILE *outputfile);

void readDMAUsedRules(void);
void printUsedRules(FILE *outputfile);

void readDMAVector(int n);
void printVector(int n, FILE *outputfile);

void readAndPrintFitness(FILE *outputfile);

/* read back result from a readTypes instruction, and place in an array */
void readDMATypes (void);

/* read back result from a readStates instruction, and place in an array */
void readDMAStates (void);

/* write types in array produces by readDMATypes to file */
void printTypes (FILE *outputfile);

/* write types in array produces by readDMAStates to file */
void printStates (FILE *outputfile);

void printStatesPS(char* filename) ;
