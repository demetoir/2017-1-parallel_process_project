// tt.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include "mpi.h"
#include <time.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <direct.h>

using namespace std;
#define MAX_DATA 100
#define BUSSY_TIME 400
// cmd : 
//
// mpiexec -n 5 \\M-5-2-5\m-5\project\M-5_project\Debug\M-5_project.exe
//
//
int main(int argc, char **argv){
	int rank;
	int size;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int namelen;
	char buff[MAX_DATA];
	char recvBuff[MAX_DATA];

	int i;
	clock_t startTime;
	clock_t endTime;
	startTime = clock();

	char currentPath[_MAX_PATH];
	_getcwd(currentPath, _MAX_PATH);



	char fileName[MAX_DATA];

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(processor_name, &namelen);
	
	sprintf(fileName, "\\\\M-5-2-5\\m-5\\project\\M-5_project\\Debug\\rank_%d.txt", rank);
	FILE *fp = fopen(fileName, "w");
	fprintf(fp,"com name = %s , rank = %d \n", processor_name, rank);
	fclose(fp);
	if (rank == 0){
		// send massage to device
		//for (i = 1; i< size; i++){
		//	sprintf(buff, "hello from rank 0 to rank %d \n", rank);
		//	MPI_Send(buff, MAX_DATA, MPI_CHAR, i, 0, MPI_COMM_WORLD);
		//	fprintf(fp, "rank 0 : send msg %s\n", buff);
		//}

		// recv 
		printf("rank 0: start recv\n");
		fflush(stdout);
		for (i = 1; i< size; i++){
			MPI_Recv(buff, MAX_DATA, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			printf("rank 0 recv :%s\n", buff); 
			fflush(stdout);
		}
		printf("rank 0: end recv\n");
	}
	else{
		//fprintf(fp, "rank %d :recv  start\n", rank);
		//// recv from rank 0
		//MPI_Recv(recvBuff, MAX_DATA, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		//fprintf(fp, "%s\n", recvBuff);
		//fflush(stdout);
		//fprintf(fp, "rank %d :recv end\n", rank);



		//bussy wait
		int a = 0;
		for (int j = 0; j < BUSSY_TIME; j++){
			for (int i = 0; i < 1000000; i++){
				a += i;
			}
		}
		

		printf( "rank %d : send start\n", rank);

		//send result 
		//sprintf(buff, "### Process %d, rank = %d from %s ### a = %d, recv: %s", rank, rank, processor_name, a, recvBuff); 
		sprintf(buff, "com name = %s,rank = %d, path = %s\n", processor_name, rank, currentPath);

		fflush(stdout);
		MPI_Send(buff, MAX_DATA, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

		printf( "rank %d : send end\n", rank);

	}

	MPI_Finalize();
	
	if (rank == 0){
		endTime = clock();
		cout << "수행시간 :" << (double)(endTime - startTime) << "ms" << endl;
	}




	//fclose(fp); 
	return 0;
}


