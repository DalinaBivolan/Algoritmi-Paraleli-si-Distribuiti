# include <iostream>
#include "mpi.h"

#define SIZE 24

using namespace std;

int main(int argc, char *argv[])
{
	const int searchedNumber = 7;

	int numProc;
	int slice;
	int v[SIZE];
	int nrIndex[SIZE];
	int resultIndex;
	int maxIndex;

	MPI_Init(&argc, &argv);	

	int procId;
	MPI_Comm_rank(MPI_COMM_WORLD, &procId);


	if (procId == 0)
	{
		for (int i = 0; i < SIZE; ++i)
		{
			v[i] = rand() % 10;
			nrIndex[i] = -1;
			cout << v[i] << " ";
		}
		cout << endl << endl;
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(v, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

	MPI_Comm_size(MPI_COMM_WORLD, &numProc);
	slice = SIZE / numProc;

	int start = slice * procId;
	int end = start + slice;
	int count = 0;

	for (int i = start; i < end; ++i)
	{
		if (v[i] == searchedNumber)
			nrIndex[count++] = i;
	}
	for (int i = 0; i < count; i++){
		cout << "Procesul " << procId << " a gasit numarul pe pozitiile : " << nrIndex[i] << " ";
	}
	maxIndex = nrIndex[0];
	for (int i = 0; i <= SIZE; ++i)
	{
		if (nrIndex[i] > maxIndex)
			maxIndex = nrIndex[i];
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Reduce(&maxIndex, &resultIndex, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (procId == 0)
	{
		if (resultIndex < 0)
			cout << "Element not found!" << endl;
		else
			cout << "\nMaximum position for " << searchedNumber << " is : " << resultIndex << endl;
	}

	MPI_Finalize();
	cout << endl;
	return 0;
}