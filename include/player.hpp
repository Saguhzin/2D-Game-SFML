#pragma once
#include <SFML/Graphics.hpp>
#include "arma.hpp"
#include "parede.hpp"
#include <iostream>


class parede;
class Personagem {
public:
    Personagem();
    void drawJogador(sf::RenderWindow& window);
    void mover(float deltaTime, std::vector<parede>& paredes);

    //Pegar

    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    int getVida() const;
    const sf::RectangleShape& getCorpo() const;

    // methods

    void SpriteNoPlayer(sf::RectangleShape& player1, sf::Sprite& spritePlayer);
    void Animacao(sf::Sprite& spritePlayer, char i);
    void Colisao(std::vector<parede>& paredes, float& futuraPosx, float& futuraPosy, sf::Vector2f& movimento); 
    void playerDano(int& vidaPlayer, int& Dano, bool& playerVivo);
    
    bool playerVivo;
    int vidaPlayer;
    bool ivulneravel;
 
    private:


    sf::Texture texturaPlayer;
    sf::Sprite spritePlayer;
    float velocidade;
    float Corrida;
    parede shape;
    sf::RectangleShape player1;
    
    
};

