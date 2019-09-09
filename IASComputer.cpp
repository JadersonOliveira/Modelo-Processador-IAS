#include "IASComputer.h"
#include <iostream>
#include <bitset>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;

IASComputer::IASComputer()
{
    Funcao_Memoria(); //INICIALIZAR A MEMORIA
    int pc;

    for(pc = 300; pc < 317; pc++)
    {
        m_registradores.MBR = Memoria[pc]; //MBR RECEBE MEMORIA
        m_registradores.IR = m_registradores.MBR; //IR RECEBE MBR
        IR_Decomposicao(); //CHAMANDO FUNCAO PARA RECOMPOR IR EM OPCODE E ENDERECO
        Funcao_Unidade_Controle(); //CHAMANDO FUNCAO DE CONTROLE
    }

    cout<<Memoria[606]<<endl; //RESULTADO DA OPERACAO APRESENTADA
}

void IASComputer::Load_MQ() //OK
{
    m_registradores.AC = m_registradores.MQ;
}

void IASComputer::Load_MQ_X() //OK
{
    unsigned long decimal_endereco = bitset<10>(Endereco).to_ulong(); //CONVERTI TIPO STRING PARA INT
    m_registradores.MQ = Memoria[decimal_endereco];
}

void IASComputer::Stor_X() //OK
{
    unsigned long decimal_endereco = bitset<10>(Endereco).to_ulong(); //CONVERTI TIPO STRING PARA INT
    Memoria[decimal_endereco] = m_registradores.AC;
}

void IASComputer::Load_X() //OK
{
    unsigned long decimal_endereco1 = bitset<10>(Endereco).to_ulong(); //CONVERTI TIPO STRING PARA INT
    m_registradores.AC = Memoria[decimal_endereco1];
}

void IASComputer::Add_X() //OK
{
    unsigned long decimal_endereco = bitset<10>(Endereco).to_ulong(); //CONVERTI TIPO STRING PARA INT

    //CONVERTENDO AS STRINGs DA MEMORIA E DO REGISTRADOR MQ, PARA DEPOIS FAZER A MULTIPLICACAO EM INT
    unsigned long decimal_Memoria = bitset<16>(Memoria[decimal_endereco]).to_ulong();
    unsigned long decimal_AC = bitset<16>(m_registradores.AC).to_ulong();

    int x = decimal_Memoria + decimal_AC;

    //CONVERSAO DA MULTIPLICACAO PARA BINARIO DE 32 Bits
    string binary_AC = bitset<16>(x).to_string();

    m_registradores.AC = binary_AC;
}

void IASComputer::Sub_X() //OK
{
    unsigned long decimal_endereco = bitset<10>(Endereco).to_ulong(); //CONVERTI TIPO STRING PARA INT

    //CONVERTENDO AS STRINGs DA MEMORIA E DO REGISTRADOR MQ, PARA DEPOIS FAZER A MULTIPLICACAO EM INT
    unsigned long decimal_Memoria = bitset<16>(Memoria[decimal_endereco]).to_ulong();
    unsigned long decimal_AC = bitset<16>(m_registradores.AC).to_ulong();

    int x = decimal_AC - decimal_Memoria;
    x = -1*x;
    //CONVERSAO DA MULTIPLICACAO PARA BINARIO DE 32 Bits
    string binary_AC = bitset<16>(x).to_string();

    m_registradores.AC = binary_AC;
}

void IASComputer::Mul_X()
{
    unsigned long decimal_endereco = bitset<10>(Endereco).to_ulong(); //CONVERTI TIPO STRING PARA INT

    //CONVERTENDO AS STRINGs DA MEMORIA E DO REGISTRADOR MQ, PARA DEPOIS FAZER A MULTIPLICACAO EM INT
    unsigned long decimal_Memoria = bitset<16>(Memoria[decimal_endereco]).to_ulong();
    unsigned long decimal_MQ = bitset<16>(m_registradores.MQ).to_ulong();

    //MULTIPLICACAO
    int x = decimal_Memoria * decimal_MQ;

    //CONVERSAO DA MULTIPLICACAO PARA BINARIO DE 32 Bits
    string binary = bitset<32>(x).to_string();

    char p1_ac[16]; //MENOS SIGNIFICATIVOS
    char p2_mq[16]; //MAIS SIGNIFICATIVOS

    for(int i = 0; i < 16; i++ )
    {
        p1_ac[i] = binary[i];
    }
    unsigned long decimal_AC = bitset<16>(p1_ac).to_ulong(); //CONVERTI TIPO CHAR PARA INT
    string binary_AC = bitset<16>(decimal_AC).to_string();  //CONVERTI INT PARA STRING

    for(int i = 16; i < 32; i++ )
    {
        p2_mq[i-16] = binary[i];
    }
    unsigned long decimal_MQ2 = bitset<16>(p2_mq).to_ulong(); //CONVERTI TIPO CHAR PARA INT
    string binary_MQ = bitset<16>(decimal_MQ2).to_string(); //CONVERTI INT PARA STRING

    m_registradores.MQ = binary_MQ; //TRANSFERINDO CONTEUDO MAIS SIGNIFICATIVOS PARA MQ
    m_registradores.AC = binary_AC; //TRANSFERINDO CONTEUDO MENOS SIGNIFICATIVOS PARA AC
}

void IASComputer::Div_X()
{
    unsigned long decimal_endereco = bitset<10>(Endereco).to_ulong(); //CONVERTI TIPO STRING PARA INT

    //CONVERTENDO AS STRINGs DA MEMORIA E DO REGISTRADOR AC, PARA DEPOIS FAZER A DIVISAO EM INT
    unsigned long decimal_Memoria = bitset<16>(Memoria[decimal_endereco]).to_ulong();
    unsigned long decimal_AC = bitset<16>(m_registradores.AC).to_ulong();

    //DIVISAO
    int x = decimal_AC / decimal_Memoria; //QUOCIENTE
    int y = decimal_AC % decimal_Memoria; //RESTO

    string binary_Quociente = bitset<16>(x).to_string(); //CONVERTENDO QUOCIENTE PARA TIPO STRING
    string binary_Resto = bitset<16>(y).to_string(); //CONVERTENDO RESTO PARA TIPO STRING

    m_registradores.MQ = binary_Quociente; //ADICIONANDO O QUOCIENTE NO REGISTRADOR MQ
    m_registradores.AC = binary_Resto; //ADICIONANDO O RESTO NO REGISTRADOR AC

}

void IASComputer::IR_Decomposicao(){

    string atual; //VARIAVEL PARA RECEBER A INSTRUCAO ATUAL
    atual = m_registradores.IR;

    char opcode[6];
    char endereco[10];

    for(int i = 0; i < 6; i++) //ARMAZENANDO O OPCODE DA INSTRUCAO(6 PRIMEIROS Bits) EM NOSSA VARIAVEL Opcode
    {
        opcode[i] = atual[i];
    }
    unsigned long opcode_string = bitset<6>(opcode).to_ulong(); //CONVERTI TIPO CHAR PARA INT
    string binary_opcode = bitset<6>(opcode_string).to_string();

    int j = 0;
    for(int i = 6; i < 16; i++ ) //ARMAZENANDO O ENDERECO DA INSTRUCAO(10 UMTIMOS Bits) EM NOSSA VARIAVEL ENDERECO
    {
        endereco[j] = atual[i];
        j++;

    }
    unsigned long endereco_string = bitset<10>(endereco).to_ulong(); //CONVERTI TIPO CHAR PARA INT
    string binary_endereco = bitset<10>(endereco_string).to_string();

    Opcode = binary_opcode;
    Endereco = binary_endereco;

}

void IASComputer::Funcao_Unidade_Controle()
{
    if((Opcode.compare("001010")) == 0){
        Load_MQ();
    }

    if((Opcode.compare("001001")) == 0){
        Load_MQ_X();
    }

    if((Opcode.compare("100001")) == 0){
        Stor_X();
    }

    if((Opcode.compare("000001")) == 0){
        Load_X();
    }

    if((Opcode.compare("000101")) == 0){
        Add_X();
    }

    if((Opcode.compare("000110")) == 0){
        Sub_X();
    }

    if((Opcode.compare("001011")) == 0){
        Mul_X();
    }

    if((Opcode.compare("001100")) == 0){
        Div_X();
    }
}

void IASComputer::Funcao_Memoria() // FUNCAO APENAS PARA INTRODUZIR AS INSTRUCOES E VARIAVEIS
{

    Memoria[300] = "0010011001011010"; //LOAD MQ, 602
    Memoria[301] = "0010111001011001"; //MUL 601
    Memoria[302] = "0010100000000000"; //LOAD MQ
    Memoria[303] = "0001011001011000"; //ADD 600
    Memoria[304] = "1000011001011111"; //STOR 607
    Memoria[305] = "0010011001011100"; //LOAD MQ, 604
    Memoria[306] = "0010111001011101"; //MUL 605
    Memoria[307] = "0010100000000000"; //LOAD MQ
    Memoria[308] = "1000011001100000"; //STOR 608
    Memoria[309] = "0000011001011011"; //LOAD 603
    Memoria[310] = "0001101001100000"; //SUB 608
    Memoria[311] = "1000011001100001"; //STOR 609
    Memoria[312] = "0000011001011111"; //LOAD 607
    Memoria[313] = "0011001001100001"; //DIV 609
    Memoria[314] = "1000011001011111"; //STOR 607
    Memoria[315] = "0010100000000000"; //LOAD MQ
    Memoria[316] = "1000011001011110"; //STOR 606

    Memoria[600] = "0000000000100101"; //37
    Memoria[601] = "0000000001010000"; //80
    Memoria[602] = "0000000000010111"; //23
    Memoria[603] = "0000000000010000"; //16
    Memoria[604] = "0000000000111111"; //63
    Memoria[605] = "0000000000001011"; //11
    Memoria[606] = "0000000000000000";//RESULTADO DA OPERACAO
    Memoria[607] = "0000000000000000";

    //APENAS PARA TESTE
    Memoria[890] = "0000000001010000"; //80
    Memoria[895] = "0000000000000101"; //5

}






