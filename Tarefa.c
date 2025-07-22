#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define ARQUIVOPACIENTE "pacientesData.txt"
#define ARQUIVOMEDICO "medicosData.txt"

/*
opcoes
1- Gestao de Pacientes
2- Gestao de Medicos
3- Fila de Atendimento
4- Sair do Sistema
*/
typedef struct
{
    int idMedico;
    char nomeMedico[256];
    char crm[20];
    char especialidade[100];
} Medico;

typedef struct
{
    int idPaciente;
    char nomePaciente[256];
    char cpfPaciente[16];
    int idadePaciente;
    int idMedico;
    int estadoPaciente;
} Paciente;

int menuPrincipal();
int gestaoPacientes();
void textoMenuPrincipal();
int gestaoMedicos();
void filaAtendimento();
void gerarRelatorioFinal();

int main()
{
    int sair_sistema = 1;
    while (sair_sistema)
    {
        switch (menuPrincipal())
        {

        case 1:
            gestaoPacientes();
            break;

        case 2:
            gestaoMedicos();
            break;

        case 3:
            filaAtendimento();
            break;

        case 4:
            gerarRelatorioFinal();
            sair_sistema = 0;
            break;

        default:
            printf("opcao nao encontrada, selecione uma valida!\n");
            break;
        }
    }
    printf("Saindo do sistema...\n");
    Sleep(2000);
    system("pause");
    return 0;
}

void textoMenuPrincipal()
{
    printf("Escolha uma das opcoes:\n1- Gestao de Pacientes\n2- Gestao de Medicos\n3- Fila de Atendimento\n4- Sair do Sistema\n-> ");
}

int menuPrincipal()
{

    int opcao = 0;
    textoMenuPrincipal();
    scanf("%d", &opcao);
    return opcao;
}

int idExiste(int idComparar)
{
    FILE *fptr;
    char linha[256];
    int idLido;
    fptr = fopen(ARQUIVOPACIENTE, "r");

    while (fgets(linha, 256, fptr) != NULL)
    {
        sscanf(linha, "%d", &idLido);
        if (idLido == idComparar)
        {
            fclose(fptr);
            return 1;
        }
    }
    fclose(fptr);
    return 0;
}

int criarId()
{
    int idValido = 0;
    while (idExiste(idValido))
    {
        idValido++;
    }
    return idValido;
}

Paciente consultaDados(int idBusca)
{
    FILE *fptr;
    Paciente consultado;
    consultado.idPaciente = -1;
    char linha[256];

    fptr = fopen(ARQUIVOPACIENTE, "r");

    while (fgets(linha, 256, fptr) != NULL)
    {
        sscanf(linha, "%d %s %s %d %d %d", &consultado.idPaciente, consultado.nomePaciente, consultado.cpfPaciente, &consultado.idadePaciente, &consultado.idMedico, &consultado.estadoPaciente);
        if (consultado.idPaciente == idBusca)
        {
            fclose(fptr);
            return consultado;
        }
    }
    return consultado;
}
// TIPO 1 PACIENTE, TIPO 2 MEDICO
void atualizarRegistro(int idAtualizar, int tipo)
{
    FILE *fptr, *temp;
    char linha[256];
    int encontrado = 0;

    // Abrir os arquivos corretos
    if (tipo == 1)
    {
        // Paciente
        Paciente p;
        fptr = fopen("pacientesData.txt", "r");
        temp = fopen("temp.txt", "w");

        while (fgets(linha, sizeof(linha), fptr))
        {
            sscanf(linha, "%d %s %s %d %d %d", &p.idPaciente, p.nomePaciente, p.cpfPaciente, &p.idadePaciente, &p.idMedico, &p.estadoPaciente);

            if (p.idPaciente == idAtualizar)
            {
                encontrado = 1;
                getchar(); // limpar buffer

                printf("Novo nome:\n-> ");
                fgets(p.nomePaciente, sizeof(p.nomePaciente), stdin);
                p.nomePaciente[strcspn(p.nomePaciente, "\n")] = '\0';
                for (int i = 0; p.nomePaciente[i]; i++)
                    if (p.nomePaciente[i] == ' ')
                        p.nomePaciente[i] = ';';

                printf("Novo CPF:\n-> ");
                fgets(p.cpfPaciente, sizeof(p.cpfPaciente), stdin);
                p.cpfPaciente[strcspn(p.cpfPaciente, "\n")] = '\0';

                printf("Nova idade:\n-> ");
                scanf("%d", &p.idadePaciente);

                printf("Novo ID do medico:\n-> ");
                scanf("%d", &p.idMedico);

                printf("Novo estado (1-Leve, 2-Moderado, 3-Grave):\n-> ");
                scanf("%d", &p.estadoPaciente);
            }

            fprintf(temp, "%d %s %s %d %d %d\n", p.idPaciente, p.nomePaciente, p.cpfPaciente, p.idadePaciente, p.idMedico, p.estadoPaciente);
        }
    }
    else if (tipo == 2)
    {
        // Médico
        Medico m;
        fptr = fopen("medicosData.txt", "r");
        temp = fopen("temp.txt", "w");

        while (fgets(linha, sizeof(linha), fptr))
        {
            sscanf(linha, "%d %s %s %s", &m.idMedico, m.nomeMedico, m.crm, m.especialidade);

            if (m.idMedico == idAtualizar)
            {
                encontrado = 1;
                getchar();

                printf("Novo nome:\n-> ");
                fgets(m.nomeMedico, sizeof(m.nomeMedico), stdin);
                m.nomeMedico[strcspn(m.nomeMedico, "\n")] = '\0';
                for (int i = 0; m.nomeMedico[i]; i++)
                    if (m.nomeMedico[i] == ' ')
                        m.nomeMedico[i] = ';';

                printf("Novo CRM:\n-> ");
                fgets(m.crm, sizeof(m.crm), stdin);
                m.crm[strcspn(m.crm, "\n")] = '\0';

                printf("Nova especialidade:\n-> ");
                fgets(m.especialidade, sizeof(m.especialidade), stdin);
                m.especialidade[strcspn(m.especialidade, "\n")] = '\0';
                for (int i = 0; m.especialidade[i]; i++)
                    if (m.especialidade[i] == ' ')
                        m.especialidade[i] = ';';
            }

            fprintf(temp, "%d %s %s %s\n", m.idMedico, m.nomeMedico, m.crm, m.especialidade);
        }
    }
    else
    {
        printf("Tipo invalido. Use 1 para paciente ou 2 para medico.\n");
        return;
    }

    fclose(fptr);
    fclose(temp);

    if (tipo == 1)
    {
        remove("pacientesData.txt");
        rename("temp.txt", "pacientesData.txt");
    }
    else
    {
        remove("medicosData.txt");
        rename("temp.txt", "medicosData.txt");
    }

    if (encontrado)
        printf("Registro atualizado com sucesso!\n");
    else
        printf("ID nao encontrado. Nenhuma alteracao feita.\n");
}

void excluirPaciente(int idPaciente)
{
    FILE *origem, *temporario;
    char linha[256];
    int idLinha;
    int encontrado = 0;

    origem = fopen(ARQUIVOPACIENTE, "r");
    temporario = fopen("temp.txt", "w");

    if (origem == NULL || temporario == NULL)
    {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), origem) != NULL)
    {
        // extrai o ID da linha
        if (sscanf(linha, "%d", &idLinha) == 1)
        {
            if (idLinha != idPaciente)
            {
                fputs(linha, temporario); // mantém no novo arquivo
            }
            else
            {
                encontrado = 1; // paciente foi encontrado e será excluído
            }
        }
        else
        {
            fputs(linha, temporario);
        }
    }

    fclose(origem);
    fclose(temporario);

    if (encontrado)
    {
        remove(ARQUIVOPACIENTE);             // remove original
        rename("temp.txt", ARQUIVOPACIENTE); // renomeia o temporário
        printf("Paciente com ID %d excluído com sucesso.\n", idPaciente);
    }
    else
    {
        remove("temp.txt"); // não precisa do temporário se não encontrou
        printf("Paciente com ID %d não encontrado.\n", idPaciente);
    }
}

int gestaoPacientes()
{
    int opSelecionada = 0;
    char linha[256];
    char idPaciente[256];
    char idArquivo[256];

    do
    {
        system("cls || clear");
        printf("1- Cadastrar Paciente\n");
        printf("2- Consultar Paciente\n");
        printf("3- Atualizar Paciente\n");
        printf("4- Excluir Paciente\n");
        printf("5- Voltar ao menu principal\n-> ");
        scanf("%d", &opSelecionada);
        getchar(); // limpa buffer

        switch (opSelecionada)
        {

        // CADASTRO PACIENTE
        case 1:
        {
            Paciente pacienteCadastro;

            pacienteCadastro.idPaciente = criarId();

            printf("Digite o nome do paciente:\n->");
            fgets(pacienteCadastro.nomePaciente, 256, stdin);
            pacienteCadastro.nomePaciente[strcspn(pacienteCadastro.nomePaciente, "\n")] = '\0'; // remove o \n do final, pra nn dar erro no output
            for (int i = 0; pacienteCadastro.nomePaciente[i]; i++)
            {
                if (pacienteCadastro.nomePaciente[i] == ' ')
                {
                    pacienteCadastro.nomePaciente[i] = ';';
                }
            }

            printf("Digite o cpf do paciente:\n->");
            fgets(pacienteCadastro.cpfPaciente, 256, stdin);
            pacienteCadastro.cpfPaciente[strcspn(pacienteCadastro.cpfPaciente, "\n")] = '\0';

            printf("Digite a idade do paciente:\n->");
            scanf("%d", &pacienteCadastro.idadePaciente);

            getchar();

            printf("Digite o id do medico responsavel:\n->");
            scanf("%d", &pacienteCadastro.idMedico);

            printf("Digite o numero do estado do paciente:\n1- Leve\n2- Moderado\n3- Grave\n->");
            scanf("%d", &pacienteCadastro.estadoPaciente);

            FILE *pacientesData;
            pacientesData = fopen(ARQUIVOPACIENTE, "a");

            //      ID NOME CPF IDADE IDMEDICO ESTADOPACIENTE
            fprintf(pacientesData, "%d %s %s %d %d %d\n", pacienteCadastro.idPaciente, pacienteCadastro.nomePaciente, pacienteCadastro.cpfPaciente, pacienteCadastro.idadePaciente, pacienteCadastro.idMedico, pacienteCadastro.estadoPaciente);
            fclose(pacientesData);
            printf("Cadastrado com Sucesso!\n");
            break;
        }

        // consultar
        case 2:
        {
            int id;
            printf("Digite o Id a ser consultado:\n-> ");
            scanf("%d", &id);
            Paciente pacienteConsultado = consultaDados(id);
            for (int i = 0; pacienteConsultado.nomePaciente[i]; i++)
            {
                if (pacienteConsultado.nomePaciente[i] == ';')
                {
                    pacienteConsultado.nomePaciente[i] = ' ';
                }
            }
            if (pacienteConsultado.idPaciente == -1)
            {
                printf("Dados nao encontrados, ID inexistente\n");
            }
            else
            {
                printf("ID: %d\n", pacienteConsultado.idPaciente);
                printf("Nome: %s\n", pacienteConsultado.nomePaciente);
                printf("Cpf: %s\n", pacienteConsultado.cpfPaciente);
                printf("Idade: %d\n", pacienteConsultado.idadePaciente);
                printf("ID Medico: %d\n", pacienteConsultado.idMedico);
                switch (pacienteConsultado.estadoPaciente)
                {
                case 1:
                    printf("Estado: Leve\n\n");
                    break;
                case 2:
                    printf("Estado: Moderado\n\n");
                    break;
                case 3:
                    printf("Estado: Grave\n\n");
                    break;
                }
            }
        }
        break;
        // Atualizar a partir do ID
        case 3:
        {
            int id, op;
            op = 1;
            printf("Digite o ID que voce quer atualizar os dados:\n-> ");
            scanf("%d", &id);
            atualizarRegistro(id, op);
            break;
        }
        case 4:
        {
            int id;
            printf("Digite o id do paciente que quer excluir:\n-> ");
            scanf("%d", &id);
            excluirPaciente(id);
            break;
        }
        default:
            break;
        }
        if (opSelecionada != 5)
        {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
    } while (opSelecionada != 5);
}

/* Verifica se o ID já existe no arquivo de médicos */
int idMedicoExiste(int idComp)
{
    FILE *f = fopen(ARQUIVOMEDICO, "r");
    char linha[256];
    int idLido;

    if (!f)
        return 0; /* arquivo ainda não existe */

    while (fgets(linha, sizeof(linha), f))
    {
        if (sscanf(linha, "%d", &idLido) == 1 && idLido == idComp)
        {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

/* Gera o menor ID livre para médicos */
int criarIdMedico()
{
    int id = 0;
    while (idMedicoExiste(id))
        id++;
    return id;
}

/* Consulta os dados de um médico pelo ID */
Medico consultaMedico(int idBusca)
{
    FILE *f = fopen(ARQUIVOMEDICO, "r");
    Medico m;
    m.idMedico = -1;
    char linha[256];

    if (!f)
        return m; /* arquivo não existe */

    while (fgets(linha, sizeof(linha), f))
    {
        sscanf(linha, "%d %s %s %s",
               &m.idMedico, m.nomeMedico, m.crm, m.especialidade);
        if (m.idMedico == idBusca)
        {
            fclose(f);
            return m;
        }
    }
    fclose(f);
    return m; /* não encontrado → idMedico = -1 */
}

/* Exclusão de médico (ID inteiro) */
void excluirMedico(int idMedico)
{
    FILE *orig = fopen(ARQUIVOMEDICO, "r");
    FILE *tmp = fopen("tmpMed.txt", "w");
    char linha[256];
    int idLinha, encontrado = 0;

    if (!orig || !tmp)
    {
        puts("Erro ao abrir arquivos.");
        return;
    }

    while (fgets(linha, sizeof(linha), orig))
    {
        if (sscanf(linha, "%d", &idLinha) == 1 && idLinha == idMedico)
        {
            encontrado = 1; /* descarta a linha */
        }
        else
        {
            fputs(linha, tmp); /* mantém            */
        }
    }
    fclose(orig);
    fclose(tmp);

    if (encontrado)
    {
        remove(ARQUIVOMEDICO);
        rename("tmpMed.txt", ARQUIVOMEDICO);
        printf("Medico ID %d excluido com sucesso.\n", idMedico);
    }
    else
    {
        remove("tmpMed.txt");
        printf("Medico ID %d nao encontrado.\n", idMedico);
    }
}

int gestaoMedicos()
{
    int opcao;

    do
    {
        system("cls || clear");
        printf("1- Cadastrar Medico\n");
        printf("2- Consultar Medico\n");
        printf("3- Atualizar Medico\n");
        printf("4- Excluir Medico\n");
        printf("5- Voltar ao menu principal\n-> ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch (opcao)
        {

        /* ---------- 1. CADASTRAR MÉDICO ---------- */
        case 1:
        {
            Medico m;
            m.idMedico = criarIdMedico();

            printf("Nome do medico:\n-> ");
            fgets(m.nomeMedico, sizeof(m.nomeMedico), stdin);
            m.nomeMedico[strcspn(m.nomeMedico, "\n")] = '\0';
            for (int i = 0; m.nomeMedico[i]; i++)
                if (m.nomeMedico[i] == ' ')
                    m.nomeMedico[i] = ';';

            printf("CRM:\n-> ");
            fgets(m.crm, sizeof(m.crm), stdin);
            m.crm[strcspn(m.crm, "\n")] = '\0';

            printf("Especialidade:\n-> ");
            fgets(m.especialidade, sizeof(m.especialidade), stdin);
            m.especialidade[strcspn(m.especialidade, "\n")] = '\0';
            for (int i = 0; m.especialidade[i]; i++)
                if (m.especialidade[i] == ' ')
                    m.especialidade[i] = ';';

            FILE *f = fopen(ARQUIVOMEDICO, "a");
            fprintf(f, "%d %s %s %s\n", m.idMedico,
                    m.nomeMedico,
                    m.crm,
                    m.especialidade);
            fclose(f);
            puts("Medico cadastrado com sucesso!");
            break;
        }

        /* ---------- 2. CONSULTAR MÉDICO ---------- */
        case 2:
        {
            int id;
            printf("ID do medico a consultar:\n-> ");
            scanf("%d", &id);

            Medico m = consultaMedico(id);
            if (m.idMedico == -1)
            {
                puts("Medico nao encontrado.");
            }
            else
            {
                for (int i = 0; m.nomeMedico[i]; i++)
                    if (m.nomeMedico[i] == ';')
                        m.nomeMedico[i] = ' ';
                for (int i = 0; m.especialidade[i]; i++)
                    if (m.especialidade[i] == ';')
                        m.especialidade[i] = ' ';

                printf("ID: %d\nNome: %s\nCRM: %s\nEspecialidade: %s\n",
                       m.idMedico, m.nomeMedico, m.crm, m.especialidade);
            }
            break;
        }

        /* ---------- 3. ATUALIZAR MÉDICO ---------- */
        case 3:
        {
            int id;
            printf("ID do medico a atualizar:\n-> ");
            scanf("%d", &id);
            atualizarRegistro(id, 2); /* tipo 2 = médico */
            break;
        }

        /* ---------- 4. EXCLUIR MÉDICO ---------- */
        case 4:
        {
            int id;
            printf("ID do medico a excluir:\n-> ");
            scanf("%d", &id);
            excluirMedico(id);
            break;
        }

        default:
            puts("Opcao invalida.");
        }
        if (opcao != 5)
        {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
    } while (opcao != 5);
    return 0;
}

void filaAtendimento()
{
    int escolha;

    // Menu fila de atendimento
    do
    {
        system("cls || clear"); // limpa terminal (Windows/Linux)
        printf("1 - Visualizar fila\n");
        printf("2 - Alterar medico de paciente\n");
        printf("3 - Atualizar estado (atendido ou alta)\n");
        printf("4 - Voltar\n");
        printf("----------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        getchar();

        // ler lista de pacientes e médicos
        if (escolha == 1 || escolha == 2 || escolha == 3)
        {
            FILE *f = fopen("pacientesData.txt", "r");
            FILE *fmed = fopen("medicosData.txt", "r");

            if (!f || !fmed)
            {
                printf("Erro ao abrir arquivos de dados.\n");
                return;
            }

            Paciente pacientes[100];
            Medico medicos[100];
            int totalPac = 0, totalMedicos = 0;
            char linha[256];

            // lê os dados dos pacientes
            while (fgets(linha, sizeof(linha), f))
            {
                sscanf(linha, "%d %s %s %d %d %d",
                       &pacientes[totalPac].idPaciente,
                       pacientes[totalPac].nomePaciente,
                       pacientes[totalPac].cpfPaciente,
                       &pacientes[totalPac].idadePaciente,
                       &pacientes[totalPac].idMedico,
                       &pacientes[totalPac].estadoPaciente);
                totalPac++;
            }

            // lê os dados dos médicos
            while (fgets(linha, sizeof(linha), fmed))
            {
                sscanf(linha, "%d %s %s %s",
                       &medicos[totalMedicos].idMedico,
                       medicos[totalMedicos].nomeMedico,
                       medicos[totalMedicos].crm,
                       medicos[totalMedicos].especialidade);
                totalMedicos++;
            }

            fclose(f);
            fclose(fmed);

            // visualização da fila de atendimento
            if (escolha == 1)
            {
                FILE *fout = fopen("filaAtendimento.txt", "w");
                fprintf(fout, "--- Fila de Atendimento ---\n");

                for (int i = 0; i < totalMedicos; i++)
                {
                    fprintf(fout, "\nMedico: %s (ID: %d)\n", medicos[i].nomeMedico, medicos[i].idMedico);
                    fprintf(fout, "------------------------------------\n");

                    Paciente doMedico[100];
                    int qtd = 0;
                    for (int j = 0; j < totalPac; j++)
                    {
                        if (pacientes[j].idMedico == medicos[i].idMedico)
                        {
                            doMedico[qtd++] = pacientes[j];
                        }
                    }

                    // ordenando pacientes por estado
                    for (int a = 0; a < qtd - 1; a++)
                    {
                        for (int b = a + 1; b < qtd; b++)
                        {
                            if (doMedico[a].estadoPaciente > doMedico[b].estadoPaciente)
                            {
                                Paciente temp = doMedico[a];
                                doMedico[a] = doMedico[b];
                                doMedico[b] = temp;
                            }
                        }
                    }

                    if (qtd == 0)
                    {
                        fprintf(fout, "Nenhum paciente na fila.\n");
                    }
                    else
                    {
                        for (int p = 0; p < qtd; p++)
                        {
                            fprintf(fout, "ID: %d, Nome: %s, Estado: ", doMedico[p].idPaciente, doMedico[p].nomePaciente);
                            switch (doMedico[p].estadoPaciente)
                            {
                            case 1:
                                fprintf(fout, "Leve\n");
                                break;
                            case 2:
                                fprintf(fout, "Moderado\n");
                                break;
                            case 3:
                                fprintf(fout, "INTERNACAO\n");
                                break;
                            default:
                                fprintf(fout, "Desconhecido\n");
                            }
                        }
                    }
                }
                fclose(fout);
                printf("\nFila salva em 'filaAtendimento.txt'.\n");
            }

            // alterar médico de paciente
            else if (escolha == 2)
            {
                int id;
                printf("Digite o ID do paciente: ");
                scanf("%d", &id);
                int achou = 0;

                for (int i = 0; i < totalPac; i++)
                {
                    if (pacientes[i].idPaciente == id)
                    {
                        achou = 1;
                        if (pacientes[i].estadoPaciente == 3)
                        {
                            printf("Paciente em INTERNACAO, não pode trocar de medico.\n");
                        }
                        else
                        {
                            int novo;
                            printf("Digite o novo ID do medico: ");
                            scanf("%d", &novo);
                            pacientes[i].idMedico = novo;
                            printf("Medico atualizado com sucesso.\n");
                        }
                        break;
                    }
                }
                if (!achou)
                    printf("Paciente nao encontrado.\n");

                FILE *fout = fopen("pacientesData.txt", "w");
                for (int i = 0; i < totalPac; i++)
                {
                    fprintf(fout, "%d %s %s %d %d %d\n",
                            pacientes[i].idPaciente, pacientes[i].nomePaciente,
                            pacientes[i].cpfPaciente, pacientes[i].idadePaciente,
                            pacientes[i].idMedico, pacientes[i].estadoPaciente);
                }
                fclose(fout);
            }

            // alterar estado do paciente
            else if (escolha == 3)
            {
                int id;
                printf("Digite o ID do paciente: ");
                scanf("%d", &id);
                getchar(); // limpa buffer

                int achou = 0;

                for (int i = 0; i < totalPac; i++)
                {
                    if (pacientes[i].idPaciente == id)
                    {
                        achou = 1;
                        int novoEstado;
                        printf("Digite novo estado (4 = atendido / 5 = alta): ");
                        scanf("%d", &novoEstado);
                        getchar();

                        if (novoEstado == 4 || novoEstado == 5)
                        {
                            // Abre o arquivo para adicionar o paciente na fila de alta
                            FILE *fAlta = fopen("filaAlta.txt", "a");
                            if (fAlta)
                            {
                                fprintf(fAlta, "%d %s %d %s\n",
                                        pacientes[i].idPaciente,
                                        pacientes[i].nomePaciente,
                                        pacientes[i].estadoPaciente,
                                        (novoEstado == 4 ? "atendido" : "alta"));
                                fclose(fAlta);
                            }
                            else
                            {
                                printf("Erro ao abrir arquivo filaAlta.txt\n");
                            }

                            // Remove paciente da lista atual (desloca array)
                            for (int j = i; j < totalPac - 1; j++)
                            {
                                pacientes[j] = pacientes[j + 1];
                            }
                            totalPac--;
                            printf("Paciente removido da fila e adicionado a fila de alta.\n");
                        }
                        else
                        {
                            // Atualiza estado se for 1, 2 ou 3 normalmente
                            pacientes[i].estadoPaciente = novoEstado;
                            printf("Estado atualizado com sucesso.\n");
                        }
                        break;
                    }
                }
                if (!achou)
                {
                    printf("Paciente nao encontrado.\n");
                }

                // Atualiza o arquivo pacientesData.txt com a lista atualizada
                FILE *fout = fopen("pacientesData.txt", "w");
                if (fout)
                {
                    for (int i = 0; i < totalPac; i++)
                    {
                        fprintf(fout, "%d %s %s %d %d %d\n",
                                pacientes[i].idPaciente,
                                pacientes[i].nomePaciente,
                                pacientes[i].cpfPaciente,
                                pacientes[i].idadePaciente,
                                pacientes[i].idMedico,
                                pacientes[i].estadoPaciente);
                    }
                    fclose(fout);
                }
                else
                {
                    printf("Erro ao salvar arquivo pacientesData.txt\n");
                }
            }
        }

        // Voltar ao menu principal
        if (escolha != 4)
        {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }

    } while (escolha != 4);
}

void gerarRelatorioFinal()
{
    FILE *fPac = fopen("pacientesData.txt", "r");
    FILE *fMed = fopen("medicosData.txt", "r");
    FILE *fAlta = fopen("filaAlta.txt", "r");
    FILE *fOut = fopen("relatorioFinal.txt", "w");

    if (!fPac || !fMed || !fAlta || !fOut)
    {
        printf("Erro ao abrir os arquivos.\n");
        if (fPac)
            fclose(fPac);
        if (fMed)
            fclose(fMed);
        if (fAlta)
            fclose(fAlta);
        if (fOut)
            fclose(fOut);
        return;
    }

    Paciente pacientes[100];
    Medico medicos[100];
    int totalPac = 0, totalMed = 0;
    int leves = 0, moderados = 0, graves = 0, totalInternados = 0;
    int atendidos = 0, alta = 0;

    char linha[256];

    // Lê pacientes
    while (fgets(linha, sizeof(linha), fPac))
    {
        if (sscanf(linha, "%d %s %s %d %d %d",
                   &pacientes[totalPac].idPaciente,
                   pacientes[totalPac].nomePaciente,
                   pacientes[totalPac].cpfPaciente,
                   &pacientes[totalPac].idadePaciente,
                   &pacientes[totalPac].idMedico,
                   &pacientes[totalPac].estadoPaciente) == 6)
        {
            switch (pacientes[totalPac].estadoPaciente)
            {
            case 1:
                leves++;
                break;
            case 2:
                moderados++;
                break;
            case 3:
                graves++;
                totalInternados++;
                break;
            }
            totalPac++;
        }
    }

    // Lê médicos
    while (fgets(linha, sizeof(linha), fMed))
    {
        if (sscanf(linha, "%d %s %s %s",
                   &medicos[totalMed].idMedico,
                   medicos[totalMed].nomeMedico,
                   medicos[totalMed].crm,
                   medicos[totalMed].especialidade) == 4)
        {
            totalMed++;
        }
    }

    // Contagem de pacientes por médico
    int pacientesPorMedico[100] = {0};
    for (int i = 0; i < totalPac; i++)
    {
        for (int j = 0; j < totalMed; j++)
        {
            if (pacientes[i].idMedico == medicos[j].idMedico)
            {
                pacientesPorMedico[j]++;
                break;
            }
        }
    }

    // Lê fila de alta
    while (fgets(linha, sizeof(linha), fAlta))
    {
        int id, estadoAnterior;
        char nome[256], tipoSaida[32];

        if (sscanf(linha, "%d %s %d %s", &id, nome, &estadoAnterior, tipoSaida) == 4)
        {
            atendidos++;
            if (strcmp(tipoSaida, "alta") == 0)
            {
                alta++;
            }
        }
    }

    // Escreve relatório
    fprintf(fOut, "=== RELATORIO FINAL ===\n");
    fprintf(fOut, "Total de pacientes: %d\n", totalPac);
    fprintf(fOut, "Total de medicos: %d\n", totalMed);
    fprintf(fOut, "- Leves: %d\n", leves);
    fprintf(fOut, "- Moderados: %d\n", moderados);
    fprintf(fOut, "- Graves: %d\n", graves);
    fprintf(fOut, "Total de pacientes internados: %d\n", totalInternados);
    fprintf(fOut, "Total de pacientes atendidos: %d\n", atendidos);
    fprintf(fOut, "Total de pacientes que receberam alta: %d\n\n", alta);
    fprintf(fOut, "=== Pacientes por medico ===\n");

    for (int i = 0; i < totalMed; i++)
    {
        for (int j = 0; medicos[i].nomeMedico[j]; j++)
        {
            if (medicos[i].nomeMedico[j] == ';')
                medicos[i].nomeMedico[j] = ' ';
        }
        fprintf(fOut, "Medico %s (ID: %d): %d paciente(s)\n",
                medicos[i].nomeMedico, medicos[i].idMedico, pacientesPorMedico[i]);
    }

    fclose(fPac);
    fclose(fMed);
    fclose(fAlta);
    fclose(fOut);
    printf("Relatorio final gerado com sucesso em 'relatorioFinal.txt'.\n");
}