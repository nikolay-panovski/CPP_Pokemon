#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "HighscoreList.hpp"

HighscoreList::HighscoreList(Vec2f startPosition, sf::Font& startFont) :
    GameObject(), font(startFont) {
    this->SetPosition(startPosition);

    std::ifstream myfileRead("highscore.cmgt");
    if (!myfileRead.fail()) {
        std::string line;

        for (int i = 0; i < this->maxSize; i++) {
            std::getline(myfileRead, line);
            highscores.push_back(std::stoi(line));
            std::getline(myfileRead, line);
            names.push_back(line);
        }

        // unhandled middle case - file exists and is readable and some games were played, but not at least 5
        // (so some scores are still default 0 - fill them in properly!)
        
        myfileRead.close();
    }

    else {
        // file does not yet exist OR failed to open etc. - no scores for you!
        for (int i = 0; i < this->maxSize; i++) {
            highscores.push_back(0);
            names.push_back("Player");
        }
    }

    this->GenerateRankList();

    for (int i = 0; i < this->maxSize; i++) {
        printf("rankTexts[%i] address: %p\n", i, rankTexts[i]);
        printf("rankTexts[%i] text value: %s\n", i, rankTexts[i]->GetText().c_str());
    }

    
}

HighscoreList::~HighscoreList() {
    for (unsigned int i = 0; i < rankTexts.size(); i++) {
        delete rankTexts[i];
    }
    rankTexts.clear();
}

Vec2f HighscoreList::GetPosition(void) const {
    return this->position;
}

void HighscoreList::SetPosition(Vec2f newPosition) {
    this->position = newPosition;
}

void HighscoreList::Render(sf::RenderWindow& window) {
    for (int i = 0; i < this->maxSize; i++) {
        rankTexts[i]->Render(window);
    }
}

void HighscoreList::TryAddHighscore(int newScore) {
	for (unsigned int i = 0; i < highscores.size(); i++) {
		if (newScore > highscores[i]) {
			highscores.emplace(highscores.begin() + i, newScore);
            highscores.pop_back();
            // todo: add according name of player to names vector
            //names.emplace(names.begin() + i, /*NAME PARAMETER HERE*/);
            //names.pop_back();

            //this->GenerateRankList();
			break;
		}
	}
}

void HighscoreList::GenerateRankList(void) {
    rankTexts.clear();

    for (int i = 0; i < this->maxSize; i++) {
        TextObject* newRank = new TextObject(Vec2f(this->GetPosition().x, this->GetPosition().y + i * 60), font,
            std::to_string(i + 1) + " " + names[i] + "        " + std::to_string(highscores[i]));
        rankTexts.push_back(newRank);
        //printf("newRank address: %p\n", &newRank);
    }
}