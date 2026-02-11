#include "enemy.hpp"
#include "player.hpp"
#include <cmath>

inimigo::inimigo(sf::Vector2f pos, sf::Vector2f size, sf::Texture& texturaInimigo)
:   spriteInimigo(texturaInimigo)
   ,shape()
   ,offset(0.f, 0.f)
 {
     
     
     vivo = true;
     shape.setSize(size);
     shape.setFillColor(sf::Color::Red);
     shape.setPosition(pos);
      // pixels per second
     
     
     
     
     spriteInimigo.setTexture(texturaInimigo);
     spriteInimigo.setPosition(pos + offset);
     spriteInimigo.setTextureRect({{0,0},{32,32}});
     spriteInimigo.setScale(sf::Vector2f(2.f, 2.f));
     spriteInimigo.setOrigin(spriteInimigo.getLocalBounds().size / 2.f);
     
     shape.setOrigin(shape.getSize() / 2.f);
     spriteInimigo.setOrigin(spriteInimigo.getLocalBounds().size / 2.f);
     
     vidaInimigo = 100;
     cooldown = false;
     velocidade = sf::Vector2f(0.f, 0.f);
     
}
void inimigo::updateSprite(){
    if (!vivo)
    return;
    spriteInimigo.setPosition(shape.getPosition());
}
bool inimigo::estaVivo()const{
    return vivo;

}
sf::RectangleShape& inimigo::getCorpo()
{
    return shape;
}

const sf::RectangleShape& inimigo::getCorpo() const
{
    return shape;
}


void inimigo::drawInimigo(sf::RenderWindow& window){
    //hitbox:www
   // window.draw(shape);
    
    if (!vivo)
    return;

    window.draw(spriteInimigo);
}
sf::Vector2f inimigo::getPosition()const{
    return shape.getPosition();
}


sf::Vector2f inimigo::moverInimigo(float dt, const Personagem& player1, std::vector <inimigo>& inimigos, sf::Texture& texturaInimigo) {

    sf::Vector2f posI = shape.getPosition();
    sf::Vector2f posP = player1.getPosition();

    float dx = posP.x - posI.x;
    float dy = posP.y - posI.y;

    float dist = std::sqrt(dx*dx + dy*dy);

    if (dist > 0.001f && dist < 2000.f) {

        float dirX = dx / dist;
        float dirY = dy / dist;
        float speed = 90.f;

      // velocidade vetorial (direção + sentido)
     velocidade.x = dirX * speed;
     velocidade.y = dirY * speed;
     alterarTextura(texturaInimigo);
      // deslocamento
     return velocidade * dt;
    }

    return sf::Vector2f(0.f, 0.f);
}

void inimigo::perdeuVida(int& vidaInimigo, int& dano, bool& vivo){
  vidaInimigo -= dano;
  if(vidaInimigo <= 0){
    vidaInimigo = 0;
    vivo = false;
  }
}

void inimigo::alterarTextura(sf::Texture& texturaInimigo){
      if (velocidade.x > 0.f)
    {
        // indo para direita
        spriteInimigo.setScale(sf::Vector2f(-2.f, 2.f));
        
    }
    else if (velocidade.x < 0.f)
    {
        // indo para esquerda
        spriteInimigo.setScale(sf::Vector2f(2.f, 2.f));
    }
}
