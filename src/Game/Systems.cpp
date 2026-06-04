#include "Headers/Systems.hpp"

#include <SFML/Graphics.hpp>

NacreCoordinator& systemsNC = NacreCoordinator::getInstance();

// -------------------------------------------------------
// start systems
// -------------------------------------------------------
void setTextSystem(sf::Font& font)
{
    auto& texts = systemsNC.getComponentArray<CText>();

    for (auto& [entity, text] : texts->getAll())
    {
        text.box.value().setString(text.string);
        text.box.value().setCharacterSize(text.size);
        text.box.value().setFillColor(text.color);
    }
}
void setTextOriginSystem()
{
    auto& texts = systemsNC.getComponentArray<CText>();
    auto& transforms = systemsNC.getComponentArray<CTransform>();

    float offsetX;
    float offsetY;

    for (auto& [entity, text] : texts->getAll())
    {
        if (!transforms->hasData(entity))
        {
            continue;
        }

        CTransform& transform = transforms->getData(entity);

        switch (text.format)
        {
        case TOP:
            offsetX = text.box.value().getLocalBounds().size.x / 2;
            offsetY = text.box.value().getLocalBounds().size.y;
            break;
        case BOTTOM:
            offsetX = text.box.value().getLocalBounds().size.x / 2;
            offsetY = text.box.value().getLocalBounds().size.y / 2;
            break;
        case MIDDLE:
        default:
            offsetX = text.box.value().getLocalBounds().size.x / 2;
            offsetY = (text.box.value().getLocalBounds().size.y / 2) + (text.box.value().getLocalBounds().size.y / 4);
            break;
        }

        text.box.value().setOrigin
        (
            {
                offsetX,
                offsetY
            }
        );
    }
}
void setShapeOriginSystem()
{
    auto& origins = systemsNC.getComponentArray<COrigin>();
    auto& shapes = systemsNC.getComponentArray<CShape>();

    for (auto& [entity, shape] : shapes->getAll())
    {
        if (!origins->hasData(entity))
        {
            continue;
        }

        COrigin& origin = origins->getData(entity);
        shape.rect.setOrigin
        (
            {
                origin.offsetX,
                origin.offsetY
            }
        );
    }
}

// -------------------------------------------------------
// update systems
// -------------------------------------------------------
const float DEFAULT_SCALE_X = 1.0f;
const float DEFAULT_SCALE_Y = 1.0f;

const float HOVER_SCALE_X = 1.1f;
const float HOVER_SCALE_Y = 1.1f;

const float CLICKED_SCALE_X = 0.9f;
const float CLICKED_SCALE_Y = 0.9f;

void buttonClickedSystem(sf::Vector2i& mouseVector, bool& buttonClicked, const DeltaTime dt)
{
    //auto& shapes = systemsNC.getComponentArray<CShape>();
    auto& shapes = systemsNC.getComponentArray<CShape>();
    auto& buttons = systemsNC.getComponentArray<CButton>();
    auto& origins = systemsNC.getComponentArray<COrigin>();
    auto& texts = systemsNC.getComponentArray<CText>();
    auto& nextScenes = systemsNC.getComponentArray<CNextScene>();
    auto& transforms = systemsNC.getComponentArray<CTransform>();
    auto& positions = systemsNC.getComponentArray<CPosition>();

    for (auto& [entity, button] : buttons->getAll())
    {
        if (!button.enabled)
        {
            continue;
        }

        // buttons must have a shape, origin, and text
        if (origins->hasData(entity) &&
            texts->hasData(entity) &&
            positions->hasData(entity) &&
            shapes->hasData(entity))
        {
            //std::cout << "button.top: " << button.top << "\n";
            //std::cout << "button.left: " << button.left << "\n";
            COrigin& origin = origins->getData(entity);
            CText& text = texts->getData(entity);
            CTransform& transform = transforms->getData(entity);
            CPosition& position = positions->getData(entity);
            CShape& shape = shapes->getData(entity);

            button.clicked = false; // reset

            if (button.clickedTimer <= 0)
            {
                shape.rect.setScale
                (
                    sf::Vector2f
                    (
                        DEFAULT_SCALE_X,
                        DEFAULT_SCALE_Y
                    )
                );
                text.box.value().setScale
                (
                    sf::Vector2f
                    (
                        DEFAULT_SCALE_X,
                        DEFAULT_SCALE_Y
                    )
                );
            }
            else
            {
                button.clickedTimer -= dt;

                if (button.clickedTimer <= 0)
                {
                    button.clicked = true;

                    if (nextScenes->hasData(entity))
                    {
                        //std::cout << "starting next scene." << "\n";
                        CNextScene& nextScene = nextScenes->getData(entity);
                        nextScene.active = true;
                    }
                }
            }

            // button hovering
            if (mouseVector.x > position.x - origin.offsetX &&
                mouseVector.x < position.x + transform.width - origin.offsetX &&
                mouseVector.y > position.y - origin.offsetY &&
                mouseVector.y < position.y + transform.height - origin.offsetY &&
                button.clickedTimer <= 0)
            {
                shape.rect.setScale
                (
                    sf::Vector2f
                    (
                        HOVER_SCALE_X,
                        HOVER_SCALE_Y
                    )
                );
                text.box.value().setScale
                (
                    sf::Vector2f
                    (
                        HOVER_SCALE_X,
                        HOVER_SCALE_Y
                    )
                );

                if (buttonClicked)
                {
                    button.clickedTimer = button.clickedDuration;
                }
            }

            // button clicking
            if (button.clickedTimer > 0)
            {
                shape.rect.setScale
                (
                    sf::Vector2f
                    (
                        CLICKED_SCALE_X,
                        CLICKED_SCALE_Y
                    )
                );
                text.box.value().setScale
                (
                    sf::Vector2f
                    (
                        CLICKED_SCALE_X,
                        CLICKED_SCALE_Y
                    )
                );
            }
        }
    }
}
void nextSceneSystem(sf::RenderWindow& window, sf::Font& font)
{
    auto& nextScenes = systemsNC.getComponentArray<CNextScene>();

    bool playNext = false;
    Scene playNextScene;

    for (auto& [entity, nextScene] : nextScenes->getAll())
    {
        // buttons must have a shape, origin, and text
        if (nextScene.active)
        {
            //std::cout << "active: " << nextScene.next << "\n";
            playNext = true;
            playNextScene = nextScene.next;
            break;
        }
    }

    if (playNext)
    {
        systemsNC.destroyAll();
        playScene(window, playNextScene, font);
        window.close();
    }
}
void playerControlSystem(const Entity player, DeltaTime dt)
// controlling seems buggy, first you move slow then you speed up suddenly
{
    auto& velocities = systemsNC.getComponentArray<CVelocity>();
    auto& speeds = systemsNC.getComponentArray<CSpeed>();
    auto& playerControllers = systemsNC.getComponentArray<CPlayerController>();

    if 
    (
        !velocities->hasData(player) ||
        !speeds->hasData(player) ||
        !playerControllers->hasData(player)
    )
    {
        return;
    }

    const CPlayerController playerController = playerControllers->getData(player);
    const CSpeed speed = speeds->getData(player);
    CVelocity& velocity = velocities->getData(player);

    if (!playerController.enabled)
    {
        return;
    }

    float newSpeedX = 0.f;
    float newSpeedY = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        newSpeedY = -speed.y;
    } 
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        newSpeedY = speed.y;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        newSpeedX = -speed.x;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        newSpeedX = speed.x;
    }

    // applies the speed (even if there aren't any changes)
    velocity.x += (newSpeedX * dt);
    velocity.y += (newSpeedY * dt);

    if (velocity.x > velocity.maxX)
    {
        velocity.x = velocity.maxX;
    }
    else if (velocity.x < velocity.minX)
    {
        velocity.x = velocity.minX;
    }

    if (velocity.y > velocity.maxY)
    {
        velocity.y = velocity.maxY;
    }
    else if (velocity.y < velocity.minY)
    {
        velocity.y = velocity.minY;
    }

}
void moveSystem(const DeltaTime dt)
{
    auto& velocities = systemsNC.getComponentArray<CVelocity>();
    auto& positions = systemsNC.getComponentArray<CPosition>();

    for (auto& [entity, velocity] : velocities->getAll())
    {
        if (!positions->hasData(entity))
        {
            continue;
        }

        CPosition& pos = positions->getData(entity);
        pos.x += (velocity.x * dt);
        pos.y += (velocity.y * dt);
    }
}
void dragSystem(const DeltaTime dt)
{
    auto& velocities = systemsNC.getComponentArray<CVelocity>();
    auto& drags = systemsNC.getComponentArray<CDrag>();

    for (auto& [entity, velocity] : velocities->getAll())
    {
        if (!drags->hasData(entity))
        {
            continue;
        }

        CDrag drag = drags->getData(entity);

        // can't be exactly 0.f because it will drift aimlessly
        velocity.x = velocity.x < -0.1f ? velocity.x + (drag.x * dt) :
            velocity.x > 0.1f ? velocity.x - (drag.x * dt) : 0.f;
        velocity.y = velocity.y < -0.1f ? velocity.y + (drag.y * dt) :
            velocity.y > 0.1f ? velocity.y - (drag.y * dt) : 0.f;
    }
}

// -------------------------------------------------------
// rendering systems
// -------------------------------------------------------
void zIndexSystem(std::queue<Entity>& renderQueue)
{
    auto& zIndexes = systemsNC.getComponentArray<CZIndex>();

    std::vector<std::pair<int, Entity>> renderVector;
    for (auto& [entity, zIndex] : zIndexes->getAll())
    {
        if (zIndex.visible) renderVector.emplace_back(zIndex.index, entity);
    }
    std::sort(renderVector.begin(), renderVector.end());

    for (auto& [zIndex, entity] : renderVector)
    {
        renderQueue.push(entity);
    }
}
void renderSystem(sf::RenderWindow& window, std::queue<Entity>& renderQueue)
{
    auto& shapes = systemsNC.getComponentArray<CShape>();
    auto& positions = systemsNC.getComponentArray<CPosition>();
    auto& texts = systemsNC.getComponentArray<CText>();

    while (!renderQueue.empty())
    {
        Entity& popped = renderQueue.front();
        //std::cout << "popped: " << popped << "\n";

        if (!positions->hasData(popped))
        {
            // this means the entity does not have a position component
            continue;
        }

        CPosition& pos = positions->getData(popped);

        if (shapes->hasData(popped))
        {
            CShape& shape = shapes->getData(popped);

            shape.rect.setPosition
            (
                {
                    pos.x,
                    pos.y
                }
            );
            window.draw(shape.rect);
        }

        if (texts->hasData(popped))
        {
            CText& text = texts->getData(popped);

            text.box.value().setPosition
            (
                {
                    pos.x,
                    pos.y
                }
            );
            window.draw(text.box.value());
        }

        renderQueue.pop();
    }
}