#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <locale.h>
#include <ctype.h>
#include "StarC.h"

Fila *criar_fila(){return NULL;}
Fila *cria_no(Estrela *estrela, Corpo_Celeste *corpo ,int control)
{
    Fila *no = malloc(sizeof(Fila));
    if(control == 0)
        no->estrela = estrela;
    else
        no->corpo = estrela->lista;
    no->prox = NULL;
    no->ant = NULL;
}
int fila_vazia(Fila *fila){return (fila == NULL);}
void enfileirar(Fila **fila, Estrela *estrela, int control, Corpo_Celeste *corpo)
{
    Fila *no = NULL;
    if(control == 0)
    {
        no = cria_no(estrela, corpo, 0);
    }
    else
    {
        no = cria_no(estrela, corpo, 1);
    }

    if(fila_vazia(*fila))
        *fila = no;
    else
    {
        Fila *aux = *fila;

        while(aux->prox)
        {
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
}
Fila *desenfileirar(Fila **fila)
{
    if(fila_vazia(*fila)){return NULL;}
    else
    {
        Fila *aux = (*fila)->prox;
        Fila *excl = *fila;
        *fila = aux;
        return excl;
    }
}
Fila *esvaziar_fila(Fila *fila, int control, char lang)
{
    Fila *fila_excl = NULL;
    if(control == 0)
    {
        Estrela *excluido = NULL;
        if (fila!=NULL)
        {
            esvaziar_fila(fila->prox, control, lang);
            fila_excl = (desenfileirar(&fila));
            excluido = fila_excl->estrela;
            lang == 'P'?printf("Nome: %s, codEstrela: %i, numCorpos: %i, fatorDobra: %f\n",
                    excluido->nome,excluido->cod_estrela,excluido->num_corpos,excluido->fator_de_dobra):
                        printf("Name: %s, codStar: %i, numCorps: %i, warpFactor: %f\n",
                    excluido->nome,excluido->cod_estrela,excluido->num_corpos,excluido->fator_de_dobra);
            free(fila_excl);
            fila_excl = NULL;
        }

    }
    else
    {
        Corpo_Celeste *fcorpo = NULL;
        if (fila!=NULL)
        {
            esvaziar_fila(fila->prox, control, lang);
            fila_excl = (desenfileirar(&fila));
            fcorpo = fila_excl->corpo;
            printf("%15s;%0.2f;%i;%0.2f;",fcorpo->nome,fcorpo->temperatura, fcorpo->peso, fcorpo->dist_do_anterior);
                switch (fcorpo->tipo_corpo)
                {
                    case 1:{//Satélite
                        lang == 'P'?printf("%0.2f;%0.2f->Satelite\n",fcorpo->satelite->temp_interna,fcorpo->satelite->rotacao):
                            printf("%0.2f;%0.2f->Satellite\n",fcorpo->satelite->temp_interna,fcorpo->satelite->rotacao);
                        break;
                    }
                    case 2:{//Asteroide
                        lang == 'P'?printf("%i;%0.2f->Asteroide\n",fcorpo->asteroide->quant_minerios,fcorpo->asteroide->velocidade):
                            printf("%i;%0.2f->Asteroid\n",fcorpo->asteroide->quant_minerios,fcorpo->asteroide->velocidade);
                        break;
                    }
                    case 3:{//Planeta Anão
                        lang == 'P'?printf("%i;%0.2f->Planeta Anao\n",fcorpo->p_anao->formato,fcorpo->p_anao->veloc_rotacao):
                            printf("%i;%0.2f->Dwarf Planet\n",fcorpo->p_anao->formato,fcorpo->p_anao->veloc_rotacao);
                        break;
                    }
                    case 4:{//Planeta
                        lang == 'P'?printf("%i;%i;%0.2f;%0.2f->Planeta\n",fcorpo->planeta->tem_vida,fcorpo->planeta->tem_atmosfera,fcorpo->planeta->perc_oxigenio,fcorpo->planeta->perc_toxica):
                            printf("%i;%i;%0.2f;%0.2f->Planet\n",fcorpo->planeta->tem_vida,fcorpo->planeta->tem_atmosfera,fcorpo->planeta->perc_oxigenio,fcorpo->planeta->perc_toxica);
                        break;
                    }
                }
            free(fila_excl);
            fila_excl = NULL;
        }
    }
    return NULL;
}
void exibir_fila(Fila *fila, int control)
{
    if(control == 1)
    {
        if(fila != NULL)
        {
            Corpo_Celeste *fcorpo = fila->corpo;
            printf("%s;%0.2f;%i;%0.2f;",fcorpo->nome,fcorpo->temperatura, fcorpo->peso, fcorpo->dist_do_anterior);
                switch (fcorpo->tipo_corpo)
                {
                    case 1:{//Satélite
                        printf("%0.2f;%0.2f->Satelite\n",fcorpo->satelite->temp_interna,fcorpo->satelite->rotacao);
                        break;
                    }
                    case 2:{//Asteroide
                        printf("%i;%0.2f->Asteroide\n",fcorpo->asteroide->quant_minerios,fcorpo->asteroide->velocidade);
                        break;
                    }
                    case 3:{//Planeta Anão
                        printf("%i;%0.2f->Planeta Anao\n",fcorpo->p_anao->formato,fcorpo->p_anao->veloc_rotacao);
                        break;
                    }
                    case 4:{//Planeta
                        printf("%i;%i;%0.2f;%0.2f->Planeta\n",fcorpo->planeta->tem_vida,fcorpo->planeta->tem_atmosfera,fcorpo->planeta->perc_oxigenio,fcorpo->planeta->perc_toxica);
                        break;
                    }
                }
            exibir_fila(fila->prox, control);
        }
        else
            printf("NULL\n");
    }
    else
    {
        if (fila->estrela==NULL)
        {
            printf("NULL\n");
        }
        else
        {
            printf("Nome: %s, codEstrela: %i, numCorpos: %i, fatorDobra: %f\n",
                    fila->estrela->nome,fila->estrela->cod_estrela,fila->estrela->num_corpos,
                    fila->estrela->fator_de_dobra);
                    exibir_fila(fila->prox, control);
        }
    }
}
Pilha *cria_pilha()
{
    Pilha *p = malloc(sizeof(Pilha));
    p->prox = NULL;
    p->ant = NULL;
    return p;
}
void empilhar(Pilha **pilha, Corpo_Celeste *corpo)
{
    Pilha *no = malloc(sizeof(Pilha));
    if(no)
    {
        no->corpo = corpo;
        no->prox = *pilha;
        no->ant = NULL;
        if(*pilha)
        {
            (*pilha)->ant = no;
        }
        *pilha = no;
    }
}
Pilha *desempilhar(Pilha **pilha)
{
    Pilha *post = (*pilha)->prox;
    Pilha *ant = (*pilha)->prox->ant;
    if(*pilha)
    {
        *pilha = post;
        return ant;
    }
}
void exibir_pilha(Pilha *pilha)
{
    while(pilha->prox != NULL)
    {
        Corpo_Celeste *pcorpo = pilha->corpo;
        printf("%s;%0.2f;%i;%0.2f;",pcorpo->nome,pcorpo->temperatura, pcorpo->peso, pcorpo->dist_do_anterior);
            switch (pcorpo->tipo_corpo)
            {
                case 1:{//Satélite
                    printf("%0.2f;%0.2f->Satelite\n",pcorpo->satelite->temp_interna,pcorpo->satelite->rotacao);
                    break;
                }
                case 2:{//Asteroide
                    printf("%i;%0.2f->Asteroide\n",pcorpo->asteroide->quant_minerios,pcorpo->asteroide->velocidade);
                    break;
                }
                case 3:{//Planeta Anão
                    printf("%i;%0.2f->Planeta Anao\n",pcorpo->p_anao->formato,pcorpo->p_anao->veloc_rotacao);
                    break;
                }
                case 4:{//Planeta
                    printf("%i;%i;%0.2f;%0.2f->Planeta\n",pcorpo->planeta->tem_vida,pcorpo->planeta->tem_atmosfera,pcorpo->planeta->perc_oxigenio,pcorpo->planeta->perc_toxica);
                    break;
                }
            }
        pilha = pilha->prox;
    }
    printf("NULL\n");
}
void esvaziar_pilha(Pilha *pilha)
{
    Pilha *excluido = NULL;
    if (pilha->prox!=NULL)
    {
        esvaziar_pilha(pilha->prox);
        excluido = (desempilhar(&pilha));
        free(excluido);
        excluido = NULL;
    }
}
FILE *openFile(char *filename,char *tipo)
{
    FILE *f = fopen(filename,"r");
    if (f==NULL)
    {
        printf("Error\n");
        exit(0);
    }
    return f;
}
Galaxia *cria_galaxia(char nome[], int num_estrelas)
{
    Galaxia *nova_galaxia = malloc(sizeof(Galaxia));
    nova_galaxia->inicio = NULL;
    nova_galaxia->limite_atual = NULL;
    strcpy(nova_galaxia->nome, nome);
    nova_galaxia->num_estrelas = num_estrelas;
    return nova_galaxia;
}
Estrela *cria_estrela(int cod_estrela, int num_corpos, char nome_estrela[], float fator_de_dobra)
{
    Estrela *nova_estrela = malloc(sizeof(Estrela));
    nova_estrela->cod_estrela = cod_estrela;
    nova_estrela->cod_prox = NULL;
    nova_estrela->fator_de_dobra = fator_de_dobra;
    nova_estrela->lista = NULL;
    strcpy(nova_estrela->nome, nome_estrela);
    nova_estrela->num_corpos = num_corpos;
    return nova_estrela;
}
Corpo_Celeste *cria_corpocl()
{
    Corpo_Celeste *ccl = malloc(sizeof(Corpo_Celeste));
    strcpy(ccl->nome , " ");
    ccl->peso = -1;
    ccl->temperatura = -1;
    ccl->tipo_corpo = -1;
    ccl->prox = NULL;
    ccl->asteroide = malloc(sizeof(Asteroide));
    ccl->satelite = malloc(sizeof(Satelite));
    ccl->p_anao = malloc(sizeof(Planeta_Anao));
    ccl->planeta = malloc(sizeof(Planeta));
    return ccl;
}
Galaxia *leitura_galaxia(char *filename)
{
    char nome[35];
    int num_estrelas;
    FILE *f = openFile(filename,"r");
    fscanf(f,"%i;%[^\n]s",&num_estrelas,nome);
    fclose(f);
    Galaxia *nova_galaxia = cria_galaxia(nome, num_estrelas);
    return nova_galaxia;
}

void leitura_estrela(char *filename, Galaxia *galaxia)
{
    int i=0;
    int cod_estrela, num_corpos;
    char nome_estrela[35];
    float fator_de_dobra;
    FILE *f = openFile(filename,"r");
    while (fscanf(f,"%i;%i;%f;%[^\n]s\n",&cod_estrela,&num_corpos,&fator_de_dobra,nome_estrela)>0)
    {
        Estrela *nova = cria_estrela(cod_estrela, num_corpos, nome_estrela, fator_de_dobra);
        if(galaxia->inicio == NULL)
        {
            galaxia->inicio = nova;
            galaxia->limite_atual = nova;

        }
        else
        {
            galaxia->limite_atual->cod_prox = nova;
            galaxia->limite_atual=nova;
        }
    }

    fclose(f);
}

void leitura_corpos(char *filename, Estrela *estrela)
{
    int i=0,n=0, j=0;
    char txt[255];
    Estrela *auxE = estrela;
    FILE *f = openFile(filename,"r");
    while (fgets(txt,255,f)>0)
    {
        n++;
    }
    printf("N:%i\n",n);
    rewind(f);
    while (i<n)
    {
        while(j < auxE->num_corpos)
        {
            Corpo_Celeste *auxL = cria_corpocl();
            fscanf(f,"%i;%[^;];%f;%i;%f;",&auxL->tipo_corpo,auxL->nome,
               &auxL->temperatura,&auxL->peso,&auxL->dist_do_anterior);
            switch (auxL->tipo_corpo)
            {
                case 1:{//Satélite
                    fscanf(f,"%f;%f\n",&auxL->satelite->temp_interna,&auxL->satelite->rotacao);
                    break;
                }
                case 2:{//Asteroide
                    fscanf(f,"%i;%f\n",&auxL->asteroide->quant_minerios,&auxL->asteroide->velocidade);
                    break;
                }
                case 3:{//Planeta Anão
                    fscanf(f,"%i;%f\n",&auxL->p_anao->formato,&auxL->p_anao->veloc_rotacao);
                    break;
                }
                case 4:{//Planeta
                    fscanf(f,"%i;%i;%f;%f\n",&auxL->planeta->tem_vida,&auxL->planeta->tem_atmosfera,
                           &auxL->planeta->perc_oxigenio,&auxL->planeta->perc_toxica);
                    break;
                }
            }
            if(auxE->lista == NULL)
            {
                auxE->lista = auxL;
            }
            else
            {
                Corpo_Celeste *aux = auxE->lista;

                while(aux->prox!= NULL)
                {
                    aux = aux->prox;
                }
                aux->prox = auxL;
            }
            auxL = auxL->prox;
            j++;
        }
        i += j;
        auxE = auxE->cod_prox;
        j=0;
    }
    fclose(f);
}
void buscar_vida(Estrela *estrela, char lang)
{
    if(lang == 'P')
        printf("\n\n%42s", "Corpos Com Vida");
    else
        printf("\n\n%47s", "Celestial Bodys with Life");

    Pilha *pilha = cria_pilha();
    Fila *fila = criar_fila();
    Estrela *aux = estrela;
    Corpo_Celeste *aux2 = NULL;
    float distancia=0;
    while(aux != NULL)
    {
        aux2 = aux->lista;
        while(aux2 != NULL)
        {
            if(aux2->tipo_corpo == 4)
            {
                if(aux2->planeta->tem_vida == 1)
                {
                    printf("\n\n%18s;%0.2f;%i;%0.2f;",aux2->nome,aux2->temperatura,
                            aux2->peso, aux2->dist_do_anterior);
                    if(lang == 'P')
                    {
                        printf("%i;%i;%0.2f;%0.2f->Planeta\n",aux2->planeta->tem_vida,aux2->planeta->tem_atmosfera,
                           aux2->planeta->perc_oxigenio,aux2->planeta->perc_toxica);
                        printf("\n%45s\n%37.2f\n","DISTÂNCIA PERCORRIDA", distancia);
                    }
                    else
                    {
                        printf("%i;%i;%0.2f;%0.2f->Planet\n",aux2->planeta->tem_vida,aux2->planeta->tem_atmosfera,
                           aux2->planeta->perc_oxigenio,aux2->planeta->perc_toxica);
                        printf("\n%44s\n%37.2f\n","TRAVELLED DISTANCE", distancia);
                    }
                    enfileirar(&fila, aux, 0, aux2);
                }
                else
                {
                    if(aux2 != NULL)
                        empilhar(&pilha, aux2);
                }
            }
            else
            {
                if(aux2 != NULL)
                    empilhar(&pilha, aux2);
            }
             aux2 = aux2->prox;
        }
        distancia += aux->fator_de_dobra;
        esvaziar_pilha(pilha);
        aux = aux->cod_prox;
        pilha = cria_pilha();
    }
    printf("\n\n");
    printf("_______________________________________________________________________\n");
    if(lang == 'P')
        printf("\n%46s\n\n", "Estrelas que têm vida");
    else
        printf("\n%42s\n\n", "Stars with life");
    fila = esvaziar_fila(fila, 0, lang);
    printf("\n_______________________________________________________________________\n");
    return;
}
void buscar_peso(Estrela *estrela, int X, char lang)
{
    Estrela *auxE = estrela;
    Fila *fila = criar_fila();
    while(auxE != NULL)
    {
        Corpo_Celeste *auxL = auxE->lista;
        while(auxL != NULL)
        {
            if(auxL->peso < X)
            {
                enfileirar(&fila, auxE, 1, auxL);
            }
            auxL = auxL->prox;
        }
        auxE = auxE->cod_prox;
    }
    fila = esvaziar_fila(fila, 1, lang);
}
void buscar_temp(Estrela *estrela, int X, int Y, char lang)
{
    if(estrela == NULL)
    {
        printf("\n");
    }
    else
    {
        Corpo_Celeste *auxL = estrela->lista;
        while(auxL != NULL)
        {
            if(auxL->temperatura < Y && auxL->temperatura > X)
            {
                printf("%18s;%0.2f;%i;%0.2f;",auxL->nome,auxL->temperatura, auxL->peso, auxL->dist_do_anterior);
                switch (auxL->tipo_corpo)
                {
                    case 1:{//Satélite
                        lang == 'P' ? printf("%0.2f;%0.2f->Satelite\n",auxL->satelite->temp_interna,auxL->satelite->rotacao):
                            printf("%0.2f;%0.2f->Satellite\n",auxL->satelite->temp_interna,auxL->satelite->rotacao);
                        break;
                    }
                    case 2:{//Asteroide
                        lang == 'P'? printf("%i;%0.2f->Asteroide\n",auxL->asteroide->quant_minerios,auxL->asteroide->velocidade):
                            printf("%i;%0.2f->Asteroid\n",auxL->asteroide->quant_minerios,auxL->asteroide->velocidade);
                        break;
                    }
                    case 3:{//Planeta Anão
                        lang == 'P'? printf("%i;%0.2f->Planeta Anao\n",auxL->p_anao->formato,auxL->p_anao->veloc_rotacao):
                           printf("%i;%0.2f->Dwarf Planet\n",auxL->p_anao->formato,auxL->p_anao->veloc_rotacao);
                        break;
                    }
                    case 4:{//Planeta
                        lang == 'P'? printf("%i;%i;%0.2f;%0.2f->Planeta\n",auxL->planeta->tem_vida,auxL->planeta->tem_atmosfera,auxL->planeta->perc_oxigenio,auxL->planeta->perc_toxica):
                            printf("%i;%i;%0.2f;%0.2f->Planet\n",auxL->planeta->tem_vida,auxL->planeta->tem_atmosfera,auxL->planeta->perc_oxigenio,auxL->planeta->perc_toxica);
                        break;
                    }
                }
            }
            auxL = auxL->prox;
        }
        buscar_temp(estrela->cod_prox, X, Y, lang);
    }
}
void exibir_estrela(Estrela *estrela, char lang)
{
    if (estrela==NULL)
    {
        printf("\n");
    }
    else
    {
        lang == 'P'? printf("Nome: %s, codEstrela: %i, numCorpos: %i, fatorDobra: %f\n",
                estrela->nome,estrela->cod_estrela,estrela->num_corpos,estrela->fator_de_dobra):
                    printf("Name: %s, codStar: %i, numCorps: %i, warpFactor: %f\n",
                estrela->nome,estrela->cod_estrela,estrela->num_corpos,estrela->fator_de_dobra);;
        exibir_estrela(estrela->cod_prox, lang);
    }
}
void exibir_corpos(Estrela *estrela, char lang)
{
    Estrela *aux = estrela;
    Corpo_Celeste *aux2 = NULL;
    while(aux != NULL)
    {
        aux2 = aux->lista;
        if(strlen(aux->nome) < 10)
            lang == 'P' ? printf("%37s\n\n%37s\n\n%37s\n\n", "ESTRELA", aux->nome, "CORPOS"):
                printf("%36s\n\n%37s\n\n%41s\n\n", "STARS", aux->nome, "CELESTIAL BODYS");
        else
            lang == 'P' ? printf("%37s\n\n%40s\n\n%37s\n\n", "ESTRELA", aux->nome, "CORPOS"):
                printf("%36s\n\n%40s\n\n%41s\n\n", "STARS", aux->nome, "CELESTIAL BODYS");
        while(aux2 != NULL)
        {
            printf("%15s;%0.2f;%i;%0.2f;",aux2->nome,aux2->temperatura, aux2->peso, aux2->dist_do_anterior);
            switch (aux2->tipo_corpo)
            {
                case 1:{//Satélite
                        lang == 'P' ? printf("%0.2f;%0.2f->Satelite\n",aux2->satelite->temp_interna,aux2->satelite->rotacao):
                            printf("%0.2f;%0.2f->Satellite\n",aux2->satelite->temp_interna,aux2->satelite->rotacao);
                        break;
                    }
                    case 2:{//Asteroide
                        lang == 'P'? printf("%i;%0.2f->Asteroide\n",aux2->asteroide->quant_minerios,aux2->asteroide->velocidade):
                            printf("%i;%0.2f->Asteroid\n",aux2->asteroide->quant_minerios,aux2->asteroide->velocidade);
                        break;
                    }
                    case 3:{//Planeta Anão
                        lang == 'P'? printf("%i;%0.2f->Planeta Anao\n",aux2->p_anao->formato,aux2->p_anao->veloc_rotacao):
                           printf("%i;%0.2f->Dwarf Planet\n",aux2->p_anao->formato,aux2->p_anao->veloc_rotacao);
                        break;
                    }
                    case 4:{//Planeta
                        lang == 'P'? printf("%i;%i;%0.2f;%0.2f->Planeta\n",aux2->planeta->tem_vida,aux2->planeta->tem_atmosfera,aux2->planeta->perc_oxigenio,aux2->planeta->perc_toxica):
                            printf("%i;%i;%0.2f;%0.2f->Planet\n",aux2->planeta->tem_vida,aux2->planeta->tem_atmosfera,aux2->planeta->perc_oxigenio,aux2->planeta->perc_toxica);
                        break;
                    }
            }
            aux2 = aux2->prox;
        }
        if(aux->num_corpos == 0)
            lang == 'P' ? printf("%44s", "Nenhum Corpo Celestial"): printf("%42s", "No Celestial body");
        printf("\n");
        printf("______________________________________________________________________\n\n");
        aux = aux->cod_prox;
    }
}
char select_lang(char **galaxyTxt, char **starTxt, char **bodyTxt)
{
    char lang;
    char *galaxia = "Galaxia.txt";
    printf("Selecione o Idioma:\nPortugues -> P\nIngles -> I\n");
    scanf("%c", &lang);
    lang = toupper(lang);
    switch(lang)
    {
    case 'I':
        {
            *galaxyTxt = "Ingles\\Galaxia.txt";
            *starTxt = "Ingles\\Estrelas.txt";
            *bodyTxt = "Ingles\\Corpos.txt";
            break;
        }
    case 'P':
        {
            setlocale(LC_ALL, "Portuguese");
            *galaxyTxt = galaxia;
            *starTxt = "Estrelas.txt";
            *bodyTxt = "Corpos.txt";
            break;
        }
    default:
        {
            puts("Letra inválida\n");
            break;
        }
    }
    return lang;
}
int main()
{
    int i, X = 1000;
    float tempX = -1, tempY = 50.0;
    char *galaxyTxt, *starTxt, *bodyTxt;
    char lang = select_lang(&galaxyTxt, &starTxt, &bodyTxt);


    Galaxia *galaxia = leitura_galaxia(galaxyTxt);

    printf("______________________________________________________________________\n\n");
    if(lang == 'P')
    {
        printf("%37s\n", "GALAXIA");
        printf("%40s\n%37s\n%34i\n",galaxia->nome," Estrelas",galaxia->num_estrelas);
    }
    else
    {
        printf("%36s\n", "GALAXY");
        printf("%40s\n%36s\n%34i\n",galaxia->nome," Stars",galaxia->num_estrelas);
    }
    printf("______________________________________________________________________\n\n");
    leitura_estrela(starTxt, galaxia);
    lang == 'P'? printf("%37s\n\n", "ESTRELAS"): printf("%36s\n\n", "STARS");
    exibir_estrela(galaxia->inicio, lang);
    leitura_corpos(bodyTxt, galaxia->inicio);
    printf("______________________________________________________________________\n\n");
    exibir_corpos(galaxia->inicio, lang);
    lang == 'P' ? printf("%42s", "BUSCA POR VIDA"): printf("%42s", "SEARCH FOR LIFE");
    buscar_vida(galaxia->inicio, lang);
    printf("\n");
    lang == 'P'? printf("%47s%i\n\n", "Corpos com peso inferior a:", X):
        printf("%45s%i\n\n", "Bodys weighing less than:", X) ;
    buscar_peso(galaxia->inicio, X, lang);
    printf("______________________________________________________________________\n\n");
    lang=='P'?printf("%37s %.2f > temp > %.2f\n\n", "Corpos com temperatura", tempX, tempY):
        printf("%36s %.2f > temp > %.2f\n\n", "Bodys with temperature", tempX, tempY);
    buscar_temp(galaxia->inicio, tempX, tempY, lang);


    return 0;
}
