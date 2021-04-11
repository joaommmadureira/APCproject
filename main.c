#include <stdio.h>

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
void mostrar_cadastro(Cadastro teste);
int validar_data(Cadastro pessoa);

int main() {
    int opcao_menu;
    Cadastro teste;

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
            teste = cadastrar_pessoa();

            if(validar_data(teste) == 0) printf("Data invalida, tente novamente.");

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
            printf("Valor invalido, por favor escolha uma das opcoes abaixo.\n");
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
    Cadastro teste;
    
    printf("\n\tPreencha as informacoes solicitadas.\n");

    printf("Nome completo: ");
    scanf(" %[^\n]s", teste.nome);

    printf("Sexo(M para Masculino ou F para feminino): ");
    scanf(" %c", &teste.sexo);

    printf("Data de nascimento(no seguinte formato ""dd/mm/aaaa""): ");
    scanf("%d/%d/%d", &teste.data.dia, &teste.data.mes, &teste.data.ano);

    printf("Cidade: ");
    scanf(" %[^\n]s", teste.cidade);

    printf("Unidade Federativa: ");
    scanf(" %[^\n]s", teste.uf);

    return teste;
};

// Funcao para mostra os dados do cadastro.
void mostrar_cadastro(Cadastro pessoa) {
    printf("\n%s", pessoa.nome);
    printf("\n%c", pessoa.sexo);
    printf("\n%d/%d/%d", pessoa.data.dia, pessoa.data.mes, pessoa.data.ano);
    printf("\n%s", pessoa.cidade);
    printf("\n%s\n", pessoa.uf);
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