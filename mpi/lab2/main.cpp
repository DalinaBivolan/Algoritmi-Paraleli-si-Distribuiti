#include "mpi.h"
#include <time.h>
#include <iostream>
using namespace std;

#define SIZE 12
#define NR 0

int main(int argc, char *argv[])
{
	int rank, numProcs, slice, index;
	int array[SIZE], segment[SIZE], found[SIZE], finalFound[SIZE + 10];
	bool display = false;

	srand((unsigned int)time(NULL));

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

	slice = SIZE / numProcs;
	if (SIZE % numProcs != 0)
		++slice;

	MPI_Barrier(MPI_COMM_WORLD);

	if (rank == 0)
	{
		cout << "Array elements are:\n";
		for (int i = 0; i < SIZE; i++)
		{
			array[i] = rand() % 5;
			cout << array[i] << " ";
			finalFound[i] = -1;
		}
		//cout << "Searched number is: ";
		//cin >> NR;
		//cout << "\n";
	}

	MPI_Scatter(array, slice, MPI_INT, segment, slice, MPI_INT, 0, MPI_COMM_WORLD);
	cout << "\n\nRank: " << rank << ". Segement size: " << slice << "\n";

	for (int i = 0; i < slice; i++)
		found[i] = -1;

	index = 0;
	for (int i = 0; i < slice; i++)
	{
		if (segment[i] == NR)
		{
			found[++index] = i + rank * slice;
		}
	}

	MPI_Gather(found, slice, MPI_INT, finalFound, slice, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		for (int i = 0; i < SIZE + 10; i++)
		{
			if (finalFound[i] >= 0)
			{
				if (!display)
					cout << "\n\nNumber found on the follwing position(s): \n";
				display = true;
				cout << finalFound[i] << " ";
			}
		}
		if (!display)
			cout << "\n\nNumber not found.";
	}

	MPI_Finalize();
	cout << endl;
	return 0;
}