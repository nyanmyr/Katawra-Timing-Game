#include "../Headers/Scenes.hpp"
#include <stdexcept>

void playScene
(
    sf::RenderWindow& window,
    Scene scene,
    sf::Font& normalFont,
    sf::Font& titleFont,
    Difficulty difficulty
)
{
    switch (scene) {
    case MENU:
        menuScene
        (
            window,
            normalFont,
            titleFont
        );
        break;
    case PLAYING:
        playingScene
        (
            window,
            normalFont,
            titleFont,
            difficulty
        );
        break;
    default:
        throw std::runtime_error("Scene does not exist.");
        break;
    }
}
