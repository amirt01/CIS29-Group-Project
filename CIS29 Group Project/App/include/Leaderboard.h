#pragma once

class Leaderboard
{
private:
	const int MAXNUMBEROFSCORES;

	class Date {
	private:
		const time_t date;
	public:
		Date() : date(time(0)) {};
		Date(const Date&) = default;
		Date(time_t d) : date(d) {} // Date in time_t format
		friend bool operator<(const Date& d1, const Date& d2) { return d1.date < d2.date; }
		friend bool operator<(const Date& d1, const time_t& d2) { return d1.date < d2; }
	};

	class Score {
	private:
		const std::string name;
		const float score;
		const Date date;
	public:
		Score(const std::string& name, const float& score)
			: name(name), score(score), date(Date()) {};
		const std::string const getName() { return name; };
		const int getScore() const { return score; };
		const Date getDate() const { return date; };
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

	Leaderboard(const int maxNumberOfScores) : MAXNUMBEROFSCORES(maxNumberOfScores) {};
	~Leaderboard() {};

	bool addNewScore(const std::string& name, const float& score);
	bool checkIfHighScore(const float& score);
};
