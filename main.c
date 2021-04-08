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
            mostrar_cadastro(teste);
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
            break;

            default:
            printf("Valor invalido, por favor escolha uma das opcoes abaixo.\n");
            break;


        }
    } while (opcao_menu != 9);

    return 0;
}

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

Cadastro cadastrar_pessoa() {
    Cadastro teste;
    
    printf("\nPreencha as informacoes solicitadas.\n");

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

void mostrar_cadastro(Cadastro pessoa) {
    printf("\n%s", pessoa.nome);
    printf("\n%c", pessoa.sexo);
    printf("\n%d/%d/%d", pessoa.data.dia, pessoa.data.mes, pessoa.data.ano);
    printf("\n%s", pessoa.cidade);
    printf("\n%s\n", pessoa.uf);
}

