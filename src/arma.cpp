#include "arma.hpp"
#include "bullet.hpp"
#include "player.hpp"

    arma::arma(Personagem& owner, sf::Texture& texturaArma, TipoArma tipo)
    : tipo(tipo)
    , weapon1(texturaArma)
    , player1(owner)
    , offset({20.f, 15.f})
    , fireRate(0.05f)
    , hitboxArma(25.f)
    , b(weapon1.getPosition())
    
    
    {
        configurarTipoArma();
        //Texture Weapon:
        ativa = true;
        
        // Weapon:
        
        weapon1.setTexture(texturaArma);

        
        weapon1.setTextureRect({{0,0}, {32,32}});
        weapon1.setScale({1.4, 1.4});
        
        sf::FloatRect bounds = weapon1.getLocalBounds();
        weapon1.setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));
        
        //hitbox arma : 

        hitboxArma.setFillColor(sf::Color::Transparent);
        hitboxArma.setOutlineColor(sf::Color::Red);
        hitboxArma.setOutlineThickness(1.f);
      

        sf::FloatRect hbb = hitboxArma.getLocalBounds();
        hitboxArma.setOrigin(sf::Vector2f(hbb.size.x / 2.f, hbb.size.y / 2.f));
        
        // Position :
        
        weapon1.setPosition(sf::Vector2f(300.f, 80.f));
        hitboxArma.setPosition(weapon1.getPosition());

        /// stats weapon :
        pegou = false;
    }


    sf::Vector2f arma::getPosition() const {
        return weapon1.getPosition();
    }

    void arma::atualizar(float dt, std::vector<bala>& balas) {
    if(!ativa) return;
    weapon1.setPosition(player1.getPosition());
    hitboxArma.setPosition(weapon1.getPosition());
    pegou = true;

    //cria a bala do canhao aqui :


}
    


    void arma::DrawArma(sf::RenderWindow& window){
        
        window.draw(weapon1);
        window.draw(hitboxArma);
    } 

    void arma::Atirando( std::vector<bala>& balas, sf::Vector2f& dir, sf::Vector2f posicaoClick)
    {
    
    //if(!ativa) return;    
    //if(!pegou) return;
    
    if (tipo == TipoArma::PISTOLA || tipo == TipoArma::RIFLE){
    
   
    balas.emplace_back(weapon1.getPosition());
    balas.back().direcao = dir;
    
    }
    else if (tipo == TipoArma::SHOTGUN){

    }
    else if (tipo == TipoArma::CANNON){
    bala nB(posicaoClick);

    nB.criandoAreaDano(posicaoClick);
    nB.direcao = sf::Vector2f(0.f, 0.f);
    balas.emplace_back(nB);

     
    }
    
    
    
}

    void arma::configurarTipoArma(){
        switch (tipo) {
            case TipoArma::PISTOLA:
                    armaDano = 10;
                    fireRate = 0.5f; // meio segundo entre tiros
                    break;
            case TipoArma::RIFLE:
                    armaDano = 60;
                    fireRate = 1.35f; // mais rápido que a pistola
                    break;
                case TipoArma::SHOTGUN:
                    armaDano = 40;
                    fireRate = 1.0f; // mais lento que a pistola
                    break;
                case TipoArma::CANNON:
                    armaDano = 100;
                    fireRate = 2.0f; // mais lento que a pistola
                    break;
            }
    }