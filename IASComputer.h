#ifndef IASCOMPUTER_H_INCLUDED
#define IASCOMPUTER_H_INCLUDED
#include <vector>
#include <string>
#include <cstdint>
#include <stdio.h>
#include <array>
#include <stdlib.h>
using namespace std;


class IASComputer
{
    struct Registradores{   //REGISTRADORES
        string AC = "0000000000010011";
        string MQ = "0000000000010011";
        string MBR = "0000000000000000";
        string PC = "0000000000";
        string IR = "0000000000000000";
        string MAR = "0000000000000000";
    };

    string Opcode; //VARIAVEL PARA ARMAZENAR O OPCODE APOS SEPARACAO DA INSTRUCAO COMPLETA
    string Endereco; //VARIAVEL PARA ARMAZENAR ENDERECO APOS SEPARACAO DA INSTRUCAO COMPLETA

    public:
        IASComputer();
        string Memoria[1023]; //DEFINE O TAMANHO DA NOSSA MEMÓRIA
        void Load_MQ();
        void Load_MQ_X();
        void Stor_X();
        void Load_X();
        void Add_X();
        void Sub_X();
        void Mul_X();
        void Div_X();
        void Funcao_Memoria();  //FUNCAO QUE INICIALIZA A MEMÓRIA
        void IR_Decomposicao(); //FUNCAO PARA DECOMPOR O IR EM OPCODE E ENDERECO
        void Funcao_Unidade_Controle();

        Registradores m_registradores;  //CRIA UM OBJETO DA STRUCT

    private:

};

#endif // IASCOMPUTER_H_INCLUDED
