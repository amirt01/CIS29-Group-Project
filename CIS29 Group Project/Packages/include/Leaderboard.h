#pragma once

class Leaderboard : public sf::Drawable
{
private:
	const int MAX_NUM_OF_SCORES;

	class Date : public sf::Drawable
	{
	private:
		sf::Font font;
		time_t date;
	public:
		Date(const sf::Font& font) : date(time(0)), font(font) {};
		Date(const Date&) = default;
		Date(time_t date, const sf::Font& font) : date(date), font(font) {} // Date in time_t format

		void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates = sf::RenderStates::Default) const
		{
			std::tm ptm{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			localtime_s(&ptm, &date);
			char buffer[32];
			std::strftime(buffer, 32, "%m/%d/%y", &ptm);

			sf::Text texDate;

			texDate.setString(buffer);
			texDate.setCharacterSize(32U);
			texDate.setFont(font);
			renderTarget.draw(texDate, renderStates);
		};
		const time_t getDate() const { return date; };
		friend bool operator<(const Date& d1, const Date& d2) { return d1.date < d2.date; }
		friend bool operator<(const Date& d1, const time_t& d2) { return d1.date < d2; }
	};
	class Score : public sf::Drawable
	{
	private:
		sf::Text name;
		sf::Text score;
		const float numScore;
		Date date;

		sf::Font font;

	public:
		Score(const std::string& name, const float& score, const sf::Font& font, const time_t date = time(0))
			: date(Date(date, font)), numScore(score), font(font)
		{
			// max name length will be 9
			sf::String strScore(std::to_string(score));
			this->score.setString(strScore.substring(0, strScore.find('.') + 3));
			this->score.setFont(font);
			this->score.setCharacterSize(32);

			this->name = this->score;
			this->name.setString(name);
		};
		const std::string getName() const { return name.getString().toAnsiString(); };
		const time_t getDate() const { return date.getDate(); };
		const float getScore() const { return numScore; };
		void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates = sf::RenderStates::Default) const
		{
			const float padding = 50.f;

			sf::RectangleShape container;
			container.setFillColor(sf::Color(100, 100, 100, 200));
			container.setSize(sf::Vector2f(renderTarget.getSize().x * 0.4f, 45.f));
			renderTarget.draw(container, renderStates);

			renderStates.transform.translate(padding / 2.f, 0.f);
			renderTarget.draw(date, renderStates);
			renderStates.transform.translate(135.f + padding, 0.f);
			renderTarget.draw(name, renderStates);
			renderStates.transform.translate(135.f + padding, 0.f);
			renderTarget.draw(score, renderStates);
		}
		friend bool operator<(const Score& s1, const Score& s2)
		{
			if (s1.numScore == s2.numScore)
				return s1.date < s2.date;
			return s1.numScore < s2.numScore;
		}
		friend bool operator<(const Score& s1, const float& s2)
		{
			if (s1.numScore == s2)
				return s1.date < time(0);
			return s1.numScore < s2;
		}
	};

	std::list<Score> scores;

public:

	Leaderboard(const int MAX_NUM_OF_SCORES) : MAX_NUM_OF_SCORES(MAX_NUM_OF_SCORES) {};
	~Leaderboard() {};

	bool loadFromFile(sf::Font& font, const std::string& path);
	bool writeToFile(const std::string& path);

	bool addNewScore(const std::string& name, const float& score, sf::Font& font, time_t date = time(0));
	bool checkIfHighScore(const float& score);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
};
