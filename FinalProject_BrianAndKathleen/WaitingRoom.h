#ifndef WAITINGROOM_H_
#define WAITINGROOM_H_

#include "Hospital.h"
#include "Patient.h"
#include "Random.h"

#include <queue>
#include <fstream>
#include <string>

extern Random my_random;  // Enables us to access the global variable declared in Hospital.h

class WaitingRoom {
private:
	std::priority_queue<Patient*> high_priority_patients;	//Only Patients w/ illness 11-20
	std::priority_queue<Patient*> low_priority_patients;	//Only Patients w/ illness 1-10
	double arrival_rate; //min 1, max 60
	std::vector<std::string> names;

public:
	//NO-ARG Constructor
	WaitingRoom(){
		arrival_rate = 0; //Set arbitrary arrival rate

		//Import names using file io
		std::fstream Name_File("Names.h", std::ios::beg | std::ios::in);
		if (Name_File.fail())
		{
			std::cout << "Opening town names failed\n";
		}
		else
		{
			while (!Name_File.eof())
			{
				std::string tempname;
				Name_File >> tempname;
				names.push_back(tempname);

			}
		}
	}

	void update(int clock) //function to run simulation
	{
		if (my_random.next_double() < arrival_rate && (names.size() != 0)) //has someone arrived , is there someone left to arrive
		{
			
			std::string name = names.back();	//pulls name from townspeople
			names.pop_back();					//Removes name from vector of names

			Patient *new_patient = new Patient(name, clock); //create a new patient

			
			if (new_patient->get_illness_level() < 11)	//test what queue patient belongs in
			{
				low_priority_patients.push(new_patient); //add them to queue
			}
			else
			{
				high_priority_patients.push(new_patient); //add them to queue
			}

		}

	}

	void pop_high_queue() //Pops patient from high priority queue
	{
		high_priority_patients.pop();
	}

	int get_high_size() //returns high priority queue size
	{
		return high_priority_patients.size();
	}


	void pop_low_queue() //Pops patient from low priority queue
	{
		low_priority_patients.pop();
	}

	int get_low_size()	//returns low priority queue size
	{
		return low_priority_patients.size();
	}

	Patient* get_high_patient() //returns patient at top of high priority queue
	{
		return high_priority_patients.top();
	}

	Patient* get_low_patient() //returns patient at top of low priority queue
	{
		return low_priority_patients.top();
	}

	
	void set_arrival_rate(double arrival_rate) //sets the arrival rate of patients
	{
		this->arrival_rate = arrival_rate;
	}

	


	
};

#endif