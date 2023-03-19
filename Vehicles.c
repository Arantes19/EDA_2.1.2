#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "op.h"

int saveVehicle(Vehicle* begin)
{
    FILE* fp;
    fp = fopen("vehicles.txt", "a");
    if (fp != NULL)
    {
        Vehicle* aux = begin;
        while (aux != NULL)
        {
            fprintf(fp, "%d;%s;%f;%f;%f;%s;%d\n", aux->vCode, aux->type, aux->batery, aux->autonomy, aux->price, aux->geocode, aux->state);
            aux = aux->nextv;
        }
        fclose(fp);
        return(1);
    }
    else 
    {
        printf("Falha na abertura do ficheiro");
        return(0);
    }
}

Vehicle* readVehicles()
{
    FILE* fp;
    int cod, stat;
    float prc, bat, aut;
    char tp[50], geo[50];

    Vehicle* aux = NULL;
    fp = fopen("vehicles.txt", "r");
    if (fp != NULL)
    {
        while(!feof(fp))
        {fscanf(fp, "%d;%[^;];%f;%f;%f;%[^;];%d\n", &cod, tp, &bat, &aut, &prc, geo, &stat);
        aux = insertVehicle(aux, cod, tp, bat, aut, prc, geo, stat);
        }
        fclose(fp);
    }
    return(aux);
}

Vehicle* insertVehicle(Vehicle* begin, int cod, char tp[], float bat, float aut, float prc, char geo[], int stat)
{
    if (!existVehicle(begin, cod))
    {
        Vehicle* newVehicle = malloc(sizeof(struct vehicle));
        if (newVehicle != NULL)
        {
            newVehicle->vCode = cod;
            strcpy(newVehicle->type, tp);
            newVehicle->batery = bat;
            newVehicle->price = prc;
            newVehicle->autonomy = aut;
            strcpy(newVehicle->geocode, geo);
            newVehicle->state = stat;
            newVehicle->nextv = begin; //update next pointer
            begin = newVehicle; //!!! 
            return newVehicle; // return new head pointer
        }
        else return begin; // Return the old head pointer if the vehicle already exists or memory allocation failed
    }
}

int existVehicle(Vehicle* begin, int cod)
{
    while (begin != NULL)
    {
        if (begin->vCode == cod) return 1;
        {
            begin = begin->nextv;
        }
        return 0;
    }
}

/*void listVehicle(Vehicle* begin)
{
    while (begin != NULL)
    {
        printf("%d %s %d %f\n", begin->code, begin->type, begin->batery, begin->price);
        begin = begin->nextv;
    }
}*/

Vehicle* removeVehicle(Vehicle* begin, int cod)
{
    Vehicle *previous = begin, *actual = begin, *aux;
    if (actual == NULL) return(NULL);
    else if (actual->vCode == cod)
    {
        aux = actual->nextv;
        free(actual);
        return(aux);
    }
    else
    {
        while((actual != NULL)&&(actual->vCode!=cod))
        {
            previous = actual;
            actual = actual->nextv;
        }
        if (actual == NULL) return(begin);
        else
        {
            previous->nextv = actual->nextv;
            free(actual);
            return(begin);
        }
    }  
}