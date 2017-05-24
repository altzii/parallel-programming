#include <omp.h>
#include <stdio.h>

int main(){
	int a[12], b[12], c[12];

#pragma omp parallel num_threads(12)
	{
#pragma omp for schedule(static, 3)
		for (int i = 0; i < 12; i++){
			a[i] = 5;
			b[i] = 12;
			printf("number of thread is %d, iteration is %d\n", omp_get_thread_num(), i);
		}

	}
	for (int i = 0; i < 12; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");


    for (int i = 0; i < 12; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");

#pragma omp parallel num_threads(4)
    {
#pragma omp for schedule(dynamic, 2)
        for (int i = 0; i < 12; i++) {
            c[i] = a[i] + b[i];
            printf("number of thread is %d, iteration is %d\n", omp_get_thread_num(), i);
        }
    }

    for (int i = 0; i < 12; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");
	return 0;
}
