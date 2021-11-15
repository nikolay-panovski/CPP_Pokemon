#pragma once

#include <SFML/Graphics.hpp>
#include <cstdio>

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
typedef sf::Vector2f Vec2f;

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
    SceneHandler handler;

    SpriteObject background(Vec2f(0.0f, 0.0f), "Assets/battle-background-sunny-hillsx4.png");

    SpriteArray charSprites("Assets/rpgcritters2_1.png", "Assets/rpgcritters2_2.png", "Assets/rpgcritters2_3.png",
                            "Assets/rpgcritters2_4.png", "Assets/rpgcritters2_5.png", "Assets/rpgcritters2_6.png",
                            "Assets/rpgcritters2_7.png", "Assets/rpgcritters2_8.png", "Assets/rpgcritters2_9.png",
                            "Assets/rpgcritters2_10.png");
    
    Scene mainMenu("menuScene");
    Scene charMenu("charCreateScene");

    Character player(Vec2f(PADDING_BIG, PADDING_BIG), font, "Player", "Assets/rpgcritters2_1.png", 8, true);
    // ---- END GLOBAL OBJECTS ----

    // ---- SCENE 1 OBJECTS ----
    HighscoreList scores(Vec2f(window.getSize().x * 0.125f, window.getSize().y * 0.5f), font);

    Button playButton(Vec2f(window.getSize().x - DEFAULT_BTN_SIZE.x - PADDING_BIG,
                            window.getSize().y * 0.5f - DEFAULT_BTN_SIZE.y - PADDING_SMALL),
                      font, "Play", "Assets/blue_button00.png");

    playButton.SetButtonAction([&playButton, &charMenu, &handler]() {
        playButton.ToggleActive();
        handler.AddScene(charMenu);
        });

    Button loadButton(Vec2f(playButton.GetPosition().x, playButton.GetPosition().y + DEFAULT_BTN_SIZE.y + PADDING_BIG),
        font, "Load Game", "Assets/blue_button00.png");

    loadButton.SetButtonAction([&scores]() {
        
        });

    Button eraseButton(Vec2f(loadButton.GetPosition().x, loadButton.GetPosition().y + DEFAULT_BTN_SIZE.y + PADDING_BIG),
        font, "Erase Data", "Assets/blue_button00.png");

    eraseButton.SetButtonAction([&scores]() {
        remove("highscore.cmgt");
        scores.GenerateRankList();
        });

    Button quitButton(Vec2f(eraseButton.GetPosition().x, eraseButton.GetPosition().y + DEFAULT_BTN_SIZE.y + PADDING_BIG),
        font, "Quit", "Assets/blue_button00.png");

    quitButton.SetButtonAction([&window]() {
        window.close();
        });
    // ---- END SCENE 1 ----


    // ---- SCENE 2 OBJECTS ----
    

    TextObject totalPoints(Vec2f(window.getSize().x * 0.5f, window.getSize().y * 0.5f - PADDING_BIG),
                           font, "Total points: " + std::to_string(player.GetStat(Character::CharStat::SkillPts)));

    TextObject strPoints(Vec2f(totalPoints.GetPosition().x - PADDING_BIG * 4, totalPoints.GetPosition().y + PADDING_BIG),
                         font, std::to_string(player.GetStat(Character::CharStat::StrPts)));

    Button strDecButton(Vec2f(strPoints.GetPosition().x - PADDING_BIG, strPoints.GetPosition().y),
                        font, "", "Assets/grey_arrowDownGrey.png");

    strDecButton.SetButtonAction([&player, &totalPoints, &strPoints]() {
        player.DecrementStat(Character::CharStat::StrPts);
        totalPoints.SetText("Total points: " + std::to_string(player.GetStat(Character::CharStat::SkillPts)));
        strPoints.SetText(std::to_string(player.GetStat(Character::CharStat::StrPts)));
        });

    Button strIncButton(Vec2f(strPoints.GetPosition().x + PADDING_BIG, strPoints.GetPosition().y),
                              font, "", "Assets/grey_arrowUpGrey.png");

    strIncButton.SetButtonAction([&player, &totalPoints, &strPoints]() {
        player.IncrementStat(Character::CharStat::StrPts);
        totalPoints.SetText("Total points: " + std::to_string(player.GetStat(Character::CharStat::SkillPts)));
        strPoints.SetText(std::to_string(player.GetStat(Character::CharStat::StrPts)));
        });

    TextObject agilPoints(Vec2f(totalPoints.GetPosition().x, totalPoints.GetPosition().y + PADDING_BIG),
                          font, std::to_string(player.GetStat(Character::CharStat::AgilPts)));

    Button agilDecButton(Vec2f(agilPoints.GetPosition().x - PADDING_BIG, agilPoints.GetPosition().y),
        font, "", "Assets/grey_arrowDownGrey.png");

    agilDecButton.SetButtonAction([&player, &totalPoints, &agilPoints]() {
        player.DecrementStat(Character::CharStat::AgilPts);
        totalPoints.SetText("Total points: " + std::to_string(player.GetStat(Character::CharStat::SkillPts)));
        agilPoints.SetText(std::to_string(player.GetStat(Character::CharStat::AgilPts)));
        });

    Button agilIncButton(Vec2f(agilPoints.GetPosition().x + PADDING_BIG, agilPoints.GetPosition().y),
        font, "", "Assets/grey_arrowUpGrey.png");

    agilIncButton.SetButtonAction([&player, &totalPoints, &agilPoints]() {
        player.IncrementStat(Character::CharStat::AgilPts);
        totalPoints.SetText("Total points: " + std::to_string(player.GetStat(Character::CharStat::SkillPts)));
        agilPoints.SetText(std::to_string(player.GetStat(Character::CharStat::AgilPts)));
        });

    TextObject witsPoints(Vec2f(totalPoints.GetPosition().x + PADDING_BIG * 4, totalPoints.GetPosition().y + PADDING_BIG),
                          font, std::to_string(player.GetStat(Character::CharStat::WitsPts)));

    Button witsDecButton(Vec2f(witsPoints.GetPosition().x - PADDING_BIG, witsPoints.GetPosition().y),
        font, "", "Assets/grey_arrowDownGrey.png");

    witsDecButton.SetButtonAction([&player, &totalPoints, &witsPoints]() {
        player.DecrementStat(Character::CharStat::WitsPts);
        totalPoints.SetText("Total points: " + std::to_string(player.GetStat(Character::CharStat::SkillPts)));
        witsPoints.SetText(std::to_string(player.GetStat(Character::CharStat::WitsPts)));
        });

    Button witsIncButton(Vec2f(witsPoints.GetPosition().x + PADDING_BIG, witsPoints.GetPosition().y),
        font, "", "Assets/grey_arrowUpGrey.png");

    witsIncButton.SetButtonAction([&player, &totalPoints, &witsPoints]() {
        player.IncrementStat(Character::CharStat::WitsPts);
        totalPoints.SetText("Total points: " + std::to_string(player.GetStat(Character::CharStat::SkillPts)));
        witsPoints.SetText(std::to_string(player.GetStat(Character::CharStat::WitsPts)));
        });

    Button randButton(Vec2f(window.getSize().x - DEFAULT_BTN_SIZE.x - PADDING_BIG,
        DEFAULT_BTN_SIZE.y - PADDING_SMALL),
        font, "Randomize", "Assets/blue_button00.png");

    randButton.SetButtonAction([&player, &totalPoints, &strPoints, &agilPoints, &witsPoints]() {
        player.ResetStats();
        player.RandomizeStats();
        totalPoints.SetText("Total points: " + std::to_string(player.GetStat(Character::CharStat::SkillPts)));
        strPoints.SetText(std::to_string(player.GetStat(Character::CharStat::StrPts)));
        agilPoints.SetText(std::to_string(player.GetStat(Character::CharStat::AgilPts)));
        witsPoints.SetText(std::to_string(player.GetStat(Character::CharStat::WitsPts)));
        //handler.AddScene(mainMenu);
        });

    Button fightButton(Vec2f(window.getSize().x - DEFAULT_BTN_SIZE.x - PADDING_BIG,
                             window.getSize().y - DEFAULT_BTN_SIZE.y - PADDING_SMALL),
                       font, "Play", "Assets/blue_button00.png");

    fightButton.SetButtonAction([&playButton, &window, &mainMenu, &handler]() {
        playButton.ToggleActive();
        handler.PopCurrentScene();
        //handler.AddScene(mainMenu);
        });

    // ---- END SCENE 2 ----


    // ---- ADD SCENES TO HANDLER / OBJECTS TO SCENE ----
    handler.AddScene(START_SCENE);

    
    mainMenu.AddGameObject(background);

    mainMenu.AddGameObject(scores);
    mainMenu.AddGameObject(playButton);
    mainMenu.AddGameObject(loadButton);
    mainMenu.AddGameObject(eraseButton);
    mainMenu.AddGameObject(quitButton);

    charMenu.AddGameObject(background);
    charMenu.AddGameObject(player);
    charMenu.AddGameObject(totalPoints);
    charMenu.AddGameObject(strPoints);
    charMenu.AddGameObject(strDecButton);
    charMenu.AddGameObject(strIncButton);
    charMenu.AddGameObject(agilPoints);
    charMenu.AddGameObject(agilDecButton);
    charMenu.AddGameObject(agilIncButton);
    charMenu.AddGameObject(witsPoints);
    charMenu.AddGameObject(witsDecButton);
    charMenu.AddGameObject(witsIncButton);
    charMenu.AddGameObject(randButton);
    charMenu.AddGameObject(fightButton);

    // ---- END ADD ----

    // ---- WINDOW LOOP ----
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else {
                handler.currentScene().HandleEvent(event, window);
            }
        }

        window.clear();
        handler.RenderCurrentScene(window);
        window.display();
    }

	return 0;
}