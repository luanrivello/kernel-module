#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//#include <unistd.h>

int sum; /* esses dados são compartilhados pelo(s) thread(s) */
void *runner(void *param); /* os threads chamam essa função */

int main(int argc, char *argv[]){
    pthread_t tid[argc-1]; /* o identificador do thread */
    pthread_attr_t attr; /* conjunto de atributos do thread */

    if (argc < 2) {
        fprintf(stderr,"usage: a.out <integer value>\n");
        return -1;
    }

    if (atoi(argv[1]) < 0) {
        fprintf(stderr,"%d must be >= 0\n", atoi(argv[1]));
        return -1;
    }

    /* obtém os atributos default */
    pthread_attr_init(&attr);

    for(int i = 1 ; i < argc ; i++){
        /* cria o thread */
        pthread_create(&tid[i-1],&attr, runner, argv[i]);
    }

    for(int j = 0 ; j < argc-1 ; j++){
        /* espera o thread ser encerrado */
        pthread_join(tid[j],NULL);
    }

    //sleep(1);

}

/* O thread assumirá o controle nessa função */
void *runner(void *param){
    int a, upper = atoi(param);
    sum = 0;

    for (a = 1; a <= upper; a++)
        sum += a;

    printf("sum = %d\n", sum);

    pthread_exit(0);
}
