#include "player.hpp"

Personagem::Personagem()
: velocidade(120.f), Corrida(200.f), shape(sf::Vector2f(0.f, 0.f),sf::Vector2f(0.f, 0.f)),spritePlayer(texturaPlayer) 
{   
   if (!texturaPlayer.loadFromFile("assets/Personagem.png")) {
    std::cerr << "Erro: não foi possível carregar a textura do personagem!\n";
   }
    spritePlayer.setTexture(texturaPlayer);
    // spritePlayer.setTextureRect({{0, 2}, {72, 72}});
    int L = 0 * 30;
    int C = 0 * 30;
    spritePlayer.setTextureRect({{L, C}, {30, 30}});
    spritePlayer.setScale({2.2f, 2.f});
    sf::FloatRect spbounds = spritePlayer.getLocalBounds();
    spritePlayer.setOrigin(sf::Vector2f(spbounds.size.x / 2.f, spbounds.size.y / 2.f));

    player1.setSize({40.f, 50.f});
    player1.setFillColor(sf::Color::Blue);
    sf::FloatRect pbounds = player1.getLocalBounds();
    player1.setOrigin(sf::Vector2f(pbounds.size.x / 2.f, pbounds.size.y / 2.f));
   
    player1.setPosition({100.f, 100.f});

    float Px = player1.getPosition().x + 10.f;
    float Py = player1.getPosition().y - 5.f;
    
    spritePlayer.setPosition({Px, Py});

    vidaPlayer = 100;
    playerVivo = true;
    ivulneravel = false;
}


void Personagem::Animacao(sf::Sprite& spritePlayer, char i){
   if (i == 'W' )
   { 
    int L = 2 * 30;
    int C = 2 * 30;
    spritePlayer.setTextureRect({{L, C}, {30, 30}});
    return;
   }

   if (i == 'S'){
    int L = 3 * 30;
    int C = 2 * 30;
    spritePlayer.setTextureRect({{L, C}, {30, 30}});
   }
   
   if (i == 'D'){
    int L = 0 * 30;
    int C = 0 * 30;
    spritePlayer.setTextureRect({{L, C}, {30, 30}});
   }
  
   if (i == 'A'){
    int L = 2 * 30;
    int C = 1 * 30;
    spritePlayer.setTextureRect({{L, C}, {30, 30}});
   }
   
}
void Personagem::SpriteNoPlayer(sf::RectangleShape& player1, sf::Sprite& spritePlayer){
     
    // Vinculando posicao Sprite (player1)
        float Px = player1.getPosition().x - 12.f;
        float Py = player1.getPosition().y - 7.f;
        spritePlayer.setPosition(sf::Vector2f(Px, Py));

}


sf::Vector2f Personagem::getPosition() const {
    return player1.getPosition();
}
sf::Vector2f Personagem::getSize() const {
    return player1.getSize();
}
int Personagem::getVida() const {
    return vidaPlayer;
}
const sf::RectangleShape& Personagem::getCorpo() const{
    return player1;
}

void Personagem::playerDano(int& vidaPlayer, int& Dano, bool& playerVivo){
    
     vidaPlayer -= Dano;
    if (vidaPlayer <= 0){
    vidaPlayer = 0;
    playerVivo = false;
    }
}


void Personagem::drawJogador(sf::RenderWindow& window) {
    
    //Ver HitBox:
   // window.draw(player1);
    
    window.draw(spritePlayer);

}


void Personagem::mover(float deltaTime, std::vector<parede>& paredes) { 
     sf::Vector2f movimento(0.f, 0.f); 

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
         velocidade = Corrida;
     }
     else {
         velocidade = 120.f;
     }
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
     movimento.y -= velocidade;
      Animacao(spritePlayer, 'W');
     }
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
     movimento.y += velocidade;
     Animacao(spritePlayer, 'S');
    }
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
     movimento.x -= velocidade;
     Animacao(spritePlayer, 'A');
    }
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
     movimento.x += velocidade; 
     Animacao(spritePlayer, 'D');
     }

     float futuraPosx = player1.getPosition().x + movimento.x * deltaTime;
     float futuraPosy = player1.getPosition().y + movimento.y * deltaTime;
        
        Colisao(paredes, futuraPosx, futuraPosy, movimento);
        player1.move(movimento * deltaTime); 
        SpriteNoPlayer(player1, spritePlayer);
       
       
        
}


void Personagem::Colisao(std::vector<parede>& paredes, float& futuraPosx, float& futuraPosy, sf::Vector2f& movimento)
{
    for (auto& p : paredes)  // ← Agora percorre TODAS as paredes
    {
        // Posição e tamanho da parede atual
        float posicaoParedex = p.getPosition().x;
        float posicaoParedey = p.getPosition().y;

        float paredeWidth  = p.getSize().x;
        float paredeHeight = p.getSize().y;

        // Posições do player baseado na futura posição
        float posicaoPlayerx = futuraPosx;
        float posicaoPlayery = futuraPosy;

        float playerWidth  = player1.getSize().x;
        float playerHeight = player1.getSize().y;

        // Centros (pra descobrir direção da colisão)
        float centerPlayerX = posicaoPlayerx + playerWidth / 2.0f;
        float centerPlayerY = posicaoPlayery + playerHeight / 2.0f;

        float centerParedeX = posicaoParedex + paredeWidth / 2.0f;
        float centerParedeY = posicaoParedey + paredeHeight / 2.0f;

        float dx = centerPlayerX - centerParedeX;
        float dy = centerPlayerY - centerParedeY;

        // AABB: verificando colisão
        if (posicaoPlayerx < posicaoParedex + paredeWidth &&
            posicaoPlayerx + playerWidth > posicaoParedex &&
            posicaoPlayery < posicaoParedey + paredeHeight &&
            posicaoPlayery + playerHeight > posicaoParedey)
        {
            // Overlaps
            float overlapX =
                std::min(posicaoPlayerx + playerWidth, posicaoParedex + paredeWidth) -
                std::max(posicaoPlayerx, posicaoParedex);

            float overlapY =
                std::min(posicaoPlayery + playerHeight, posicaoParedey + paredeHeight) -
                std::max(posicaoPlayery, posicaoParedey);

            if (overlapX < overlapY)
            {
                // Colisão horizontal
                if (dx > 0)
                {
                    if (movimento.x < 0) movimento.x = 0; 
                }
                else
                {
                    if (movimento.x > 0) movimento.x = 0;
                }
            }
            else
            {
                // Colisão vertical
                if (dy > 0)
                {
                    if (movimento.y < 0) movimento.y = 0;
                }
                else
                {
                    if (movimento.y > 0) movimento.y = 0;
                }
            }
        }
    }
}

