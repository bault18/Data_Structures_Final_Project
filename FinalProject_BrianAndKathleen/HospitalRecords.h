#ifndef HOSPITALRECORDS_H_
#define HOSPITALRECORDS_H_

#include "Hospital.h"

#include <map>
#include <vector>
#include <string>

class HospitalRecords
{
private:
	std::vector<Patient*> Treated;	//Vector of treated patients
	std::multimap<std::string, int> Records; //Name, Illness Level, Enter Hospital, Enter Treatment, Leave Hospital
	WaitingRoom *Wait;

	double time_in_hospital; //average time spent in hospital
	int people_left_in_hospital;

public:
	HospitalRecords(WaitingRoom *Temp)
	{
		Wait = Temp;
		time_in_hospital = 0;
		people_left_in_hospital = 0;
	}

	void create_map()
	{
		double sum_of_wait_time = 0;

		for (int i = 0; i < Treated.size(); i++)
		{
			Records.insert(std::pair<std::string, int>(Treated[i]->get_name(), Treated[i]->get_illness_level())); //Adds a patient to the treated map

			sum_of_wait_time += (Treated[i]->get_leave_hospital() - Treated[i]->get_enter_hospital());	//Finds patient time in hospital, adds to total wait time
		}

		time_in_hospital = sum_of_wait_time / Treated.size(); //Finds average time in hospital

		people_left_in_hospital = Wait->get_high_size() + Wait->get_low_size(); //Finds people left in queue

	}


	void search_name()
	{
		system("cls");
		std::string name;
		std::cout << "Who would you like to search for: ";
		std::cin >> name;
		
		/*
		* NOTE: We know there is a find function for multimaps and chose to do our own thing
		*/
		int tick = 0; //test to see if person was found
		for (std::multimap<std::string, int>::iterator current = Records.begin(); current != Records.end(); current++)
		{
			if (current->first == name) //if patient found
			{
				std::cout << "For this visit " << current->first << " had an illness level of: " << current->second << std::endl;
				tick++;
			}
		}

		if (tick == 0) //if no patient was found
			std::cout << "No record of " << name << " was found\n\n";
			

		system("pause");
		system("cls");
	}

	void list_names()
	{
		system("cls");

		//loop displays all patients for the simulation
		for (std::multimap<std::string, int>::iterator current = Records.begin(); current != Records.end(); current++)
		{
			std::cout << current->first << "\t had an illness level of: " << current->second << std::endl << std::endl;
		}
		system("pause");
		system("cls");
	}

	double get_time_in_hospital() //returns average time in hospital
	{
		return time_in_hospital;
	}

	void add_to_record(Patient *done_treating) //adds patient to finished vector
	{
		Treated.push_back(done_treating);
	}

	int get_people_left()
	{
		return people_left_in_hospital;
	}

};



#endif