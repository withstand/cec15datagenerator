#include <stdio.h>

#include "datagenerator.h"

int  main()
{
	int m=4;
	int k;
	double shift[10];
	int shuffle[10];
	double Qout[100];
	FILE* fid;
	char filename[256];
	int i,j;

	cec15_reseed(10,20,30,40);

	for(i=0; i<10; i++)
	{
		cec15_print_state();
		printf("%g\n", cec15_rand());
	}


	cec15_reseed(10,20,30,40);

	for (k=0; k<10; k++)
	{
		cec15_rotate(m, Qout);
		sprintf(filename,"M4-%d.txt", k+1);
		fid = fopen(filename, "w");
		for (i=0; i<m; i++)
		{
			for (j=0; j<m; j++)
			{
				fprintf(fid, "%15.6e\t", Qout[i*m+j]);
			}
			fprintf(fid,"\n");
		}
		fclose(fid);
	}



	cec15_shift(m, shift);
	sprintf(filename,"shift-%d.txt",m);
	fid = fopen(filename, "w");
	for (i=0; i<m; i++)
	{
		fprintf(fid, "%15.6e\t", shift[i]);
	}
	fprintf(fid,"\n");
	fclose(fid);




	cec15_shuffle(m, shuffle);

	sprintf(filename,"shuffle-%d.txt",m);
	fid = fopen(filename, "w");
	for (i=0; i<m; i++)
		fprintf(fid, "%.0f\t", shuffle[i]);
	fprintf(fid,"\n");
	fclose(fid);


	return 0;
}