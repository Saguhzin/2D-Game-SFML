#pragma once
#include <SFML/Graphics.hpp>

#include "parede.hpp"

#include <iostream>
#include "player.hpp"
class inimigo {
public:
    bool vivo;
   
    inimigo(sf::Vector2f pos, sf::Vector2f size, sf::Texture& texturaInimigo);
    
        

    void drawInimigo(sf::RenderWindow& window);
   
    sf::Vector2f moverInimigo(float dt, const Personagem& player1, std::vector <inimigo>& inimigos, sf::Texture& texturaInimigo);
    void perdeuVida(int& vidaInimigo, int& dano, bool& vivo);
    bool estaVivo()const;
   
    void updateSprite();
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    sf::RectangleShape& getCorpo();
    const sf::RectangleShape& getCorpo() const;
    void alterarTextura(sf::Texture& texturaInimigo);

    
    
    
    sf::RectangleShape shape;
    sf::Sprite spriteInimigo;
    
    sf::Vector2f futuraP;
    int vidaInimigo;
    float speed;

    // direçao e sentido :
    sf::Vector2f velocidade;
    
    bool cooldown;
    float cooldownTimer = 0.f;
    sf::Vector2f offset;
    
   
    Personagem player1;
    
};
