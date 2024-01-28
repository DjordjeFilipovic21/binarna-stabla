#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba{
    char ime[15];
    char dijeta[15];
    int izgubljeniKG;
    struct Osoba *left, *right;
}Osoba;

int ispisiMeni(){
    char opcija[10];
    int op = 0;
    printf("1. Ucitaj stablo\n");
    printf("2. Ispis podataka\n");
    printf("3. Ispisi najefikasnije dijete\n");
    printf("4. Pronadji podatak o osobi\n");
    printf("5. Ocisti\n");
    while(op < 1 || op > 5)
    {
        printf("Unesite opciju: ");
        fgets(opcija, 10, stdin);
        opcija[strlen(opcija) - 1] = 0;
        op = atoi(opcija);
    }
    return op;
}

Osoba *dodajElement(Osoba *root, Osoba *noviEl)
{
        if(!root)
            return noviEl;

        if(strcmp(noviEl->dijeta, root->dijeta) == 0)
        {
            if(noviEl->izgubljeniKG > root->izgubljeniKG)
            {
                root->left = dodajElement(root->left, noviEl);
            }
            else
            {
                root->right = dodajElement(root->right, noviEl);
            }
        }
        else if(strcmp(noviEl->dijeta, root->dijeta) < 0)
        {
            root->left = dodajElement(root->left, noviEl);
        }
        else
        {
            root->right = dodajElement(root->right, noviEl);
        }
        return root;
}

Osoba *ucitajDatoteku()
{
    char naziv[100], string[100], *token;
    FILE *f;
    Osoba *root = NULL;
    printf("Unesite ime datoteke: ");
    fgets(naziv, 100, stdin);
    naziv[strlen(naziv) - 1] = 0;
    if(f = fopen(naziv, "r")){
        while(fgets(string, 99, f) == string){
            Osoba *noviElement = (Osoba*) malloc(sizeof(Osoba));
            token = strtok(string, ",");
            strcpy(noviElement->ime, token);
            token = strtok(NULL, ",");
            strcpy(noviElement->dijeta, token);
            token = strtok(NULL, " \n");
            noviElement->izgubljeniKG = atoi(token);
            noviElement->left = NULL;
            noviElement->right = NULL;
            root = dodajElement(root, noviElement);
        }
        fclose(f);
        printf("Datoteka je uspesno ucitana\n");
    }
    else{
        printf("Datoteka ne postoji ili je nije moguce citati\n");
    }
    return root;
}

void ispisi(Osoba *root)
{
    if(!root)
        return;
    ispisi(root->left);
    printf("%s %s %d\n",root->ime, root->dijeta, root->izgubljeniKG);
    ispisi(root->right);

}
int max = -1;
int min = 99;
Osoba *maxP = NULL;
Osoba *minP = NULL;

Osoba *maxF(Osoba *root)
{
    if(!root)
        return;
    maxF(root->left);
    if(root->izgubljeniKG > max)
    {
        max = root->izgubljeniKG;
        maxP = root;
    }

    maxF(root->right);
    return maxP;

}
Osoba *minF(Osoba *root)
{
    if(!root)
        return;
    minF(root->left);
    if(root->izgubljeniKG < min)
    {
        min = root->izgubljeniKG;
        minP = root;
    }
    minF(root->right);
    return minP;
}

int brisiStablo(Osoba *root)
{
    if(!root)
        return;
    brisiStablo(root->left);
    brisiStablo(root->right);
    free(root);
}


int main()
{
    Osoba *root = NULL;
    Osoba *min = NULL;
    Osoba *max = NULL;
    int opcija;
    while(1){
        opcija = ispisiMeni();
        switch(opcija)
        {
            case 1:{
                brisiStablo(root);
                root = ucitajDatoteku();
                break;
            }
            case 2:{
                ispisi(root);
                break;
            }
            case 3:{
                max = maxF(root);
                printf("%s\n", max->dijeta);
                min = minF(root);
                printf("%s\n", min->dijeta);

                break;
            }
            case 4:{
                brisiStablo(root);
                break;
                return 0;
            }
        }
    }
}
