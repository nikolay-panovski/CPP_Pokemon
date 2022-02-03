#pragma once

#include <SFML/Graphics.hpp>
#include <cstdio>
#include <memory>

typedef sf::Vector2f Vec2f;

#include "Character.hpp"
#include "HighscoreList.hpp"
#include "Scene.hpp"
#include "SceneHandler.hpp"
#include "TextObject.hpp"
#include "SpriteObject.hpp"
#include "SpriteArray.hpp"
#include "Button.hpp"


#define WINDOW_NAME "Pokeys"
#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720
#define DEFAULT_BTN_SIZE Vec2f(200.0f, 50.0f)
#define PADDING_BIG 50
#define PADDING_SMALL 25
#define START_SCENE mainMenu


// !16KB of stack used by 1 function result in a warning. turn over to pointers.
int main(int argCount, char* argVals[]) {
    // ---- GLOBAL VARS - FONT ----
    sf::Font font;
    font.loadFromFile("Lato-Regular.ttf");
    // ---- END GLOBAL VARS ----

    // ---- WINDOW CREATION ----
	sf::RenderWindow window;

    if (argCount > 2) {
        window.create(sf::VideoMode(std::stoi(argVals[1]), std::stoi(argVals[2])), WINDOW_NAME);
    }
    else if (argCount > 1) {
        window.create(sf::VideoMode(std::stoi(argVals[1]), DEFAULT_HEIGHT), WINDOW_NAME);
    }
    else {
        window.create(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), WINDOW_NAME);
    }
    // ---- END WINDOW CREATION ----

    // ---- IMPORTANT GLOBAL OBJECTS (SCENES ETC.) ----

    // TO RECAP: stack vs heap allocated memory
    std::unique_ptr<SceneHandler> handler = std::make_unique<SceneHandler>();

    std::unique_ptr<SpriteObject> background = std::make_unique<SpriteObject>(Vec2f(0.0f, 0.0f), "Assets/battle-background-sunny-hillsx4.png");

    // leaving this unpointered because of list-initialization (might have to refactor huge chunks to accommodate)
    SpriteArray charSprites{Vec2f(PADDING_BIG * 2.0f, PADDING_BIG * 2.0f),
                            {"Assets/rpgcritters2_1.png", "Assets/rpgcritters2_2.png", "Assets/rpgcritters2_3.png",
                            "Assets/rpgcritters2_4.png", "Assets/rpgcritters2_5.png", "Assets/rpgcritters2_6.png",
                            "Assets/rpgcritters2_7.png", "Assets/rpgcritters2_8.png", "Assets/rpgcritters2_9.png",
                            "Assets/rpgcritters2_10.png"} };
    
    std::unique_ptr<Scene> mainMenu = std::make_unique<Scene>("menuScene");
    std::unique_ptr<Scene> charMenu = std::make_unique<Scene>("charCreateScene");
    std::unique_ptr<Scene> fightScreen = std::make_unique<Scene>("fightScene");

    std::unique_ptr<Character> player = std::make_unique<Character>(Vec2f(PADDING_BIG, window.getSize().y * 0.5f),
                    font, "Player", "Assets/rpgcritters2_1.png", 8, true);
    std::unique_ptr<Character> enemy = std::make_unique<Character>(Vec2f(window.getSize().x - PADDING_BIG, window.getSize().y * 0.5f),
                    font, "Enemy", "Assets/rpgcritters2_4.png", 6, false);
    // ---- END GLOBAL OBJECTS ----

    // ---- SCENE 1 OBJECTS ----

    // unpointered?
    std::unique_ptr<HighscoreList> scores = std::make_unique<HighscoreList>(Vec2f(window.getSize().x * 0.125f, window.getSize().y * 0.5f), font);

    std::unique_ptr<Button> playButton = std::make_unique<Button>
        (Vec2f(window.getSize().x - DEFAULT_BTN_SIZE.x - PADDING_BIG,
               window.getSize().y * 0.5f - DEFAULT_BTN_SIZE.y - PADDING_SMALL),
               font, "Play", "Assets/blue_button00.png");

    playButton->SetButtonAction([&playButton, &charMenu, &handler]() {
        playButton->ToggleActive();
        handler->AddScene(*charMenu);
        });

    std::unique_ptr<Button> loadButton = std::make_unique<Button>
        (Vec2f(playButton->GetPosition().x, playButton->GetPosition().y + DEFAULT_BTN_SIZE.y + PADDING_BIG),
               font, "Load Game", "Assets/blue_button00.png");

    loadButton->SetButtonAction([&scores]() {
        
        });

    std::unique_ptr<Button> eraseButton = std::make_unique<Button>
        (Vec2f(loadButton->GetPosition().x, loadButton->GetPosition().y + DEFAULT_BTN_SIZE.y + PADDING_BIG),
               font, "Erase Data", "Assets/blue_button00.png");

    eraseButton->SetButtonAction([&scores]() {
        remove("highscore.cmgt");
        scores->GenerateRankList();
        });

    std::unique_ptr<Button> quitButton = std::make_unique<Button>
        (Vec2f(eraseButton->GetPosition().x, eraseButton->GetPosition().y + DEFAULT_BTN_SIZE.y + PADDING_BIG),
               font, "Quit", "Assets/blue_button00.png");

    quitButton->SetButtonAction([&window]() {
        window.close();
        });
    // ---- END SCENE 1 ----


    // ---- SCENE 2 OBJECTS ----
    std::unique_ptr<Button> sprArrayDecButton = std::make_unique<Button>
        (Vec2f(charSprites.GetPosition().x - PADDING_BIG, charSprites.GetPosition().y),
               font, "", "Assets/grey_arrowDownGrey.png");

    sprArrayDecButton->SetButtonAction([&charSprites]() {
        charSprites.DecrementActiveSprite();
        });

    std::unique_ptr<Button> sprArrayIncButton = std::make_unique<Button>
        (Vec2f(charSprites.GetPosition().x + PADDING_BIG, charSprites.GetPosition().y),
               font, "", "Assets/grey_arrowUpGrey.png");

    sprArrayIncButton->SetButtonAction([&charSprites]() {
        charSprites.IncrementActiveSprite();
        });

    std::unique_ptr<TextObject> totalPoints = std::make_unique<TextObject>
        (Vec2f(window.getSize().x * 0.5f, window.getSize().y * 0.5f - PADDING_BIG),
               font, "Total points: " + std::to_string(player->GetStat(Character::CharStat::SkillPts)));

    std::unique_ptr<TextObject> strPoints = std::make_unique<TextObject>
        (Vec2f(totalPoints->GetPosition().x - PADDING_BIG * 4, totalPoints->GetPosition().y + PADDING_BIG),
               font, std::to_string(player->GetStat(Character::CharStat::StrPts)));

    std::unique_ptr<TextObject> strLabel = std::make_unique<TextObject>
        (Vec2f(strPoints->GetPosition().x - PADDING_BIG, strPoints->GetPosition().y + PADDING_BIG),
            font, "Strength");

    std::unique_ptr<Button> strDecButton = std::make_unique<Button>
        (Vec2f(strPoints->GetPosition().x - PADDING_BIG, strPoints->GetPosition().y),
               font, "", "Assets/grey_arrowDownGrey.png");

    strDecButton->SetButtonAction([&player, &totalPoints, &strPoints]() {
        player->DecrementStat(Character::CharStat::StrPts);
        totalPoints->SetText("Total points: " + std::to_string(player->GetStat(Character::CharStat::SkillPts)));
        strPoints->SetText(std::to_string(player->GetStat(Character::CharStat::StrPts)));
        });

    std::unique_ptr<Button> strIncButton = std::make_unique<Button>
        (Vec2f(strPoints->GetPosition().x + PADDING_BIG, strPoints->GetPosition().y),
               font, "", "Assets/grey_arrowUpGrey.png");

    strIncButton->SetButtonAction([&player, &totalPoints, &strPoints]() {
        player->IncrementStat(Character::CharStat::StrPts);
        totalPoints->SetText("Total points: " + std::to_string(player->GetStat(Character::CharStat::SkillPts)));
        strPoints->SetText(std::to_string(player->GetStat(Character::CharStat::StrPts)));
        });

    std::unique_ptr<TextObject> agilPoints = std::make_unique<TextObject>
        (Vec2f(totalPoints->GetPosition().x, totalPoints->GetPosition().y + PADDING_BIG),
               font, std::to_string(player->GetStat(Character::CharStat::AgilPts)));

    std::unique_ptr<TextObject> agilLabel = std::make_unique<TextObject>
        (Vec2f(agilPoints->GetPosition().x - PADDING_BIG, agilPoints->GetPosition().y + PADDING_BIG),
            font, "Agility");

    std::unique_ptr<Button> agilDecButton = std::make_unique<Button>
        (Vec2f(agilPoints->GetPosition().x - PADDING_BIG, agilPoints->GetPosition().y),
               font, "", "Assets/grey_arrowDownGrey.png");

    agilDecButton->SetButtonAction([&player, &totalPoints, &agilPoints]() {
        player->DecrementStat(Character::CharStat::AgilPts);
        totalPoints->SetText("Total points: " + std::to_string(player->GetStat(Character::CharStat::SkillPts)));
        agilPoints->SetText(std::to_string(player->GetStat(Character::CharStat::AgilPts)));
        });

    std::unique_ptr<Button> agilIncButton = std::make_unique<Button>
        (Vec2f(agilPoints->GetPosition().x + PADDING_BIG, agilPoints->GetPosition().y),
               font, "", "Assets/grey_arrowUpGrey.png");

    agilIncButton->SetButtonAction([&player, &totalPoints, &agilPoints]() {
        player->IncrementStat(Character::CharStat::AgilPts);
        totalPoints->SetText("Total points: " + std::to_string(player->GetStat(Character::CharStat::SkillPts)));
        agilPoints->SetText(std::to_string(player->GetStat(Character::CharStat::AgilPts)));
        });

    std::unique_ptr<TextObject> witsPoints = std::make_unique<TextObject>
        (Vec2f(totalPoints->GetPosition().x + PADDING_BIG * 4, totalPoints->GetPosition().y + PADDING_BIG),
               font, std::to_string(player->GetStat(Character::CharStat::WitsPts)));

    std::unique_ptr<TextObject> witsLabel = std::make_unique<TextObject>
        (Vec2f(witsPoints->GetPosition().x - PADDING_BIG, witsPoints->GetPosition().y + PADDING_BIG),
            font, "Wits");

    std::unique_ptr<Button> witsDecButton = std::make_unique<Button>
        (Vec2f(witsPoints->GetPosition().x - PADDING_BIG, witsPoints->GetPosition().y),
               font, "", "Assets/grey_arrowDownGrey.png");

    witsDecButton->SetButtonAction([&player, &totalPoints, &witsPoints]() {
        player->DecrementStat(Character::CharStat::WitsPts);
        totalPoints->SetText("Total points: " + std::to_string(player->GetStat(Character::CharStat::SkillPts)));
        witsPoints->SetText(std::to_string(player->GetStat(Character::CharStat::WitsPts)));
        });

    std::unique_ptr<Button> witsIncButton = std::make_unique<Button>
        (Vec2f(witsPoints->GetPosition().x + PADDING_BIG, witsPoints->GetPosition().y),
               font, "", "Assets/grey_arrowUpGrey.png");

    witsIncButton->SetButtonAction([&player, &totalPoints, &witsPoints]() {
        player->IncrementStat(Character::CharStat::WitsPts);
        totalPoints->SetText("Total points: " + std::to_string(player->GetStat(Character::CharStat::SkillPts)));
        witsPoints->SetText(std::to_string(player->GetStat(Character::CharStat::WitsPts)));
        });

    std::unique_ptr<Button> randButton = std::make_unique<Button>
        (Vec2f(window.getSize().x - DEFAULT_BTN_SIZE.x - PADDING_BIG,
               DEFAULT_BTN_SIZE.y - PADDING_SMALL),
               font, "Randomize", "Assets/blue_button00.png");

    randButton->SetButtonAction([&player, &totalPoints, &strPoints, &agilPoints, &witsPoints]() {
        player->ResetStats();
        player->RandomizeStats();
        totalPoints->SetText("Total points: " + std::to_string(player->GetStat(Character::CharStat::SkillPts)));
        strPoints->SetText(std::to_string(player->GetStat(Character::CharStat::StrPts)));
        agilPoints->SetText(std::to_string(player->GetStat(Character::CharStat::AgilPts)));
        witsPoints->SetText(std::to_string(player->GetStat(Character::CharStat::WitsPts)));
        //handler->AddScene(mainMenu);
        });

    std::unique_ptr<TextObject> errorText = std::make_unique<TextObject>
        (Vec2f(window.getSize().x * 0.5f, window.getSize().y * 0.5f + PADDING_BIG * 4),
               font, "");

    std::unique_ptr<Button> fightButton = std::make_unique<Button>
        (Vec2f(window.getSize().x - DEFAULT_BTN_SIZE.x - PADDING_BIG,
               window.getSize().y - DEFAULT_BTN_SIZE.y - PADDING_SMALL),
               font, "Fight", "Assets/blue_button00.png");

    fightButton->SetButtonAction([&playButton, &player, &enemy, &charMenu, &handler, &errorText, &fightScreen]() {
        playButton->ToggleActive();
        //handler->PopCurrentScene();
        
        if (player->VerifyMinStats()) {
            charMenu->RemoveGameObject(*errorText);
            handler->AddScene(*fightScreen);
            player->CompareFightStartAgil(*enemy);
            player->VerifyStatsFromCharPts();
            enemy->VerifyStatsFromCharPts();
        }
        else {
            charMenu->AddGameObject(*errorText);
            errorText->SetText("Strength and Wits points cannot be 0, redistribute!");
        }
        
        });

    // ---- END SCENE 2 ----

    // ---- SCENE 3 (UNIQUE) OBJECTS ----
    std::unique_ptr<TextObject> playerActiveLabel = std::make_unique<TextObject>
        (Vec2f(player->GetPosition().x - PADDING_BIG, player->GetPosition().y + PADDING_BIG * 2),
            font, "Active: " + std::to_string(player->hasCurrentTurn));

    std::unique_ptr<TextObject> enemyActiveLabel = std::make_unique<TextObject>
        (Vec2f(enemy->GetPosition().x - PADDING_BIG, enemy->GetPosition().y + PADDING_BIG * 2),
            font, "Active: " + std::to_string(enemy->hasCurrentTurn));

    std::unique_ptr<Button> updateActiveInfoButton = std::make_unique<Button>
        (Vec2f(DEFAULT_BTN_SIZE.x,
            DEFAULT_BTN_SIZE.y + PADDING_BIG * 2),
            font, "UpdateActiveText", "Assets/blue_button00.png");

    updateActiveInfoButton->SetButtonAction([&player, &enemy, &playerActiveLabel, &enemyActiveLabel]() {
        playerActiveLabel->SetText("Active: " + std::to_string(player->hasCurrentTurn));
        enemyActiveLabel->SetText("Active: " + std::to_string(enemy->hasCurrentTurn));
        });

    std::unique_ptr<Button> attackButton = std::make_unique<Button>
        (Vec2f(DEFAULT_BTN_SIZE.x,
            window.getSize().y - DEFAULT_BTN_SIZE.y - PADDING_BIG * 2),
            font, "Attack", "Assets/blue_button00.png");

    attackButton->SetButtonAction([&player, &enemy]() {
        if (player->hasCurrentTurn) {
            player->Attack(*enemy);
        }
        else enemy->Attack(*player);

        player->ToggleActiveTurn();
        enemy->ToggleActiveTurn();
        });

    std::unique_ptr<Button> healButton = std::make_unique<Button>
        (Vec2f(attackButton->GetPosition().x + PADDING_BIG * 4, attackButton->GetPosition().y),
            font, "Heal", "Assets/blue_button00.png");

    healButton->SetButtonAction([&player, &enemy]() {
        if (player->hasCurrentTurn) {
            player->Heal();
        }
        // else... how does enemy react (automatically)?

        player->ToggleActiveTurn();
        enemy->ToggleActiveTurn();
        });

    std::unique_ptr<Button> prepareButton = std::make_unique<Button>
        (Vec2f(healButton->GetPosition().x + PADDING_BIG * 4, healButton->GetPosition().y),
            font, "Prepare", "Assets/blue_button00.png");

    prepareButton->SetButtonAction([&player, &enemy]() {
        if (player->hasCurrentTurn) {
            enemy->wasAttackedLastTurn = false;
            // display/update text
        }
        else {
            player->wasAttackedLastTurn = false;
            // display/update text
        }
        });

    std::unique_ptr<Button> castMagicButton = std::make_unique<Button>
        (Vec2f(prepareButton->GetPosition().x + PADDING_BIG * 4, prepareButton->GetPosition().y),
            font, "Cast Magic", "Assets/blue_button00.png");

    castMagicButton->SetButtonAction([&player, &enemy]() {
        if (player->hasCurrentTurn) {
            player->CastMagic(*enemy);
        }
        else {
            enemy->CastMagic(*player);
        }
        });

    std::unique_ptr<Button> quitBattleButton = std::make_unique<Button>
        (Vec2f(window.getSize().x - PADDING_BIG * 4, window.getSize().y - PADDING_SMALL * 4),
            font, "Quit Battle", "Assets/blue_button00.png");

    quitBattleButton->SetButtonAction([&attackButton, &charMenu, &handler]() {

        });

    // ---- END SCENE 3 ----


    // ---- ADD SCENES TO HANDLER / OBJECTS TO SCENE ----
    handler->AddScene(*START_SCENE);

    
    mainMenu->AddGameObject(*background);

    mainMenu->AddGameObject(*scores);
    mainMenu->AddGameObject(*playButton);
    mainMenu->AddGameObject(*loadButton);
    mainMenu->AddGameObject(*eraseButton);
    mainMenu->AddGameObject(*quitButton);

    charMenu->AddGameObject(*background);
    //charMenu->AddGameObject(sprArrayDecButton);
    //charMenu->AddGameObject(sprArrayIncButton);
    charMenu->AddGameObject(*player);
    //charMenu->AddGameObject(charSprites);
    charMenu->AddGameObject(*totalPoints);
    charMenu->AddGameObject(*strPoints);
    charMenu->AddGameObject(*strLabel);
    charMenu->AddGameObject(*strDecButton);
    charMenu->AddGameObject(*strIncButton);
    charMenu->AddGameObject(*agilPoints);
    charMenu->AddGameObject(*agilLabel);
    charMenu->AddGameObject(*agilDecButton);
    charMenu->AddGameObject(*agilIncButton);
    charMenu->AddGameObject(*witsPoints);
    charMenu->AddGameObject(*witsLabel);
    charMenu->AddGameObject(*witsDecButton);
    charMenu->AddGameObject(*witsIncButton);
    charMenu->AddGameObject(*randButton);
    charMenu->AddGameObject(*errorText);
    charMenu->AddGameObject(*fightButton);

    fightScreen->AddGameObject(*background);
    fightScreen->AddGameObject(*player);
    fightScreen->AddGameObject(*enemy);
    fightScreen->AddGameObject(*playerActiveLabel);     // debug
    fightScreen->AddGameObject(*enemyActiveLabel);       // debug
    fightScreen->AddGameObject(*updateActiveInfoButton);       // debug
    fightScreen->AddGameObject(*attackButton);
    fightScreen->AddGameObject(*healButton);
    fightScreen->AddGameObject(*prepareButton);
    fightScreen->AddGameObject(*castMagicButton);
    fightScreen->AddGameObject(*quitBattleButton);

    // ---- END ADD ----

    // ---- WINDOW LOOP ----
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else {
                handler->currentScene().HandleEvent(event, window);
            }
        }

        window.clear();
        handler->RenderCurrentScene(window);
        window.display();
    }

	return 0;
}