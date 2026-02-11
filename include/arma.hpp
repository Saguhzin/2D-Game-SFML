
#pragma once
#include <SFML/Graphics.hpp>
#include "bullet.hpp"
#include <cmath>

class Personagem;


enum class TipoArma {
    PISTOLA,
    RIFLE,
    SHOTGUN,
    CANNON
};

class arma {
    public:
    TipoArma tipo;
    sf::Vector2f PosA;
    Personagem& player1;
    sf::Texture texturaArma;
    sf::Sprite weapon1;
    sf::CircleShape hitboxArma;
    bala b;
    
    bool pegou;
    bool ativa;

  
    sf::Vector2f offset;

    int armaDano;
    float fireRate;
    
    arma(Personagem& owner, sf::Texture& texturaArma, TipoArma tipo);
    void atualizar(float dt, std::vector<bala>& balas);
    void DrawArma(sf::RenderWindow& window); 
    void Atirando(std::vector<bala>& balas, sf::Vector2f& dir, sf::Vector2f posicaoClick);
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    void Colararma(Personagem& owner);
    void  configurarTipoArma();

    
};
