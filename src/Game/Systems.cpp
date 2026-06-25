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

void loadTextures_StartSystem(Entity loadedTextures)
{
    auto& texturesContainerArray = systemsNC.getComponentArray<CTexturesContainer>();

    if (!texturesContainerArray->hasData(loadedTextures))
    {
        return;
    }

    CTexturesContainer& container = texturesContainerArray->getData(loadedTextures);

    container.map.emplace(TextureEnum::INDICATOR, sf::Texture(SPRITES_PATH "indicator_texture.png"));
    container.map.emplace(TextureEnum::BAR, sf::Texture(SPRITES_PATH "bar_texture.png"));
    container.map.emplace(TextureEnum::FILL, sf::Texture(SPRITES_PATH "fill_texture.jpg"));
    container.map.emplace(TextureEnum::BACKGROUND, sf::Texture(SPRITES_PATH "background_texture.jpg"));
    container.map.emplace(TextureEnum::TEXTURE_PLACEHOLDER_PLACEHOLDER, sf::Texture(SPRITES_PATH "placeholder_placeholder.jpg"));
}
void loadSprites_StartSystem(Entity loadedTextures)
{
    auto& spriteArray = systemsNC.getComponentArray<CSprite>();
    auto& transformArray = systemsNC.getComponentArray<CTransform>();
    auto& textureArray = systemsNC.getComponentArray<CTexture>();
    auto& texturesContainerArray = systemsNC.getComponentArray<CTexturesContainer>();

    if (!texturesContainerArray->hasData(loadedTextures))
    {
        return;
    }

    CTexturesContainer& container = texturesContainerArray->getData(loadedTextures);

    for (auto& [entity, sprite] : spriteArray->getAll())
    {
        if
            (
                !transformArray->hasData(entity) ||
                !textureArray->hasData(entity)
                )
        {
            continue;
        }

        CTexture& texture = textureArray->getData(entity);
        CTransform& transform = transformArray->getData(entity);

        sprite.body.emplace(container.map[texture.data]);
        sprite.body->setScale
        (
            {
                transform.width / sprite.body->getGlobalBounds().size.x,
                transform.height / sprite.body->getGlobalBounds().size.y
            }
        );
    }
}

void loadSoundEffects_Start(Entity soundEffects)
{
    if (!systemsNC.getComponentArray<CSoundEffectsContainer>()->hasData(soundEffects))
    {
        return;
    }

    CSoundEffectsContainer& container = systemsNC.getComponentArray<CSoundEffectsContainer>()->getData(soundEffects);

    container.sounds.emplace(SoundEffect::BONUS, sf::SoundBuffer(SOUND_EFFECTS_PATH "Bonus.wav"));
    container.sounds.emplace(SoundEffect::BUTTON, sf::SoundBuffer(SOUND_EFFECTS_PATH "Button.wav"));
    container.sounds.emplace(SoundEffect::CENTER, sf::SoundBuffer(SOUND_EFFECTS_PATH "Center.wav"));
    container.sounds.emplace(SoundEffect::FAIL, sf::SoundBuffer(SOUND_EFFECTS_PATH "Fail.wav"));
    container.sounds.emplace(SoundEffect::HIT, sf::SoundBuffer(SOUND_EFFECTS_PATH "Hit.wav"));
    container.sounds.emplace(SoundEffect::HOVER, sf::SoundBuffer(SOUND_EFFECTS_PATH "Hover.wav"));
}

void setSpriteOrigins_StartSystem()
{
    auto& originArray = systemsNC.getComponentArray<COrigin>();
    auto& spriteArray = systemsNC.getComponentArray<CSprite>();

    for (auto& [entity, sprite] : spriteArray->getAll())
    {
        if (!originArray->hasData(entity))
        {
            continue;
        }

        COrigin& origin = originArray->getData(entity);

        sprite.body->setOrigin
        (
            {
                origin.offsetX / sprite.body->getScale().x,
                origin.offsetY / sprite.body->getScale().y
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

void buttonClicks_UpdateSystem(sf::Vector2i mouseVector)
{
    auto& spriteArray = systemsNC.getComponentArray<CSprite>();
    auto& buttonArray = systemsNC.getComponentArray<CButton>();
    auto& originArray = systemsNC.getComponentArray<COrigin>();
    auto& transformArray = systemsNC.getComponentArray<CTransform>();
    auto& positionArray = systemsNC.getComponentArray<CPosition>();

    for (auto& [entity, button] : buttonArray->getAll())
    {
        if (!button.enabled)
        {
            continue;
        }

        // buttonArray must have a shape, origin, and text
        if 
        (
            originArray->hasData(entity) &&
            positionArray->hasData(entity) &&
            spriteArray->hasData(entity)
        )
        {
            ////std::cout << "button.top: " << button.top << "\n";
            ////std::cout << "button.left: " << button.left << "\n";
            COrigin& origin = originArray->getData(entity);
            CTransform& transform = transformArray->getData(entity);
            CPosition& position = positionArray->getData(entity);
            CSprite& sprite = spriteArray->getData(entity);

            if 
            (
                mouseVector.x > position.x - origin.offsetX &&
                mouseVector.x < position.x + transform.width - origin.offsetX &&
                mouseVector.y > position.y - origin.offsetY &&
                mouseVector.y < position.y + transform.height - origin.offsetY
            )
            {
                button.clickedTimer = button.clickedDuration;
            }
        }
    }
}
void button_Update
(
    sf::Vector2i mouseVector,
    DeltaTime dt
)
{
    auto& spriteArray = systemsNC.getComponentArray<CSprite>();
    auto& buttonArray = systemsNC.getComponentArray<CButton>();
    auto& originArray = systemsNC.getComponentArray<COrigin>();
    auto& textArray = systemsNC.getComponentArray<CText>();
    auto& nextSceneArray = systemsNC.getComponentArray<CNextScene>();
    auto& transformArray = systemsNC.getComponentArray<CTransform>();
    auto& positionArray = systemsNC.getComponentArray<CPosition>();

    for (auto& [entity, button] : buttonArray->getAll())
    {
        if (!button.enabled)
        {
            continue;
        }

        // buttonArray must have a shape, origin, and text
        if
        (
            originArray->hasData(entity) &&
            textArray->hasData(entity) &&
            positionArray->hasData(entity) &&
            spriteArray->hasData(entity)
        )
        {
            ////std::cout << "button.top: " << button.top << "\n";
            ////std::cout << "button.left: " << button.left << "\n";
            COrigin& origin = originArray->getData(entity);
            CText& text = textArray->getData(entity);
            CTransform& transform = transformArray->getData(entity);
            CPosition& position = positionArray->getData(entity);
            CSprite& sprite = spriteArray->getData(entity);


            if (button.clickedTimer <= 0)
            {
                sprite.body->setScale
                (
                    sf::Vector2f
                    (
                        DEFAULT_SCALE_X * (transform.width / sprite.body->getTexture().getSize().x),
                        DEFAULT_SCALE_Y * (transform.height / sprite.body->getTexture().getSize().y)
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
                button.clicked = false; // reset
            }
            else
            {
                button.clickedTimer -= dt;
                if (button.clickedTimer <= 0)
                {
                    button.clicked = true;
                    if (nextSceneArray->hasData(entity))
                    {
                        ////std::cout << "starting next scene." << "\n";
                        CNextScene& nextScene = nextSceneArray->getData(entity);
                        nextScene.active = true;
                    }
                }
            }

            // button hovering
            if
            (
                mouseVector.x > position.x - origin.offsetX &&
                mouseVector.x < position.x + transform.width - origin.offsetX &&
                mouseVector.y > position.y - origin.offsetY &&
                mouseVector.y < position.y + transform.height - origin.offsetY &&
                button.clickedTimer <= 0
            )
            {
                sprite.body->setScale
                (
                    sf::Vector2f
                    (
                        HOVER_SCALE_X * (transform.width / sprite.body->getTexture().getSize().x),
                        HOVER_SCALE_Y * (transform.height / sprite.body->getTexture().getSize().y)
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
            }

            // button clicking
            if (button.clickedTimer > 0)
            {
                sprite.body->setScale
                (
                    sf::Vector2f
                    (
                        CLICKED_SCALE_X * (transform.width / sprite.body->getTexture().getSize().x),
                        CLICKED_SCALE_Y * (transform.height / sprite.body->getTexture().getSize().y)
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

const float FILL_TIMER = 1.f;

const sf::Color SCORE_COLOR = sf::Color::White;
const sf::Color FAIL_COLOR = sf::Color::Red;

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
    CFeed& feed = systemsNC.getComponentArray<CFeed>()->getData(scoreFeed);

    //std::cout << "x:" << indicPos.x << "\n";
    //std::cout << "min:" << hitPos.x - (hitTrans.width / 2.f) << " max:" << hitPos.x + (hitTrans.width / 2.f) << "\n\n";

    if 
    (
        indicPos.x < hitPos.x - (hitTrans.width / 2.f) ||
        indicPos.x > hitPos.x + (hitTrans.width / 2.f)
    )
    {
        makeSound(SoundEffect::FAIL);

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
        score.unaccounted = 0;
        score.fillTimer = 0;

        hit.spawned = false;

        feed.feed.push
        (
            makeLog
            (
                {
                    50,
                    50
                },
                font,
                FAIL_COLOR,
                "FAIL!",
                LOG_TIMER,
                FADE_TIMER
            )
        );

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


    score.unaccounted += HIT_SCORE + (HIT_SCORE * dist);
    makeSound(SoundEffect::HIT);
    makeSound(SoundEffect::CENTER, 1.f + dist);

    // hit score
    feed.feed.push
    (
        makeLog
        (
            {
                50,
                50
            },
            font,
            SCORE_COLOR,
            "+" + std::to_string(HIT_SCORE) + " SCORE",
            LOG_TIMER,
            FADE_TIMER
        )
    );
    // bonus hitscore
    feed.feed.push
    (
        makeLog
        (
            {
                50,
                50
            },
            font,
            SCORE_COLOR,
            "+" + std::to_string((int)(HIT_SCORE * dist)) + " CENTER",
            LOG_TIMER,
            FADE_TIMER
        )
    );

    if (score.bounces < 2)
    {
        makeSound(SoundEffect::BONUS);
        score.unaccounted += BOUNCE_BONUS;
        // bonus bounce
        feed.feed.push
        (
            makeLog
            (
                {
                    50,
                    50
                },
                font,
                SCORE_COLOR,
                "+" + std::to_string(BOUNCE_BONUS) + " BONUS",
                LOG_TIMER,
                FADE_TIMER
            )
        );
    }

    feed.positionsSet = false;

    // resets the fill timer when not already ticking
    if (score.fillTimer <= 0.f)
    {
        score.fillTimer = FILL_TIMER;
    }

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

const float HITBOX_HEIGHT = 11.5f;

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
    CSprite& hitSprite = systemsNC.getComponentArray<CSprite>()->getData(hitbox);
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

    hitTrans.width = spawnSize;
    hitTrans.height = HITBOX_HEIGHT;

    hirOrig.offsetX = hitTrans.width / 2.f;
    hirOrig.offsetY = HITBOX_HEIGHT / 2.f;

    //std::cout << "slidTrans.height: " << slidTrans.height << "\n";
    //std::cout << "TexX: " << hitSprite.body->getTexture().getSize().x << "\n";
    //std::cout << "TexY: " << hitSprite.body->getTexture().getSize().y << "\n";

    hitSprite.body->setScale
    (
        {
            spawnSize / hitSprite.body->getTexture().getSize().x,
            HITBOX_HEIGHT / hitSprite.body->getTexture().getSize().y
        }
    );

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
    Entity hitbox,
    DeltaTime dt
)
{
    CText& scoreText = systemsNC.getComponentArray<CText>()->getData(score);
    CScore& hitScore = systemsNC.getComponentArray<CScore>()->getData(hitbox);

    scoreText.box->setString("Score: " + std::to_string(hitScore.count));


    if (hitScore.fillTimer <= 0.f)
    {
        return;
    }

    float fillPercent = 1.f - inverseLerp_Auxiliary
    (
        0.f,
        FILL_TIMER,
        hitScore.fillTimer
    );

    int fillAdd = std::ceil(hitScore.unaccounted * fillPercent);

    //std::cout << "hitScore.unaccounted: " << hitScore.unaccounted << "\n";
    //std::cout << "fillAdd: " << fillAdd << "\n";

    hitScore.count += fillAdd;
    hitScore.unaccounted -= fillAdd;

    hitScore.fillTimer -= dt;
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

void doFeed
(
    sf::Vector2f startPos,
    DeltaTime dt,
    Entity feed
)
{
    CFeed& feedScore = systemsNC.getComponentArray<CFeed>()->getData(feed);
    
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

    CLog& scoreLog = systemsNC.getComponentArray<CLog>()->getData(feedScore.feed.front());
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
void playSounds(Entity soundEffects)
{
    auto& soundsArray = systemsNC.getComponentArray<CSound>();
    if (soundsArray->getAll().empty())
    {
        //std::cout << "test";
        return;
    }

    CSoundEffectsContainer& container = systemsNC.getComponentArray<CSoundEffectsContainer>()->getData(soundEffects);

    for (auto& [entity, sound] : soundsArray->getAll())
    {
        //sprite.body.emplace(container.map[texture.data]);
        if (!sound.sound.has_value())
        {
            sound.sound.emplace(container.sounds[sound.type]);
        }

        if 
        (
            sound.sound->getStatus() == sf::SoundSource::Status::Stopped &&
            sound.played
        )
        {
            systemsNC.addComponent
            (
                entity,
                CDelete{}
            );
            continue;
        }
        else if (!sound.played)
        {
            sound.sound->setPitch(sound.pitch);
            sound.sound->play();
            sound.played = true;
        }

    }
}
void delete_UpdateSystem(DeltaTime dt)
{
    auto& deleteArray = systemsNC.getComponentArray<CDelete>();

    if (deleteArray->getAll().empty())
    {
        return;
    }

    std::vector<Entity> toBeDeleted;

    for (auto& [entity, deleteComponent] : deleteArray->getAll())
    {
        if (deleteComponent.timer <= 0.f)
        {
            toBeDeleted.emplace_back(entity);
            continue;
        }

        deleteComponent.timer -= dt;
    }

    for (Entity entity : toBeDeleted)
    {
        systemsNC.deleteEntity(entity);
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
void renderSystem
(
    sf::RenderWindow& window,
    std::queue<Entity>& renderQueue
)

{
    auto& spriteArray = systemsNC.getComponentArray<CSprite>();
    auto& positionArray = systemsNC.getComponentArray<CPosition>();
    auto& textArray = systemsNC.getComponentArray<CText>();

    while (!renderQueue.empty())
    {
        Entity& popped = renderQueue.front();
        ////std::cout << "popped: " << popped << "\n";

        if
            (
                !positionArray->hasData(popped)
                )
        {
            // this means the entity does not have a position component
            continue;
        }

        CPosition& pos = positionArray->getData(popped);

        if (spriteArray->hasData(popped))
        {
            CSprite& sprite = spriteArray->getData(popped);

            sprite.body->setPosition
            (
                {
                    pos.x,
                    pos.y
                }
            );
            window.draw(sprite.body.value());
        }

        if (textArray->hasData(popped))
        {
            CText& text = textArray->getData(popped);

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