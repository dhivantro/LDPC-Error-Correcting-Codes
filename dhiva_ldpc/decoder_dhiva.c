//This is the LDPC Decoder block (1st half)
//Initialisation and row operation steps are
//conducted here

//Import 2D H array from txt file
//Size of H = Size of L


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //for uint8_t


void L_initial( uint8_t *input, uint8_t *output);
  
int main(){

  int i, j, k;

  uint8_t *input; //get input from detector
  uint8_t *output;

  int size;
  
  int *A;
  A = (int*)malloc(size * sizeof(uint8_t));

  //Get values from make file to calculate size of L
  //Brows: Num of rows in B
  //Bcols: Num of cols in B
  //z: expansion factor
  int Lr = (Brows*z); //# rows in L
  int Lc = (Bcols*z); //# cols in L

  int *L_arr = (int*)malloc(Lr * Lc * sizeof(uint8_t));

  //Assign 0 to the whoe L matrix
  for(i=0; i<Lr; i++) //row
    {
      for(j=0; j<Lc; j++)
	{
	  *(L_arr + i*Lc + j) = 0;
	}
    }
  
  L_initial(input, output); //initialisation
 
  //deallocate
  free(A);
  free(L_arr);

}//main fx

void L_initial( uint8_t *input, uint8_t *output){

  int i, j ,k;

  //This part gets H (either txt file or using method dynamic array

  //Dynamically allocate L, make L size=H size

  //input col[1] = L 1st col(wherever non zero)

  //if(L[i][1]==1): L[i][j]=input[j]

  for(i=0; i<Hcol; i++)
    {
      for(j=0; j<Hrow; j++)
	{
	  if 
	}
    }
  
}//fx
