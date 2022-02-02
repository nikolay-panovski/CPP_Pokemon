#pragma once

#include <fstream>
#include <random>
#include <time.h>
#include "Character.hpp"

#define OFFSET Vec2f(-25.0f, 50.0f)

Character::Character(Vec2f startPosition, sf::Font& startFont, std::string nameText, std::string textureFilename,
					 int totalSP, bool isPlayerChar) :
	charName(startPosition + OFFSET, startFont, nameText), charSprite(startPosition, textureFilename),
	totalSkillPoints(totalSP), isPlayer(isPlayerChar) {
	if (isPlayer == false) {
		this->RandomizeStats();
	}
}

Character::~Character() {}

Vec2f Character::GetPosition(void) const {
	return this->charSprite.GetPosition();
}

void Character::SetPosition(Vec2f newPosition) {
	this->charName.SetPosition(newPosition);
	this->charSprite.SetPosition(newPosition);
}

int Character::GetStat(Character::CharStat stat) const {
	switch (stat) {
		case Character::CharStat::SkillPts:
			return this->totalSkillPoints;
			break;
		case Character::CharStat::StrPts:
			return this->strPoints;
			break;
		case Character::CharStat::AgilPts:
			return this->agilPoints;
			break;
		case Character::CharStat::WitsPts:
			return this->witsPoints;
			break;
		case Character::CharStat::CurHP:
			return this->hp;
			break;
		case Character::CharStat::MaxHP:
			return this->maxHP;
			break;
		default:
			break;
	}
}

void Character::IncrementStat(Character::CharStat stat) {
	if (this->totalSkillPoints > 0) {
		switch (stat) {
			case Character::CharStat::SkillPts:
				this->totalSkillPoints++;
				break;
			case Character::CharStat::StrPts:
				this->strPoints++;
				//do not do this here?
				this->totalSkillPoints--;
				break;
			case Character::CharStat::AgilPts:
				this->agilPoints++;
				this->totalSkillPoints--;
				break;
			case Character::CharStat::WitsPts:
				this->witsPoints++;
				this->totalSkillPoints--;
				break;
			case Character::CharStat::CurHP:
				this->hp++;
				break;
			case Character::CharStat::MaxHP:
				this->maxHP++;
				break;
			default:
				break;
		}
	}
}

void Character::DecrementStat(Character::CharStat stat) {
	switch (stat) {
		case Character::CharStat::SkillPts:
			this->totalSkillPoints--;
			break;
		case Character::CharStat::StrPts:
			if (this->strPoints > 0) {
				this->strPoints--;
				//do not do this here?
				this->totalSkillPoints++;
			}
			break;
		case Character::CharStat::AgilPts:
			if (this->agilPoints > 0) {
				this->agilPoints--;
				this->totalSkillPoints++;
			}
			break;
		case Character::CharStat::WitsPts:
			if (this->witsPoints > 0) {
				this->witsPoints--;
				this->totalSkillPoints++;
			}
			break;
		case Character::CharStat::CurHP:
			if (this->hp > 0) {
				this->hp--;
			}
			break;
		case Character::CharStat::MaxHP:
			// if maxHP < 0, well, congratulations...
			this->maxHP--;
			break;
		default:
			break;
	}
}

void Character::ResetStats(void) {
	this->totalSkillPoints += (this->strPoints + this->agilPoints + this->witsPoints);
	this->strPoints = 0;
	this->agilPoints = 0;
	this->witsPoints = 0;
}

void Character::RandomizeStats(void) {
	// RNG with current time as seed (NULL means the returned time will not be stored anywhere)
	srand(time(NULL));
	
	this->strPoints = rand() % (this->totalSkillPoints / 2) + 1;
	this->witsPoints = rand() % (this->totalSkillPoints / 2) + 1;
	this->totalSkillPoints -= this->strPoints;
	this->totalSkillPoints -= this->witsPoints;
	this->agilPoints = this->totalSkillPoints;
	this->totalSkillPoints -= this->agilPoints;
}

void Character::CompareFightStartAgil(Character& other) {
	if (other.GetStat(Character::CharStat::AgilPts) > this->agilPoints) {
		other.hasCurrentTurn = true;
	}
	else this->hasCurrentTurn = true;
}

bool Character::VerifyMinStats(void) {
	if (this->strPoints > 0 && this->witsPoints > 0) return true;
	else return false;
}

// according to the "example game" game design document
void Character::VerifyStatsFromCharPts(void) {
	this->maxHP = this->strPoints * 3;
	this->maxSanity = this->witsPoints * 2;
}


void Character::ExportCharacter(void) {
	std::ofstream exporter;
	exporter.open("data.cmgt");

	// save ALL information (fields)
	// name, sprite, skill points distribution, current stats (HP/secondary), score/current fight
	// extra challenge: add human-readable labels while exporting to file,
	// then properly import the stats ignoring the labels (std::istream::ignore)
	exporter << this->charName.GetText() << "\n";

	exporter << this->charSprite.GetSpriteFilename() << "\n";

	exporter.close();
}

void Character::Render(sf::RenderWindow& window) {
	this->charName.Render(window);
	this->charSprite.Render(window);
}