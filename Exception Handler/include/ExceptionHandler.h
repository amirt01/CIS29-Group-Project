#pragma once

namespace exc {
	template<typename T>
	class SpawnError
	{
	private:
		T holder;
	public:
		SpawnError(const T& error) : holder(error) {};
		std::string Typeid() const {
			std::string id = typeid(T).name();
			return id.substr(id.find_first_not_of("0123456789"));;
		};
		const std::string what() const {
			static std::string ret;
			ret = "Error spawning object.\nReason: Invalid input.\nInput: ";
			ret += std::to_string(holder);
			ret += "\nInput Type: ";
			ret += Typeid();
			ret += "\n";
			return ret;
		};
	};
}