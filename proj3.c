/**TODO Valgrind TODO
 * Kostra programu pro 3. projekt IZP 2017/18
 *
 * Jednoducha shlukova analyza
 * Unweighted pair-group average
 * https://is.muni.cz/th/172767/fi_b/5739129/web/web/usrov.html
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h> // sqrtf
#include <limits.h> // INT_MAX

/*****************************************************************
 * Ladici makra. Vypnout jejich efekt lze definici makra
 * NDEBUG, napr.:
 *   a) pri prekladu argumentem prekladaci -DNDEBUG
 *   b) v souboru (na radek pred #include <assert.h>
 *      #define NDEBUG
 */
#ifdef NDEBUG
#define debug(s)
#define dfmt(s, ...)
#define dint(i)
#define dfloat(f)
#else

// vypise ladici retezec
#define debug(s) printf("- %s\n", s)

// vypise formatovany ladici vystup - pouziti podobne jako printf
#define dfmt(s, ...) printf(" - "__FILE__":%u: "s"\n",__LINE__,__VA_ARGS__)

// vypise ladici informaci o promenne - pouziti dint(identifikator_promenne)
#define dint(i) printf(" - " __FILE__ ":%u: " #i " = %d\n", __LINE__, i)

// vypise ladici informaci o promenne typu float - pouziti
// dfloat(identifikator_promenne)
#define dfloat(f) printf(" - " __FILE__ ":%u: " #f " = %g\n", __LINE__, f)

#endif

/*****************************************************************
 * Deklarace potrebnych datovych typu:
 *
 * TYTO DEKLARACE NEMENTE
 *
 *   struct obj_t - struktura objektu: identifikator a souradnice
 *   struct cluster_t - shluk objektu:
 *      pocet objektu ve shluku,
 *      kapacita shluku (pocet objektu, pro ktere je rezervovano
 *          misto v poli),
 *      ukazatel na pole shluku.
 */

struct obj_t {
    int id;
    float x;
    float y;
};

struct cluster_t {
    int size;
    int capacity;
    struct obj_t *obj;
};

/*****************************************************************
 * Deklarace potrebnych funkci.
 *
 * PROTOTYPY FUNKCI NEMENTE
 *
 * IMPLEMENTUJTE POUZE FUNKCE NA MISTECH OZNACENYCH 'TODO'
 *
 */

/*
 Inicializace shluku 'c'. Alokuje pamet pro cap objektu (kapacitu).
 Ukazatel NULL u pole objektu znamena kapacitu 0.
*/
void init_cluster(struct cluster_t *c, int cap)
{
    assert(c != NULL);
    assert(cap >= 0);

    // TODO
    
    c->size = 0;
    c->capacity = cap;
    

    size_t capacity_allocate = cap * sizeof(struct obj_t);
    void *objects = malloc(capacity_allocate);
    c->obj= objects;
    
	if(cap == 0)
    	c->obj = NULL;

}

/*
 Odstraneni vsech objektu shluku a inicializace na prazdny shluk.
 */
void clear_cluster(struct cluster_t *c)
{
    // TODO
    
    if(c->obj)
    	free(c->obj);
    	
    c->capacity = 0;
    c->size = 0;
    c->obj = NULL;
    
}

/// Chunk of cluster objects. Value recommended for reallocation.
const int CLUSTER_CHUNK = 10;

/*
 Zmena kapacity shluku 'c' na kapacitu 'new_cap'.
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap)
{
    // TUTO FUNKCI NEMENTE
    assert(c);
    assert(c->capacity >= 0);
    assert(new_cap >= 0);

    if (c->capacity >= new_cap)
        return c;

    size_t size = sizeof(struct obj_t) * new_cap;

    void *arr = realloc(c->obj, size);
    if (arr == NULL)
        return NULL;

    c->obj = (struct obj_t*)arr;
    c->capacity = new_cap;
    return c;
}

/*
 Prida objekt 'obj' na konec shluku 'c'. Rozsiri shluk, pokud se do nej objekt
 nevejde.
 */
void append_cluster(struct cluster_t *c, struct obj_t obj)
{
    // TODO
    
    
	if(c->size + 1 == c->capacity)
   	{
   		int new_cap = c->capacity + CLUSTER_CHUNK;
    	resize_cluster(c, new_cap); //FIXME
    	
    }
    	
    if(c->size + 1 < c->capacity)
	{
		c->obj[c->size] = obj;
		c->size++;
	}	
}

/*
 Seradi objekty ve shluku 'c' vzestupne podle jejich identifikacniho cisla.
 */
void sort_cluster(struct cluster_t *c);

/*
 Do shluku 'c1' prida objekty 'c2'. Shluk 'c1' bude v pripade nutnosti rozsiren.
 Objekty ve shluku 'c1' budou serazeny vzestupne podle identifikacniho cisla.
 Shluk 'c2' bude nezmenen.
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2)
{
    assert(c1 != NULL);
    assert(c2 != NULL);

    // TODO
    
    if((c1->size + c2->size) >= c1->capacity)
    {    	
		int new_cap = c1->capacity + CLUSTER_CHUNK;
    	c1 = resize_cluster(c1, new_cap);	
    }
    
    for(int i = 0; i < c2->size; i++)
    {
    	append_cluster(c1, c2->obj[i]);
    	sort_cluster(c1);
	}
    
}

/**********************************************************************/
/* Prace s polem shluku */

/*
 Odstrani shluk z pole shluku 'carr'. Pole shluku obsahuje 'narr' polozek
 (shluku). Shluk pro odstraneni se nachazi na indexu 'idx'. Funkce vraci novy
 pocet shluku v poli.
*/
int remove_cluster(struct cluster_t *carr, int narr, int idx)
{
    assert(idx < narr);
    assert(narr > 0);

    // TODO
    clear_cluster(&carr[idx]);
    int continued = idx + 1;
    while(continued < narr)
    {
    	carr[idx] = carr[continued];
    	idx++;
    	continued++;
	}
    return narr - 1;
}

/*
 Pocita Euklidovskou vzdalenost mezi dvema objekty.
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2)
{
    assert(o1 != NULL);
    assert(o2 != NULL);

    // TODO
    
    float x = o1->x - o2->x;
    float y = o1->y - o2->y;
    float result = sqrtf(x * x + y * y);
    return result;
}

/*
 Pocita vzdalenost dvou shluku.
*/
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2)
{
    assert(c1 != NULL);
    assert(c1->size > 0);
    assert(c2 != NULL);
    assert(c2->size > 0);

    // TODO
    
   
    float sum_obj_distance = 0.0;
    int count_of_pairs = 0;
    for(int i = 0; i < c1->size; i++)
    {
    	for(int j = 0; j < c2->size; j++)
    	{
    		sum_obj_distance = obj_distance(&c1->obj[i],&c2->obj[j]);
    		count_of_pairs++;
    	}
    
    }
    float cluster_distance = sum_obj_distance / count_of_pairs;
    return cluster_distance;
}

/*
 Funkce najde dva nejblizsi shluky. V poli shluku 'carr' o velikosti 'narr'
 hleda dva nejblizsi shluky. Nalezene shluky identifikuje jejich indexy v poli
 'carr'. Funkce nalezene shluky (indexy do pole 'carr') uklada do pameti na
 adresu 'c1' resp. 'c2'.
*/
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2)
{
    assert(narr > 0);

    // TODO
    
	
	int min_index1 = 0;
	int min_index2 = 1;
	
	float min_dist = cluster_distance(&carr[0], &carr[1]);
	float tmp_min;
	
    for(int index1 = 0; index1 < narr; index1++)
    {
    
    	for(int index2 = 0; index2 < narr; index2++)
    	{
    		if(index1 != index2)
			{
				tmp_min = cluster_distance(&carr[index1], &carr[index2]);
				if(tmp_min < min_dist)
				{
					min_dist = tmp_min;
					min_index1 = index1;
					min_index2 = index2;
				}
			}
		
		//index2++;	
    	}
    //index1++;	
    }
    
    *c1 = min_index1;
    *c2 = min_index2;
}

// pomocna funkce pro razeni shluku
static int obj_sort_compar(const void *a, const void *b)
{
    // TUTO FUNKCI NEMENTE
    const struct obj_t *o1 = (const struct obj_t *)a;
    const struct obj_t *o2 = (const struct obj_t *)b;
    if (o1->id < o2->id) return -1;
    if (o1->id > o2->id) return 1;
    return 0;
}

/*
 Razeni objektu ve shluku vzestupne podle jejich identifikatoru.
*/
void sort_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    qsort(c->obj, c->size, sizeof(struct obj_t), &obj_sort_compar);
}

/*
 Tisk shluku 'c' na stdout.
*/
void print_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    for (int i = 0; i < c->size; i++)
    {
        if (i) putchar(' ');
        printf("%d[%g,%g]", c->obj[i].id, c->obj[i].x, c->obj[i].y);
    }
    putchar('\n');
}

/*
 Ze souboru 'filename' nacte objekty. Pro kazdy objekt vytvori shluk a ulozi
 jej do pole shluku. Alokuje prostor pro pole vsech shluku a ukazatel na prvni
 polozku pole (ukalazatel na prvni shluk v alokovanem poli) ulozi do pameti,
 kam se odkazuje parametr 'arr'. Funkce vraci pocet nactenych objektu (shluku).
 V pripade nejake chyby uklada do pameti, kam se odkazuje 'arr', hodnotu NULL.
*/
int load_clusters(char *filename, struct cluster_t **arr)
{
    assert(arr != NULL);

    // TODO
    

    FILE *pFILE = fopen(filename, "r");
    if(pFILE == NULL){
    	arr = NULL;
    	return 0;
		}
		

    
    int n_count=20;//prvni radek ze souboru
	fscanf(pFILE, "count=%d" , &n_count);


    struct cluster_t *tmp_arr= malloc(sizeof(struct cluster_t)* n_count);
	int i = 0;
    while(i < n_count)
    {	
    	
    	
		struct cluster_t cluster;	
    	init_cluster(&cluster,CLUSTER_CHUNK);
		
    	int id;
    	float x, y;
    	fscanf(pFILE,"%d %f %f",&id,&x,&y);
    	
    	cluster.size = 1;
    	cluster.obj->id = id;
    	cluster.obj->x = x;
    	cluster.obj->y = y;
    	
    	tmp_arr[i].size = 1;
    	tmp_arr[i] = cluster;
    
    	i++;	
	}
	*arr = tmp_arr;
	fclose(pFILE);
	
    return i;
}

/*
 Tisk pole shluku. Parametr 'carr' je ukazatel na prvni polozku (shluk).
 Tiskne se prvnich 'narr' shluku.
*/
void print_clusters(struct cluster_t *carr, int narr)
{
    printf("Clusters:\n");
    for (int i = 0; i < narr; i++)
    {
        printf("cluster %d: ", i);
        print_cluster(&carr[i]);
    }
}

int main(int argc, char *argv[])
{
    struct cluster_t *clusters;
    
    // TODO

    
	if(argc == 1 || argc > 3){
		fprintf(stderr,"Chybny pocet argumentu\n");
		return 1;
		}
    
    int n = 1;//cilovi pocet shluku
    if(argc == 3){
    	n = atoi(argv[2]);
    	}
	
    int loaded_clusters = load_clusters(argv[1], &clusters);
	
    while(loaded_clusters > n)
    {
    	int idx1, idx2;
    	find_neighbours(clusters, loaded_clusters, &idx1, &idx2);
    	merge_clusters(&clusters[idx1], &clusters[idx2]);
    	remove_cluster(clusters, loaded_clusters, idx2);
    	
    	loaded_clusters--;
	}

    print_clusters(clusters,n);
    for(int i = 0; i < loaded_clusters ; i++)
    {
    	 clear_cluster(&clusters[i]);
	}
   
    free(clusters);
    return 0;
}
