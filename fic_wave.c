#include <stdio.h>
#include "fic_wave.h"

FILE    *abre_wave(const char *ficWave, float *fm) {
    FILE    *fpWave;
    int fmuestra;

    if ((fpWave = fopen(ficWave, "r")) == NULL) return NULL;
    if (fseek(fpWave, 44, SEEK_SET) < 0) return NULL;
    //Utilizando "fseek" ponemos el offset en el byte 24
    //para extraer los 4 bytes de información y asi obtener la 'fm'
    fseek(fpWave,24, SEEK_SET);
    
    //Leemos los 4 bytes de información sobre la fm
    //que es lo que ocupa el chuk de la frecuencia de muestreo en el earchivo.wav
    fread(&fmuestra,4,1,fpWave);

    //finalemente volvemos a colocar el offset en el byte 24 
    //ya que es donde tenemos la datos de audio
    fseek(fpWave,44,SEEK_SET);

    *fm = (float)fmuestra;
    printf("La fm es: %d Hz\n",fmuestra);
    return fpWave;
}

size_t   lee_wave(void *x, size_t size, size_t nmemb, FILE *fpWave) {
    return fread(x, size, nmemb, fpWave);
}

void    cierra_wave(FILE *fpWave) {
    fclose(fpWave);
}
