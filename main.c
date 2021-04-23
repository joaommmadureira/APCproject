#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo constantes
#define TAM_MAX 100
#define arq_cadastros "arquivos/cadastros.bin"
#define arq_cidades "arquivos/cidades.txt"
#define arq_estados "arquivos/estados.txt"

// Struct para data
typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

// Registro do cadastro de uma pessoa
typedef struct
{
    char nome[TAM_MAX];
    char sexo;
    Data data;
    char cidade[TAM_MAX];
    char estado[TAM_MAX];
} Cadastro;

// Funcoes e procedimentos presentes no programa
void mostrar_menu();
void cadastrar_pessoa();
int validar_sexo(char sexo);
int validar_data(Cadastro pessoa);
int validar_cidade(char cidade[]);
int validar_estado(char estado[]);
void gravar_registro(Cadastro pessoa);
void cadastrar_estado();
void cadastrar_cidade();
void listar_pessoas_estado();
void listar_pessoas_cidade();
void listar_pessoas_nome();


int main() {
    int opcao_menu;

    printf("\nREGISTRO DEMOGRAFICO DE VACINACAO\n");

    do {
        // Escolhendo um operacao do programa
        printf("\n--------------------------------------------\n");
        mostrar_menu();
        printf("\n--------------------------------------------\n");
        printf("\n\tEscolha uma operacao: ");
        scanf("%d", &opcao_menu);

        switch ( opcao_menu ) {
            case 1:
            // Cadastrando um estado.
            cadastrar_estado();

            printf("Pressione uma tecla para continuar...\n");
            getch();
            break;

            case 2:
            // Cadastrando uma cidade.
            cadastrar_cidade();

            printf("Pressione uma tecla para continuar...\n");
            getch();
            break;

            case 3:
            // Cadastrando uma pessoa.
            cadastrar_pessoa();

            printf("Pressione uma tecla para continuar...\n");
            getch();
            break;

            case 4:
            // Listando pessoas por estado.
            listar_pessoas_estado();

            printf("Pressione uma tecla para continuar...\n");
            getch();
            break;

            case 5:
            // Listando pessoas por cidade.
            listar_pessoas_cidade();

            printf("Pressione uma tecla para continuar...\n");
            getch();
            break;

            case 6:
            // Listando pessoas por nome.
            listar_pessoas_nome();

            printf("Pressione uma tecla para continuar...\n");
            getch();
            break;

            case 7:
            //

            break;

            case 8:
            //

            break;

            case 9: 
            break;

            default:
            printf("\nValor invalido, por favor escolha uma das opcoes abaixo.\n");
            break;


        }
    } while (opcao_menu != 9);

    return 0;
}

// Procedimento para mostrar o menu do programa.
void mostrar_menu() {
    printf("\n1) Cadastrar estado\n");
    printf("2) Cadastrar cidade\n");
    printf("3) Cadrastar pessoa\n");
    printf("4) Listar pessoas por estado\n");
    printf("5) Listar pessoas por cidade\n");
    printf("6) Consultar pessoa por nome\n");
    printf("7) Excluir pessoa\n");
    printf("8) Gerar relatorio de vacincao\n");
    printf("9) Encerrar Programa\n");
};

// Cadastrar um novo estado
void cadastrar_estado() {
    char estado[TAM_MAX];
    char estado_existente[TAM_MAX];
    int verificador = 0;
    int i;

    printf("\nCADASTRAR ESTADO");
    printf("\n\tDigite o nome do estado que deseja cadastrar: ");
    scanf(" %[^\n]s", estado);

    FILE *arquivo;
    arquivo = fopen(arq_estados, "r+t");

    if (validar_estado(estado) == 1)
    {
        printf("\nEstado ja cadastrado!\n");
        return;
    }

    if(verificador != 1)
    {
        strcat(estado, ",");
        fputs(strlwr(estado), arquivo);

        if(ferror(arquivo))
            printf("\nErro ao salvar os dados\n");
        else
        {
            fclose(arquivo);
            printf("\nEstado cadastrado com sucesso!\n");
        }
    }
}

// Cadastrar uma nova cidade
void cadastrar_cidade() {
    char cidade[TAM_MAX];
    char cidade_existente[TAM_MAX];
    int verificador = 0;
    int i;

    printf("\nCADASTRAR CIDADE");
    printf("\n\tDigite o nome da cidade que deseja cadastrar: ");
    // Lendo cidade a ser cadastrada.
    scanf(" %[^\n]s", cidade);

    // Abrindo arquivo.
    FILE *arquivo;
    arquivo = fopen(arq_cidades, "r+t");

    if (validar_cidade(cidade) == 1)
    {
        printf("\nCidade ja cadastrada!\n");
        return;
    }

    if(verificador != 1)
    {
        strcat(cidade, ",");
        fputs(strlwr(cidade), arquivo);

        if(ferror(arquivo))
            printf("\nErro ao salvar os dados\n");
        else
        {
            fclose(arquivo);
            printf("\nCidade cadastrada com sucesso!\n");
        }
    }
}

// Funcao para cadastrar uma pessoa no sistema.
void cadastrar_pessoa() {
    Cadastro pessoa;
    
    printf("\nCADASTRAR PESSOA");
    printf("\nPreencha as informacoes solicitadas.\n");

    printf("\tNome completo: ");
    scanf(" %[^\n]s", pessoa.nome);

    printf("\tSexo(M para Masculino ou F para feminino): ");
    scanf(" %c", &pessoa.sexo);
    if (validar_sexo(pessoa.sexo) == 0)
    {
        printf ("\nInsira um sexo valido. Por favor, tente novamente.\n");
        return;
    }

    printf("\tData de nascimento (no seguinte formato ""dd/mm/aaaa""): ");
    scanf("%d/%d/%d", &pessoa.data.dia, &pessoa.data.mes, &pessoa.data.ano);
    if (validar_data(pessoa) == 0)
    {
        printf ("\nInsira uma data valida! Por favor, tente novamente.\n");
        return;
    }

    printf("\tCidade: ");
    scanf(" %[^\n]s", pessoa.cidade);
    // Fazendo a validacao da cidade
    if (validar_cidade(pessoa.cidade) == 0)
    {
        printf ("\nE necessario cadastrar a cidade antes de registrar pessoas nela! Por favor, tente novamente.\n");
        return;
    }

    printf("\tUnidade Federativa: ");
    scanf(" %[^\n]s", pessoa.estado);
    // Fazendo a validacao da cidade
    if (validar_estado(pessoa.estado) == 0)
    {
        printf ("\nE necessario cadastrar o estado antes de registrar pessoas nele! Por favor, tente novamente.\n");
        return;
    }

    gravar_registro(pessoa);
};

// Funcao para validar o sexo selecionado, retorna 0 quando invalido.
int validar_sexo(char sexo) {
    if(sexo == 'M' || sexo== 'F') return;
    else return 0;
}

// Funcao para validar a data escrita, retorna 0 quando invalida.
int validar_data(Cadastro pessoa) {
    // Verficacoes gerais.
    if(pessoa.data.mes < 1 || pessoa.data.mes > 12 || pessoa.data.dia < 1) return 0;
    // Verificando o mes de fevereiro, incluindo os anos bissextos.
    if(pessoa.data.mes == 2) 
    {
        if(pessoa.data.ano%4 == 0)
        {
            if(pessoa.data.dia > 29) return 0;
        }
        else if(pessoa.data.dia > 28) return 0;  
    }
    // Verificando os meses com 30 dias.
    else if(pessoa.data.mes == 4 || pessoa.data.mes == 6 || pessoa.data.mes == 9 || pessoa.data.mes == 11) 
    {
        if(pessoa.data.dia > 30) return 0;
    }
    // Verificando os meses com 31 dias.
    else if(pessoa.data.dia > 31) return 0;

    return;
}

// Funcao que verifica se a cidade passada existe no arquivos de cidades. Retorna 1 se encontrar e 0 se nao.
int validar_cidade(char cidade[]) {
    char cidade_existe[TAM_MAX];

    FILE *arquivo;
    arquivo = fopen(arq_cidades, "rt");

    while(!feof(arquivo))
    {
        fscanf(arquivo, " %[^,],", cidade_existe);
        
        if(strcmp(strlwr(cidade_existe), strlwr(cidade)) == 0)
        {
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0;
}

// Funcao que verifica se o estado passado existe no arquivos de estados. Retorna 1 se encontrar e 0 se nao.
int validar_estado(char estado[]) {
    char estado_existe[TAM_MAX];

    FILE *arquivo;
    arquivo = fopen(arq_estados, "rt");

    while(!feof(arquivo))
    {
        
        fscanf(arquivo, " %[^,],", estado_existe);
        
        if(strcmp(strlwr(estado_existe), strlwr(estado)) == 0)
        {
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0;
}

// Procedimento que salva as informacoes inseridas no registro no arquivo.
void gravar_registro(Cadastro pessoa) {
    FILE *arquivo;
    arquivo = fopen(arq_cadastros, "r+b");

    if(arquivo) 
    {
        fseek(arquivo, 0, SEEK_END);
        fwrite(&pessoa, sizeof(pessoa), 1, arquivo);
        fclose(arquivo);
        printf("\nCadastro realizado!\n");
    }
    else 
    {
        fclose(arquivo);
        printf("Erro ao armazenar os dados. Por favor, tente novamente.");
    } 
}

// Procedimento para listar pessoas por estado.
void listar_pessoas_estado() {
    char estado[TAM_MAX];
    Cadastro pessoa;
    int i = 1;

    printf("\nLISTAR PESSOAS POR ESTADO");
    printf("\n\tDigite o estado a ser pesquisado: ");
    scanf(" %[^\n]s", estado);

    if (validar_estado(estado) == 0)
    {
        printf("\nEstado nao cadastrado!\n");
    }

    FILE *arquivo;
    arquivo = fopen(arq_cadastros, "rb");

    fseek(arquivo, 0, SEEK_SET);

    while(fread(&pessoa, sizeof(Cadastro), 1, arquivo))
    {
        if (strcmp(strlwr(estado), strlwr(pessoa.estado)) == 0)
        {
            printf("%d - %s\n", i, pessoa.nome);
            i++;
        }
    }
    fclose(arquivo);
}

// Procedimento para listar pessoas por estado.
void listar_pessoas_cidade() {
    char cidade[TAM_MAX];
    Cadastro pessoa;
    int i = 0;

    printf("\nLISTAR PESSOAS POR CIDADE");
    printf("\n\tDigite a cidade a ser pesquisada: ");
    scanf(" %[^\n]s", cidade);

    if (validar_cidade(cidade) == 0)
    {
        printf("\nCidade nao cadastrada!\n");
    }

    FILE *arquivo;
    arquivo = fopen(arq_cadastros, "rb");

    fseek(arquivo, 0, SEEK_SET);

    while(fread(&pessoa, sizeof(Cadastro), 1, arquivo))
    {
        if (strcmp(strlwr(cidade), strlwr(pessoa.cidade)) == 0)
        {
            i++;
            printf("%d - %s\n", i, pessoa.nome);
        }
    }
    fclose(arquivo);
}

// Procedimento para a listagem por nome.
void listar_pessoas_nome() {
    char nome[TAM_MAX];
    Cadastro pessoa;
    int i = 0;

    printf("\nCONSULTAR PESSOA POR NOME");
    printf("\n\tDigite o nome a ser consultado: ");
    scanf(" %[^\n]s", nome);

    FILE *arquivo;
    arquivo = fopen(arq_cadastros, "rb");

    fseek(arquivo, 0, SEEK_SET);

    while(fread(&pessoa, sizeof(Cadastro), 1, arquivo))
    {
        if (strcmp(strlwr(pessoa.nome), strlwr(nome)) >= 0)
        {
            i++;
            printf("%d - %s\n", i, pessoa.nome);
        }
    }
    fclose(arquivo);
}

// 