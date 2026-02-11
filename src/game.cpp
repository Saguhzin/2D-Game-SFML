#include "GameG.hpp"
#include "arma.hpp"
#include "bullet.hpp"
#include "player.hpp"


    Game::Game()

    : window(sf::VideoMode({1000, 620}), "Fuzyx"),
     player1(),                           // correto
     inimigos(),                   // correto
     shapeP(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)),
     paredes(),
     balas(),
     weapon(player1, texturaArma1, TipoArma::CANNON),
     gen(std::random_device{}()),
     spriteBullet(textureBullet),
     soundShoot(bufferShoot),
     itensVetor(),
     textHud(fontHud),
     textAtt(fontHud),
     itemEscolhaArma(texturaItemArmas, sf::Vector2f(200.f, 300.f)),
     escolhaArma1(texturaEscolha),
     escolhaArma2(texturaEscolha),
     escolhaArma3(texturaEscolha)
     
    {   
        camera = window.getView();
        camera.zoom(1.f);
        sf::Vector2f dirM;
        pegouArmaBool = false;
        clicou = false;
        

        
        paused = false;
        // inicializando texturas:

        
        if(!texturaArma1.loadFromFile("assets/arma.png")){
        std::cerr << "Erro: não foi possível carregar a textura do Arma!\n";
        }
        if(!texturaItemArmas.loadFromFile("assets/ItemArma.png")){
        std::cerr << "Erro: não foi possível carregar a textura do itemarmasArma!\n";
        }
        

        if (!bufferShoot.loadFromFile("assets/TiroAudio2.wav"))
         {std::cerr << "Erro ao carregar som do tiro\n"; }
         
         soundShoot.setBuffer(bufferShoot);
         soundShoot.setVolume(100.f);

         ///////// TEXTURE WEAPON ////////////
         if(!textureBullet.loadFromFile("assets/arma.png")){
         std::cerr << "Erro: não foi possível carregar a textura do bala!\n";}
         
         //////////// SPRITE BULLET ////////////
         spriteBullet.setTexture(textureBullet);
         spriteBullet.setTextureRect({{0,0}, {32,32}});
         spriteBullet.setScale({0.1f, 0.1f});


       
        if (!texturaInimigo.loadFromFile("assets/Vilao.png")){
        std::cerr << "Erro: não foi possível carregar a textura do inimigo!\n";
        }
         if (!texturaChefe.loadFromFile("assets/louvaDeus.png")){
        std::cerr << "Erro: não foi possível carregar a textura do chefe!\n";
        }

        if (!backgroundT.loadFromFile("assets/PlanoFundo.jpg"))
        {std::cerr << "Erro: não foi possível carregar a textura do Fundo!\n";}

        if(!texturaItem.loadFromFile("assets/2x.png")){
         std::cerr << "Erro: não foi possível carregar a textura do item!\n";}
         
         
         itemEscolhaArma.sprite.setTextureRect({{0,0}, {32, 32}});
         itemEscolhaArma.sprite.setScale({1.f, 1.f});
         
        {
         background.emplace(backgroundT); // cria o sprite aqui
        }
       
        if (!texturaEscolha.loadFromFile("assets/fundoEscolha.png"))
        {std::cerr << "Erro: não foi possível carregar a textura do Fundo!\n";}
        
        
       
        escolhaArma1.setTexture(texturaEscolha);
        escolhaArma1.setOrigin(sf::Vector2f(escolhaArma1.getLocalBounds().size.x / 2.f, escolhaArma1.getLocalBounds().size.y / 2.f));
        escolhaArma1.setTextureRect({{0,0}, {200,500}});
        escolhaArma1.setScale(sf::Vector2f(1.f, 1.f));
        escolhaArma1.setPosition(sf::Vector2f(100.f, 100.f));

        
        escolhaArma2.setTexture(texturaEscolha);
        escolhaArma2.setOrigin(sf::Vector2f(escolhaArma2.getLocalBounds().size.x / 2.f, escolhaArma2.getLocalBounds().size.y / 2.f));
        escolhaArma2.setTextureRect({{0,0}, {200,500}});
        escolhaArma2.setScale(sf::Vector2f(1.f, 1.f));
        escolhaArma2.setPosition(sf::Vector2f(400.f, 100.f));
        
        escolhaArma3.setTexture(texturaEscolha);
        escolhaArma3.setOrigin(sf::Vector2f(escolhaArma3.getLocalBounds().size.x / 2.f, escolhaArma3.getLocalBounds().size.y / 2.f));
        escolhaArma3.setTextureRect({{0,0}, {200,500}});
        escolhaArma3.setScale(sf::Vector2f(1.f, 1.f));
        escolhaArma3.setPosition(sf::Vector2f(700.f, 100.f));
        
        
        

        if (!fontHud.openFromFile("assets/fonts/arial.ttf"))
        {
            std::cout << "Erro carregando fonte. Diretorio atual: "
              << std::filesystem::current_path() << std::endl;
        }




        //inicializating text and font hud;
        
        if (!fontHud.openFromFile("assets/fonts/arial.ttf"))
        {
        std::cerr << "Erro: não foi possível carregar a fonte do HUD\n";
        }
        textHud.setFont(fontHud);
        textHud.setCharacterSize(30);
        textHud.setFillColor(sf::Color::White);
        textHud.setPosition({500.f, 20.f});
        score = 0;
        textHud.setString("Score: " + std::to_string(score));

        //text for att weapons:

        textAtt.setFont(fontHud);
        textAtt.setCharacterSize(20);
        textAtt.setFillColor(sf::Color::White);
        textAtt.setPosition({120.f, 400.f});
        textAtt.setString("Dano : \nFireRate :\n " + std::to_string(score));

   
    

        // inicializando funções de gerenciamento
        inicializarArma(armasVetor);
        gerenciarInimigos(inimigos);
        // gerenciarParedes(paredes);
        gerenciarItens(itensVetor);
        window.setFramerateLimit(75);
        

        // barra vida player : 

         barraFundo.setFillColor(sf::Color::Red);
         barraFundo.setSize(sf::Vector2f(200.f, 15.f));
         barraFundo.setPosition(sf::Vector2f(70.f, 50.f));
         
         barraVida.setFillColor(sf::Color::Green);
         barraVida.setSize(sf::Vector2f(200.f, 15.f));
         barraVida.setPosition(sf::Vector2f(70.f, 50.f));

         
         
        }   
    void Game::inicializarArma(std::vector <arma>& armasVetor){
       
        
        
    }
    void Game::gerenciarInimigos(std::vector <inimigo>& inimigos){
        inimigos.emplace_back(sf::Vector2f(1400.f, 50.f), sf::Vector2f(30.f, 50.f), texturaInimigo);
        inimigos.emplace_back(sf::Vector2f(1400.f, 200.f), sf::Vector2f(30.f, 50.f), texturaInimigo);
        inimigos.emplace_back(sf::Vector2f(1400.f, 300.f), sf::Vector2f(30.f, 50.f), texturaChefe);
        inimigos[2].speed = 50.f; // chefe mais lento
        inimigos[2].vidaInimigo = 300; // chefe com mais vida
        inimigos[2].spriteInimigo.setTextureRect({{0,0},{300,300}});
        inimigos[2].spriteInimigo.setOrigin(inimigos[2].spriteInimigo.getLocalBounds().size / 2.f);
       // inimigos[2].spriteInimigo.setScale(sf::Vector2f(1.5f, 1.5f));// chefe maior
       
        inimigos[2].shape.setSize(sf::Vector2f(100.f, 100.f)); // hitbox maior
    }
    void Game::gerenciarItens(std::vector<itens>& itensVetor){

        itensVetor.emplace_back(texturaItem, sf::Vector2f(400.f, 300.f));
         itensVetor.emplace_back(texturaItem, sf::Vector2f(500.f, 300.f));
          itensVetor.emplace_back(texturaItem, sf::Vector2f(600.f, 300.f));
           itensVetor.emplace_back(texturaItem, sf::Vector2f(700.f, 300.f));
     
    }
    void Game::pegarItem(Personagem& player1, std::vector<itens>& itensVetor, arma& weapon){
        
        for (auto it = itensVetor.begin(); it != itensVetor.end(); ++it){
        
        if (!it->living)
           continue;

        if (it->sprite.getGlobalBounds().findIntersection(player1.getCorpo().getGlobalBounds()))
        {
        
        // velocidade de disparo
        weapon.fireRate -= 0.4f; 
        

        it->living = false;
        it->collected = true;
        }
      
    }
    }

    void Game::respawInimigo(std::vector <inimigo>& inimigos, float dt){
           
           for (auto it = inimigos.begin(); it != inimigos.end(); it++){
            
            if (!it->vivo) {
                  
             
                  float x = numAleatorio(0.f, 1150.f);
                  float y = numAleatorio(0.f,  1100.f);

                  float dx = x - player1.getPosition().x;
                  float dy = y - player1.getPosition().y;
                  
                  float dist = dx*dx + dy*dy;

                   if (dist >= 900.f*900.f)
                    {
            
                      it->getCorpo().setPosition(sf::Vector2f(x, y));
                      
                      
                      it->cooldown = false;
                      it->vivo = true;
                      it->vidaInimigo = 100;
                      it->updateSprite();
                      
                   }
            }
            
                
         }
        }
    void Game::gerenciarParedes(std::vector<parede>& paredes) 
    {
        paredes.emplace_back(sf::Vector2f(150.f, 200.f), sf::Vector2f(250.f, 100.f));
        paredes.emplace_back(sf::Vector2f(200.f, 300.f), sf::Vector2f(250.f, 100.f));
        paredes.emplace_back(sf::Vector2f(550.f, 100.f), sf::Vector2f(250.f, 100.f));
        paredes.emplace_back(sf::Vector2f(300.f, 300.f), sf::Vector2f(250.f, 100.f));
    }
    void inicializarP();

    void Game::vidaPlayer(sf::RenderWindow& window, Personagem& player1){

        float vidaAtual = 200.f * (player1.vidaPlayer / 100.f);
        if (vidaAtual < 0.f)
            vidaAtual = 0.f;
        barraVida.setSize(sf::Vector2f(vidaAtual, 15.f));
        window.draw(barraFundo);
        window.draw(barraVida);

    }

    void Game::processarEventos()
 {

    while (auto eventOpt = window.pollEvent()) {
            const auto& event = *eventOpt; // referencia o evento atual

            // verificar se é Closed
            if (event.is<sf::Event::Closed>())
            {
            window.close();
            }

            else if (event.is<sf::Event::KeyPressed>())
            {
              const auto* keyEvent = event.getIf<sf::Event::KeyPressed>();
              if (keyEvent->code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }
            }
            
           
            if (event.is<sf::Event::KeyPressed>())
            {
              const auto* keyEvent = event.getIf<sf::Event::KeyPressed>();
              if (keyEvent->code == sf::Keyboard::Key::P)
                {
                    paused = !paused;
                }
            }
             if(event.is<sf::Event::MouseButtonPressed>())
             {
              const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();

              if(mouseEvent->button == sf::Mouse::Button::Left)
               posClick = window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getDefaultView());
               //fica false no ArmaCHeck para evitar click fantasma no PosClick
               clicou = true;
             }
            
    }
 }


bool Game::pegou(Personagem& player1, arma& weapon, float dt){

    float Px =  player1.getPosition().x;
    float Py =  player1.getPosition().y; 
    float Ax =  weapon.getPosition().x;
    float Ay =  weapon.getPosition().y; 
    float Dx = Px - Ax;
    float Dy = Py - Ay;
    float dist = std::sqrt(Dx*Dx + Dy*Dy);
    
    if (dist < 50.f){
        
       weapon.atualizar(dt, balas);
        
        return true;
    }
    return false;
};
bool Game::pegouItemArma(Personagem& player1, itens& itemEscolhaArma){

    float Px =  player1.getPosition().x;
    float Py =  player1.getPosition().y; 
    float Ax =  itemEscolhaArma.position.x;
    float Ay =  itemEscolhaArma.position.y; 
    float Dx = Px - Ax;
    float Dy = Py - Ay;
    float dist = std::sqrt(Dx*Dx + Dy*Dy);
    
    if (dist < 50.f){
        
      // itemEscolhaArma.position += player1.getPosition() * dt;
        
        return true;
    }
    return false;
};


sf::Vector2f Game::PosicaoMouse(sf::RenderWindow& window, arma& weapon){

sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window), camera);

sf::Vector2f direcao =  mouse - weapon.getPosition();

float len = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y);

 if (len != 0.f)
        direcao /= len;
    else
        direcao = {1.f, 0.f};



return direcao;


};

void Game::atualizar() {
    
    // dt = deltaTime ele conta o tempo entre cada frame e dps é resetado.

    float dt = clock.restart().asSeconds();
    tempoAcumulado += dt;
    
    
    //chamando a funcao (ela é ativada normalmente) 
    pegouArmaBool = pegouItemArma(player1, itemEscolhaArma);
    
    // Atualiza a camera para seguir o jogador

    camera.setCenter(player1.getPosition());

    if(pegouArmaBool)
    escolhaArmaCheck(weapon, posClick, escolhaArma1, escolhaArma2, escolhaArma3, dt, clicou);
    
   
    if (!player1.playerVivo){
     paused = true;
    }
   
    if (!paused){
    // ========= INIMIGOS =========
    acertoDano(inimigos, balas);
    for (auto& i : inimigos)
    { 
        
        

        if (!i.vivo or !player1.playerVivo) continue; // inimigo morto não faz nada
        
        // cooldown timer
        if(i.cooldown)
        {
        i.cooldownTimer -= dt;

        if(i.cooldownTimer <= 0.f)
        {
            i.cooldown = false;
            i.cooldownTimer = 0.f;
        }
        }
        
        // 6. dano por bala
        

        if (!i.cooldown){
        // 1. calcula movimento
        sf::Vector2f movimento = i.moverInimigo(dt, player1, inimigos, texturaInimigo);

        // 2. futura posição
        sf::Vector2f futuraP = i.getCorpo().getPosition() + movimento;

        // 3. colisão com paredes
        Colisao(paredes, i.getCorpo(), futuraP, movimento);

        // 4. move inimigo
        i.getCorpo().move(movimento);

        // 5. sprite segue o corpo
        }
        
        i.updateSprite();
         
    }
    
   
       
    // ========= ITENS =========
    pegarItem(player1, itensVetor, weapon);
    // ========= PLAYER =========
    if (player1.playerVivo)
    player1.mover(dt, paredes);

    // ========= ARMA =========  
    pegou(player1, weapon,dt);

    // ========= DANO PLAYER =========
        
    danoPlayer(inimigos, player1);

    // ========= BALAS =========
    AtualizarBala(balas, dt);

    // mouse firing direction 
    //firing :
    if(player1.playerVivo){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            
            
              
              if (weapon.pegou)
              {
              

              sf::Vector2f dirM = PosicaoMouse(window, weapon);
              miraCanhao = window.mapPixelToCoords(sf::Mouse::getPosition(window), camera);
              //Mouse Position:
              if (tempoAcumulado >= weapon.fireRate){
              //Cria bala:
              weapon.PosA = weapon.getPosition();
              weapon.Atirando(balas, dirM, miraCanhao);
            
              soundShoot.play();
            

              tempoAcumulado = 0.f;
              
              }

            }

        }
    }

  }
   // 7. Respawn caso morra :
    respawInimigo(inimigos, dt);
    
  
}
void Game::desenhar() {
   
    // Limpa a Tela (Limpa oq foi feito antes para atualizar):
    window.clear();
    window.setView(camera);
    
   //Desenha tudo:
   
    if (background) {
        window.draw(*background);
    }
    
    if (player1.playerVivo)
    player1.drawJogador(window);

    weapon.DrawArma(window);

    for( auto& b : balas)
    {
    //b.corpoB.setTexture(&textureBullet);
    b.desenharCirculoeBala(window);
    } 
    
    // Vetor inimigos :

    for (auto& i : inimigos)
    i.drawInimigo(window);
    
    
    // vetor itens:
    
     for( auto& i : itensVetor)
     if (i.living) 
      window.draw(i.sprite);

      window.draw(itemEscolhaArma.sprite);
    
    shapeP.drawParede(window);
    
    //weapon.Atirando(balas , 0, window);
    
    for (auto& p : paredes) {
        p.drawParede(window);
    }
    // Reset view to default for hud:
    window.setView(window.getDefaultView());

   
    
    //hud :
    bool MostrarEscolhaItem0 = pegouArmaBool;

    if (MostrarEscolhaItem0){
    desenhaEscolhaArma(window, escolhaArma1, escolhaArma2, escolhaArma3, itensVetor[0], textAtt);
    MostrarEscolhaItem0 = false;
    }
    
    vidaPlayer(window, player1);
    window.draw(textHud);
    

    window.display();
}

void Game::AtualizarBala(std::vector <bala>& balas, float dt){
     
        
    
         for (auto it = balas.begin(); it != balas.end(); )
        {
        if(weapon.tipo == TipoArma::CANNON){
        it->mover(dt, true);
        }
        else
        it->mover(dt, false);

        float dx = it->corpoB.getPosition().x - weapon.PosA.x;
        float dy = it->corpoB.getPosition().y - weapon.PosA.y;

        float dist = std::sqrt(dx * dx + dy * dy);

        if (it->Vida <= 0.f || dist > 800.f)
        {
            it = balas.erase(it); // 👈 REMOVE A BALA
            
        }
        else
        {
            ++it; // só avança se NÃO apagou
        }
        }
    } 
     void Game::run()
    {
        
        while (window.isOpen()) {
        processarEventos();
        atualizar();
        desenhar();
        }
    }

 float Game::Colisao(std::vector<parede>& paredes, sf::RectangleShape& pe, sf::Vector2f& futuraP, sf::Vector2f& movimento)
{
      
    for (auto& p : paredes)  // ← Agora percorre TODAS as paredes
    {
        
        

        // Posição e tamanho da parede atual
        float posicaoParedex = p.getPosition().x;
        float posicaoParedey = p.getPosition().y;

        float paredeWidth  = p.getSize().x;
        float paredeHeight = p.getSize().y;

        // Posições do player baseado na futura posição
        float posicaoPlayerx = futuraP.x + 5.f; 
        float posicaoPlayery = futuraP.y + 5.f;

        float playerWidth  = pe.getSize().x;
        float playerHeight = pe.getSize().y;

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
                    if (movimento.x < 0)
                    return movimento.x = 0; 
                }
                else
                {
                    if (movimento.x > 0)  return movimento.x = 0;
                }
            }
            else
            {
                // Colisão vertical
                if (dy > 0)
                {
                    if (movimento.y < 0) return movimento.y = 0;
                }
                else
                {
                    if (movimento.y > 0) return movimento.y = 0;
                }
            }
        }
    }
    return 0;
}
 
 void Game::acertoDano(std::vector <inimigo>& inimigos, std::vector <bala>& balas)
 {
  for (auto it = balas.begin(); it != balas.end(); )
  {

    for(auto& inimigo : inimigos)
    {

        if(!inimigo.vivo) continue;

        if (it->corpoB.getGlobalBounds().findIntersection(inimigo.getCorpo().getGlobalBounds()))
        {

            inimigo.perdeuVida(inimigo.vidaInimigo, weapon.armaDano , inimigo.vivo);
            it->danoAplicado = true;

            //it = balas.erase(it);
            
        }
        
    
        if (it->danoAplicado)
        {
            it = balas.erase(it);

        }
        else
        {
            ++it;
        }
    }
  }
}

  void  Game::danoPlayer(std::vector <inimigo>& inimigos, Personagem& player1){
  int  dano;
  

    for (auto it = inimigos.begin(); it != inimigos.end(); ++it){
        
        if (!player1.playerVivo)
        break;
        
        if (it->cooldown)
           continue;

        if (it->getCorpo().getGlobalBounds().findIntersection(player1.getCorpo().getGlobalBounds()))
        {
        
        player1.playerDano(player1.vidaPlayer,dano = 10, player1.playerVivo);
        it->cooldown = true;
        it->cooldownTimer = 0.5f;

        
        }
      
    }
 }
    float Game::numAleatorio(float min, float max){
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
    }

 void Game::escolhaArmaCheck(arma& weapon,sf::Vector2f posClick,  sf::Sprite& escolhaArma1, sf::Sprite& escolhaArma2, sf::Sprite& escolhaArma3, float dt, bool& clicou){
       
    
  
    
    if (escolhaArma1.getGlobalBounds().contains(posClick)){
        weapon.tipo = TipoArma::PISTOLA;
        weapon.configurarTipoArma();
        clicou = false;

    }
    if (escolhaArma2.getGlobalBounds().contains(posClick)){
        weapon.tipo = TipoArma::RIFLE;
        weapon.configurarTipoArma();
        clicou = false;

    }
    if (escolhaArma3.getGlobalBounds().contains(posClick)){
        weapon.tipo = TipoArma::CANNON;
        weapon.configurarTipoArma();
        clicou = false;

    }


 };

  void Game::desenhaEscolhaArma(sf::RenderWindow& window,sf::Sprite escolhaArma1, sf::Sprite escolhaArma2, sf::Sprite escolhaArma3, itens& itemEscolhaArma, sf::Text textAtt){
    window.draw(escolhaArma1);
    window.draw(escolhaArma2);
    window.draw(escolhaArma3);
    window.draw(textAtt);
  }

