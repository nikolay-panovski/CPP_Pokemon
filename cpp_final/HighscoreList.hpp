#pragma once

#include "GameObject.hpp"
#include "TextObject.hpp"
#include <vector>

class HighscoreList : public GameObject {
	private:
		int maxSize = 5;
		sf::Font font;
		Vec2f position;
		std::vector<int> highscores;
		std::vector<std::string> names;
		std::vector<TextObject> rankTexts;

	public:
		HighscoreList(Vec2f startPosition, sf::Font& startFont);
		~HighscoreList();

		Vec2f GetPosition(void) const override;
		void SetPosition(Vec2f newPosition) override;

		void Render(sf::RenderWindow& window) override;

		void TryAddHighscore(int newScore);
		void GenerateRankList(void);
};