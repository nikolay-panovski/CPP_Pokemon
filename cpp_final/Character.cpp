#pragma once

// this is how they created the Celeste player class

#include <fstream>
#include <random>
#include <math.h>
#include <algorithm>
#include <time.h>
#include "Character.hpp"

#define OFFSETX -25.0f
#define OFFSETY 50.0f

Character::Character(Vec2f startPosition, sf::Font& startFont, std::string nameText, std::string textureFilename,
					 int totalSP, bool isPlayerChar) :
	charName(startPosition + Vec2f(OFFSETX, OFFSETY), startFont, nameText),
	charSprite(startPosition, textureFilename), totalSkillPoints(totalSP), isPlayer(isPlayerChar),
	activeLabel(startPosition + Vec2f(OFFSETX, OFFSETY * 2), startFont),
	hpLabel(startPosition + Vec2f(OFFSETX, OFFSETY * 3), startFont),
	sanityLabel(startPosition + Vec2f(OFFSETX, OFFSETY * 4), startFont) {
	if (isPlayer == false) {
		this->RandomizeStats();
		//printf_s("\nEnemy strength: %i", this->strPoints);
		//printf_s("\nEnemy agility: %i", this->agilPoints);
		//printf_s("\nEnemy wits: %i", this->witsPoints);
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

/* DIRECT STATS FUNCTIONS */

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
		case Character::CharStat::CurSanity:
			return this->sanity;
			break;
		case Character::CharStat::MaxSanity:
			return this->maxSanity;
			break;
		default:
			break;
	}
}

// this next code (INCs/DECs) is tailored to fail Software Architecture with a grade of "Does not have a brain"
// only use this signature on character screen
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

// only use this signature on fight screen
void Character::IncrementStat(Character::CharStat stat, int value) {
		switch (stat) {
			case Character::CharStat::SkillPts:
				this->totalSkillPoints += value;
				break;
			case Character::CharStat::StrPts:
				this->strPoints += value;
				//do not do this here?
				this->totalSkillPoints -= value;
				break;
			case Character::CharStat::AgilPts:
				this->agilPoints += value;
				this->totalSkillPoints -= value;
				break;
			case Character::CharStat::WitsPts:
				this->witsPoints += value;
				this->totalSkillPoints -= value;
				break;
			case Character::CharStat::CurHP:
				this->hp += value;
				break;
			case Character::CharStat::MaxHP:
				this->maxHP += value;
				break;
			default:
				break;
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
		case Character::CharStat::CurSanity:
			if (this->sanity > 0) {
				this->sanity--;
			}
			break;
		default:
			break;
	}
}

void Character::DecrementStat(Character::CharStat stat, int value) {
	switch (stat) {
		case Character::CharStat::SkillPts:
			this->totalSkillPoints -= value;
			break;
		case Character::CharStat::StrPts:
			if (this->strPoints > 0) {
				this->strPoints -= value;
				//do not do this here?
				this->totalSkillPoints += value;
			}
			break;
		case Character::CharStat::AgilPts:
			if (this->agilPoints > 0) {
				this->agilPoints -= value;
				this->totalSkillPoints += value;
			}
			break;
		case Character::CharStat::WitsPts:
			if (this->witsPoints > 0) {
				this->witsPoints -= value;
				this->totalSkillPoints += value;
			}
			break;
		case Character::CharStat::CurHP:
			if (this->hp > 0) {
				this->hp -= value;
			}
			break;
		case Character::CharStat::MaxHP:
			this->maxHP -= value;
			break;
		case Character::CharStat::CurSanity:
			if (this->sanity > 0) {
				this->sanity -= value;
			}
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
	this->hp = this->maxHP;
	this->maxSanity = this->witsPoints * 2;
	this->sanity = this->maxSanity;
}

/* END DIRECT STATS FUNCTIONS */

/* FIGHT ACTIONS FUNCTIONS */

void Character::ToggleActiveTurn(void) {
	this->hasCurrentTurn ^= true;
}

void Character::Attack(Character& other) {
	if (rand() % 100 >= other.agilPoints * 10) {
		int component1 = this->strPoints;
		int component2;
		int component3 = ceil(other.GetStat(Character::CharStat::StrPts) / 2);

		if (wasAttackedLastTurn) {
			component2 = rand() % 4 + 1;
		}
		else {
			if (this->agilPoints == 0) {
				component2 = 1;
			}
			else component2 = std::max(2, this->agilPoints * 2);
		}

		other.DecrementStat(Character::CharStat::CurHP,
			std::max(component1 + component2 - component3, 1));

		other.wasAttackedLastTurn = true;

		//printf_s("\ncomponent1 = %i", component1);
		//printf_s("\ncomponent2 = %i", component2);
		//printf_s("\ncomponent3 = %i", component3);
		//printf_s("\nPlayer HP: %i", this->hp);
		//printf_s("\nEnemy HP: %i", other.hp);
	}

	else {
		other.wasAttackedLastTurn = false;
		printf_s("\nOther was not attacked this turn.");
	}
}

void Character::Heal(void) {
	if (rand() % 100 < ceil(this->witsPoints * 1.5f) * 11) {
		this->IncrementStat(Character::CharStat::CurHP, rand() % 4);
		this->IncrementStat(Character::CharStat::CurSanity, rand() % 2 + 1);
		printf_s("Heal successful.");
	}
	else printf_s("Heal failed.");
	
	// this is not best suited for here
	if (this->sanity > this->maxSanity) this->sanity = this->maxSanity;
	if (this->hp > this->maxHP) this->hp = this->maxHP;

	printf_s("\nPlayer HP: %i", this->hp);
	printf_s("\nPlayer Sanity: %i", this->sanity);
}

void Character::CastMagic(Character& other) {
	int dmg = this->witsPoints + (rand() % 8 - 3);

	if (dmg >= 0) other.DecrementStat(Character::CharStat::CurHP, dmg);
	else this->DecrementStat(Character::CharStat::CurSanity);
}
/* END FIGHT ACTIONS FUNCTIONS */


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

	this->activeLabel.Render(window);
	this->hpLabel.Render(window);
	this->sanityLabel.Render(window);
}