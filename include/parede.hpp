#include <SFML/Graphics.hpp>

#pragma once

class parede {
public:
    parede(sf::Vector2f pos, sf::Vector2f size);
    void drawParede(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    
    
     
    
    
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    float speed;
    sf::Vector2f tamanho;
    
    float largura;
    float altura;
    float x;
    float y;
   
    
};
