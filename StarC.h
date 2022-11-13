#ifndef STARC_H
#define STARC_H

typedef struct
{
    int quant_minerios;
    float velocidade;
}Asteroide;
typedef struct
{
    int formato;
    float veloc_rotacao;
}Planeta_Anao;
typedef struct
{
    float temp_interna;
    float rotacao;
}Satelite;
typedef struct
{
    int tem_vida;
    int tem_atmosfera;
    float perc_oxigenio;
    float perc_toxica;
}Planeta;
typedef struct _corpo_celeste
{
    char nome[35];
    float temperatura;
    int peso;
    float dist_do_anterior;
    struct _corpo_celeste *prox;
    int tipo_corpo;
    union
    {
        Planeta *planeta;
        Planeta_Anao *p_anao;
        Asteroide *asteroide;
        Satelite *satelite;
    };

}Corpo_Celeste;
typedef struct _estrela
{
    char nome[35];
    int num_corpos;
    int cod_estrela;
    float fator_de_dobra;
    Corpo_Celeste *lista;
    struct _estrela *cod_prox;
}Estrela;
typedef struct
{
    char nome[35];
    int num_estrelas;
    Estrela *inicio;
    Estrela *limite_atual;
}Galaxia;
typedef struct _fila
{
    Estrela *estrela;
    Corpo_Celeste *corpo;
    struct _fila *ant;
    struct _fila *prox;
}Fila;
typedef struct _pilha
{
    Corpo_Celeste *corpo;
    struct _pilha *prox;
    struct _pilha *ant;
}Pilha;

Fila *criar_fila();
Fila *cria_no(Estrela *estrela, Corpo_Celeste *corpo ,int control);
int fila_vazia(Fila *fila);
void enfileirar(Fila **fila, Estrela *estrela, int control, Corpo_Celeste *corpo);
Fila *desenfileirar(Fila **fila);
Fila *esvaziar_fila(Fila *fila, int control, char lang);
void exibir_fila(Fila *fila, int control);
Pilha *cria_pilha();
void empilhar(Pilha **pilha, Corpo_Celeste *corpo);
Pilha *desempilhar(Pilha **pilha);
void exibir_pilha(Pilha *pilha);
void esvaziar_pilha(Pilha *pilha);
FILE *openFile(char *filename,char *tipo);
Galaxia *cria_galaxia(char nome[], int num_estrelas);
Estrela *cria_estrela(int cod_estrela, int num_corpos, char nome_estrela[], float fator_de_dobra);
Corpo_Celeste *cria_corpocl();
Galaxia *leitura_galaxia(char *filename);
void leitura_estrela(char *filename, Galaxia *galaxia);
void leitura_corpos(char *filename, Estrela *estrela);
void buscar_vida(Estrela *estrela, char lang);
void buscar_vida(Estrela *estrela, char lang);
void buscar_temp(Estrela *estrela, int X, int Y, char lang);
void exibir_estrela(Estrela *estrela, char lang);
void exibir_corpos(Estrela *estrela, char lang);
char select_lang(char **galaxyTxt, char **starTxt, char **bodyTxt);

#endif
