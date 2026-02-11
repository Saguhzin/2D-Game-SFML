#include <SFML/Graphics.hpp>
#include <iostream>
#pragma once


struct bala
{
  public:

    sf::CircleShape corpoB;
    sf::Vector2f direcao;
    sf::CircleShape areaDano;
    
    float Vida;
    float velocidade;

    

    bool esperando;    
    bool podeCriar;
    bool danoAplicado;

    sf::Clock timer;
    sf::Clock vidaTimer;

    void criandoAreaDano(sf::Vector2f posClick){

    //Configuraçao para Canhao:    
    areaDano.setRadius(80.f);
    areaDano.setFillColor(sf::Color::Transparent);
    areaDano.setOutlineColor(sf::Color::Red);
    areaDano.setOutlineThickness(1.f);
    sf::Vector2f hb = areaDano.getGlobalBounds().size;
    areaDano.setOrigin(sf::Vector2f(hb.x / 2.f, hb.y / 2.f));
    areaDano.setPosition(posClick);
    Vida = 5.f;
    direcao = sf::Vector2f(0.f, 0.f);
    corpoB.setPosition(posClick);
    

    esperando = true;
    corpoB.setRadius(0.f);
    podeCriar = false;
    danoAplicado = false;
    timer.restart();

    }
    void timerCriarCorpo(){
      if (!esperando) return; 
        if (timer.getElapsedTime().asSeconds() >= 1.0f){
            podeCriar = true;
            corpoB.setRadius(70.f);
            sf::FloatRect bb = corpoB.getLocalBounds();
            corpoB.setOrigin(sf::Vector2f(bb.size.x / 2.f, bb.size.y / 2.f));
            
        
            esperando = false;
            
        }
       
    }
    void timerVidaBala(){
      
        if (vidaTimer.getElapsedTime().asSeconds() >= 1.5f){
            Vida = 0.f;
        }
       
    }
    
    void mover(float dt, bool canhao){
        if (canhao)
        timerCriarCorpo();
        

        timerVidaBala();

        if (!canhao){
        sf::Vector2f movimento = direcao * velocidade * dt;
        corpoB.move(movimento);
        }
    }

    void desenharCirculoeBala(sf::RenderWindow& window){
        if(podeCriar)
        window.draw(corpoB);
        if(Vida <= 0) return;

        window.draw(areaDano);
        
     
    }
    

    bala(sf::Vector2f pos) : Vida(5.f), velocidade(1000.f), esperando(false), podeCriar(true), timer() {
       
       corpoB.setRadius(5.f);
       sf::FloatRect bb = corpoB.getLocalBounds();
       corpoB.setOrigin(sf::Vector2f(bb.size.x / 2.f, bb.size.y / 2.f));
       corpoB.setPosition(pos);
       corpoB.setFillColor(sf::Color::White);

       Vida = 5.f;
       direcao = sf::Vector2f(0.f, 0.f);

    }


        
    

};

