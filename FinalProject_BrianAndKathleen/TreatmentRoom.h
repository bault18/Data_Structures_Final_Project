#ifndef HOSPITALEMPLOYEES_H_
#define HOSPITALEMPLOYEES_H_

#include <vector>
#include <iostream>
#include <iterator>

#include "HospitalRecords.h"
#include "HospitalWorkers.h"
#include "Hospital.h"

class TreatmentRooms
{
private:
	std::vector<Doctor*> Doctors;
	std::vector<Nurse*> Nurses;

public:

	TreatmentRooms(int docs, int nurse, WaitingRoom *wait, HospitalRecords *record) //creates doctors and nurses
	{
		for (int i = 0; i < docs; i++) //loop to create doctors
		{
			Doctors.push_back(new Doctor(wait, record));
		}
		for (int i = 0; i < nurse; i++) //loop to create nurses
		{
			Nurses.push_back(new Nurse(wait, record));
		}

	}

	//Function to run through Doctor & nurses to see if they are free to treat
	void update(int clock)
	{
		for (int i = 0; i < Doctors.size(); i++) //loop to update doctors
		{
			Doctors[i]->check_if_done(clock);
		}
		for (int i = 0; i < Nurses.size(); i++) //loop to update nurses
		{
			Nurses[i]->check_if_done(clock);
		}
	}
};

#endif