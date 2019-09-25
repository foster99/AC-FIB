#include <stdio.h> 

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
    else tag_out = 0;

	printf("%x\t%x\t%x\t%x\t%x\t%x\t%x\t%x\n", address, byte, bloque_m, linea_mc, tag,
			miss, replacement, tag_out);
}

int main() {
    unsigned int address [] = {
        
        0x20f2e110,
        0x20f2e111,
        0x20f26152,
        0x20f2e113,
        0x20f27155,
        0x20f27155,
        0x20f2f116,
        0x20f2e117,
        0x20f26158,
        0x20f2f119,
        0x50f2e210,
        0x20f2e111,
        0x20f26152,
        0x50f2e213,
        0x20f27155,
        0x20f27155,
        0x20f2f116,
        0x50f2e217,
        0x20f26258,
        0x20f2f119
    };
    int i;
    for(i=0; i<20; ++i) reference(address[i]);
}
