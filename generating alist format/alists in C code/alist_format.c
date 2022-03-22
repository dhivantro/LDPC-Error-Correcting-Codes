#include <stdio.h>
#define row_B 46
#define column_B 68
#define expFactor 5

//codeword size: row_B * expFactor

int H [row_B*expFactor] [column_B*expFactor];

void pchk2alist();

int main(){

 

  pchk2alist();
  
 
  
}


void pchk2alist(){

  int i,j,k;

  FILE* f;
  f=fopen("H_matrix.txt", "r"); //reading dense matrix

  if (!feof(f))
    {
      for (i=0;i< (row_B*expFactor) ;i++)
        {
	  for (j=0;j< (column_B*expFactor) ;j++)
            {
                fscanf(f, "%d",&H[i][j]);
               
            }
        }
    }
   fclose(f);
   
   /*
   //Printing H matrix
   for (i=0;i< (row_B*expFactor) ;i++)
        {
	  for (j=0;j< (column_B*expFactor) ;j++)
            {
               printf("%d",H[i][j]);
               
            }
	  printf("\n");

	}
   */

   //Write size of H matrix
   FILE * file;
   file = fopen ("1_2_5.alist", "w+");
   fprintf(file, "%d %d\n", row_B*expFactor, column_B*expFactor);
   int sum = 0;
   //Sum matrix in each row (Weight in row)
   int row_weight [row_B*expFactor];
   int row_temp [row_B*expFactor];

   for (i=0; i< (row_B*expFactor); i++)
     {
       for (j=0; j< (column_B*expFactor); j++)
	 {
	   if (H[i][j] == 1)
	     {
	       sum+=1;
	     }
	   
	 }
       //printf("%d ",sum);
       //fprintf(file, "%d ", sum);
       row_weight[i] = sum;
       row_temp[i] = sum;
       sum = 0; //reset before new row
     }

   
   //Sum matrix in each column (Weight in column)
   int column_weight [column_B*expFactor];
   int column_temp [column_B*expFactor];

   for (i=0; i< (column_B*expFactor); i++)
     {
       for (j=0; j< (row_B*expFactor); j++)
	 {
	   if (H[j][i] == 1)
	     {
	       sum+=1;
	     }
	   
	 }
       //printf("%d ",sum);
       //fprintf(file, "%d ", sum);
       column_weight[i] = sum;
       column_temp[i] = sum;
       sum = 0; //reset before new column      
     }

   //Find max weight
   for (i=0; i< (row_B*expFactor); i++)
     {
       if (row_temp[0] < row_temp[i])
	 {
	   row_temp[0] = row_temp[i];
	 }
     }

    for (i=0; i< (column_B*expFactor); i++)
     {
       if (column_temp[0] < column_temp[i])
	 {
	   column_temp[0] = column_temp[i];
	 }
     }

    //Writing max weight to file
    fprintf(file,"%d %d\n", row_temp[0], column_temp[0]);

    //Writing weight in each row and column to file
     for (i=0; i< (row_B*expFactor); i++)
     {
       fprintf(file, "%d ", row_weight[i]);
     }
     
     fprintf(file, "\n");

      for (i=0; i< (column_B*expFactor); i++)
     {
       fprintf(file, "%d ", column_weight[i]);
     }

     fprintf(file, "\n");

     //Writing column index of non-zero elements in each row
     int pos[]={}, pos_temp[]={0};
     int x=0;
     for (i=0; i< (row_B*expFactor); i++)
       {
	 for (j=0; j < (column_B*expFactor); j++)
	   {
	     if (H[i][j] != 0)
	       {
		 pos[x] = j+1;
		 pos_temp[x] = pos[x];
		 //printf(" %d",pos[x]);
		 fprintf(file, "%d ", pos[x]);
	       }
	   
		 //printf("%d ",pos_temp[0]);
	   }
	   

	 
	 //printf("\n");
	 fprintf(file, "\n");
	 x=0;
       }

     
     int pos2[]={};
     for (i=0; i< (column_B*expFactor); i++)
       {
	 for (j=0; j < (row_B*expFactor); j++)
	   {
	     if (H[j][i] != 0)
	       {
		 pos2[x] = j+1;		
		 fprintf(file, "%d ", pos2[x]);
	       }
	  
	   }
	 //printf("\n");
	 fprintf(file, "\n");
       }
     
     
}
