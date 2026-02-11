#include "parede.hpp"

parede::parede(sf::Vector2f pos, sf::Vector2f size)
:
speed(0.f),
position(pos),
shape(),
tamanho(size)
{
   
    shape.setSize(size);
    shape.setPosition(pos);
    shape.setFillColor(sf::Color::Yellow);

    tamanho = shape.getSize();
    altura = tamanho.y;
    largura = tamanho.x;
    
    position = shape.getPosition();
    x = position.x;
    y = position.y;
}

sf::Vector2f parede::getPosition() const {
    return shape.getPosition();
}

sf::Vector2f parede::getSize() const {
    return shape.getSize();
}

void parede::drawParede(sf::RenderWindow& window) {
window.draw(shape);
   
}