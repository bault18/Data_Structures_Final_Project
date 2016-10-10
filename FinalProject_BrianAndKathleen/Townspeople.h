#include <string>


class Townspeople{
private:
	int illness_level;
	std::string name;
	int time;

public:
	bool operator<(const Townspeople &other) const {
		return illness_level < other.illness_level;
	}

	Townspeople(std::string name){
		illness_level; //set illness level here
		this->name = name;
		time = 0;
	}

	std::string get_name(){
		return name;
	
	int get_illness_level(){
		return illness_level;
	}
};