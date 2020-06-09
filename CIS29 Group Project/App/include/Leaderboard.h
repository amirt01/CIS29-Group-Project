#pragma once

class Leaderboard : public sf::Drawable
{
private:
	const int MAX_NUM_OF_SCORES;

	class Date {
	private:
		const time_t date;
	public:
		Date() : date(time(0)) {};
		Date(const Date&) = default;
		Date(time_t d) : date(d) {} // Date in time_t format
		operator sf::String() const
		{
			std::tm* ptm = new tm{ 0 };
			localtime_s(ptm, &date);
			char buffer[32];
			std::strftime(buffer, 32, "%m/%d/%y", ptm);
			delete ptm;
			return sf::String(buffer);
		};
		const time_t getDate() const { return date; };
		friend bool operator<(const Date& d1, const Date& d2) { return d1.date < d2.date; }
		friend bool operator<(const Date& d1, const time_t& d2) { return d1.date < d2; }
	};

	class Score : public sf::Drawable
	{
	private:
		const std::string name;
		const float score;
		Date date;
	public:
		Score()
			: name(""), score(0), date() {};
		Score(const std::string& name, const float& score, const time_t date = time(0))
			: name(name), score(score), date(Date(date)) {};
		const std::string getName() const { return name; };
		const float getScore() const { return score; };
		const time_t getDate() const { return date.getDate(); };
		void draw(sf::RenderTarget& renderTarget, sf::RenderStates states = sf::RenderStates::Default) const
		{
			sf::Font font;
			font.loadFromFile("Resources/Fonts/Dosis-Light.ttf");
			sf::Text date(sf::String(name), font, 50);

			sf::String strScore(std::to_string(score));

			sf::Text tScore(strScore.substring(0, strScore.find('.') + 3), font, 50);
			renderTarget.draw(date, states);
			states.transform.translate(200.f, 0.f);
			renderTarget.draw(tScore, states);
		}
		friend bool operator<(const Score& s1, const Score& s2)
		{
			if (s1.score == s2.score)
				return s1.date < s2.date;
			return s1.score < s2.score;
		}
		friend bool operator<(const Score& s1, const float& s2)
		{
			if (s1.score == s2)
				return s1.date < time(0);
			return s1.score < s2;
		}
	};

public:
	std::list<Score> scores;

	Leaderboard(const int MAX_NUM_OF_SCORES) : MAX_NUM_OF_SCORES(MAX_NUM_OF_SCORES) {};
	~Leaderboard() {};

	bool loadFromFile(const std::string& path);
	bool writeToFile(const std::string& path);

	bool addNewScore(const std::string& name, const float& score, time_t date = time(0));
	bool checkIfHighScore(const float& score);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
};
