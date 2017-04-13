#include <mpi.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

#define MASTER 0
#define ARRAYSIZE 40

int main(int argc, char* argv[]) {
	int procid, numprocs, nr;
	int nvalues, low, high;
	int b[ARRAYSIZE];
	int result;
	int finalResult;
	int i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &procid);//obtinerea id-ului unic al procesului curent
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);//obtinerea dimensiunii comunicatorului
	
	if (procid == MASTER) {
		cout << "MASTER: Number of MPI procs is: " << numprocs << "\n";
		for (i = 0; i < ARRAYSIZE; ++i) {
			cout << "b[" << i << "]= ";
			b[i] = rand() % 10;
			cout << b[i] << "\n";
		}
		cout << "Search number: ";
		cin >> nr;
	}

	MPI_Bcast(b, ARRAYSIZE, MPI_INT, MASTER, MPI_COMM_WORLD);

	nvalues = ARRAYSIZE / numprocs;
	low = procid*nvalues;
	high = low + nvalues;
	for (i = low; i < high; i++) {
		if (b[i] == nr) {
			result = i;
			break;
		}
	}
	cout << "\n";

	MPI_Reduce(&result, &finalResult, 1, MPI_INT, MPI_MAX, MASTER, MPI_COMM_WORLD);

	if (procid == MASTER){
		cout << "The MAX index is : " << finalResult;
	}
	
	MPI_Finalize();
	return 0;
}