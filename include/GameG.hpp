#pragma once
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "enemy.hpp"
#include "parede.hpp"
#include "arma.hpp"
#include "bullet.hpp"
#include <iostream>
#include <cmath>
#include <random>
#include <SFML/Audio.hpp>
#include "itens.hpp"

class arma;

class Game {
public:
    
    Game();
    void run();

private:
    
    //Window :
    sf::RenderWindow window;
    
    //cam
    sf::View camera;


    //DT:
    
    sf::Clock clock;
    
    std::mt19937 gen;
    float numerox;
    
    
    //Objects:
    
    std::vector<parede> paredes;
    Personagem player1;
    std::vector <inimigo> inimigos;
    std::vector <itens> itensVetor;
    std::vector <arma> armasVetor;
    arma weapon;
    itens itemEscolhaArma;

    //teste:

    sf::Sprite escolhaArma1;
    sf::Sprite escolhaArma2;
    sf::Sprite escolhaArma3;
    
    parede shapeP;
    std::vector <bala> balas;
    sf::Vector2f PosB;
    
    //Texture :
    sf::Texture backgroundT;
    std::optional<sf::Sprite> background;
    sf::Texture texturaInimigo;
    sf::Texture texturaItem;
    sf::Texture texturaChefe;
    sf::Texture texturaArma1;
    sf::Texture texturaItemArmas;

    sf::Texture texturaEscolha;
    
    
    sf::Texture textureBullet;
    sf::Sprite spriteBullet;


    // audio :
    sf::SoundBuffer bufferShoot;
    sf::Sound soundShoot;

    // Text hud :

    int score;
    sf::Text textHud;
    sf::Font fontHud;
    sf::Text textAtt;

    // click cheack:
    sf::Vector2f posClick;
    bool clockCheck;
    
    bool pegouArmaBool;
    // mira pro canhao :
    sf::Vector2f miraCanhao;
    float contadorBalaCanhao;
    bool podeCriar;
    
    

    float dt;
    sf::Vector2f dir;
    float tempoAcumulado = 0.f;

    // hud : 

    // vida player : 

        sf::RectangleShape barraVida;
        sf::RectangleShape barraFundo;
    

    
    
    
    
    void processarEventos();
    bool pegou(Personagem& player1, arma& weapon, float dt);
    void atualizar();
    void desenhar();
    void gerenciarParedes(std::vector<parede>& paredes);
    void gerenciarInimigos(std::vector <inimigo>& inimigos);
    void inicializarArma(std::vector <arma>& armasVetor);
    sf::Vector2f PosicaoMouse(sf::RenderWindow& window, arma& weapon);
    void AtualizarBala(std::vector <bala>& balas, float dt);
    float Colisao(std::vector<parede>& paredes, sf::RectangleShape& pe, sf::Vector2f& futuraP, sf::Vector2f& movimento);
    void acertoDano(std::vector <inimigo>& inimigos, std::vector <bala>& balas);
    void respawInimigo(std::vector <inimigo>& inimigos, float dt);
    void vidaPlayer(sf::RenderWindow& window, Personagem& player1);
    void danoPlayer(std::vector <inimigo>& inimigos, Personagem& player1);
    float numAleatorio(float min, float max);
    void gerenciarItens(std::vector<itens>& itensVetor);
    void pegarItem(Personagem& player1, std::vector<itens>& itensVetor, arma& weapon);
    void escolhaArmaCheck(arma& weapon, sf::Vector2f posClick,  sf::Sprite& escolhaArma1, sf::Sprite& escolhaArma2, sf::Sprite& escolhaArma3, float dt, bool& clicou );
    bool pegouItemArma(Personagem& player1, itens& itemEscolhaArma);
    void desenhaEscolhaArma(sf::RenderWindow& window, sf::Sprite escolhaArma1, sf::Sprite escolhaArma2, sf::Sprite escolhaArma3, itens& itemEscolhaArma, sf::Text textAtt);

    

    // So para testar no EscolhaArmaCheck;
    bool clicou;
    bool paused;
   
    
};
