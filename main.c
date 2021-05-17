#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Definindo constantes.
#define TAM_CIDADE 40
#define TAM_ESTADO 4
#define TAM_SEXO 10
#define TAM_MAX 100
// Constantes para os arquivos.
#define arq_cadastros "cadastros.bin"
#define arq_cidades "cidades.txt"
#define arq_estados "estados.txt"

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
    char sexo[TAM_SEXO];
    Data data;
    char cidade[TAM_CIDADE];
    char estado[TAM_ESTADO];
} Cadastro;

// Funções e procedimentos presentes no programa.
void mostrar_menu();
void cadastrar_pessoa();
int verificar_cadastro(Cadastro pessoa);
int validar_sexo(char sexo[]);
int validar_data(Data pessoa);
int validar_cidade(char cidade[], char estado[]);
int validar_estado(char estado[]);
void gravar_registro(Cadastro pessoa);
void cadastrar_estado(char estado[]);
void cadastrar_cidade(char cidade[], char estado[]);
void listar_pessoas_estado(char estado[]);
void listar_pessoas_cidade(char cidade[]);
void consultar_pessoas_nome(char nome[]);
void deletar_pessoas(char nome[]);
void gerar_relatorio_demografico();
FILE * abrir_arquivos(char arquivo[], char modo[]);
int calcular_idade(Data data);
int validar_nome(char nome[]);
int comparar_strings(char pesquisa[], char consulta[]);
char* deixar_maiusculo(char texto[]);


int main() {
    int opcao_menu; // Armazena a escolha de operação do usuário;
    char estado[TAM_ESTADO];
    char cidade[TAM_CIDADE];
    char nome[TAM_MAX];
    int repetidor; // Variável que vai armazenar a resposta do usuário para repetir a operação.

    do {
        printf("\nREGISTRO DEMOGRAFICO DE VACINACAO\n");
        // Escolhendo um operação do programa
        printf("\n--------------------------------------------\n");
        mostrar_menu();
        printf("\n\tEscolha uma operacao: ");
        scanf("%d", &opcao_menu);
        printf("\n--------------------------------------------\n");

        switch ( opcao_menu ) {
            case 1:
            // Cadastrando um estado.
                printf("\nCADASTRAR ESTADO\n");
                printf("- digite 0 para sair -\n");
                do {
                    printf("\n\tDigite a sigla do estado que deseja cadastrar: ");
                // Lendo o estado a ser cadastrado e chamando o procedimento.
                    scanf(" %[^\n]s", estado);

                    // Interrompendo a execução caso o usuário digite 0
                    if(strcmp(estado, "0") == 0)
                    {
                        printf("\n- Operacao cancelada! -");
                        printf("\nPressione qualquer tecla para continuar...\n");
                        getch();
                        repetidor = 2; // Cancelando a repetiçaõ
                    }
                    else
                    {
                        cadastrar_estado(estado);

                    // Pausando a aplicação
                        printf("\nPressione qualquer tecla para continuar...\n");
                        getch();

                    // Verificando se o usuário quer repetir a 
                        printf("\nDeseja cadastrar outro estado?\n");
                        printf("\t1 - SIM\n\t2 - NAO\n- ");
                        scanf("%d", &repetidor);
                    }
                } while (repetidor == 1);

            break;

        // A maioria das operações abaixo segue o padrão apresentado acima. Com o repetidor e a interupção em caso de 0.

            case 2:
            // Cadastrando uma cidade.
                printf("\nCADASTRAR CIDADE\n");
                printf("- digite 0 para sair -\n");
                do {
                // Lendo a cidade a ser cadastrada e o estado onde ela se encontra.
                    printf("\n\tDigite o nome da cidade que deseja cadastrar: ");
                    scanf(" %[^\n]s", cidade);

                    if (strcmp(cidade, "0") == 0)
                    {
                        printf("\n- Operacao cancelada! -");
                        printf("\nPressione qualquer tecla para continuar...\n");
                        getch();
                        repetidor = 2; // Cancelando a repetiçaõ
                    }
                    else
                    {
                        printf("\tDigite a sigla do estado onde a cidade se encontra: ");
                        scanf(" %[^\n]s", estado);

                        if (strcmp(estado, "0") == 0)
                        {
                            printf("\n- Operacao cancelada! -");
                            printf("\nPressione qualquer tecla para continuar...\n");
                            getch();
                            repetidor = 2; // Cancelando a repetiçaõ
                        }
                        else
                        {
                        // Chamando o procedimento para cadastrar cidades.
                            cadastrar_cidade(cidade, estado);

                            printf("\nPressione qualquer tecla para continuar...\n");
                            getch();

                            printf("\nDeseja cadastrar outra cidade?\n");
                            printf("\t1 - SIM\n\t2 - NAO\n- ");
                            scanf("%d", &repetidor);
                        }
                    }

                } while (repetidor == 1);

            break;

            case 3:
            // Cadastrando uma pessoa.
                printf("\nCADASTRAR PESSOA\n");
                do {
                // Chamando o procedimento para cadastrar pessoas.
                    cadastrar_pessoa();

                    printf("\nPressione qualquer tecla para continuar...\n");
                    getch();

                    printf("\nDeseja cadastrar outra pessoa?\n");
                    printf("\t1 - SIM\n\t2 - NAO\n- ");
                    scanf("%d", &repetidor);
                } while (repetidor == 1);

            break;

            case 4:
            // Listando pessoas por estado.
                printf("\nLISTAR PESSOAS POR ESTADO\n");
                printf("- digite 0 para sair -\n");
                do {
                    printf("\n\tDigite a sigla do estado a ser pesquisado: ");
                // Lendo o estado e chamando procedimento.
                    scanf(" %[^\n]s", estado);

                    if (strcmp(estado, "0") == 0)
                    {
                        printf("\n- Operacao cancelada! -");
                        printf("\nPressione qualquer tecla para continuar...\n");
                        getch();
                        repetidor = 2; // Cancelando a repetiçaõ
                    }                
                    else
                    {
                    listar_pessoas_estado(estado);

                    printf("\nPressione qualquer tecla para continuar...\n");
                    getch();         

                    printf("\nDeseja listar pessoas de outro estado?\n");
                    printf("\t1 - SIM\n\t2 - NAO\n- ");
                    scanf("%d", &repetidor);
                    }

                } while (repetidor == 1);

            break;

            case 5:
            // Listando pessoas por cidade.
                printf("\nLISTAR PESSOAS POR CIDADE\n");
                printf("- digite 0 para sair -\n");
                do {
                    printf("\n\tDigite a cidade a ser pesquisada: ");
                // Lendo a cidade e chamando procedimento.
                    scanf(" %[^\n]s", cidade);

                    if (strcmp(cidade, "0") == 0)
                    {
                        printf("\n- Operacao cancelada! -");
                        printf("\nPressione qualquer tecla para continuar...\n");
                        getch();
                        repetidor = 2; // Cancelando a repetiçaõ
                    }
                    else 
                    {
                        listar_pessoas_cidade(cidade);

                        printf("\nPressione qualquer tecla para continuar...\n");
                        getch(); 

                        printf("\nDeseja listar pessoas de outra cidade?\n");
                        printf("\t1 - SIM\n\t2 - NAO\n- ");
                        scanf("%d", &repetidor);
                    }
                } while (repetidor == 1);

            break;

            case 6:
            // Listando pessoas por nome.
                printf("\nCONSULTAR PESSOA POR NOME\n");
                printf("- digite 0 para sair -\n");
                do {
                    printf("\n\tDigite o nome a ser consultado: ");
                // Lendo o nome da pessoa e chamando procedimento.
                    scanf(" %[^\n]s", nome);

                    if (strcmp(nome, "0") == 0)
                    {
                        printf("\n- Operacao cancelada! -");
                        printf("\nPressione qualquer tecla para continuar...\n");
                        getch();
                        repetidor = 2; // Cancelando a repetiçaõ
                    } 
                    else
                    {
                        consultar_pessoas_nome(nome);

                        printf("\nPressione qualquer tecla para continuar...\n");
                        getch(); 

                        printf("\nDeseja consultar outra pessoa?\n");
                        printf("\t1 - SIM\n\t2 - NAO\n- ");
                        scanf("%d", &repetidor);
                    }

                } while (repetidor == 1);

            break;

            case 7:
            // Deletando um registro.
                printf("\nDELETAR CADASTRO\n");
                printf("- digite 0 para sair -\n");
                do {
                    printf("\n\tDigite o nome do cadastro que deseja excluir: ");
                // Lendo o nome do usuário a ser deletado e chamando o procedimento.
                    scanf(" %[^\n]s", nome);

                    if (strcmp(nome, "0") == 0)
                    {
                        printf("\n- Operacao cancelada! -");
                        printf("\nPressione qualquer tecla para continuar...\n");
                        getch();
                        repetidor = 2; // Cancelando a repetiçaõ
                    }
                    else
                    {
                        deletar_pessoas(nome);

                        printf("\nPressione qualquer tecla para continuar...\n");
                        getch(); 

                        printf("\nDeseja deletar outro cadastro?\n");
                        printf("\t1 - SIM\n\t2 - NAO\n- ");
                        scanf("%d", &repetidor);
                    }
                } while (repetidor == 1);

            break;

            case 8:
            // Gerando relatório demografico.
                printf("\nGERAR RELATORIO DE VACINACAO\n");
            // Chamando o procedimento.
                gerar_relatorio_demografico();

                printf("\nPressione qualquer tecla para continuar...\n");
                getch();
                 
            break;

            case 9: 
            // Mensagem final e fechamento do programa.
                printf("\nPrograma fechado.\n\n");
            break;

            default:
                printf("\nValor invalido, por favor escolha uma das opcoes abaixo.\n");
            break;

        }
    // Verificação de continuidade do programa.
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

// Procedimento para cadastrar um novo estado.
void cadastrar_estado(char estado[]) {
    if (validar_estado(estado) == 2)
    {
        printf("\nPor favor insira a SIGLA do estado que deseja cadastrar.\n");
        return;
    }

    if (validar_estado(estado) == 1)
    {
        printf("\nEstado ja cadastrado!");
        return;
    }

    // Declarando o ponteiro do arquivo e abrindo os arquivos chamando a função de abrir arquivos.
    FILE *arquivo;
    arquivo = abrir_arquivos(arq_estados, "at");

    //Adicionando uma vírgula para a divisão no arquivo e salvando o estado.
    strcat(estado, ",");
    fputs(strupr(estado), arquivo);

    // Verificando o resultado da adicao do estado no arquivo.
    if(ferror(arquivo))
        printf("\nErro ao salvar os dados. Por favor tente novamente!\n");
    else
    {
        fclose(arquivo);
        printf("\nEstado cadastrado com sucesso!");
    }
}

// Cadastrar uma nova cidade, recebe a cidade e o estado em que ela se encontra como parametro.
void cadastrar_cidade(char cidade[], char estado[]) {
    // Verficando se o estado indicado existe.
    if (validar_estado(estado) == 2)
    {
        printf("\nPor favor insira a SIGLA do estado em que deseja cadastrar a cidade.\n");
        return;
    }
    if (validar_estado(estado) == 0) {
        printf("\nEstado nao cadastrado!\nE necessario cadastrar o estado antes de cadastrar cidades nele.\n");
        return;
    }

    // Verficando se a cidade existe naquele estado.
    if (validar_cidade(cidade, estado) == 1)
    {
        printf("\nCidade ja cadastrada!");
        return;
    }

    // Declarando o ponteiro do arquivo e abrindo os arquivos chamando a função de abrir arquivos.
    FILE *arquivo;
    arquivo = abrir_arquivos(arq_cidades, "at");

    // Adicionando uma virgula como separador entre cidade e estado.
    strcat(cidade, ",");
    fputs(strlwr(cidade), arquivo);
    // Adicionando um espaço como separador entre diferentes cidades.
    strcat(estado, "\n");
    fputs(strupr(estado), arquivo);

    // Retornando o resultado da operação.
    if(ferror(arquivo)) 
    {        
        fclose(arquivo);
        printf("\nErro ao salvar os dados");
    }
    else
    {
        fclose(arquivo);
        printf("\nCidade cadastrada com sucesso!");
    }
}

// Procedimento para registrar uma nova pessoa no sistema.
void cadastrar_pessoa() {
    // Declarando a struct.
    Cadastro pessoa;
    
    // Pedindo informacoes da pessoa a ser registrada.
    printf("\nPreencha as informacoes solicitadas.\n");

    printf("\tNome completo: ");
    scanf(" %[^\n]s", pessoa.nome);
    // Verificando a validade do nome.
    if (validar_nome(pessoa.nome) == 0)
    {
        printf ("\nInsira um nome valido, pode conter apenas letras e espacos. Por favor, tente novamente.\n");
        return;
    }

    printf("\tSexo(M para Masculino ou F para feminino): ");
    scanf(" %[^\n]s", pessoa.sexo);
    // Verificando se o sexo inserido e valido.
    if (validar_sexo(pessoa.sexo) == 0)
    {
        printf ("\nInsira um sexo valido. Por favor, tente novamente.\n");
        return;
    }

    printf("\tData de nascimento (no seguinte formato ""dd/mm/aaaa""): ");
    scanf("%d/%d/%d", &pessoa.data.dia, &pessoa.data.mes, &pessoa.data.ano);
    // Verificando se a data inserida e valida.
    if (validar_data(pessoa.data) == 0)
    {
        printf ("\nInsira uma data valida! Por favor, tente novamente.\n");
        return;
    }

    printf("\tA sigla do estado: ");
    scanf(" %[^\n]s", pessoa.estado);

    // Fazendo a validacao do estado.
    if (validar_estado(pessoa.estado) == 2)
    {
        printf ("\nInsira a SIGLA do estado em que deseja fazer o registro. Por favor, tente novamente!\n");
        return;
    }
    if (validar_estado(pessoa.estado) == 0)
    {
        printf ("\nEstado nao cadastrado!\nE necessario cadastrar o estado antes de registrar pessoas nele. Por favor, tente novamente.\n");
        return;
    }

    printf("\tCidade: ");
    scanf(" %[^\n]s", pessoa.cidade);

    // Fazendo a validacao da cidade.
    if (validar_cidade(pessoa.cidade, pessoa.estado) == 0)
    {
        printf ("\nCidade nao cadastrada\nE necessario cadastrar a cidade antes de registrar pessoas nela! Por favor, tente novamente.\n");
        return;
    }

    // Verificando se essa pessoa ja esta cadastrada.
    if(verificar_cadastro(pessoa) == 1)
    {
        printf("\nPessoa ja cadastrada!\n");
        return;
    }

    // Chamando função que registra os dados no arquivo.
    gravar_registro(pessoa);
};

/* função que verifica se o usuário cadastrado ja existe. Compara todas as informacoes e caso tiverem identicas reconhece como ja cadastrado. 
Retorna 1 se encontrar e 0 se nao. */
int verificar_cadastro(Cadastro pessoa) {
    Cadastro pessoa_existe;

    // Declarando o ponteiro do arquivo e abrindo os arquivos chamando a função de abrir arquivos.
    FILE *arquivo;
    arquivo = abrir_arquivos(arq_cadastros, "a+b");

    // Fazendo um loop para varrer todo o arquivo.
    while(!feof(arquivo)) {
        // Lendo os registros presentes no arquivo.
        fread(&pessoa_existe, sizeof(Cadastro), 1, arquivo);
        // Comparando cada campo do resgistro.
        if(
            strcmp(strlwr(pessoa_existe.nome), strlwr(pessoa.nome)) == 0 && 
            strcmp(strlwr(pessoa_existe.cidade), strlwr(pessoa.cidade)) == 0 && 
            strcmp(pessoa_existe.estado, pessoa.estado) == 0 && 
            strcmp(strlwr(pessoa_existe.sexo), strlwr(pessoa.sexo))== 0 && 
            pessoa_existe.data.dia == pessoa.data.dia && 
            pessoa_existe.data.mes == pessoa.data.mes && 
            pessoa_existe.data.ano == pessoa.data.ano
        ) 
        {
            fclose(arquivo);
            return 1;
        }

    }
    fclose(arquivo);
    return 0;
}

// função para validar o nome selecionado, recebe o nome digitado como paramentro. Retorna 0 quando invalido e 1 quando valido.
int validar_nome(char nome[]) {
    int i;

    // Verificando se o nome contem algo alem de letras e espacos. E outras letras acentuadas.
    for(i = 0; i<strlen(nome); i++) {
        if(!isalpha(nome[i]) && !isspace(nome[i])) 
            if(nome[i] < 128 && nome[i] > 154) 
                if(nome[i] < 160 && nome[i] > 165)
                    if(nome[i] < 181 && nome[i] > 183)
                        if(nome[i] != 198 && nome[i] != 199)
                            if(nome[i] < 210 && nome[i] > 212)
                                if(nome[i] < 224 && nome[i] > 228)
                                    if(nome[i] < 233 && nome[i] > 237)
                                        return 0;
    }
    return 1;
}

// função para validar o sexo selecionado, recebe o sexo como paramentro. Retorna 0 quando invalido e 1 quando valido.
int validar_sexo(char sexo[]) {
    if(strlen(sexo) != 1) return 0;
    if(strcmp(strlwr(sexo), "m") == 0 || strcmp(strlwr(sexo), "f") == 0) return 1;
    return 0;
}

// função para validar a data escrita, recebe uma struct Data como parâmetro .Retorna 0 quando invalida e 1 quando valida.
int validar_data(Data data) {
    // Verficacoes gerais.
    if(data.mes < 1 || data.mes > 12 || data.dia < 1) return 0;
    // Verificando o mes de fevereiro, incluindo os anos bissextos.
    if(data.mes == 2) 
    {
        if(data.ano%4 == 0)
        {
            if(data.dia > 29) return 0;
        }
        else if(data.dia > 28) return 0;  
    }
    // Verificando os meses com 30 dias.
    else if(data.mes == 4 || data.mes == 6 || data.mes == 9 || data.mes == 11) 
    {
        if(data.dia > 30) return 0;
    }
    // Verificando os meses com 31 dias.
    else if(data.dia > 31) return 0;

    return 1;
}

// função que verifica se a cidade passada existe no arquivo de cidades. Retorna 1 se encontrar e 0 se nao.
int validar_cidade(char cidade[], char estado[]) {
    // Declarando variáveis pra receber os valores lidos no arquivo.
    char cidade_existe[TAM_CIDADE];
    char estado_existe[TAM_ESTADO];

    // Declarando o ponteiro do arquivo e abrindo os arquivos chamando a função de abrir arquivos.
    FILE *arquivo;
    arquivo = abrir_arquivos(arq_cidades, "a+t");

    // Fazendo um loop para varrer todo o arquivo.
    while(!feof(arquivo))
    {
        // Lendo o arquivo e comparando a cidade passada por parametro e as lidas no arquivo.
        fscanf(arquivo, " %[^,],", cidade_existe);
        fscanf(arquivo, " %[^\n]\n", estado_existe);
        
        if(strcmp(strlwr(cidade_existe), strlwr(cidade)) == 0 && strcmp(estado_existe, strupr(estado)) == 0)
        {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

/* função que verifica se o estado passado e uma sigla e se existe no arquivo de estados. Retorna 1 se encontrar e 0 se nao 
e 2 caso nao tenha passado uma sigla. */
int validar_estado(char estado[]) {
    // Verificando se o texto passado e uma sigla.
    if (strlen(estado) != 2) return 2;

    // Declarando a variavel que recebera os estados lidos no arquivo.
    char estado_existe[TAM_ESTADO];

    // Declarando o ponteiro do arquivo e abrindo os arquivos chamando a função de abrir arquivos.
    FILE *arquivo;
    arquivo = abrir_arquivos(arq_estados, "a+t");

    // Fazendo um loop para varrer todo o arquivo.
    while(!feof(arquivo))
    {
        // Lendo cada estado e comparando com o que foi passado como parametro.
        fscanf(arquivo, " %[^,],", estado_existe);
        
        if(strcmp(estado_existe, strupr(estado)) == 0)
        {
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0;
}

// Procedimento que salva as informacoes inseridas no registro no arquivo, recebe o registro do tipoe Cadastro como paramentro.
void gravar_registro(Cadastro pessoa) {
    // Declarando o ponteiro do arquivo e abrindo os arquivos chamando a função de abrir arquivos.
    FILE *arquivo;
    arquivo = abrir_arquivos(arq_cadastros, "a+b");

    // Condicao que se o arquivo existir ira salvar o valor do registro nele.
    if(arquivo) 
    {
        fseek(arquivo, 0, SEEK_END);
        fwrite(&pessoa, sizeof(pessoa), 1, arquivo);
        fclose(arquivo);
        printf("\nCadastro realizado!");
    }
    else 
    {
        fclose(arquivo);
        printf("\nErro ao armazenar os dados. Por favor, tente novamente.");
    } 
}

// Procedimento para listar pessoas por estado., recebe o estado como parametro.
void listar_pessoas_estado(char estado[]) {
    Cadastro pessoa;
    int i = 0;
    char estado_existe[TAM_ESTADO];

    // Validando o estado passado.
    if (validar_estado(estado) == 0)
    {
        printf("\nEstado nao cadastrado!");
        return;
    }

    printf("\n------ %s ------\n", strupr(estado));

    // Declarando o ponteiro do arquivo e abrindo os arquivos chamando a função de abrir arquivos.
    FILE *arquivo = abrir_arquivos(arq_cadastros, "rb");

    while(fread(&pessoa, sizeof(Cadastro), 1, arquivo))
    {
        if (strcmp(strlwr(estado), strlwr(pessoa.estado)) == 0)
        {
            printf("%d - %s\n", i + 1, deixar_maiusculo(pessoa.nome));
            i++;
        }
    }
    // Caso nao tenham pessoas cadastradas naquele estado.
    if (i == 0)
    {
        printf("\nNenhum cadastro encontrado!\n");
    }
    fclose(arquivo);
}

// Procedimento para listar pessoas por estado.
void listar_pessoas_cidade(char cidade[]) {
    // Declarando variaveis importantes no procedimento.
    Cadastro pessoa;
    int i = 0;
    char cidade_existe[TAM_CIDADE];
    char estado_existe[TAM_ESTADO];
    char cidade_encontrada[TAM_CIDADE];
    char estado_cidade_encontrada[TAM_ESTADO];

    // Declarando o ponteiro do arquivo e abrindo os arquivos chamando a função de abrir arquivos.
    FILE *arquivo;
    arquivo = abrir_arquivos(arq_cidades, "rt");

    // Retornando o arquivo não exista.
    if(!arquivo)
    {
        printf("\nCidade nao encontrada!\n");
        return;
    }

    // Verificando se a cidade existe nos arquivos.
    while(!feof(arquivo))
    {
        fscanf(arquivo, " %[^,],", cidade_existe);
        fscanf(arquivo, " %[^\n]\n", estado_existe);

        // Comparando se o nome da cidade esta incluido no nome de alguma cidade existente no arquivo e adicionando ao contador.
        if(comparar_strings(strlwr(cidade), cidade_existe) >= 0)
        {
            i++;
            strcpy(cidade_encontrada, cidade_existe); // Variavel que vai ser utilizada para mostrar o nome caso haja apenas uma.
            strcpy(estado_cidade_encontrada, estado_existe);
        }
    }

    fseek(arquivo, 0, SEEK_SET);
    
    // Nenhuma cidade compativel.
    if(i == 0)
    {
        printf("\nCidade nao encontrada!\n");
        return;
    }

    // Abrindos o arquivo com os cadastros para listar os registros.
    FILE* arquivo_cadastros = abrir_arquivos(arq_cadastros, "rb");
    
    // So foi encontrada uma unica cidade compativel.
    if(i == 1)
    {
        i = 0; // Resetando a variavel.

        printf("\n---- %s, %s ----\n", deixar_maiusculo(cidade_encontrada), estado_cidade_encontrada);

        // Mostrando as pessoas da cidade compativel.
        while(fread(&pessoa, sizeof(Cadastro), 1, arquivo_cadastros))
        {
            if (comparar_strings(strlwr(cidade) ,strlwr(pessoa.cidade)) >= 0)
            {
                i++;
                printf("%d - %s\n", i, deixar_maiusculo(pessoa.nome));
            }
        }

        // Caso nao tenham pessoas cadastradas naquela cidade.
        if (i == 0)
        {
            printf("\nNenhum cadastro encontrado!\n");
        }

        fclose(arquivo_cadastros);
        return;
    }

    printf("\nEncontramos %d resultados:\n", i);

    // Mais de uma cidade com o mesmo nome.
    if(i >= 1) 
    {
        char estados[i+1][TAM_ESTADO];
        char cidades[i+1][TAM_CIDADE];
        i = 0; // Resetando a variavel.

        // Selecionando todas as cidades com o mesmo nome e arquivando elas e os estados em que se encontram em matrizes.
        while(!feof(arquivo))
        {
            fscanf(arquivo, " %[^,],", cidade_existe);
            fscanf(arquivo, " %[^\n]\n", estado_existe);
            
            if(comparar_strings(strlwr(cidade), strlwr(cidade_existe)) >= 0)
            {
                strcpy(estados[i], estado_existe);
                strcpy(cidades[i], cidade_existe);
                printf("  %d - %s, %s\n", i+1, deixar_maiusculo(cidades[i]), estados[i]);
                i++;
            }
        }

        // Verificando qual cidade o usuário deseja listar.
        printf("\nSelecione o numero da cidade que deseja consultar (digite 0 para sair): ");
        int cidade_escolhida;
        scanf("%d", &cidade_escolhida);

        if(cidade_escolhida == 0)
        {
            fclose(arquivo);
            fclose(arquivo_cadastros);
            printf("\n- Operacao cancelada! -");
            return;
        }

        i = 0; // Resetando a variavel para uso futuro.

        printf("\n---- %s, %s ----\n", deixar_maiusculo(cidades[cidade_escolhida - 1]), estados[cidade_escolhida - 1]);

        // Comparando a cidade e o estado para listar os cadastros.
        while(fread(&pessoa, sizeof(Cadastro), 1, arquivo_cadastros))
        {
            if (strcmp(strlwr(pessoa.cidade), strlwr(cidades[cidade_escolhida - 1])) == 0 && 
            strcmp(strlwr(pessoa.estado), strlwr(estados[cidade_escolhida - 1])) == 0)  
            {
                i++;
                printf("%d - %s\n", i, deixar_maiusculo(pessoa.nome));
            }
        }
        fclose(arquivo_cadastros);

        // Caso nao tenham pessoas cadastradas naquela cidade.
        if (i == 0)
        {
            printf("\nNenhum cadastro encontrado!\n");
        }
    }

    fclose(arquivo);
}

// Procedimento para a listagem por nome.
void consultar_pessoas_nome(char nome[]) {
    Cadastro pessoa;
    int i = 0;

    FILE *arquivo = abrir_arquivos(arq_cadastros, "rb");

    while(fread(&pessoa, sizeof(Cadastro), 1, arquivo))
    {
        if (comparar_strings(strlwr(nome) ,strlwr(pessoa.nome)) >= 0)
        {
            i++;
        }
    }

    fseek(arquivo, 0, SEEK_SET);
    printf("\n");

    if (i == 0)
    {
        printf("Nome nao encontrado!");
        fclose(arquivo);
        return;
    }

    printf("\nEncontramos %d resultado(s):\n", i);

    if(i >= 1)
    {
        char pessoas[i+1][TAM_MAX];
        char cidades[i+1][TAM_CIDADE];
        char estados[i+1][TAM_ESTADO];
        Data aniversarios[i+1];
        int pessoa_escolhida;
        i = 0;

        while(fread(&pessoa, sizeof(Cadastro), 1, arquivo))
        {
            if (comparar_strings(strlwr(nome), strlwr(pessoa.nome)) >= 0)
            {
                printf("%d) %s ", i + 1, deixar_maiusculo(pessoa.nome));
                printf("- %s, %s\n", deixar_maiusculo(pessoa.cidade), strupr(pessoa.estado));
                strcpy(pessoas[i], pessoa.nome);
                strcpy(cidades[i], pessoa.cidade);
                strcpy(estados[i], pessoa.estado);
                aniversarios[i].dia = pessoa.data.dia;
                aniversarios[i].mes = pessoa.data.mes;
                aniversarios[i].ano = pessoa.data.ano;
                i++;
            }
        }

        printf("\nSelecione o registro que deseja consultar (digite 0 para cancelar): ");
        scanf("%d", &pessoa_escolhida);

        if(pessoa_escolhida == 0) 
        {
            fclose(arquivo);
            printf("\n- Operacao cancelada! -");
            return;
        }

        fseek(arquivo, 0, SEEK_SET);

        while(fread(&pessoa, sizeof(Cadastro), 1, arquivo))
        {
            // Encontrando o registro e mostrando as informacoes.
            if (strcmp(strlwr(pessoas[pessoa_escolhida - 1]), strlwr(pessoa.nome)) == 0
                && strcmp(strlwr(cidades[pessoa_escolhida - 1]), strlwr(pessoa.cidade)) == 0
                && strcmp(strlwr(estados[pessoa_escolhida - 1]), strlwr(pessoa.estado)) == 0
                && aniversarios[pessoa_escolhida - 1].dia == pessoa.data.dia
                && aniversarios[pessoa_escolhida - 1].mes == pessoa.data.mes
                && aniversarios[pessoa_escolhida - 1].ano == pessoa.data.ano
            )
            {
                printf("\n-> %s\n", deixar_maiusculo(pessoa.nome));
                printf("\tData de nascimento: %d/%d/%d\n", pessoa.data.dia, pessoa.data.mes, pessoa.data.ano);
                printf("\tSexo: %s\n", strupr(pessoa.sexo));
                printf("\tLocal: %s, %s\n", deixar_maiusculo(pessoa.cidade), strupr(pessoa.estado));
            }
        }
    }

    fclose(arquivo);
}

/* função para deletar um cadastro do sistema. Recebe o nome (completo ou parcialmente) da pessoa que deseja deletar.
Valida o cadastro e deleta. */
void deletar_pessoas(char nome[]) {
    Cadastro pessoa;
    int i = 0;

    FILE *arquivo = abrir_arquivos(arq_cadastros, "rb");

    // Verificando se existe um cadastro compativel no arquivo.
    while(fread(&pessoa, sizeof(Cadastro), 1, arquivo)) {
        if (comparar_strings(strlwr(nome), strlwr(pessoa.nome)) >= 0) 
        {
            i++;
        } 
    }

    if(i == 0)
    {
        printf("\nNenhum cadastro compativel!");
        fclose(arquivo);
        return;
    }

    fseek(arquivo, 0, SEEK_SET);

    char pessoas[i+1][TAM_MAX];
    char cidades[i+1][TAM_CIDADE];
    char estados[i+1][TAM_ESTADO];
    char sexos[i+1];
    Data aniversarios[i+1];

    printf("\nResultados encontrados: \n");
    i = 0;

    while(fread(&pessoa, sizeof(Cadastro), 1, arquivo)) {
        if (comparar_strings(strlwr(nome), strlwr(pessoa.nome)) >= 0) 
        {
            printf("\t%d) %s ", i + 1, deixar_maiusculo(pessoa.nome));
            printf("- %c - %s, %s - %d/%d/%d\n", toupper(pessoa.sexo[0]), deixar_maiusculo(pessoa.cidade), strupr(pessoa.estado), pessoa.data.dia, pessoa.data.mes, pessoa.data.ano);
            strcpy(pessoas[i], pessoa.nome);
            strcpy(cidades[i], pessoa.cidade);
            strcpy(estados[i], strlwr(pessoa.estado));
            sexos[i] = pessoa.sexo[0];
            aniversarios[i].dia = pessoa.data.dia;
            aniversarios[i].mes = pessoa.data.mes;
            aniversarios[i].ano = pessoa.data.ano;
            i++;
        } 
    }

    printf("\nSelecione qual cadastro deseja excluir (digite 0 para cancelar): ");
    int pessoa_escolhida;
    scanf("%d", &pessoa_escolhida);

    if(pessoa_escolhida == 0)
    {
        fclose(arquivo);
        printf("\n- Operacao cancelada! -");
        return;
    }

    // Confirmando a decisao do usurario.
    printf("\nTem certeza que deseja excluir o registro de - %s -?\nIsso apagara todos os dados desse cadastro do sistema. Essa operacao nao podera ser desfeita!\n", strupr(pessoas[pessoa_escolhida - 1]));
    printf("\t1 - SIM\n\t2 - NAO\n- ");
    int escolha_final;
    scanf("%d", &escolha_final);

    fseek(arquivo, 0, SEEK_SET);

    // Excluindo o cadastro.
    if(escolha_final == 1)
    {
        // Abrindo arquivo temporario que ira substituir o atual.
        FILE *arquivo_temporario = abrir_arquivos("temp.bin", "wb");

        // Passando todos os registros para o novo arquivo exceto o que ira ser excluido.
        while(fread(&pessoa, sizeof(Cadastro), 1, arquivo)) {
            // Selecionando o registro que irá ser excluido.
            if (strcmp(strlwr(pessoas[pessoa_escolhida - 1]), strlwr(pessoa.nome)) == 0
                && strcmp(strlwr(cidades[pessoa_escolhida - 1]), strlwr(pessoa.cidade)) == 0
                && strcmp(estados[pessoa_escolhida - 1], strlwr(pessoa.estado)) == 0
                && sexos[pessoa_escolhida - 1] == pessoa.sexo[0]
                && aniversarios[pessoa_escolhida - 1].dia == pessoa.data.dia
                && aniversarios[pessoa_escolhida - 1].mes == pessoa.data.mes
                && aniversarios[pessoa_escolhida - 1].ano == pessoa.data.ano
            ) 
            {
                printf("\nCadastro de -> %s <- deletado com sucesso!\n", deixar_maiusculo(pessoas[pessoa_escolhida - 1]));
            } 
            else
            {
                fwrite(&pessoa, sizeof(Cadastro), 1, arquivo_temporario);
            }
        }

        fclose(arquivo);
        fclose(arquivo_temporario);

        // remove(arq_cadastros);
        // rename("temp.bin", "cadastros.bin");

        if(remove(arq_cadastros) != 0 || rename("temp.bin", "cadastros.bin"))
        {
            remove("temp.bin");
            printf("\nNao foi possivel deletar o cadastro. Por favor tente novamente!\n");
        }
    }
    else
    {
        printf("\n- Operacao cancelada! -");
        fclose(arquivo);
        return;
    }
}

void gerar_relatorio_demografico() {
    FILE *arquivo;
    Cadastro pessoa;
    int idade;
    int total_pessoas = 0;
    float masculino = 0;
    float feminino = 0;

    // Declarando as faixas etaria
    float faixa_etaria_1; // 0 a 15
    float faixa_etaria_2; // 15 a 29
    float faixa_etaria_3; // 30 a 49
    float faixa_etaria_4; // 50 a 60
    float faixa_etaria_5; // acima de 60

    arquivo = abrir_arquivos(arq_cadastros, "rb");

    while(fread(&pessoa, sizeof(Cadastro), 1, arquivo)) {
        total_pessoas++;

        if (strcmp(strlwr(pessoa.sexo),"m")==0) masculino++;
        else feminino++;

        idade = calcular_idade(pessoa.data);
        if (idade < 15) faixa_etaria_1++;
        else if (idade < 30) faixa_etaria_2++;
        else if (idade < 50) faixa_etaria_3++;
        else if (idade < 61) faixa_etaria_4++;
        else faixa_etaria_5++;
    }

    if(!arquivo) total_pessoas = 1;

    // Mostrando as porcentagens.
    printf("\nPercentual de pessoas em cada faixa etaria:\n");
    printf("\n\t0 a 15 anos  -\t%.2f%%", faixa_etaria_1/total_pessoas * 100);
    printf("\n\t16 a 29 anos -\t%.2f%%", faixa_etaria_2/total_pessoas * 100);
    printf("\n\t30 a 49 anos -\t%.2f%%", faixa_etaria_3/total_pessoas * 100);
    printf("\n\t50 a 60 anos -\t%.2f%%", faixa_etaria_4/total_pessoas * 100);
    printf("\n\tacima de 60  -\t%.2f%%\n", faixa_etaria_5/total_pessoas * 100);

    printf("\nPercentual de pessoa por sexo:\n");
    printf("\n\tMasculino:\t%.2f %%", (masculino/total_pessoas) * 100);
    printf("\n\tFeminino:\t%.2f %%\n", (feminino/total_pessoas) * 100);
}

FILE * abrir_arquivos(char arquivo[], char modo[]) {
    FILE *ponteiro_arquivo;

    ponteiro_arquivo = fopen(arquivo, modo);

    if(ponteiro_arquivo != NULL) 
        return ponteiro_arquivo;
    else
    {
        printf("\nErro ao abrir o arquivo. Por favor tente novamente!");
        return 0;
    }
}

// função para calcular a idade de uma pessoa com base na struct Data passada como parãmetro. Retorna a idade calculada.
int calcular_idade(Data nascimento) {
    // Pegando a data atual com base no sistema.
    time_t pegar_data = time(NULL);
    struct tm data_atual = *localtime(&pegar_data);
    int ano_atual = data_atual.tm_year + 1900;
    int mes_atual = data_atual.tm_mon + 1;
    int dia_atual = data_atual.tm_mday;

    int i; // Variavel de controle, vai receber o ano de nascimento e ser incrementada no loop.
    int idade = 0; // Variável que irá armazenar a idade e ser retornada no final da função.

    // Calculando a idade.
    for (i = nascimento.ano + 1; i <= ano_atual; i++) {
        if (ano_atual > i) idade++;
        else if(ano_atual == i)
        {
            if (mes_atual > nascimento.mes) idade++;
            else if (mes_atual == nascimento.mes)
            {
                if (dia_atual >= nascimento.dia) idade++;
                break;
            }
            else break;
        }
    }

    return idade;
}

/* função para comparar duas strings. Recebe a string que se deseja consultar e a string de base. Retorna 0 se caso sejam identicas, 
-1 caso sejam diferentes e 1 caso a de pesquise esteja inserida na de base. */
int comparar_strings(char pesquisa[], char consulta[]) {
    int i;
    int j;
    int z = 0;
    int verificador = 0;

    // Verificando se as duas strings sao identicas.
    if (strcmp(strlwr(pesquisa), strlwr(consulta)) == 0) return 0;

    // Comparando os caracteres.
    // Passando por todos verificando se acham algum caractere igual ao primeiro da string de pesquisa.
    for(i = 0; i < strlen(consulta); i++) {
        z = 0;
        if (consulta[i] != ' ') // Pulando os espacos vazios.
        {
            if (pesquisa[z] == consulta[i])
            {
                // Ao achar algum caractere igual verifica se os outros tambem sao iguais.
                for(j = i + 1; j<strlen(consulta); j++) {
                    z++;
                    if (z < strlen(pesquisa)) {
                        if(pesquisa[z] != consulta[j]) 
                        {
                            verificador = 0;
                            break;
                        }
                        else verificador = 1;
                    }
                    else break;
                }
                if (j == strlen(consulta)) z++;
                if (verificador == 1 && z == strlen(pesquisa)) return 1;
            }
        }
    }
    return -1;
}

// função para deixar a primeira letra de cada palavra maiuscula e o resto minusculo.
char* deixar_maiusculo(char texto[]) {
    int i;
    char texto_modificado[TAM_MAX];
    strcpy(texto_modificado, texto); // Atribuido a string a uma nova variavel.
    
    for (i = 0; i<strlen(texto); i++) {
        if(i == 0) texto_modificado[i] = toupper(texto[i]);
        else if( texto[i-1] == ' ') texto_modificado[i] = toupper(texto[i]);
        else texto_modificado[i] = tolower(texto[i]);
    }

    return texto_modificado;
}