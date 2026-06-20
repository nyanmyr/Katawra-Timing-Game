#include "Headers/Systems.hpp"

#include <iostream>
#include <random>

#include <SFML/Graphics.hpp>

const float E = 2.1781828f;

NacreCoordinator& systemsNC = NacreCoordinator::getInstance();

// -------------------------------------------------------
// auxiliary systems
// -------------------------------------------------------
float inverseLerp_Auxiliary
(
    float min,
    float max,
    float current
)
{
    return (current - min) / (max - min);
}

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
    Difficulty diff;

    for (auto& [entity, nextScene] : nextScenes->getAll())
    {
        if (!systemsNC.getComponentArray<CMode>()->hasData(entity))
        {
            continue;
        }

        switch (systemsNC.getComponentArray<CMode>()->getData(entity).selected)
        {
            case DIFFICULTY_HARD:
                diff = Difficulty::DIFFICULTY_HARD;
                break;
            case DIFFICULTY_NORMAL:
            default:
                diff = Difficulty::DIFFICULTY_NORMAL;
                break;
        }

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
        playScene(window, playNextScene, font, diff);
        window.close();
    }
}

const int HIT_SCORE = 100.f;
const int BOUNCE_BONUS = 50.f;

const float HIT_INTENSITY = 10.f;
const float HIT_SHAKE_TIMER = 0.15f;

const float FAIL_INTENSITY = 30.f;
const float FAIL_SHAKE_TIMER = 0.1f;

const float LOG_TIMER = .24f;
const float FADE_TIMER = .12f;

// TODO: rename systems to start with lowercase
void Hit_Control
(
    sf::Font& font,
    Entity indicator,
    Entity hitbox,
    Entity cameraShake,
    Entity scoreFeed
)
{
    const CPosition& indicPos = systemsNC.getComponentArray<CPosition>()->getData(indicator);

    const CPosition& hitPos = systemsNC.getComponentArray<CPosition>()->getData(hitbox);
    const CTransform& hitTrans = systemsNC.getComponentArray<CTransform>()->getData(hitbox);
    CScore& score = systemsNC.getComponentArray<CScore>()->getData(hitbox);
    CHitbox& hit = systemsNC.getComponentArray<CHitbox>()->getData(hitbox);

    CCameraShake& shakeCam = systemsNC.getComponentArray<CCameraShake>()->getData(cameraShake);
    CScoreFeed& feedScore = systemsNC.getComponentArray<CScoreFeed>()->getData(scoreFeed);

    //std::cout << "x:" << indicPos.x << "\n";
    //std::cout << "min:" << hitPos.x - (hitTrans.width / 2.f) << " max:" << hitPos.x + (hitTrans.width / 2.f) << "\n\n";

    if 
    (
        indicPos.x < hitPos.x - (hitTrans.width / 2.f) ||
        indicPos.x > hitPos.x + (hitTrans.width / 2.f)
    )
    {
        if (shakeCam.intensity <= FAIL_INTENSITY)
        {
            shakeCam.intensity = FAIL_INTENSITY;
        }
        if (shakeCam.timer <= FAIL_SHAKE_TIMER)
        {
            shakeCam.timer = FAIL_SHAKE_TIMER;
        }

        //std::cout << "Missed!" << "\n";
        score.count = 0;
        score.hits = 0;

        score.bounces = 0;
        hit.spawned = false;
        return;
    }

    if (shakeCam.intensity <= HIT_INTENSITY)
    {
        shakeCam.intensity = HIT_INTENSITY;
    }
    if (shakeCam.timer <= HIT_SHAKE_TIMER)
    {
        shakeCam.timer = HIT_SHAKE_TIMER;
    }

    float dist = 1.f - std::abs
    (
        inverseLerp_Auxiliary
        (
            hitPos.x,
            hitPos.x + (hitTrans.width / 2.f),
            indicPos.x
        )
    );

    ++score.hits;

    score.count += HIT_SCORE + (HIT_SCORE * dist);
    // hit score
    feedScore.feed.push
    (
        makeScoreLog
        (
            {
                50,
                50
            },
            font,
            "+" + std::to_string(HIT_SCORE) + " SCORE",
            LOG_TIMER,
            FADE_TIMER
        )
    );
    // bonus hitscore
    feedScore.feed.push
    (
        makeScoreLog
        (
            {
                50,
                50
            },
            font,
            "+" + std::to_string((int)(HIT_SCORE * dist)) + " CENTER",
            LOG_TIMER,
            FADE_TIMER
        )
    );

    if (score.bounces < 2)
    {
        score.count += BOUNCE_BONUS;
        // bonus bounce
        feedScore.feed.push
        (
            makeScoreLog
            (
                {
                    50,
                    50
                },
                font,
                "+" + std::to_string(BOUNCE_BONUS) + " BONUS",
                LOG_TIMER,
                FADE_TIMER
            )
        );
    }

    feedScore.positionsSet = false;

    score.bounces = 0;
    hit.spawned = false;

    //std::cout << "distance: " << dist << "\n";
}

void moveIndicator_Update
(
    Entity indicator,
    Entity slider,
    Entity hitbox
)
{
    const CXBounds& xBounds = systemsNC.getComponentArray<CXBounds>()->getData(slider);
    const CSpeed& speed = systemsNC.getComponentArray<CSpeed>()->getData(indicator);
    CPosition& pos = systemsNC.getComponentArray<CPosition>()->getData(indicator);
    CVelocity& vel = systemsNC.getComponentArray<CVelocity>()->getData(indicator);
    CScore& score = systemsNC.getComponentArray<CScore>()->getData(hitbox);

    vel.x = vel.x < 0 ? -speed.amount : speed.amount;

    //std::cout << "speed.amount: " << speed.amount << "\n";
    //std::cout << "vel.x: " << vel.x << "\n";

    if (pos.x > xBounds.max || pos.x < xBounds.min)
    {
        vel.x = -vel.x;
        ++score.bounces;
    }

    if (pos.x > xBounds.max)
    {
        pos.x = xBounds.max;
    }
    else if (pos.x < xBounds.min)
    {
        pos.x = xBounds.min;
    }
}

void spawnHitbox
(
    Entity hitbox,
    Entity slider,
    DeltaTime dt
)
{
    const CXBounds& xBounds = systemsNC.getComponentArray<CXBounds>()->getData(slider);
    const CPosition& slidPos = systemsNC.getComponentArray<CPosition>()->getData(slider);
    const CTransform& slidTrans = systemsNC.getComponentArray<CTransform>()->getData(slider);

    const CScore& score = systemsNC.getComponentArray<CScore>()->getData(hitbox);
    CHitbox& hit = systemsNC.getComponentArray<CHitbox>()->getData(hitbox);
    CPosition& hitPos = systemsNC.getComponentArray<CPosition>()->getData(hitbox);
    CShape& hitRect = systemsNC.getComponentArray<CShape>()->getData(hitbox);
    CTransform& hitTrans = systemsNC.getComponentArray<CTransform>()->getData(hitbox);
    COrigin& hirOrig = systemsNC.getComponentArray<COrigin>()->getData(hitbox);

    if (hit.spawned)
    {
        return;
    }

    float spawnSize = hit.startSize - (hit.sizeDecrease * score.hits);
    if (spawnSize < hit.minSize)
    {
        spawnSize = hit.minSize;
    }

    std::hash<DeltaTime> hasher;
    uint32_t hashValue = hasher(dt);

    std::mt19937 gen(hashValue);

    float minSpawnX = xBounds.min + (spawnSize / 2.f);
    float maxSpawnX = xBounds.max - (spawnSize / 2.f);

    std::uniform_real_distribution<> distrib(minSpawnX, maxSpawnX);

    hitPos.x = distrib(gen);
    hitPos.y = slidPos.y;

    hitRect.rect.setSize
    (
        {
            spawnSize,
            slidTrans.height
        }
    );

    hitTrans.width = spawnSize;
    hitTrans.height = slidTrans.height;

    hirOrig.offsetX = spawnSize / 2.f;
    hirOrig.offsetY = slidTrans.height / 2.f;

    hit.spawned = true;
}

const float MINIMUM_SCALED_FACTOR = 0.25f;
const float CENTER_OFFSET = 175.f;

void indicatorSpeed
(
    Entity slider,
    Entity indicator,
    Entity hitbox
)
{
    const CXBounds& xBounds = systemsNC.getComponentArray<CXBounds>()->getData(slider);
    const CSpeedIncrease& speedIncrease = systemsNC.getComponentArray<CSpeedIncrease>()->getData(indicator);
    const CPosition& pos = systemsNC.getComponentArray<CPosition>()->getData(indicator);
    const CVelocity& vel = systemsNC.getComponentArray<CVelocity>()->getData(indicator);
    CSpeed& speed = systemsNC.getComponentArray<CSpeed>()->getData(indicator);
    CScore& hitScore = systemsNC.getComponentArray<CScore>()->getData(hitbox);

    float scaledSpeed = 0.f;

    float center = (xBounds.min + xBounds.max) / 2.;

    if (pos.x > center + CENTER_OFFSET && vel.x > 0.f)
    {
        scaledSpeed = std::abs
        (
            inverseLerp_Auxiliary
            (
                center + CENTER_OFFSET,
                xBounds.max,
                pos.x
            )
        );
    }
    else if (pos.x < center - CENTER_OFFSET && vel.x < 0.f)
    {
        scaledSpeed = std::abs
        (
            inverseLerp_Auxiliary
            (
                center - CENTER_OFFSET,
                xBounds.min,
                pos.x
            )
        );
    }

    if ((1.f - scaledSpeed) < MINIMUM_SCALED_FACTOR)
    {
        scaledSpeed = (1.f - MINIMUM_SCALED_FACTOR);
    }

    //std::cout << "where: " << (1.f - scaledSpeed) << "\n";

    speed.amount = speed.original + (speedIncrease.increase * hitScore.hits);
    speed.amount *= (1.f - scaledSpeed);
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

void displayScore
(
    Entity score,
    Entity hitbox
)
{
    CText& scoreText = systemsNC.getComponentArray<CText>()->getData(score);
    CScore& hitScore = systemsNC.getComponentArray<CScore>()->getData(hitbox);

    scoreText.box->setString("Score: " + std::to_string(hitScore.count));
}

void shakeCamera_UpdateSystem
(
    Entity cameraShake,
    sf::RenderWindow& window,
    DeltaTime dt
)
{
    CCameraShake& shakeCam = systemsNC.getComponentArray<CCameraShake>()->getData(cameraShake);

    sf::View view = window.getView();

    //std::cout << "before:" << "\n";
    //std::cout << "intensity: " << shakeCam.intensity << "\n";
    //std::cout << "timer: " << shakeCam.timer << "\n\n";

    if (shakeCam.timer <= 0)
    {
        shakeCam.intensity = 0.f;
        shakeCam.timer = 0.f;
        view.setCenter
        (
            {
                window.getDefaultView().getSize().x / 2.f,
                window.getDefaultView().getSize().y / 2.f
            }
        );
        window.setView(view);
        return;
    }

    //std::cout << "after:" << "\n";
    //std::cout << "intensity: " << shakeCam.intensity << "\n";
    //std::cout << "timer: " << shakeCam.timer << "\n\n\n";

    shakeCam.timer -= dt;

    std::hash<DeltaTime> hasher;
    uint32_t hashValue = hasher(dt);

    std::mt19937 gen(hashValue);
    std::uniform_real_distribution<> distrib(0, shakeCam.intensity);

    //std::cout << "x: " << cam.currentPos.x << "y: " << cam.currentPos.y << "\n";
    view.setCenter
    (
        {
            (window.getDefaultView().getSize().x / 2.f) + (float)distrib(gen),
            (window.getDefaultView().getSize().y / 2.f) + (float)distrib(gen)
        }
    );

    //shakeCam.intensity -= dt;

    window.setView(view);
}

const float LOG_SPACING_Y = 40.f;

void doScoreFeed
(
    sf::Vector2f startPos,
    DeltaTime dt,
    Entity scoreFeed
)
{
    CScoreFeed& feedScore = systemsNC.getComponentArray<CScoreFeed>()->getData(scoreFeed);
    
    if (feedScore.feed.empty())
    {
        return;
    }

    if (!feedScore.positionsSet)
    {
        std::queue<Entity> temp;

        int count = 0;

        while (!feedScore.feed.empty())
        {
            CPosition& pos = systemsNC.getComponentArray<CPosition>()->getData(feedScore.feed.front());
            pos.x = startPos.x;
            pos.y = startPos.y + (LOG_SPACING_Y * count);
            ++count;

            temp.push(feedScore.feed.front());
            feedScore.feed.pop();
        }

        while (!temp.empty())
        {
            feedScore.feed.push(temp.front());
            temp.pop();
        }

        feedScore.positionsSet = true;
    }

    CScoreLog& scoreLog = systemsNC.getComponentArray<CScoreLog>()->getData(feedScore.feed.front());
    CText& scoreText = systemsNC.getComponentArray<CText>()->getData(feedScore.feed.front());

    if (scoreLog.timer > 0.f)
    {
        scoreLog.timer -= dt;
        //std::cout << "timer: " << scoreLog.timer << "\n";
        return;
    }

    if (scoreLog.fadeTimer > 0.f)
    {
        scoreLog.fadeTimer -= dt;
        //std::cout << "fadeTimer: " << scoreLog.fadeTimer << "\n";
        scoreText.box.value().setFillColor
        (
            sf::Color
            (
                scoreText.box.value().getFillColor().r,
                scoreText.box.value().getFillColor().g,
                scoreText.box.value().getFillColor().b,
                inverseLerp_Auxiliary
                (
                    0.f,
                    scoreLog.fadeSet,
                    scoreLog.fadeTimer
                ) * 255
            )
        );
        return;
    }

    feedScore.positionsSet = false;
    systemsNC.deleteEntity(feedScore.feed.front());
    feedScore.feed.pop();
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