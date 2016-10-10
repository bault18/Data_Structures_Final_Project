#ifndef PATIENT_H_
#define PATIENT_H_

#include <string>
#include <ctime>
#include "Random.h"

extern Random my_random;  // Enables us to access the global variable declared in Hospital.h

class Patient{
private:
	int illness_level;
	std::string name;
	
	int start_waiting_room_time;	//time when entered into first queue
	int end_treatment_time;			//time when doctor finished treating
	int left_hospital;				//time when pushed to hospital records

public:

	//Overloaded operater used to compare class of same type
	bool operator<(const Patient &other) const {
		return illness_level < other.illness_level;
	}


	//ARG-Constructor
	Patient(std::string name, int clock){
	
		random_illness_generator();		 //set illness
		this->name = name;				 //set name
		start_waiting_room_time = clock; //set arrival time
	}

	//Return Patient Name
	std::string get_name(){
		return name;
	}

	//Return Patient Illness Level
	int get_illness_level(){
		return illness_level;
	}

	//set how long till patient is done being treated
	void set_treatment_time(int time)
	{
		end_treatment_time = time;
	}

	//get how long treatment takes
	int get_treatment_time()
	{
		return end_treatment_time;
	}

	//get when put into queue
	int get_enter_hospital()
	{
		return start_waiting_room_time;
	}

	//get when patient pushed to hospital records
	int get_leave_hospital()
	{
		return left_hospital;
	}

	//set when patient left hospital
	void set_leave_time(int leave)
	{
		left_hospital = leave;
	}

	//Created by: Kathleen
	void random_illness_generator()
	{		
		my_random.next_int(100);

		int rand_number = my_random.next_int(100);
		if (rand_number <= 70) {
			illness_level = my_random.next_int(10) + 1;
		}
		else if (rand_number > 70 && rand_number <= 90){
			int number_2 = my_random.next_int(15) + 1;
			while (number_2 < 11) {
				number_2 = my_random.next_int(15) + 1;
			}
			illness_level = number_2;
		}
		else{
			int number_3 = my_random.next_int(20) + 1;
			while (number_3 < 16) {
				number_3 = my_random.next_int(20) + 1;
			}
			illness_level = number_3;
		}

	}
	
};

#endif