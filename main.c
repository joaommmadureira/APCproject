#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct
{
    char nome[50];
    char sexo;
    Data data;
    char cidade[50];
    char uf[50];
} Cadastro;

void mostrar_menu();
Cadastro cadastrar_pessoa();
void mostrar_cadastro(Cadastro pessoa);
int validar_data(Cadastro pessoa);
int validar_cidade(Cadastro pessoa);
int validar_uf(Cadastro pessoa);
int gravar_dados(Cadastro pessoa);

int main() {
    int opcao_menu;
    Cadastro pessoa;

    do {
        mostrar_menu();
        printf("Escolha uma operacao: ");
        scanf("%d", &opcao_menu);

        switch ( opcao_menu )
        {
            case 1:
            //

            break;

            case 2:
            //

            break;

            case 3:
            // Coletando os dados.
            pessoa = cadastrar_pessoa();
            // Verficando os dados.
            if(validar_sexo(pessoa) == 0 || validar_data(pessoa) == 0 || validar_cidade(pessoa) == 0 || validar_uf(pessoa) == 0) 
            {
                printf("\nDados invalidos!\n");
                if(validar_data(pessoa) == 0) printf("\tColoque uma data valida.\n");
                if(validar_sexo(pessoa) == 0) printf("\tSelecione uma opcao de sexo valida.\n");
                if(validar_cidade(pessoa) == 0 || validar_uf(pessoa) == 0) printf("\tÉ preciso cadastrar a cidade e a unidade federativa antes de se cadastrar uma pessoa neles.\n");
                printf("\nPor favor, verifique seus dados e tente novamente.\n");
            }
            // Gravando o cadastro.
            else gravar_dados(pessoa);

            printf("\nPressione uma tecla para continuar...\n");
            getch();
            break;

            case 4:
            //

            break;

            case 5:
            //

            break;

            case 6:
            //

            break;

            case 7:
            //

            break;

            case 8:
            //

            break;

            case 9: 
            //

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

// Funcao para cadastrar uma pessoa no sistema.
Cadastro cadastrar_pessoa() {
    Cadastro pessoa;
    
    printf("\nPreencha as informacoes solicitadas.\n");

    printf("\tNome completo: ");
    scanf(" %[^\n]s", pessoa.nome);

    printf("\tSexo(M para Masculino ou F para feminino): ");
    scanf(" %c", &pessoa.sexo);

    printf("\tData de nascimento(no seguinte formato ""dd/mm/aaaa""): ");
    scanf("%d/%d/%d", &pessoa.data.dia, &pessoa.data.mes, &pessoa.data.ano);

    printf("\tCidade: ");
    scanf(" %[^\n]s", pessoa.cidade);

    printf("\tUnidade Federativa: ");
    scanf(" %[^\n]s", pessoa.uf);

    return pessoa;
};

// Funcao para mostra os dados do cadastro.
void mostrar_cadastro(Cadastro pessoa) {
    printf("\n%s", pessoa.nome);
    printf("\n%c", pessoa.sexo);
    printf("\n%d/%d/%d", pessoa.data.dia, pessoa.data.mes, pessoa.data.ano);
    printf("\n%s", pessoa.cidade);
    printf("\n%s\n", pessoa.uf);
}

int validar_sexo(Cadastro pessoa) {
    if(pessoa.sexo == 'M' || pessoa.sexo== 'F') return 1;
    else return 0;
}

// Validando a data escrita, retorna 1 quando valida e 0 quando invalida.
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

    return 1;
}

int validar_cidade(Cadastro pessoa) {
    // TO DO
}

int validar_uf(Cadastro pessoa) {
    // TO DO
}

int gravar_dados(Cadastro pessoa) {
    FILE *arquivo;
    arquivo = fopen("dados.txt", "r+b");

    if(arquivo) 
    {
        fseek(arquivo,0,SEEK_END);
        fwrite(&pessoa, sizeof(pessoa), 1, arquivo);
        fclose(arquivo);
        printf("\nCadastro realizado!\n");
    }
    else printf("Erro ao armazenar os dados. Por favor, tente novamente. ");
}