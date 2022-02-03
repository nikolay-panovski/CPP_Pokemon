#pragma once

#include "GameObject.hpp"
#include "TextObject.hpp"
#include "SpriteObject.hpp"

class Character : public GameObject {
	// have name (text)
	// default/randomly picked from a list/(editable?)

	// have sprite
	// randomly picked from a sheet/a set of files
	// scrollable array for non-random pick? (implement/display current selection)

	// have skill points
	// total/strength/agility/wits
	// incrementable and decrementable
	// need NOT have displays (TextObject/SpriteObject) innate to this class
	// -> must be gettable

	// randomize button
	// for skill points only/(random name?)
	// abide by skill points limitations (total amount, individual ranges)

	// have HP
	// current and max (both are modifiable)
	// text and/or sprite (bar(s)) ~~(button??)~~

	// have secondary stat (sanity or something)
	// --||--
	// --||--

	// have score/number of won battles

	// ---- suitable for player character AND enemy character
	// identifier for player character
	// identifier of the current player with an action/turn
	// start as false, compare agility, give true to the one with more first (function)
	// give false at end of turn(player with true) and true to the other one, keep swapping (function)

	// ---- for enemy character only:
	// invoke action(attack/heal/magic respectively take damage/get HP etc.) functions based on randomness

	// save ALL information (fields)
	// name, sprite, skill points distribution, current stats (HP/secondary), score/current fight
	// read all information from file (load button -> function here [see HighscoreList->GenerateRankList()])


	private:
		TextObject charName;
		SpriteObject charSprite;
		int totalSkillPoints;

		// these stats are initted as 0 and updated later according to other stats
		int strPoints = 0;
		int agilPoints = 0;
		int witsPoints = 0;

		int maxHP = 0;
		int hp = 0;
		int maxSanity = 0;
		int sanity = 0;

		bool isPlayer;
		

	public:
		bool hasCurrentTurn = false;
		// dirtiest possible way to not apply attack formula bonus at the start of a battle
		bool wasAttackedLastTurn = true;

		enum class CharStat : int {
			SkillPts,
			StrPts,
			AgilPts,
			WitsPts,
			CurHP,
			MaxHP,
			CurSanity,
			MaxSanity
		};

		// ...the following is still way better than keeping the labels in main(). even though public is not cool.
		TextObject activeLabel;
		TextObject hpLabel;
		TextObject sanityLabel;

	public:
		Character(Vec2f startPosition, sf::Font& startFont, std::string nameText, std::string textureFilename,
				  int totalSP, bool isPlayerChar);
		~Character();

		Vec2f GetPosition(void) const override;
		void SetPosition(Vec2f newPosition) override;
		std::string GetName(void) const;

		int GetStat(Character::CharStat stat) const;
		void IncrementStat(Character::CharStat stat);
		void IncrementStat(Character::CharStat stat, int value);
		void DecrementStat(Character::CharStat stat);
		void DecrementStat(Character::CharStat stat, int value);
		void ResetStats(void);
		void RandomizeStats(void);
		void CompareFightStartAgil(Character& other);
		bool VerifyMinStats(void);
		void VerifyStatsFromCharPts(void);

		void ToggleActiveTurn(void);
		int Attack(Character& other);
		Vec2i Heal(void);
		int CastMagic(Character& other);
		void Prepare(Character& other);

		void ExportCharacter(void);

		void Render(sf::RenderWindow& window) override;
};