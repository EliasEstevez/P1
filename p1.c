#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "pav_analysis.h"
#include "fic_wave.h"

int main(int argc, char *argv[]) { //argc es el numero de parametros pasados 1=funciónes 2='1'+archivo de audio
                                   // 3='2'+archivo.txt 
    float durTrm = 0.010;
    float fm;
    int   N;
    int   trm;
    float *x;
    short *buffer;
    FILE  *fpWave;
    //FILE  *fpResult;
    FILE *f_write=fopen(argv[2],"w");
    FILE *p_write=fopen("potencia.txt","w");
    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Empleo: %s inputfile [outputfile]\n", argv[0]);
        return -1;
    }

    if ((fpWave = abre_wave(argv[1], &fm)) == NULL) {
        fprintf(stderr, "Error al abrir el fichero WAVE de entrada %s (%s)\n", argv[1], strerror(errno));
        return -1;
    }

    N = durTrm * fm;
    if ((buffer = malloc(N * sizeof(*buffer))) == 0 ||
        (x = malloc(N * sizeof(*x))) == 0) {
        fprintf(stderr, "Error al ubicar los vectores (%s)\n", strerror(errno));
        return -1;
    }
    //if (argc==3)
    //{
      //  fpResult=fopen(argv[2],"at");// abrimos el archivo.txt pasado como parametro para escribir al final
    //}
    
    
    trm = 0;
    while (lee_wave(buffer, sizeof(*buffer), N, fpWave) == N) {
        for (int n = 0; n < N; n++) x[n] = buffer[n] / (float) (1 << 15);

       if(argc==3)//Miramos si nos han pasado un parametro extra para escribir los resultados en el
       {
        //Escribimos en el fichero pasado como parametro
        fprintf(f_write,"%d\t%f\t%f\t%f\n", trm, compute_power(x, N),
                                        compute_am(x, N),
                                        compute_zcr(x, N, fm));

        fprintf(p_write,"%f\n",compute_power(x, N));
    
    
       }
       else{
        printf("%d",argc);
        printf("%d\t%f\t%f\t%f\n", trm, compute_power(x, N),
                                        compute_am(x, N),
                                        compute_zcr(x, N, fm));
        }
        trm += 1;
    }
   // if(argc==3){
     //   fclose(fpResult); //Cerramos el archivo.txt
    //}
    cierra_wave(fpWave);
    free(buffer);
    free(x);

    return 0;
}
