#include <iostream>
#include <mpi.h>
#include <stdlib.h> 
#include <time.h> 
using namespace std;

//#define N 5
//#define M 102 //m>=100 && m<=1000

int main(int argc, char *argv[]){
	int numprocs, procid, j, s, M, nr,i;
	double startTime, endTime;

	srand(static_cast<unsigned int>(time(NULL)));
	M = rand() % 901 + 100;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	//MPI_Comm_rank(MPI_COMM_WORLD, &procid);
	for (i = 0; i < numprocs; i++){		
		MPI_Comm_rank(MPI_COMM_WORLD, &procid);
		startTime = MPI_Wtime();
		s = 0;
		cout << "Hello from proc " << procid << "!Started procs " << numprocs << "!\n";
		cout << "Proc " << procid << " generates " << M << " numbers: \n";
		for (j = 0; j < M; j++){
			nr = rand() % 10;
			cout << nr << " ";
			s = s + nr;
		}
		cout << "\n";
		cout << "Proc " << procid << " sum=" << s << "\n";
		endTime = MPI_Wtime();
		cout << "Proc " << procid << " took " << endTime - startTime << " seconds to do the job.\n";
	}
	MPI_Finalize();
	system("pause");
	return 0;
}