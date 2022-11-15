//
// Created by Caio- on 15/11/2022.
//

#include "Banco.h"
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "sys/types.h"
#include "signal.h"
#include "sched.h"
#include <iostream>


// Funcao para trasnferir o dinheiro de uma conta a outra
int transferencia(int quant){
    conta clienteA; // Criando a contaA
    conta clienteB; // Criando a contaB

    clienteA.saldo = 100; // Definindo saldo padrao
    clienteB.saldo = 100; // Definindo saldo padrao

    int valor = quant; // Valor recebe quant

    if(clienteA.saldo >=valor ){ // Se o saldo do clienteA for igual ou maior ao valor da transferencia

        std::cout << std::endl << "Transferencia Concluida com Sucesso" << std::endl;
        
        clienteA.saldo -= valor;
        std::cout << "Saldo da conta A = " << clienteA.saldo << std::endl;

        clienteB.saldo +=valor;
        std::cout << "Saldo da conta B = " << clienteB.saldo << std::endl;
    }
    else{ // Se o saldo do clienteA for infeiror ao valor
        std::cout << std::endl << " ERRO DE TRANSFENCIA: ";
        std::cout << std::endl << " Falta de Saldo " << std::endl;
    }

    return 0;
}

int main() {

    conta clienteA, clienteB;

    pid_t thread;
    int i;
    int valorTransacao;

    valorTransacao += 100;

    size_t s = 0;
    int* pilha = (int*) malloc(s);

    if (pilha == 0 ){
        std::cout << "Malloc nao conseguiu criar a pilha" << std::endl;
        exit(1);
    }

    transferencia(valorTransacao);

    return 0;

}