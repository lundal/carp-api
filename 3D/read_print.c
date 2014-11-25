/* read_print.c
 *
 * Methods for reading data from PCI-bus and for printing formated data
 * to a file. 
 *
 * Kjetil Aamodt, 2005
 */

#include "constants.h"
#include "read_print.h"
#include "sblocklib.h"

static int typeArray[ROWS][COLUMNS];
static bool stateArray[ROWS][COLUMNS];
static int ruleArray[ROWS*COLUMNS];
static int sumArray[BUFFER_SIZE];
static int ruleVector[256][8]; //max 256 vectors in BRAM          

void readDMATypes (void) {
  int x;

  /* read types */
  readDMA (ROWS * COLUMNS / 4);
  for (x = 0; x < ROWS * COLUMNS / 4; x++) {
    uint32_t type;

    int xx = (4 * x) % COLUMNS;
    int yy = (4 * x) / COLUMNS;

    type = receiveBuffer[x];

    typeArray[yy][xx + 0] = (type >> 15) & 0x1f;
    typeArray[yy][xx + 1] = (type >> 10) & 0x1f;
    typeArray[yy][xx + 2] = (type >> 5) & 0x1f;
    typeArray[yy][xx + 3] = type & 0x1f;
  }
}

void readDMAStates (void) {
  int x, y;

  /* read states */
  readDMA (ROWS * COLUMNS / 32);
  for (x = 0; x < ROWS * COLUMNS / 32; x++) {
    uint32_t state;

    int xx = (32 * x) % COLUMNS;
    int yy = (32 * x) / COLUMNS;

    state = receiveBuffer[x];

    for (y = 0; y < 32; y++) {
      stateArray[yy + (y / COLUMNS)][xx + (y % COLUMNS)] =
        (state >> (31 - y)) & 1;
    }
  }
}


void printTypes (FILE *outputfile) {
  int x, y;
  fprintf(outputfile, "Printing types:\n"); fflush(stdout);
  /* print types */
  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLUMNS; x++) {
      int type = typeArray[y][x];
      fprintf (outputfile, "%d ", type); fflush (stdout);
    }
    fprintf (outputfile, "\n"); fflush (stdout);
  }
  fprintf (outputfile, "\n");
}


void printStates (FILE *outputfile) {
  int x, y;
  int ones;
  /* print states */
  fprintf(outputfile, "Printing states:\n"); fflush(stdout);
  ones = 0;
  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLUMNS; x++) {
      int state = stateArray[y][x];
      state ? ones++: ones;
      fprintf (outputfile, "%c ", state ? 'X': '.'); fflush (stdout);
    }
    fprintf (outputfile, "\n"); fflush (stdout);
  }
  fprintf (outputfile, "Number of '1': %i\n", ones);
  fprintf (outputfile, "\n");
}


void readDMASums(int n){
  int i;
  readDMA(n/2);
  for(i = 0; i < n/2; i++){
    //fprintf(outputfile, "%x ", receiveBuffer[i]); fflush(stdout);
    sumArray[2*i  ] = receiveBuffer[i] & 0x0000ffff;
    sumArray[2*i+1] = ((receiveBuffer[i] & 0xffff0000) >> 16);
  }

}


void printSums(int n, FILE *outputfile){
  int i;
  fprintf(outputfile, "Printing sums:\n"); fflush(stdout);

  for(i = 0; i < n; i++){
    fprintf(outputfile, "Run-step");
    fprintf(outputfile, " %3i - %3i (0x%04x)\n", i, sumArray[i], sumArray[i]);
  }
}

void readDMAUsedRules(void){
  int x;

  /* read types */
  readDMA (ROWS * COLUMNS / 4);
  for (x = 0; x < ROWS * COLUMNS/4; x++) {
    uint32_t rules;

    rules = receiveBuffer[x];
    //fprintf(outputfile, "rules... %x \n", rules); fflush(stdout);
    ruleArray[4*x + 0] = (rules >> 24) & 0xff;
    ruleArray[4*x + 1] = (rules >> 16) & 0xff;
    ruleArray[4*x + 2] = (rules >> 8) & 0xff;
    ruleArray[4*x + 3] = rules & 0xff;
  }
}
void printUsedRules(FILE *outputfile){
  int x;

  /* print used rules */
  fprintf(outputfile, "Printing rules for last dev-step:\n"); fflush(stdout);
  for (x = 0; x < ROWS * COLUMNS; x++) {
    int rule = ruleArray[x];
    //fprintf (outputfile, "Sblock: %i - Rule: ", x); fflush (stdout); 
    if(rule!=0xFF){ //255 mean no rule are fired           
      fprintf (outputfile, "Sblock: %i - Rule: ", x); fflush (stdout);
      fprintf(outputfile, "%i\n", rule);
    }
    else{
      //fprintf(outputfile, "%c\n", '-');
    }
  }
  fprintf (outputfile, "\n\n");

}

void readDMAVector(int n){
  int i, j;
  //256 bit each vector = 8 * 32 bit
  for(i = 0; i < n; i++){
    readDMA(8);
    for(j = 0; j < 8; j++){
      ruleVector[i][j] = receiveBuffer[j];
    }
    //fprintf(outputfile, "\n"); fflush(stdout); 
  }
}

void printVector(int n, FILE *outputfile){
  int value;
  int i, j, k;

  fprintf(outputfile, "Printing rulevectors:\n"); fflush(stdout);

  for(i = 0; i < n; i++){
    fprintf(outputfile, "Rulevector: %i\n", i); fflush(stdout);

    for(j = 0; j < 8; j++){
      value = ruleVector[i][j];
      for(k = 0; k < 32; k++){
        if (value & 0x01){
          fprintf(outputfile, "%i", k+j*32); fflush(stdout);
          if(k+j*32 != 255) fprintf(outputfile, ", "); fflush(stdout);
        }
        value = value >> 1;
      }
    }
    fprintf(outputfile, ".\n"); fflush(stdout);
  }

}

void readAndPrintFitness(FILE *outputfile){
  readDMA(1);
  fprintf(outputfile, "Fitness register: 0x%08x (%3i)\n", (uint32_t)(receiveBuffer[0]), (uint32_t)(receiveBuffer[0]));
  fflush(stdout);
}

/* Write matrix states to ps-file
 */
void printStatesPS(char* filename) {
  FILE *out;
  int i,j;
  out = fopen(filename, "wb");
  printf("...Saving map\n");
  fprintf(out, "%%!PS-Adobe-3.0 EPSF-3,0\n");   
  fprintf(out, "%%BoundingBox: ");             
  
  fprintf(out, "0 0 %i %i\n", ROWS*6, COLUMNS*6);
  fprintf(out, "/en {10 mul} def\n");           

  for (i = 0; i < ROWS ; i++){
    for (j = 0; j < COLUMNS; j++){     
      fprintf(out, "newpath\n");
      fprintf(out, "%i en %i en moveto\n", j, ROWS-i); 
      fprintf(out, "%i en %i en rlineto\n", 1, 0);
      fprintf(out, "%i en %i en rlineto\n", 0, -1);
      fprintf(out, "%i en %i en rlineto\n", -1, 0 );
      fprintf(out, "closepath\n");
      
      if (stateArray[i][j] == 1) {
	//fprintf(out, "0.5 setgray\n");
	fprintf(out, "fill\n");
	//fprintf(out, "0 setgray\n");
      }
      else { 
	fprintf(out, "stroke\n"); 
      }
      
    }
  }       
  fclose(out); 
}
