#include "CacheSim.h"

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */



struct linea {
    char v;
    unsigned int tag;
    //unsigned int data[32];
};

int hit_count;

struct linea cache[128];

/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al començar cada un dels tests.
 * */
void init_cache ()
{
    totaltime=0.0;
    hit_count = 0;
    int i;
	for(i=0; i<128; ++i) cache[i].v = '0';
}

/* La rutina reference es cridada per cada referencia a simular */ 
void reference (unsigned int address)
{
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int linea_mc;
	unsigned int tag;
	unsigned int miss;	   // boolea que ens indica si es miss
	unsigned int replacement;  // boolea que indica si es reemplaça una linia valida
	unsigned int tag_out;	   // TAG de la linia reemplaçada
	float t1,t2;		// Variables per mesurar el temps (NO modificar)
	
	t1=GetTime();
	/* Escriu aqui el teu codi */
    
    byte = address & 31; //5b menos significativos para offset
    bloque_m = address >> 5;
    linea_mc = bloque_m%128;
    tag = address >> 12;
    
    // Hit (especulation)
    miss = 0;
    replacement = 0;
    
    if (cache[linea_mc].v == '0')  miss = 1;
    else if (cache[linea_mc].tag != tag)  {
        miss = 1;
        replacement = 1;
    }
    else ++hit_count;
    
    if (miss) {
        if (replacement) tag_out = cache[linea_mc].tag;
        cache[linea_mc].tag = tag;
        cache[linea_mc].v = '1';
    }

	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual. També mesurem el temps d'execució
	 * */
	t2=GetTime();
	totaltime+=t2-t1;
	test_and_print (address, byte, bloque_m, linea_mc, tag,
			miss, replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */ 
void final ()
{
   // char buffer[64];
   // sprintf(buffer,"aciertos %d\n",hit_count);
   // write(1,buffer,strlen(buffer));
}
