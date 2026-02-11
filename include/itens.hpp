#include <SFML/Graphics.hpp>
#include <vector>

struct itens {
    
    sf::Sprite sprite;
    sf::Vector2f position;
    // active = living or not.
    bool living;
    bool collected;

    itens(sf::Texture& texture, sf::Vector2f pos)
        : position(pos), living(true), collected(false), sprite(texture) 
        {
        
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setTextureRect({{0,0}, {100,100}});
        sprite.setScale({0.4, 0.4});

        
        }
};