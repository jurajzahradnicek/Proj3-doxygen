/**
 * @mainpage Projekt 3
 * @link
 * Proj3.h
 * @endlink
 *
 * @file Proj3.h
 * @brief Projekt 3 - Jednoducha shlukova analyza - Unweighted pair-group average
 * @author Juraj Zahradnicek - xzahra31
 * @date December 2016
 * @version 1.0
 * @see https://is.muni.cz/th/172767/fi_b/5739129/web/web/usrov.html
 */
/**
 @brief Struktura objektu s urcitymi suradnicami
 */
struct obj_t {
    /** Identifikator */
    int id;
    /** Suradnica x */
    float x;
    /** Suradnica y */
    float y;
};
/**
 * @brief Struktura cluster s urcitou velkostou, kapacitou a odkazom na objekt pridavany do clustera
 */
struct cluster_t {
    /** Velkost clustera - pocet ovjektov v poli */
    int size;
    /** Kapacita clustera - pocet objektov, ktore maju rezervovane miesto v poli */
    int capacity;
    /** Pole objektov prisluchajuce urcitemu zhluku */
    struct obj_t *obj;
};
/**
 * @defgroup Zhluky - Praca so zhlukami
 * @{
 */

/**
 * Inicializacia zhluku 'c'. Alokuje pamat pre cap objektu (kapacitu).
 * Ukazovatel NULL pri poli objektu znamena kapacitu 0.
 *
 * @pre
 * Zhluk 'c' sa nerovna NULL
 *
 * @pre
 * Kapacita 'cap' je vacsia alebo rovna 0
 *
 * @post
 * Kapacita 'cap' (pocet objektov) sa alokuje pre zhluk 'c'
 *
 * @param c - zhluk, pre ktory sa alokuje kapacita
 * @param cap - pocet objektov, ktorym alokuje pamat v zhluku
 */
void init_cluster(struct cluster_t *c, int cap);
/**
 * Odstranenie vsetkych objektov v zhluku a inicializacia na prazdny zhluk.
 *
 * @post
 * Funkcia dealokuje pamat pre vsetky objekty v zhluku 'c'
 *
 * @param c - zhluk, ktoremu sa dealokuje pamat
 */
void clear_cluster(struct cluster_t *c);
/**
 * Konstantna hodnota pre realokaciu zhluku
 */
extern const int CLUSTER_CHUNK;
/**
 * Zmena kapacity zhluku 'c' na kapacitu 'new_cap'
 *
 * @pre
 * Je nacitany zhluk 'c'
 *
 * @pre
 * Hodnota zhluku 'c' je vacsia alebo rovna 0
 *
 * @pre
 * Nova kapacita 'new_cap' je vacsia alebo rovna 0
 *
 * @post
 * Kapacita zhluku 'c' bude rozsirena na kapacitu 'new_cap',
 * ak nenastane chyba pri alokacii
 *
 * @param c - zhluk, ktory sa rozsiruje
 * @param new_cap - nova kapacita zhluku
 * @return - nova kapacita zhluku 'c', v pripade chyby NULL
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap);
/**
 * Prida objekt 'obj' na koniec zhluku 'c'. Rozsiri zhluk, ak sa do neho objekt
 * nevojde.
 *
 * @post
 * Na poslednu poziciu zhluku 'c' prida objekt 'obj'
 *
 * @param c - zhluk, ku ktoremu sa prida objekt
 * @param obj - objekt, ktory sa prida
 */
void append_cluster(struct cluster_t *c, struct obj_t obj);
/**
 * Do zhluku 'c1' prida objekty zhluku 'c2'. Zhluk 'c1' bude v pripade nutnosti rozsireny.
 * Objekty v zhluku 'c1' budu zoradene vzostupne podla identifikacneho cisla.
 * Zhluk 'c2' bude nezmeneny.
 *
 * @pre
 * Zhluk 'c1' nema hodnotu NULL
 *
 * @pre
 * Zhluk 'c2' nema hodnotu NULL
 *
 * @post
 * Objekty v zhluku 'c1' budu rozsirene o objekty zhluku 'c2'
 *
 * @post
 * Pokial nebude stacit kapacita zhluku 'c1' bude navysena
 *
 * @param c1 - zhluk 'c1'
 * @param c2 - zhluk 'c2'
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2);
/**
 * Zoradi objekty v zhluku 'c' vzostupne podla ich identifikatorov.
 *
 * @post
 * Objekty v zhluku 'c' budu zoradene vzostupne podla ich ID
 *
 * @param c - zhluk, ktory bude zoradeny
 */
void sort_cluster(struct cluster_t *c);
/**
 * Vypis zhluku 'c' na stdout.
 *
 * @post
 * Objekty zhluku 'c' budu vypisane na stdout
 *
 * @param c - zhluk, ktoreho objekty sa vypisu
 */
void print_cluster(struct cluster_t *c);

/**
 * @}
 */

/**
 * @defgroup pole_zhlukov - Praca s polom zhlukov
 * @{
 */

/**
 * Odstrani zhluk z pola zhlukov 'carr'. Pole zhlukov obsahuje 'narr' poloziek
 * (zhlukov). Zhluk pre odstranenie sa nachadza na indexu 'isx'. Funkcia vracia novy
 * pocet zhlukov v poli.
 *
 * @pre
 * Hodnota 'idx' je mensia ako hodnota 'narr'
 *
 * @pre
 * Hodnota 'narr' je vacisa ako nula
 *
 * @post
 * Funkcia uvolni pamat vyhradenu pre prvok na indexu 'idx'
 * nachadzajuceho sa v poli 'carr', cim ho vymaze z pola
 * a vrati hodnotu 'narr - 1'
 * @param carr - pole vsetkych zhlukov
 * @param narr - pocet zhlukov v poli 'carr'
 * @param idx - identifikator zhluku v poli
 * @return - pocet prvok v poli 'carr' po vymazani zhluku (narr - 1)
 */
int remove_cluster(struct cluster_t *carr, int narr, int idx);
/**
 * Pocita euklidovu vzdialenost medzi dvoma objektami.
 *
 * @pre
 * Objekt 'o1' nema hodnotu NULL
 *
 * @pre
 * Objekt 'o2' nema hodnotu NULL
 *
 * @post
 * Funkcia pocita vzdialenost dvoch objektov podla matematickeho vztahu
 *
 * @see
 * https://en.wikipedia.org/wiki/Euclidean_distance
 *
 * @param o1 - objekt 1
 * @param o2 - objekt 2
 * @return - vypocitana vzdialenost dvoch objektov
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2);
/**
 * Pocita vzdialensot dvoch zhlukov
 *
 * @pre
 * Zhluk 'c1' nema hodnotu NULL
 *
 * @pre
 * Zhluk 'c1' ma velkost vacsiu ako 0
 *
 * @pre
 * Zhluk 'c2' nema hodnotu NULL
 *
 * @pre
 * Zhluk 'c2' ma velkost vacsiu ako 0
 *
 * @post
 * Funkcia vrati vypocitanu vzdialenost dvoch zhlukov, pricom pouziva funkciu 'obj_distance'
 *
 * @param c1 - zhluk 1
 * @param c2 - zhluk 2
 * @return - vypocitana vzdialenost
 */
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2);
/**
 * Funkcia najde dva najblizsie zhluky. V poli zhlukov 'carr' o velkosti 'narr'
 * hlada dva najblizsie zhluky. Najde zhluky, identifikuje ich indexy v poli
 * 'carr'. Funkcia najde zhlukuy (indexy do pola 'carr') uklada do pamati na
 * adresu 'c1' resp. 'c2'.
 *
 * @pre
 * Hodnota 'narr' je vacsia ako 0
 *
 * @post
 * Indexy dvoch najblizsich najdenych susedov budu ulozene do pamati na adresu 'c1' a 'c2'
 *
 * @param carr - pole vsetkych zhlukov
 * @param narr - pocet zhlukov v poli
 * @param c1 - index jedneho najdeneho zhluku
 * @param c2 - index druheho najdeneho zhluku
 */
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2);
/**
 * Zo suboru 'filename' nacita objekty. Pre kazdy objekt vytvori zhluk a ulozi
 * ho do pola zhlukov. Alokuje priestor pre pole vsetkych zhlukov a ukazovatel na prvu
 * polozku pola (ukazovatel na prvy zhluk v alokovanom poli) ulozi do pamati,
 * kam sa odkazuje parameter 'arr'. Funkcia vracia pocet nacitanych objektov (zhlukov).
 * V pripade nejakej chyby uklada do pamati, kam sa odkazuje 'arr', hodnotu NULL.
 *
 * @pre
 * Pole 'arr' nema hodotu NULL
 *
 * @post
 * Pre kazdy objekt nacitany zo vstupneho suboru bude vytvoreny zhluk v poli 'arr',
 * ktoremu sa naalokuje pamat pre vsetky tieto vytvorene zhluky.
 *
 * @param filename - vstupny subor obsahujuci objekty
 * @param arr - pole vsetkych nacitanych zhlukov
 * @return - pocet nacitanych zhlukov
 */
int load_clusters(char *filename, struct cluster_t **arr);
/**
 * Vypis pola zhlukov. Parameter 'carr' je ukazovatel na prvu polozku (zhluk).
 * Vypisuje sa prvych 'narr' zhlukov.
 *
 * @post
 * Vsetky objekty zhlukov z pola 'carr' budu vypisane na stdout
 *
 * @param carr - pole vsetkych zhlukov
 * @param narr - pocet zhlukov v poli
 */
void print_clusters(struct cluster_t *carr, int narr);

/**
 * @}
 */