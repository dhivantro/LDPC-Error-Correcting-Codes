#include <stdio.h>
#define row_B 46
#define column_B 68
#define expFactor 5

//codeword size: row_B * expFactor

int H [row_B*expFactor] [column_B*expFactor];
//int Hnew[][]={};

void pchk2alist();
void alist2pchk();

int main(){

 

  //pchk2alist();
  alist2pchk();
 
  
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

     //Find max number of ones in column
     int num_c=0, num_r=0;
     
     for (i=0; i< (1); i++)
       {
	 for (j=0; j < (column_B*expFactor); j++)
	   {
	     if (H[i][j] != 0)
	       {			        
		 num_c+=1;
	       }
	   
		
	   }
	 //printf("%d ",num);
       }

     for (i=0; i< (1); i++)
       {
	 for (j=0; j < (row_B*expFactor); j++)
	   {
	     if (H[j][i] != 0)
	       {			        
		 num_r+=1;
	       }
	   
		
	   }
	 //printf("\n%d\n ",num_r);
       }

	 
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
		 //pos_temp[x] = pos[x];
		 //printf(" %d",pos[x]);
		 fprintf(file, "%d ", pos[x]);
		 //num+=1;
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
     
     fclose(file);
}

void alist2pchk(){

  int rowH, columnH, maxinrow, junk, maxincol;
 
  int i, j;
  
   FILE * f;
   f = fopen ("1_2_5.alist", "r+");

   fscanf(f, "%d",&rowH);
   fscanf(f, "%d",&columnH);
   int Hnew[rowH][columnH];

   fscanf(f, "%d",&maxinrow); //19
   fscanf(f, "%d",&maxincol); //30


   //Number of 1s in each row
   int numbers_row[rowH], nummax[rowH];;

   for (i=0; i<rowH; i++)
     {
       fscanf(f, "%d",&numbers_row[i]);
       //printf("\n%d ",numbers[i]);
     }

   //For rows in alist
   for(i=0; i<rowH; i++)
     {
       nummax[i] = maxinrow;
     }

   int numbers_col[columnH];
    for (i=0; i<columnH; i++)
     {
       fscanf(f, "%d",&numbers_col[i]);
       //printf("\n%d ",junk2[i]);
     }

    int position[rowH][maxinrow];
    for (i=0; i<rowH; i++)  //initialise as all zeros
      {
	for (j=0; j<maxinrow; j++)
	  {
	    position[i][j] = 0;
	  }
      }

    //scan every row in alist H, in each row: put each element in each column
    for (i=0; i<rowH; i++)
      {
	for (j=0; j<numbers_row[i]; j++)
	  {
	    fscanf(f, "%d",&position[i][j]);
	    //printf("%d ",position[i][j]);
	  }
	//printf("\n");
      }

    //Sum numbers array
    int sum=0;
    for (i=0; i<rowH; i++)
      {
	sum+=numbers_row[i];
      }
    //printf("%d ",sum);

    int ii[sum], jj[sum];

    for (i=0; i<sum; i++)
      {
	ii[i] = 0;
	jj[i] = 0;
      }
    
    int k = 0;
    for (i=0; i<rowH; i++)
      {
	for (j=0; j<(numbers_row[i]); j++)
	  {
	    jj[k] = i;
	    ii[k] = position[i][j];
	    k+=1;
	  }
      }

    //Initialise all 0 H
    for (i = 0; i<rowH; i++)
      {
	for (j=0; j<columnH; j++)
	  {
	    
	     H[i][j]=0;
	      
	  }
      }

   
    FILE * p;
    p = fopen ("PCHK", "w+");

     for (i = 0; i<rowH; i++)
      {
	for (j=0; j<numbers_row[i]; j++)
	  {
	    //printf("%d ",position[i][j]);
	    H [i] [(position[i][j])]=1;
	    	    	      
	  }
	//printf("\n");
      }

     for (i = 0; i<rowH; i++)
      {
	for (j=0; j<columnH; j++)
	  {
	    
	    printf("%d", H[i][j]);
	    fprintf(p,"%d", H [i][j]);
	      
	  }
	printf("\n");
	fprintf(p,"\n");
      }
    
}
