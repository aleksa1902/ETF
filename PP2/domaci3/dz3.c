#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

void check(void *str){
	if(str == NULL){
		printf("Neuspela alokacija memorije\n");
		exit(1);
	}
}

void ispisStringova(char **strs, int x){
	int i;
	printf("Svi stringovi:\n");
	for(i=0; i<x; i++){
		printf("%d. %s\tDuzina %d\n",i+1, strs[i], strlen(strs[i]));
	}
	printf("\n");
}

void oslobadjanjeMemorije(char **strs, int x){
	int i;
	for(i=0; i<x; i++){
		free(strs[i]);
	}
	free(strs);
}
/*
uklanja iz stringa sve one reci koje ne sadrže minimalan broj znakova iz zadate reci za pretragu;
broj znakova zadaje korisnik; npr. za rec za pretragu eto u stringu evo cuje se eho iz
sobe i minimalan broj znakova dva, rezultujuci string ce biti evo eho sobe;
*/
void obradiSve(char** strs, int x){
	char *rech, ch, *pom, *slova;
	int n, i, j, l, y, poc, br, duz, yMax;
	//dinamicki unos jedne reci
	y=0;
	yMax=2;
	rech = (char*)malloc(sizeof(char)*(yMax+1));
	check(rech);
	printf("Unesite rec za proveru:\n");
	while( (ch=getchar())!='\n' ){
		if(isspace(ch)) break;
		if(y == yMax){
			yMax *= 2;
			rech = (char*) realloc(rech, sizeof(char)*(yMax+1));
			check(rech);
		}
		rech[y] = ch;
		y++;
	}
	rech[y] = '\0';
	rech = (char*) realloc(rech, sizeof(char)*(y+1));
	printf("Uneti broj neophonih poklapanja> ");
	scanf("%d",&n);
	getchar();
	
	//evo cuje se eho iz sobe
	//   i
	//eho
	
	//obrada Niza stringova;

	for(i=0; i<x; i++){
		duz = strlen(strs[i]);
		printf("Duzina Stringa je %d\n",duz);
		pom = (char*)malloc(sizeof(char)*(duz+1) );
		check(pom);
		slova = (char*)malloc(sizeof(char)*(strlen(rech)+1) );
		check(slova);
		slova[0]='\0';

		poc = 0;
		br = 0;
		y = 0; //brojac kroz pom
		for(j=0; j<=duz; j++){
			if( strs[i][j] == ' ' || strs[i][j] == '\0' || strs[i][j] == '\t'){
				printf("Broj poklapanja %d na pocetnom mestu %d\n",br, poc);
				if(br>=n){
					//dodajem tekucu rec u pom string.
					for(l=poc; l<=j; l++){
						pom[y] = strs[i][l];
						y++;
					}
				}
				poc = j+1;
				br=0;
				slova[br]='\0';
			}else{
				if(strchr(rech, strs[i][j]) != NULL && strchr(slova, strs[i][j]) == NULL){
					slova[br]=strs[i][j];
					br++;
					slova[br] = '\0';
				}
			}
		}
		if(y==0){
			pom[0] = '\0';
			y=1;
		}else{
			if(pom[y-1]!='\0'){
				pom[y-1] = '\0';
			}
		}
		
		
		printf("Pomocni je: %s\n", pom);
		strcpy(strs[i], pom);
		strs[i] = (char*)realloc(strs[i], sizeof(char)*(y));
		
		free(slova);
		free(pom);
	
	}
	
}


main(){
	
	char **strs, ch;
	int x, xMax, y, yMax, i, j, n;
	
	while(1){
		
		printf("=================================================================================================================");
		printf("Unesite stringove:\n");

		x=0;
		xMax = 2;

		strs = (char**) malloc(sizeof(char*)*xMax);
		check(strs);
		while(1){
			if(x == xMax){
				xMax *= 2;
				strs = (char**) realloc(strs, sizeof(char*)*xMax);
				check(strs);
			}
			//dinamicki unos niza karatkera do unosa enter.
			y=0;
			yMax=2;
			strs[x] = (char*)malloc(sizeof(char)*(yMax+1));
			check(strs[x]);
			while( (ch=getchar())!='\n' ){
				if(y == yMax){
					yMax *= 2;
					strs[x] = (char*) realloc(strs[x], sizeof(char)*(yMax+1));
					check(strs[x]);
				}
				strs[x][y] = ch;
				y++;
			}
			strs[x][y] = '\0';
			
			//ako je prazan string.
			if(strs[x][0] == '\0'){
				free(strs[x]);
				break;
			}
			
			if(strcmp(strs[x], "Dosta Brus Li") == 0){
				oslobadjanjeMemorije(strs, x);
				exit(1);
			}
			
			//realokacija jednog stringa u nizu na tacan broj elemenata.
			strs[x] = (char*) realloc(strs[x], sizeof(char)*(y+1));
			x++;
		}
		//realokacija pokazivaca na stringove.
		strs = (char**) realloc(strs, sizeof(char*)*x);
		
		printf("Uneto stringova: %d\n",x);
		
		ispisStringova(strs, x);
		
		obradiSve(strs,x);
		
		ispisStringova(strs, x);
		
		oslobadjanjeMemorije(strs, x);
	}
}
