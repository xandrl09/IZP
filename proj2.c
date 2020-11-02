/*
IZP PROJEKT 2: ITERACNI VYPOCTY
AUTOR: ONDREJ ANDRLA
Projekt je vypracovan podle zadani na wiki strankach predmetu IZP.
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


#define HELP 0
#define ERROR 1
#define TANGENS 2
#define DISTANCE 3
#define DISTANCE_X 4
#define DISTANCE_AND_HEIGHT 5
#define DISTANCE_AND_HEIGHT_X 6

#define IMPLICIT_ITERATIONS 13
#define MAX_HEIGHT 100



int check_arguments(int, char *[]);

void print_help(void);

double taylor_tan(double, unsigned int);
double cfrac_tan(double, unsigned int);

void compare_tans(double, unsigned int,  double, double);

double compute_distance(double, double);
double compute_height(double, double, double);

//void print_result(double, double, int);






int main(int argc, char *argv[])
{

	double taylor_tan_x = 0.0;
	double cfrac_tan_x = 0.0;

	double height_of_machine = 1.5;
	unsigned int n = IMPLICIT_ITERATIONS;
	double distance_x = 0.0;
	double height_x = 0.0;
	
	int ret_val = check_arguments(argc, argv);
	
	if(ret_val == HELP){
		print_help();
		return 0;
		}

	if (ret_val == 1){
		fprintf(stderr,"Chyba: nespravny pocet argumentu\n"
			"nebo nespravne zadane argumenty.\n"
			"Pro napovedu zadejte --help\n");
		return 1;
		}

	if (ret_val == 2){
		double x = atof(argv[2]);

		unsigned int m = atoi(argv[4]);

		for(unsigned int n = atoi(argv[3]); n <= m; n++){
			taylor_tan_x = taylor_tan(x, n);
			cfrac_tan_x = cfrac_tan(x, n);
			compare_tans(x, n, taylor_tan_x, cfrac_tan_x);
		}
		return 0;	
	}

	if (ret_val == DISTANCE || DISTANCE_AND_HEIGHT){
			
		double x = atof(argv[2]);
		cfrac_tan_x = cfrac_tan(x, n);

		distance_x = compute_distance(cfrac_tan_x, height_of_machine);
		printf("%.10e \n", distance_x);

		if(ret_val == 5){
			double x = atof(argv[3]);
			cfrac_tan_x = cfrac_tan(x, n);
			height_x = compute_height(cfrac_tan_x, distance_x, height_of_machine);
			printf("%.10e \n", height_x);
			}
		return 0;	
	}

	if (ret_val == 4 || 6) {
		
		height_of_machine = atof(argv[2]);

		double x = atof(argv[4]);
		if(x > 0 || x <= 1.4){
			cfrac_tan_x = cfrac_tan(x, n);
			distance_x = compute_distance(cfrac_tan_x, height_of_machine);
			printf("%.10e \n", distance_x);
		}
		
		if(ret_val == 6){
			double x = atof(argv[5]);
			
			cfrac_tan_x = cfrac_tan(x, n);
			height_x = compute_height(cfrac_tan_x, distance_x, height_of_machine);
			printf ("%.10e \n", height_x); 
		}
	}

	return 0;
}

/*
Po zavolani funkce zkontroluje argumenty na vstupu.
*/
int check_arguments(int argc, char *argv[])
{
	
	if(argc == 2){

		if(strcmp(argv[1], "--help") == 0)
			return HELP;
		else	
			return ERROR;
	}

	if(argc == 3){
		if(strcmp(argv[1], "-m") == 0){
			return DISTANCE;
		}
		else
			return ERROR;
	}

	if(argc == 4){
		if(strcmp(argv[1], "-m") == 0 && atof(argv[2]))
			return DISTANCE_AND_HEIGHT;
		else
			return ERROR;
	}

	if(argc == 5){
		if(strcmp(argv[1], "--tan") == 0 && atof(argv[2]))
			return TANGENS;
		else if(strcmp(argv[1], "-c") == 0)
			return DISTANCE_X;
		else
			return ERROR;
	}

	if(argc == 6){
		if(strcmp(argv[1], "-c") == 0)
			return DISTANCE_AND_HEIGHT_X;
		else
			return ERROR;
	}
	return 1;
}


/*
Funkce print_help po zavolani vypise napovedu.
*/
void print_help (void)
{
	printf("\nHELP:\n\n"
		"1. VYPOCET TANGENS UHLU A.\n"
		"Jako prvni argument zadejte : --tan \n"
		"Jako druhy argument zadejte velikost uhlu A v radianech.\n"
		"Jako treti a ctvrty argument zadejte cisla N a M pro ktera plati 0 < N <= M < 14.\n"
		"M a N udavaji v kolika iteracich se budou vysledky porovnavat.\n\n"
		"2. VYPOCET VZDALENOSI (A VYSKY OBJEKTU).\n"
		"\n"
		"\n");
}


/*
Funkce vypocita tangens  pomoci Taylorova polynomu.
*/
double taylor_tan(double x, unsigned int n)
{

	double iter1 = x;
	double iter2 = iter1 + ((x*x*x)/3);
	double iter3 = iter2 + (2*(x*x*x*x*x)/15);
	double iter4 = iter3 + (17*(x*x*x*x*x*x*x)/315);
	double iter5 = iter4 + (62*(x*x*x*x*x*x*x*x*x)/2835);
	double iter6 = iter5 + (1382*(x*x*x*x*x*x*x*x*x*x*x)/155925);
	double iter7 = iter6 + (21844*(x*x*x*x*x*x*x*x*x*x*x*x*x)/6081075);
	double iter8 = iter7 + (929569*(x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)/638512875);
	double iter9 = iter8 + (6404582*(x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)/10854718875);
	double iter10 = iter9 + (443861162*(x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)/1856156927625);
	double iter11 = iter10 + (18888466084*(x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)/194896477400625);
	double iter12 = iter11 + (113927491862*(x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)/49308808782358125);
	double iter13 = iter12 + (58870668456604*(x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)/3698160658676859375);

	switch(n){
	case 1:
		return iter1;
		break;
	case 2:
		return iter2;
		break;
	case 3:
		return iter3;
		break;
	
	case 4:
		return iter4;
		break;
	case 5:
		return iter5;
		break;
	case 6:
		return iter6;
		break;
	
	case 7:
		return iter7;
		break;
	case 8:
		return iter8;
		break;
	case 9:
		return iter9;
		break;
	case 10:
		return iter10;
		break;
	case 11:
		return iter11;
		break;
	case 12:
		return iter12;
		break;
	case 13:
		return iter13;
		break;
	}
	return 1;

}

/*
Funkce vypocita tangens  pomoci zretezenych zlomku.
*/
double cfrac_tan(double x, unsigned int n)
{

	int k;
	double cfrac_tan_x = 0.0;
	for(k = n; k > 1; k--){
	
			double a = 2*k - 1;
			double b = x*x;
			cfrac_tan_x = b /( a - cfrac_tan_x);
		
		}
		cfrac_tan_x = x / (1 - cfrac_tan_x) ;
	
	
	return cfrac_tan_x;


}

/*
Funkce spocita tangens pomoci funkce z matematicke knihovny 
a porovna jej s vysledky funkci taylor_tan a cfrac_tan.
Pote vysledky vypise na standerdni vystup.
*/
void compare_tans(double x, unsigned int N, double taylor_tan_x, double cfrac_tan_x)
{

	//for(unsigned int i = N; i <= M; i++)
	//{
		unsigned int i = N;

		double math_library_result = tan(x);

		printf("%d %e %e %e %e %e\n",i , math_library_result ,taylor_tan_x ,
		fabs(taylor_tan_x - math_library_result),cfrac_tan_x ,fabs(cfrac_tan_x - math_library_result));

	//}

}

/*
Funkce vypocita vzdalenost mereneho objektu.
*/
double compute_distance(double cfrac_tan_x, double height_of_machine)
{

	
	double distance_x = height_of_machine / cfrac_tan_x;

	return distance_x;
}

/*
Funkce vypocita vysku mereneho objektu.
*/
double compute_height(double cfrac_tan_x, double distance_x, double height_of_machine)
{

	double height_x = (distance_x * cfrac_tan_x) + height_of_machine;

	return height_x;
}


