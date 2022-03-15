//This is the LDPC Decoder block (1st half)
//Initialisation and row operation steps are
//conducted here

//Import 2D H array from txt file
//Size of H = Size of L


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //for uint8_t
#include <limits.h> // For INT_MAX in row operation

#define row_B 4
#define column_B 5
#define expFactor 1
#define row_L (row_B*expFactor)
#define column_L (column_B*expFactor)

int z = expFactor;
//int Lr = (Brows*z); //# rows in L
//int Lc = (Bcols*z); //# cols in L

//uint8_t *input; //get input from detector
//uint8_t *output;
//float *L_arr = (float*)malloc(Lr * Lc * sizeof(uint8_t));
double L[row_L][column_L];
double temp[row_L][column_L];
double Lnew[row_L][column_L];
double sign[row_L][column_L];

int i, j, k;

int H[4][5] = {
		{1,1,1,0,1},
		{0,1,1,1,0},
		{1,1,0,1,0},
		{1,0,1,0,1}};
  

void update_parity_L(float n, int i){

  for(j=0; j<column_L; j++)
    {
      if(L[i][j]<0 && n>0)
	{
	  Lnew[i][j] = Lnew[i][j] * -1;
	}
      else if (L[i][j]>0 && n<0)
	{
	  Lnew[i][j] = Lnew[i][j] * -1;
	}
      //printf("L[%d][%d]: %f ",i,j,L[i][j]);
    }
  printf("\n");
  printf("\n n: %f",n);
}

void get_parity_L(){

  float n = 1;
  int x = 1;

  for(i=0; i<row_L; i++)
    {
      for(j=0; j<column_L; j++)
	{
	  if(L[i][j] != 0.0)
	    {	      	      
	       n = n * L[i][j];
	    }
	}     
      
      update_parity_L(n, i);
      n = 1; //reset n
    }

}
  
void print_L_matrix(){

   printf("\n\n-------Printing Updated L Matrix------- \n \n");

    for(i=0; i<row_L; i++)
    {
      for(j=0; j<column_L; j++)
	{
	   
	  printf("%f ",L[i][j]);
	    
	}
      printf("\n");
    }
}

void update_L_matrix(){

   printf("\n\n\n------Updating L Matrix ----------- \n \n");

    for(i=0; i<row_L; i++)
    {
      for(j=0; j<column_L; j++)
	{	   
	  L[i][j] = Lnew[i][j];
	}
    }
}

void Adjust_Row_Element(double first, double second, int index){

  int start = 0; //1st non zero position in L
  
  // printf("\n f: %f  s: %f ",first, second);
   
      for(j=0; j<column_L; j++)
	{
	  if (L[index][j] == 0)
	    {
	      //j++;
	    }

	  else if (start == 0)
	    {
	      Lnew[index][j] = second;
	      start = 1; //update
	    }
	  else if (start != 0)
	    {
	      Lnew[index][j] = first;
	      start = 1; //update
	    }
	}
    
   
}

void row_operation(){

  int i, j, k;
  double first, second;

  first = second = INT_MAX;

  //reset negative sign
  for(i=0; i<row_L; i++)
    {
      for(j=0; j<column_L; j++)
	{
	   if (L[i][j] < 0)
	    {
	      temp[i][j] = L[i][j]*(-1);
	    }

	   else
	     {
	       temp[i][j] = L[i][j];
	     }
	}
    }

  printf("\n");

    for(i=0; i<row_L; i++)
    {
      for(j=0; j<column_L; j++)
	{
	   
	  printf("%f ",temp[i][j]);
	    
	}
      printf("\n");
    }
    
  //Row Operation Starts
  for(i=0; i<row_L; i++)
    {
      for(j=0; j<column_L; j++)
	{

	  // if (temp[i][j] == 0.0 )
	  //  {
	      //j++; //if comment out this part, it can work
	      //second = first;
	      //first = temp[i][j];
	      //printf("\nfirst: %f",first);
	      
	  //  }
	  if (H[i][j] != 0.0){
	  
	   if (temp[i][j] < first )
	    {
	      //If current element smaller than first, update first and second
	      second = first;
	      //printf("\n sec: %f ",second);
	      first = temp[i][j]; //update first to current element
	      //printf("\n col [%d][%d]   %f     %f",i,j,first,second);
	      //printf("\nfirst: %f",first);
	      
	    }//1
	  
	  else if (temp[i][j] < second && temp[i][j] != first )
	    {	     
	      //if current element in between first and second
	    
		  second = temp[i][j];

	      //printf("\n col [%d][%d]   %f     %f",i,j,first,second);
	      //printf("\nfirst: %f",first);
		  
	    }//2

	  else if (temp[i][j] == first)
	    {
	      second = first;
	      //printf("\nfirst: %f",first);
	    }//3

	  else if (temp[i][j] < first && L[i][j]!=0.0 )
	    {
	      second = temp[i][j];
	    }//4	   
	   
	  }//if H!=0
	 
	}
      printf("\n\nRow %d: smallest: %f \t2nd smallest: %f ",i,first,second);
      Adjust_Row_Element(first, second, i);
      first = second = INT_MAX; //reset values
      //printf("\n col [%d][%d]   %f     %f",i,j,first,second);
    }


  //print_L_matrix(); //Only magnitude
   
}//fx

void L_row_operation(){

  row_operation(); //Get magnitude
  get_parity_L(); //Get the sign first
  
  update_L_matrix(); //Updating magnitude with sign
}

void L_initial(){

  int i, j ,k;

 
  //double input[] = {0.2,-0.3,1.2,-0.5,0.8};
  //double input[] = {0.0,0.0,0.0,0.0,0.0};
  //double input[] = {1,0,1,0,1};
  double input[] = {1,1,1,1,1};

  //This part gets H 

  //Dynamically allocate L, make L size=H size

  //input col[1] = L 1st col(wherever non zero)

  //if(L[i][1]==1): L[i][j]=input[j]

  for(i=0; i<column_L; i++)
    {
      for(j=0; j<row_L; j++)
	{
	  if (H[j][i] == 0)
	    {
	      L[j][i] = 0;
	    }
	  else
	    {
	       L[j][i] = input[i];
	    }
	   
	}
    }//for

    for (i=0; i<row_L; i++)
    {
      for (j=0; j<column_L; j++)
	{
	   printf("%f ", L[i][j]);
	}
       printf("\n");
    }

  /*
  //dynamic memory ver
    for(i=0; i<Lr; i++) //row
    {
      for(j=0; j<Lc; j++)
	{
	  if(*(H_arr + i*Lc + j) == 0)
	    {
	      *(L_arr + i*Lc + j) = 0;
	    }
	  else
	    {
	      *(L_arr + i*Lc + j) = *(H_arr + i*Lc + j);
	    }
	}
    }
  */
  
}//fx


int main(){

  int i, j, k;

  //uint8_t *input; //get input from detector
  //uint8_t *output;

  int size;
  
  int *A;
  A = (int*)malloc(size * sizeof(uint8_t));

  //Get values from make file to calculate size of L
  

  //int *L_arr = (int*)malloc(Lr * Lc * sizeof(uint8_t));

  /*  //Assign 0 to the whole L matrix
  for(i=0; i<Lr; i++) //row
    {
      for(j=0; j<Lc; j++)
	{
	  *(L_arr + i*Lc + j) = 0;
	}
    }
  */
  
  for (i=0; i<row_L; i++)
    {
      for (j=0; j<column_L; j++)
	{
	  L[i][j]=0;
	}
    }

   for (i=0; i<row_L; i++)
    {
      for (j=0; j<column_L; j++)
	{
	  // printf("%f ", L[i][j]);
	}
      // printf("\n");
    }
   
  L_initial(); //initialisation
  L_row_operation();
  
  print_L_matrix();

 
  //deallocate
  free(A);
  //free(L);

}//main fx

