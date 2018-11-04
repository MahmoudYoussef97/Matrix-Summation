#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define M 3
#define K 3
#define N 3


int A[M][M] = {{1, 4 , 4}, {2, 5 , 8}, {3, 6 , 8}};
int B[M][M] = {{8, 7, 6}, {5, 4, 3},{2, 5 , 8}};
int C[M][M];

struct v
{
    int i;          /* rows */
};

//The thread will begin control in this function
void *runner(void *param)
{
    int n;
    struct v *data = param; // the structure that holds our data
    for(n = 0; n < M; n++)
    C[data->i][n] = A[data->i][n] + B[data->i][n];

    //Exit the thread
    pthread_exit(0);
}


int main(int argc, char *argv[])
{

    int i, j;
    for (i = 0; i < M; i++)
    {
            //Assign a row for each thread
            struct v *data = (struct v *)malloc(sizeof(struct v));
            data->i = i;
            /* Now create the thread passing it data as a parameter */
            pthread_t tid;       //Thread ID
            pthread_attr_t attr; //Set of thread attributes
            //Get the default attributes
            pthread_attr_init(&attr);
            //Create the thread
            pthread_create(&tid, &attr, runner, data);
            //Make sure the parent waits for all thread to complete
            pthread_join(tid, NULL);
    }

    //Print out the resulting matrix
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
}

