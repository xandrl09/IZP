/*
IZP PROJEKT 1: PRACE S TEXTEM
AUTOR: ONDREJ ANDRLA
Projekt je vyhotoven podle zadani na wiki strankach predmetu IZP.
*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

#define RECORD_LEN 100
#define BUFSIZE 101
#define ALL_CHARS 256

int check_arguments(int argc, char *argv[], char search[]);
int load_input (char []);
int compare_strings (char *, char []);
void print_result (int, int[], char[]);



/*
Funkce main nejprve zavolá funkci check_arguments, která zkontroluje argumenty na standartnim vstupu.
Poté zavolá funkci load_input, ktera nacte hodnoty z databaze na standartnim vstupu.
Pak zavola funkci compare_strings, ktera porovna argument s hodnotami z databaze.
Nakonec vola funkci print_result, ktera na standartni vystup vypise vysledky.
*/


int main(int argc, char *argv[])
{

    char db_record[BUFSIZE] = {0};
    int correspondence = 0;
	char last_adress[BUFSIZE] = {0};
	char search[BUFSIZE] = {0};
	int enabled[ALL_CHARS] = {0}; //V poli enabled jsou ukládány znaky pro vypsání na výstup.
                            //Pole má 256 pozic což znací pocet znaku v ASCII tabulce. Pozice jsou pri inicializaci nastaveny na hodnotu 0.
	int c = 0;
	int ret_val = check_arguments(argc, argv, search);

	if(ret_val != 0)
		return 1;

        while((ret_val = load_input(db_record)) == 1){

            if(compare_strings(search, db_record) == 1){
                correspondence++;
                strcpy(last_adress, db_record);
                c = db_record[strlen(search)];
                enabled[c] = 1;

            }
        }

    if(ret_val == 0){
        print_result(correspondence, enabled, last_adress);
    }
    else{
        return 1;
    }


	return 0;
}

/*
Funkce zkontroluje argumenty na vstupu. Pokud jsou zde vice nez dva argumenty, vypise standartni chybove hlaseni.
Pokud je zde prave jeden argument prevede funkce mala pismena na velka.
*/
int check_arguments(int argc, char *argv[], char search[])
{

	if(argc > 2){
		fprintf(stderr, "Chybny pocet argumentu\n");
		return 1;
	}

	if(argc == 2){
        if(strlen(argv[1]) >= RECORD_LEN){
            fprintf(stderr, "Chyba: zadany argument je prilis dlouhy (MAX. %d)\n", RECORD_LEN);
            return 1;
        }

		for(unsigned int i = 0; i < strlen(argv[1]); i++){
			search[i] = toupper(argv[1][i]);
		}
	}

	return 0;
}


/*
Funkce nacte ze standartního vstupu databázi adres.
Pokud bude retezec, nebo rádek databáze delší než 100 znakù, vypíše chybové hlášení.
Funkce prevede všechna písmena na velká pro snazší porovnávání retezcu.
*/

int load_input(char db_record[]){

	int c;
	int i = 0;

	while( (c = getchar()) != EOF && c != '\n' ){

        if(i >= RECORD_LEN){
            fprintf(stderr, "Chyba - zadana adresa je prilis dlouha\n");
            return 2;
        }

		db_record[i] = toupper(c);
		i++;
	}
	db_record[i] = '\0';


	if(c == EOF)
		return 0;
	else
		return 1;

}



/*
Funkce postupne porovna retezec zadany na vstupu s jednotlivími rádky z databaze.
Pokud dojde ke shode navíší se promená correspondence o jedna.
Funkce zaznamená na kterých rádcích došlo ke shode.
*/
int compare_strings (char *search, char db_record[])
{

	int lenght;
	lenght = strlen(search);


	if(strncmp(search, db_record, lenght) == 0)
		return 1;
	else
		return 0;

}



/*
Funkce vrati vysledek porovnani retezcu na standartni výstup.
Pokud je shoda nulova vrátí "not found".
Pokud došlo ke shode v jednom prípade vypíše nalezenou adresu.
Pokud došlo ke shode ve více prípadech vypíše možnosti.
*/
void print_result (int correspondence, int enabled[],char last_adress[])
{
	if (correspondence == 1){
		printf("Found: %s \n", last_adress);
	}
	else if(correspondence > 1){
        printf("Enabled: ");
		for(int i = 0; i < 256; i++)
            if(enabled[i] == 1)
                printf("%c", i);
        printf("\n");
    }
    else
		printf("Not found \n");


}

