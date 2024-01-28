#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Student{
    char smer[3];
    int index;
    int godUpisa;
    int t1;
    int klk1;
    int t2;
    int klk2;
    struct Student *next;
}Student;

int ispisiMeni()
{
    int opcija = 0;
    char op[15];

    printf("Meni:\n");
    printf("1. Ucitaj i ispisi listu:\n");
    printf("2. Najveci broj indeksa po smeru i godini:\n");
    printf("3. studenti po poenima:\n");
    printf("4. Izlaz i brisanje:\n");
    while(opcija < 1 || opcija > 4)
    {
        printf("Unesite opciju: ");
        fgets(op, 15, stdin);
        opcija = atoi(op);
    }
    return opcija;

}

Student *sortirajElemente(Student *head, Student *new)
{
    if(!head)
        return new;
    int ukupnoHead = head->t1 + head->t2 + head->klk1 + head->klk2;
    int ukupnoNew = new->t1 + new->t2 + new->klk1 + new->klk2;
    if(ukupnoNew > ukupnoHead)
    {
        new->next = head;
        return new;
    }
    else
    {
        head->next = sortirajElemente(head->next, new);
    }
}

Student *ucitajDatoteku()
{
    char naziv[15], string[400], *token;
    Student *head = NULL;
    FILE *f;
    printf("Unesite naziv datoteke: ");
    fgets(naziv, 200, stdin);
    naziv[strlen(naziv)-1] = 0;
    if(f = fopen(naziv, "r"))
    {
        while(fgets(string, 400, f) == string)
        {
            Student *new = malloc(sizeof(Student));
            token = strtok(string, ",");
            strcpy(new->smer, token);
            token = strtok(NULL, ",");
            new->index = atoi(token);
            token = strtok(NULL, ",");
            new->godUpisa = atoi(token);
            token = strtok(NULL, ",");
            new->t1 = atoi(token);
            token = strtok(NULL, ",");
            new->klk1 = atoi(token);
            token = strtok(NULL, ",");
            new->t2 = atoi(token);
            token = strtok(NULL, " \n");
            new->klk2 = atoi(token);
            head = sortirajElemente(head, new);
        }
        printf("Datoteka je uspeno ucitana!\n");
        fclose(f);
        return head;
    }
    else
    {
        printf("datoteka nije ucitana!\n");
    }
}

void ispisi(Student *head)
{
    if(!head)
        return;
    printf("%s %i %i %i %i %i %i\n", head->smer, head->index, head->godUpisa, head->t1, head->klk1, head->t2, head->klk2);
    ispisi(head->next);
}

int main()
{
    Student *head = NULL;
    int opcija;
    while(1)
    {
        opcija = ispisiMeni();
        switch(opcija)
        {
            case 1:
                {
                    head = ucitajDatoteku();
                    ispisi(head);
                    break;
                }
            case 2:
                {
                    printf("PROSAO"); break;
                }
            case 3:
                {
                    break;
                }
            case 4:
                {
                    break;
                }

        }
    }


}
