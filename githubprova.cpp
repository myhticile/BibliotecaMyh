#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring>

using namespace std;

struct emprestimos {
    char dt_emp[10], dt_dev[10], usuario[255];
};

struct livros {
    int codigo, paginas;
    char area[30], titulo[255], autores[255], editora[50];
    struct emprestimos emp;
};

int primeiraopc, cod, pos;
char opc;

FILE *arquivo, *arquivoaux;

struct livros livro;

int main(){

    do {
        cout << "-- Biblioteca Myhticile! --" << endl << endl;

        cout << "1 - Cadastrar" << endl;
        cout << "2 - Alterar" << endl;
        cout << "3 - Excluir" << endl;
        cout << "4 - Fazer um emprestimo" << endl;
        cout << "5 - Concluir uma devolução" << endl;
        cout << "6 - Consultar um livro" << endl;
        cout << "7 - Consultar livros disponiveis" << endl;
        cout << "8 - Consulta da listagem geral dos livros" << endl;
        cout << "9 - Desejo sair!" << endl;

        cout << "O que você deseja, querido cliente?: " << endl;
        cin >> primeiraopc;

        switch (primeiraopc) {
            case 1:
                cout << "Deseja cadastrar um livro? (s/n): ";
                cin >> opc;
                while (opc == 's' && 'S') {
                    cout << "Insira o codigo do livro desejado: ";
                    cin >> livro.codigo;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Insira a area: ";
                    cin.get (livro.area, 30);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Insira o titulo: ";
                    cin.get (livro.titulo, 255);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Insira o(s) autor(res): ";
                    cin.get (livro.autores, 255);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Insira a editora: ";
                    cin.get (livro.editora, 50);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Insira o número de paginas: ";
                    cin >> livro.paginas;

                    arquivo = fopen ("dados.dat", "ab");
                    if (arquivo == NULL) {
                        arquivo = fopen ("dados.dat", "wb");
                    }

                    if (fwrite(&livro, sizeof(struct livros), 1, arquivo) == 1){
                        cout << "O seu livro foi cadastrado com sucesso, parabéns!";
                    } else {
                        cout << "Oh não... ocorreu um erro durante o cadastro.";
                    }

                    fclose(arquivo);
                    
                    cin.ignore();
                    cin.get();

                    cout << "Deseja cadastrar um livro? (s/n): ";
                    cin >> opc;
            }
            break;

        case 2:
         arquivo = fopen("dados.dat", "rb+");
                if (arquivo != NULL){

                    cout << "Digite o código do livro que deseja alterar: ";
                    cin >> cod;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    pos = -1;
                    while(!feof(arquivo)){
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                        pos++;
                        if (cod == livro.codigo){
                            cout << "Área: ";
                            cin.get(livro.area, 30);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            cout << "Título: ";
                            cin.get(livro.titulo, 255);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            cout << "Autor(es): ";
                            cin.get(livro.autores, 255);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            cout << "Editora: ";
                            cin.get(livro.editora, 50);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            cout << "Nº páginas: ";
                            cin >> livro.paginas;

                            fseek(arquivo, sizeof(struct livros) * pos, SEEK_SET);

                            if (fwrite(&livro, sizeof(struct livros), 1, arquivo) == 1){
                                cout << "Parabéns, o livro foi alterado!";
                            } else {
                                cout << "Erro ao alterar o livro!";
                            } 

                            cin.ignore();
                            cin.get();
                            break;
                        }
                    }
                    fclose (arquivo);

                } else {
                    cout << "Oh não... não conseguimos concluir essa operação...";
                    cin.ignore();
                    cin.get();
                }
                break;
        case 3:
         cout << "Insira o código do livro que gostaria de deletar: ";
                cin >> cod;
                arquivo = fopen("dados.dat", "rb");
                arquivoaux = fopen("dados.aux", "wb");

                fread (&livro, sizeof(struct livros), 1, arquivo);
                while(!feof(arquivo)){
                    if (cod != livro.codigo){
                        fwrite(&livro, sizeof(struct livros), 1, arquivoaux);
                    }
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                }

                fclose (arquivo);
                fclose (arquivoaux);

                remove ("dados.dat");
                rename ("dados.aux", "dados.dat");
            break;

        case 4:
                arquivo = fopen("dados.dat", "rb+");
                if (arquivo != NULL){
                    cout << "Insira o código do livro que gostaria de pegar emprestado: ";
                    cin >> cod;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    pos = -1;
                    while(!feof(arquivo)){
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                        pos++;
                        if (cod == livro.codigo){
                            fseek(arquivo, sizeof(struct livros) * pos, SEEK_SET);
                            cout << "Data de empréstimo: ";

                            cin.get(livro.emp.dt_emp, 10);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            cout << "Data de devolução: ";
                            cin.get(livro.emp.dt_dev, 10);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            cout << "Usuário: ";
                            cin.get(livro.emp.usuario, 255);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            fwrite(&livro, sizeof(struct livros), 1, arquivo);
                            break;
                        }
                    }
                    fclose (arquivo);

                } else {
                    cout << "Erro ao abrir o banco de dados!";
                    cin.ignore();
                    cin.get();
                }
            
            break;
        case 5:
         arquivo = fopen("dados.dat", "rb+");
                if (arquivo != NULL){
                    cout << "Insira o código do livro que gostaria de realizar a devolução: ";
                    cin >> cod;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    pos = -1;
                    while(!feof(arquivo)){
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                        pos++;
                        if (cod == livro.codigo){
                            fseek(arquivo, sizeof(struct livros) * pos, SEEK_SET);
                            strcpy(livro.emp.dt_emp, "");
                            strcpy(livro.emp.dt_dev, "");
                            strcpy(livro.emp.usuario, "");
                            fwrite(&livro, sizeof(struct livros), 1, arquivo);
                            break;
                        }
                    }
                    fclose(arquivo);

                } else {
                    cout << "Oh não... não conseguimos realizar esta operação.";
                    cin.ignore();
                    cin.get();
                }
            break;
        case 6:
        arquivo = fopen("dados.dat", "rb");
                if (arquivo != NULL){
                    cout << "Insira o código do livro que gostaria pesquisar em nosso sitema: ";
                    cin >> cod;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    while(!feof(arquivo)){
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                        if (cod == livro.codigo){
                            cout << "Codigo: " << livro.codigo << endl;

                            cout << "Area: " << livro.area << endl;

                            cout << "Titulo: " << livro.titulo << endl;

                            cout << "Autor(es): " << livro.autores << endl;

                            cout << "Editora: " << livro.editora << endl;

                            cout << "Numero páginas: " << livro.paginas << endl;

                            cin.get();
                            break;
                        }
                    }
                    fclose(arquivo);

                } else {
                    cout << "Oh não... não conseguimos realizar esta operação.";

                    cin.ignore();
                    cin.get();
                }
            break;
        case 7:
         arquivo = fopen("dados.dat", "rb");
                if (arquivo != NULL){
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                    while(!feof(arquivo)){
                        
                        if (strcmp(livro.emp.dt_emp, "") == 0){
                            cout << "Código: " << livro.codigo << endl;

                            cout << "Área: " << livro.area << endl;

                            cout << "Título: " << livro.titulo << endl;

                            cout << "Autor(es): " << livro.autores << endl;

                            cout << "Editora: " << livro.editora << endl;

                            cout << "Nº páginas: " << livro.paginas << endl;

                        }
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                    }
                    fclose(arquivo);
                    cin.ignore();
                    cin.get();
                } else {
                    cout << "Oh não... não conseguimos realizar esta operação.";

                    cin.ignore();
                    cin.get();
                }
            break;
        case 8:
            arquivo = fopen("dados.dat", "rb");
                if (arquivo != NULL){
                    fread(&livro, sizeof(struct livros), 1, arquivo);

                    while(!feof(arquivo)){
                        cout << "Codigo do livro: " << livro.codigo << endl;

                        cout << "Area do livro: " << livro.area << endl;

                        cout << "Titulo do livro: " << livro.titulo << endl;

                        cout << "Autor(es) do livro: " << livro.autores << endl;

                        cout << "Editora do livro: " << livro.editora << endl;

                        cout << "Numero de paginas: " << livro.paginas << endl;


                        fread(&livro, sizeof(struct livros), 1, arquivo);
                    }

                    fclose(arquivo);

                    cin.ignore();
                    cin.get();

                } else {
                    cout << "Perdão, nosso sistema não conseguiu concluir este processo...";
                    cin.ignore();
                    cin.get();
                }
            break;

        case 9:
        cout << "Agradeço por considerar utilizar o nosso sistema!";
            break;
        default:
        cout << "Perdão, esta opção é invalida... Poderia inserir novamente?";
            break;
        }
        cout << "\e[2J" << "\e[0;0H";
    } while (primeiraopc !=9);
}