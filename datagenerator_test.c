#include <stdio.h>
#include <string.h>

#include "datagenerator.h"

int main()
{    
    // new variables
    int i,j,k;
    char Mfile[256], Sfile[256], Permfile[256];
    int cf_numbers[] = {1,1,1,1,1,1,1,1,1,1,1,1,5,3,5};
    int func_num;
    int dim;
    double Mdata[4500], Sdata[150];
    FILE* fid;
    //double Qout[900];
    int shuffle[30];
    int cf_number;
    
    cec15_reseed(12345, 67890, 98765, 43210);
    
    for (func_num = 1; func_num <= 15; func_num++) {
        for (dim = 10; dim<=30; dim+= 20){
            sprintf(Mfile, "M_%d_D%d.txt",func_num,dim);
            sprintf(Sfile, "shift_data_%d_D%d.txt", func_num, dim);
            sprintf(Permfile, "shuffle_data_%d_D%d.txt", func_num, dim);
            cf_number = cf_numbers[func_num-1];
            
            //Mdata = (double*)malloc(dim*cf_number*dim*sizeof(double));
            for (i = 1; i<= cf_number; i++) {
                cec15_rotate(dim, Mdata+(i-1)*dim);
            }
            
            //Sdata = (double*)malloc(dim*cf_number*sizeof(double));;
            for (i = 1; i<= cf_number; i++) {
                cec15_rand_matrix(1, dim, Sdata+(i-1)*dim);
                for (j=0; j<dim; j++){
                    *(Sdata+(i-1)*dim+j) *= 160.0;
                    *(Sdata+(i-1)*dim+j) -= 80.0;
                }
            }
            cec15_shuffle(dim, shuffle);
            
            fid = fopen(Permfile,"w");
            for (k=0; k<dim; k++)
                fprintf(fid,"%d\t", shuffle[k]);
            fclose(fid);
            
            fid = fopen(Mfile,"w");
            for (j=0; j<cf_number*dim; j++) {
                for (k=0; k<dim; k++) {
                    fprintf(fid,"%24.16e ", Mdata[j*dim + k]);
                }
                fprintf(fid,"\n");

            }
            fclose(fid);


            fid = fopen(Sfile,"w");
            for (j=0; j<cf_number; j++) {
                for (k=0; k<dim; k++) {
                    fprintf(fid,"%24.16e ", Sdata[j*dim + k]);
                }
                fprintf(fid,"\n");
            }
            fclose(fid);
            
            //free(Mdata);
            //free(Sdata);
            
        }
    }
    return 0;
}
