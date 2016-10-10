#ifndef HOSPITALWORKERS_H_
#define HOSPITALWORKERS_H_

#include "Patient.h"
#include "Hospital.h"
#include "WaitingRoom.h"
#include "Random.h"

#include <iostream>
#include <ctime>



class Doctor
{
private:
	bool treating;
	int treatment_time;
	Patient *current_patient;	//pointer to current patient
	WaitingRoom *Wait;			//pointer to Waiting_room
	HospitalRecords *Record;	//pointer to Hospital_records

public:

	//NO-ARG Constructor
	Doctor(WaitingRoom *temp, HospitalRecords *temp2)
	{		
		treatment_time = 0;
		treating = false; //Not initially treating a patient

		Wait = temp;
		Record = temp2;
	}
	

	
	
	void check_if_done(int clock)
	{
		

		if (treating == false)		//if no patient
		{
			if (Wait->get_high_size() != 0)	//check high queue
			{

				current_patient = Wait->get_high_patient(); //Take patient from queue
				current_patient->set_treatment_time(clock + treatment_time); //set how long treatment takes
				treating = true;
				treatment_time = my_random.next_int(20) + 1; //set treatment time 1-20

				Wait->pop_high_queue();	//pop patient off of queue
			}
			else if(Wait->get_low_size() != 0)	//check low queue
			{
				current_patient = Wait->get_low_patient();	//take from low queue
				current_patient->set_treatment_time(clock + treatment_time); //set how long treatment takes
				treating = true;
				treatment_time = my_random.next_int(20) + 1; //set treatment time 1-20

				Wait->pop_low_queue();	//pop low queue
			}
		}
		else if (current_patient->get_treatment_time() < clock) //check if done treating
		{
			current_patient->set_leave_time(clock); //set patient leave time
			Record->add_to_record(current_patient); //push patient to hospital records
			treating = false; //prepare for new patient
		}

	}



};


class Nurse
{
private:
	bool treating;
	int treatment_time;
	Patient *current_patient;
	WaitingRoom *Wait;
	HospitalRecords *Record;
	

public:

	Nurse(WaitingRoom *temp, HospitalRecords *temp2)
	{
		//random number generator
		srand(std::time(NULL));
		treatment_time = 0;

		treating = false; //Not initially treating a patient

		Wait = temp;
		Record = temp2;
	}

	void check_if_done(int clock)
	{
		if (treating == false)		//if no patient
		{
			
			if (Wait->get_low_size() != 0)	//check low queue
			{
				current_patient = Wait->get_low_patient();	//take from low queue
				current_patient->set_treatment_time(clock + treatment_time); //set how long treatment takes
				treating = true;
				treatment_time = my_random.next_int(10) + 1; //set treatment time 1-10

				Wait->pop_low_queue();	//pop low queue
			}
		}
		else if (current_patient->get_treatment_time() < clock) //check if done treating
		{
			current_patient->set_leave_time(clock); //set patient leave time
			Record->add_to_record(current_patient); //push patient to hospital records
			treating = false; //prepare for new patient
		}

	}

};

#endif