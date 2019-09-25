#include "CacheSim.h"

struct vias {
    unsigned int v;
    unsigned int tag;
};

struct conjunto {
    
    unsigned int LRU;
    struct vias via[2];
};

struct conjunto cache[64];



void init_cache ()
{
    totaltime=0.0;
    
    int i;
	for(i=0; i<64; ++i) {
        cache[i].via[0].v = 0;
        cache[i].via[1].v = 0;
        cache[i].LRU = 0;
    }

}

/* La rutina reference es cridada per cada referencia a simular */ 
void reference (unsigned int address)
{
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int conj_mc;
	unsigned int via_mc;
	unsigned int tag;
	unsigned int miss;	   // boolea que ens indica si es miss
	unsigned int replacement;  // boolea que indica si es reemplaça una linia valida
	unsigned int tag_out;	   // TAG de la linia reemplaçada
	float t1,t2;		// Variables per mesurar el temps (NO modificar)
	
	t1=GetTime();
	
    
    
    byte = address%32; //5b menos significativos para offset
    bloque_m = address/32;
    conj_mc = bloque_m%64;
    tag = address >> 11;
    
    if (cache[conj_mc].via[0].v) {
        miss = 0;
        if (cache[conj_mc].via[0].tag == tag) cache[conj_mc].LRU = 0;
        else miss = 1;     
    }
    else if (miss && cache[conj_mc].via[1].v) {
        
        miss = 0;
        if (cache[conj_mc].via[1].tag == tag) cache[conj_mc].LRU = 1;
        else miss = 1;    
    }
    
    if (miss) {
        
        if (!cache[conj_mc].via[0].v) {
            replacement = 0;
            via_mc = 0;
        }
        else if (!cache[conj_mc].via[1].v) {
            replacement = 0;
            via_mc = 1;
        }
        
        else {
            replacement = 1;
            
            if (cache[conj_mc].LRU) via_mc = 0;
            else via_mc = 1;
            
            tag_out = cache[conj_mc].via[via_mc].tag;
        }
        
        cache[conj_mc].via[via_mc].tag = tag;
        cache[conj_mc].via[via_mc].v = 1;
        cache[conj_mc].LRU = via_mc;
        
        
    }


	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual. També mesurem el temps d'execució
	 * */
	t2=GetTime();
	totaltime+=t2-t1;
	test_and_print2 (address, byte, bloque_m, conj_mc, via_mc, tag,
			miss, replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */ 
void final ()
{
 	/* Escriu aqui el teu codi */ 
  
  
}
