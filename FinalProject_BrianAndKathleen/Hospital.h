#ifndef HOSPITAL_H_
#define HOSPITAL_H_

#include <iostream>
#include <string>
#include <vector>

#include "Patient.h"
#include "WaitingRoom.h"
#include "TreatmentRoom.h"
#include "Random.h"
#include "HospitalRecords.h"


Random my_random;  // Global variable 

class Hospital{
private:
	int total_time;		//total time to run simulation
	int clock;			//current time


	WaitingRoom *Waiting_room;			//Creates waiting room
	TreatmentRooms *Treatment_Rooms;	//Creates treatment_room and doctors/nurses
	HospitalRecords *Hospital_records;	//Creates place to store cured patients

	//read_int inspired by the Airport_Simulator project 
	int read_int(const std::string &prompt, int low, int high)
	{
		if (low >= high) // invalid range
			throw std::invalid_argument("invalid range specified");

		std::cin.exceptions(std::ios_base::failbit);
		int num = 0;
		while (true) {
			try {
				while (true) {
					std::cout << prompt;
					std::cin >> num;
					if (num >= low && num <= high) { // within the specified range
						std::cout << std::endl;
						return num;
					}
				}
			}
			catch (std::ios_base::failure) {
				std::cout << "Bad numeric string -- try again\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
		}
	}
	
public:

	//NO-ARG Constructor
	Hospital()
	{
		total_time = 10080; //minutes in a week

		Waiting_room = new WaitingRoom();	//Creates new WaitingRoom
		
		Hospital_records = new HospitalRecords(Waiting_room); //Creates new HospitalRecord

	}

	//set doctor, nurses, patients per hour
	void enter_data()
	{
		std::cout << "Welcome CS273 to the simple Hospital Simulator.\n\n";

		double arrival_rate = read_int("How many sick people would you like to arrive per hour: ", 1, 60) / static_cast<double>(60); //Min = 0, Max = 60
		Waiting_room->set_arrival_rate(arrival_rate); //create the waiting room

		int docs = read_int("How many doctors would you like: ", 0, INT_MAX); //Min = 0, Max = Unlimited

		int nurses = read_int("How many nurses would you like: ", 0, INT_MAX); //Min = 0, Max = Unlimited
		Treatment_Rooms = new TreatmentRooms(docs, nurses, Waiting_room, Hospital_records); //creates the TreatmentRooms using user inputs




	}

	void run_simulation()
	{
		for (clock = 0; clock < total_time; ++clock) //ticks through simulation 1 min at a time till we reach 1 week
		{
			Waiting_room->update(clock);
			Treatment_Rooms->update(clock);
		}
	}

	void show_data()
	{
		system("cls");
		Hospital_records->create_map(); // creates map of data

		int switch_control = 0;
		do
		{
			std::cout << "ENDING STATISTICS\n\n"
				<< "People left in Waiting Room: " << Hospital_records->get_people_left() << std::endl << std::endl
				<< "Average time spent in hospital by treated patients: " << Hospital_records->get_time_in_hospital() << " min\n\n";

			std::cout << "Options:\n"
				<< "1. List all patients treated\n"
				<< "2. Search for specific patient\n"
				<< "3. Exit Simulation\n"
				<< "Enter Option: ";
			std::cin >> switch_control;

			switch (switch_control) //Test User Inputs
			{
			case 1: //list all names
				Hospital_records->list_names();
				break;
			case 2: //search for one name
				Hospital_records->search_name();
				break;
			case 3:	//exit program
				system("cls");
				std::cout << "Thankyou for using our simulation\n\n";
				std::exit(0);
				break;
			default: //Faulty user input
				system("cls");
				std::cout << "Invalid Entry. Please select an action with the numbers 1-3\n\n";
				system("pause");
				system("cls");
			}
		} while (switch_control != 3);
	}


};

#endif