#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

/*ESTRUCTURA DA EQUIPA*/
struct Equipa {
    int id;
    char nome[50];
};

/*ESTRUCTURA DOS JAGADORES*/
struct Jogador {
    int id, num_gols;
    char nome[50], apelido[50], data_Ini_cont[10], data_fim_cont[10];
    int idEquipa;
    //struct Equipa equipa;
};

void listaJogadores();
void listarEquipas();
void adicionarJogador(struct Jogador);
void adicionarEquipa(struct Equipa);

int main(void) {

    int opcao;
    printf("Bem vindo,"
            " Escolha uma das opcoes:\n"
            "1. Listar os jogadores de uma equipa\n"
            "2. Eliminar o terceiro jogador mais golos\n"
            "3. Cadastrar jogadores\n"
            "4. Cadastrar Equipas\n"
            "5. Listar Equipas\n\nOpcao:");

    scanf("%i", &opcao);

    if (opcao == 1) {/*LISTAR OS JOGADORES*/
        system("clear");
        printf("Lista de jodadores agrupado por equipas\n");
        listaJogadores();
    } else if (opcao == 2) {/*APAGAR O TERCEIRO MELHOR*/
        system("clear");
        apagarTercMarc();
    } else if (opcao == 3) {/*ADICIONAR JOGADOR*/
        system("clear");
        struct Jogador jogad;
        printf("Insira os dados\n"
                "Nome: ");
        scanf("%s", &jogad.nome);
        printf("Apelido: ");
        scanf("%s", &jogad.apelido);
        printf("Data Inicio contracto: ");
        scanf("%s", &jogad.data_Ini_cont);
        printf("Data fim contrato: ");
        scanf("%s", &jogad.data_fim_cont);
        printf("Numero de Golos: ");
        scanf("%d", &jogad.num_gols);
        printf("Seleciona uma das equipas pelo id:\n");
        listarEquipas();
        printf("Numero da Equipa: ");
        scanf("%d", &jogad.idEquipa);
        jogad.id = ultimoJogadId() + 1;

        /*adiciona os dados*/
        adicionarJogador(jogad);

    } else if (opcao == 4) {/*ADICIONAR EQUIPA*/
        system("clear");
        struct Equipa equip;
        printf("Insira os dados\n"
                "Nome: ");
        scanf("%s", &equip.nome);

        equip.id = ultimaEquipId() + 1;

        /*adiciona os dados*/
        adicionarEquipa(equip);

    } else if (opcao == 5) {/*Listar Equipas*/
        system("clear");
        printf("Lista de Equipas:\n");
        listarEquipas();
    }

    //  listaJogadores();

}

/*******************FUNCOES********************/
void listaJogadores() {
    int numj = contarEquipas();
    struct Equipa equip[numj];
    vectorEquipas(equip);
    FILE *f;
    f = fopen("dados.txt", "rb");
    if (f == NULL) {
        criarArquivoJogad(f);
    }
    struct Jogador jogad;
    int t = sizeof (struct Jogador);

    for (int z = 0; z < numj; z++) {
        printf(".......................Equipa: %s........................\n", equip[z].nome);
        rewind(f);
        while (fread(&jogad, t, 1, f) == 1) {

            if (equip[z].id == jogad.idEquipa) {
                printf("Nome: %s, Apelido: %s, Numero de Golos: %d, Data.In.Cont: %s, Data.fim.Cont: %s\n",
                        jogad.nome, jogad.apelido, jogad.num_gols, jogad.data_Ini_cont, jogad.data_fim_cont);
            }
        }
        printf("........................................................\n\n");
    }
    fclose(f);

}

void listarEquipas() {

    FILE *f;
    f = fopen("equipas.txt", "rb");
    if (f == NULL) {
        criarArquivoEquip(f);
    }
    struct Equipa equip;
    int t = sizeof (struct Equipa);
    while (fread(&equip, t, 1, f) == 1) {
        printf("%d. %s;\n", equip.id, equip.nome);

    }
    fclose(f);
}

int ultimoJogadId() {
    FILE *f;
    f = fopen("dados.txt", "rb");
    if (f == NULL) {
        criarArquivoJogad(f);
    }
    struct Jogador jogad;

    fseek(f, -sizeof (struct Jogador), SEEK_END);
    int n = fread(&jogad, sizeof (struct Jogador), 1, f);
    if (n != 1) {
        return 0;
    }

    fclose(f);
    return jogad.id;
}

int ultimaEquipId() {
    FILE *f;
    f = fopen("equipas.txt", "rb");
    if (f == NULL) {
        criarArquivoJogad(f);
    }
    struct Equipa equip;

    fseek(f, -sizeof (struct Equipa), SEEK_END);
    int n = fread(&equip, sizeof (struct Equipa), 1, f);
    if (n != 1) {
        fclose(f);
        return 0;
    }

    fclose(f);
    return equip.id;
}

void adicionarJogador(struct Jogador jogad) {
    FILE *f;
    f = fopen("dados.txt", "ab");
    if (f == NULL) {
        criarArquivoJogad(f);
    }

    int j = fwrite(&jogad, sizeof (struct Jogador), 1, f);
    if (j == 1) {
        printf("Adicionado com sucesso");
    } else {
        printf("Erro ao adicionar");
    }
    fclose(f);
}

void adicionarEquipa(struct Equipa equip) {
    FILE *f;
    f = fopen("equipas.txt", "ab");
    if (f == NULL) {
        criarArquivoEquip(f);
    }

    int j = fwrite(&equip, sizeof (struct Equipa), 1, f);
    if (j == 1) {
        printf("Adicionado com sucesso");
    } else {
        printf("Erro ao adicionar");
        exit(1);
    }
    fclose(f);
}

int contarJogadores() {
    FILE *f;
    f = fopen("dados.txt", "rb");
    if (f == NULL) {
        criarArquivoJogad(f);
    }
    struct Jogador jogada;
    int t = sizeof (struct Jogador);
    int i = 0;
    while (fread(&jogada, t, 1, f) == 1) {
        i++;
    }
    fclose(f);
    return i;
}

int contarEquipas() {
    FILE *f;
    f = fopen("equipas.txt", "rb");
    if (f == NULL) {
        criarArquivoJogad(f);
    }
    struct Equipa equip;
    int t = sizeof (struct Equipa);
    int i = 0;

    while (fread(&equip, t, 1, f) == 1) {
        i++;
    }
    fclose(f);
    return i;
}

int vectorEquipas(struct Equipa* equipas) {
    FILE *f;
    f = fopen("equipas.txt", "rb");
    if (f == NULL) {
        criarArquivoJogad(f);
    }
    struct Equipa equip;
    int t = sizeof (struct Equipa);
    int j = 0;

    while (fread(&equip, t, 1, f) == 1) {
        equipas[j] = equip;
        j++;
    }
    fclose(f);
}

int vectorJogadores(struct Jogador* jogadores) {
    FILE *f;
    f = fopen("dados.txt", "rb");
    if (f == NULL) {
        criarArquivoJogad(f);
    }

    struct Jogador jogad;
    int t = sizeof (struct Jogador);
    int j = 0;

    while (fread(&jogad, t, 1, f) == 1) {
        jogadores[j] = jogad;
        j++;
    }
    fclose(f);
}

int terceiroMaior() {
    int num_jogad = contarJogadores();

    struct Jogador jogadores[num_jogad];
    vectorJogadores(jogadores);


    struct Jogador aux;
    int i = 0, j = 0;

    for (i = 0; i < num_jogad; i++) {
        for (j = i + 1; j < num_jogad; j++) {
            if (jogadores[i].num_gols < jogadores[j].num_gols) {
                aux = jogadores[j];
                jogadores[j] = jogadores[i];
                jogadores[i] = aux;
            }
        }
    }
    return jogadores[2].id;
}

void apagarTercMarc() {
    int idJog = terceiroMaior();
    int num_jogad = contarJogadores();

    struct Jogador jogadores[num_jogad];
    vectorJogadores(jogadores);
    int t;
    for (int j = 0; j < num_jogad; j++) {
        if (jogadores[j].id == idJog) {
            t = j;
            break;
        }
    }

    printf("Deseja mesmo apagar %d. %s Digite[S] para continuar e outra para nao...  ", jogadores[t].id, jogadores[t].nome);
    char perm[2];
    fflush(stdin);
    scanf("%s", &perm);
    if (strcmp(perm, "S") == 0 || strcmp(perm, "s") == 0) {

    } else {
        printf("Canselado");
        return;
    }

    struct Jogador jog;

    FILE *f;
    f = fopen("dados.txt", "w");
    if (f == NULL) {
        criarArquivoJogad(f);
    }

    for (int j = 0; j < num_jogad; j++) {
        if (jogadores[j].id != idJog) {
            jog = jogadores[j];
            fwrite(&jog, sizeof (struct Jogador), 1, f);
        }
    }
    printf("Removido com sucesso!");
    fclose(f);


}

void criarArquivoJogad(FILE * f) {
    f = fopen("dados.txt", "wb");
    if (f == NULL) {
        printf("Erro ao Criar!");
        system("pause");
        exit(1);
    }
}

void criarArquivoEquip(FILE * f) {
    f = fopen("equipas.txt", "wb");
    if (f == NULL) {
        printf("Erro ao Criar!");
        system("pause");
        exit(1);
    }
}