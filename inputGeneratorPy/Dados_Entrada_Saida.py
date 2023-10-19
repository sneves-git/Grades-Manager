# -*- encoding: utf -8 -*-

import pprint
import random

random.seed(10)


def nomesNumerosFicheiro():
    Nomes = {"Sofia Neves": 2019220082,
             "Tatiana Almeida": 2019219581,
             "Samuel Carinhas": 2019217199,
             "Alexy de Almeida": 2019192123,
             "Bernardo Arzileiro": 2019216874,
             "Duarte Meneses": 2019216949,
             "Sofia Botelho": 2019227240,
             "Andre Figo": 2019216156,
             "Paulo Cortesao": 2019216517,
             "Joao Artur": 2019217853,
             "Rui Casaleiro": 2012832830,
             "Adelino Pereira": 2017267194,
             "Filipe Viana": 2019216279,
             "Paulo Rocha": 2018003456,
             "Eva Filipe": 2016772891,
             "Joana Simoes": 2019884456,
             "Jonas Rua": 2016218077,
             "Ana Silva": 2015667788,
             "Pedro Faria": 2018990023,
             "Ze Teixeira": 2014675645}

    # Criar ficheiro c/ nome e número de aluno
    fichNomeNumero = open("nomesNumeros.txt", "w")
    for key, value in Nomes.items():
        linhaNomeNumero = key + "::" + str(value) + "\n"
        fichNomeNumero.write(linhaNomeNumero)
    fichNomeNumero.close()


def EscreverClassificacoesParaFicheiro():
    numAlunos = 20
    numCadeiras = 10
    numProvas = 2
    NumeroAluno = [2019220082, 2019219581, 2019217199, 2019192123, 2019216874,
                   2019216949, 2019227240, 2019216156, 2019216517, 2019217853,
                   2012832830, 2017267194, 2019216279, 2018003456, 2016772891,
                   2019884456, 2016218077, 2015667788, 2018990023, 2014675645]
    Cadeiras = ["AMI", "ED", "IPRP", "TC", "ALGA",
                "PPP", "AC", "ESTA", "TFM", "AMII",
                "IRC", "POO", "SO", "TeoC", "TI",
                "AED", "ATD", "PC", "SCC", "MULT"]
    fichClassificacoesDeProvas = open("classificacoes.txt", "w")

    # Criar ficheiro com número aluno/Disciplina/Prova/Classificação
    listaCadeiras = []
    for num in NumeroAluno:
        for i in range(numCadeiras):
            cadeira = random.choice(Cadeiras)

            if (i == 0):
                listaCadeiras = cadeira
            else:
                while (cadeira in listaCadeiras):
                    cadeira = random.choice(Cadeiras)
                listaCadeiras += cadeira

            for j in range(numProvas):
                prova = "Prova " + str(j + 1)
                classificacao = round(random.uniform(0.0, 20.0), 2)
                linha = str(num) + "::" + cadeira + "::" + prova + "::" + str(classificacao) + "\n"
                fichClassificacoesDeProvas.write(linha)
    fichClassificacoesDeProvas.close()


def EscreverPautasPorDisciplina():
    flag = 0
    dicCadeiraAlunoClassificacao = {}

    fichProvasClassificacoes = open("classificacoes.txt", "r")
    listaProvasClassificacoees = fichProvasClassificacoes.readlines()
    fichProvasClassificacoes.close()

    for i in range(len(listaProvasClassificacoees)):
        linhaProvasClassificacoes = listaProvasClassificacoees[i]
        linhaProvasClassificacoes = linhaProvasClassificacoes.strip().split("::")

        if flag == 0:
            numAluno = int(linhaProvasClassificacoes[0])
            cadeira = linhaProvasClassificacoes[1]

            soma = float(linhaProvasClassificacoes[3])

            # Procurar nome de acordo c/ o numAluno
            fichNomeNumero = open("nomesNumeros.txt", "r")
            listaNomeNumero = fichNomeNumero.readlines()
            for j in range(len(listaNomeNumero)):
                linhaNomeNumero = listaNomeNumero[j]
                linhaNomeNumero = linhaNomeNumero.strip().split("::")
                if (numAluno == int(linhaNomeNumero[1])):
                    aluno = str(linhaNomeNumero[0])
                    break
            flag = flag + 1

        else:
            soma += float(linhaProvasClassificacoes[3])
            media = round(soma / 2)

            if cadeira not in dicCadeiraAlunoClassificacao:
                dicCadeiraAlunoClassificacao[cadeira] = [[aluno, media]]
            else:
                dicCadeiraAlunoClassificacao[cadeira] += [[aluno, media]]

            soma = 0
            flag = 0

    fichNomeNumero.close()

    # Guardar os alunos e a respetiva classificação por ordem alfabética
    fichAlunoClassificacao = open("classificacaoFinal.txt", "w")

    print("\nLista Aluno/Classificação final:\n")
    for key, value in sorted(dicCadeiraAlunoClassificacao.items()):
        print(key, ":")
        value.sort()
        for lista in value:
            print("\t", lista)

            frase = ("%4s %20s %4d\n" % (key, lista[0], lista[1]))
            fichAlunoClassificacao.write(frase)
        fichAlunoClassificacao.write("\n")
    fichAlunoClassificacao.close()
    return dicCadeiraAlunoClassificacao


def DeterminarQuemPassaDeAno(dicCadeiraAlunoClassificacao):
    fichNomeNumero = open("nomesNumeros.txt", "r")
    listaNomeNumero = fichNomeNumero.readlines()
    fichNomeNumero.close()

    # Guardar os alunos e o número de disciplinas a que passaram
    alunosPassaramAno = {}
    for i in range(len(listaNomeNumero)):
        linhaNomeNumero = listaNomeNumero[i]
        linhaNomeNumero = linhaNomeNumero.strip().split("::")

        nome = linhaNomeNumero[0]

        for key, values in dicCadeiraAlunoClassificacao.items():
            for lista in values:
                if lista[0] == nome:
                    media = float(lista[1])
                    if (nome not in alunosPassaramAno) and (media < 9.5):
                        alunosPassaramAno[nome] = 0
                    elif (nome not in alunosPassaramAno) and (media >= 9.5):
                        alunosPassaramAno[nome] = 1
                    elif (nome in alunosPassaramAno) and (media >= 9.5):
                        alunosPassaramAno[nome] += 1

    print("\n\nDisciplinas passadas: ")
    pprint.pprint(alunosPassaramAno)
    # Selecionar quem passou de ano
    apagar = []
    for key, value in alunosPassaramAno.items():
        if value < 8:
            apagar += [key]
    for i in apagar:
        del alunosPassaramAno[i]

    # Guardar e imprimir quem passou de ano
    fichAlunosPassaramAno = open("alunosPassaramAno.txt", "w")

    print("\n\nAlunos que passaram de ano:")
    for key in sorted(alunosPassaramAno):
        print("\t%s" % key)
        fichAlunosPassaramAno.write("%s\n" % key)
    fichAlunosPassaramAno.close()


if __name__ == "__main__":
    nomesNumerosFicheiro()
    EscreverClassificacoesParaFicheiro()
    dicCadeiraAlunoClassificacao = EscreverPautasPorDisciplina()
    DeterminarQuemPassaDeAno(dicCadeiraAlunoClassificacao)
