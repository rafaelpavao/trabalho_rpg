#include <iostream>
#include <string>
#include <time.h>
using namespace std;

struct Arma{
    int dano_min;
    int dano_max;
};
struct Inimigo{
    string nome;
    int vida;
    Arma arma;
};
struct Fase{
    string nome;
    Inimigo inimigos[5];
};

struct Jogador{
    int nivel;
    int vida;
    Arma arma;
};

template<typename Tipo>
bool morreu(Tipo personagem){
    if (personagem.vida <=0){
        return true;
    }
    else{
        return false;
    }
}

Jogador jogador(){

    Jogador novo_jogador;
    novo_jogador.nivel = 1;
    novo_jogador.vida = 300;
    novo_jogador.arma.dano_min = 1;
    novo_jogador.arma.dano_max = 20;

    return novo_jogador;
}

void declara_inimigos(Inimigo &inimigo, string nome, int vida, int dano_min, int dano_max){
    inimigo.nome = nome;
    inimigo.arma.dano_max = dano_max;
    inimigo.arma.dano_min = dano_min;
    inimigo.vida = vida;
}

Fase fase(){
    Fase nova_fase;
    nova_fase.nome = "Univero Marvel";
    declara_inimigos(nova_fase.inimigos[0], "Mandarim", 10, 0, 10);
    declara_inimigos(nova_fase.inimigos[1], "Cavera Vermelha", 20, 0, 20);
    declara_inimigos(nova_fase.inimigos[2], "Killmonger", 30, 0, 30);
    declara_inimigos(nova_fase.inimigos[3], "Loki", 40, 0, 40);
    declara_inimigos(nova_fase.inimigos[4], "Thanos", 50, 0, 50);

    return nova_fase;
}


template<typename Atacante, typename Vitima>
Vitima ataque(Atacante atacante, Vitima vitima){
    vitima.vida -= rand() % (atacante.arma.dano_max - atacante.arma.dano_min) + atacante.arma.dano_min;
    return vitima;
}

bool jogarFase(Jogador jogador, Fase fase){
    cout << "\nEntrando em: " << fase.nome << "...\n"<< endl;

    for(int i = 0; i < 5; i++){
        cout<< "-------------------\n" << endl;
        cout<< "Inimigo: " << fase.inimigos[i].nome << endl;
        cout<< "Vida: " << fase.inimigos[i].vida << "\n"<< endl;

        while (!morreu(fase.inimigos[i])){

            jogador = ataque(fase.inimigos[i], jogador);
            fase.inimigos[i] = ataque(jogador, fase.inimigos[i]);
            cout << "O jogador atacou " << fase.inimigos[i].nome << " e ele ficou com " << fase.inimigos[i].vida << " de vida." << endl;
            cout << "O " << fase.inimigos[i].nome <<" atacou ao mesmo tempo e o jogador ficou com  " << jogador.vida << " de vida." << endl;
            if (morreu(fase.inimigos[i])){
                cout << "O " << fase.inimigos[i].nome << " foi morto!\n" << endl;
            }
            if (morreu(jogador)){
                return false;
            }

        }
    }
    return true;
}






int main() {
    Fase nova_fase;
    nova_fase = fase();
    Jogador novo_jogador;
    novo_jogador = jogador();

    srand(time(NULL));
    if (!jogarFase(novo_jogador, nova_fase)){
        cout << "Jogador morreu!" << endl;
    }
    else{
        cout << "Jogador venceu!" << endl;
    }
    return 0;
}
