/*
Hospital Simulator
Created by Brian and Kathleen
*/
#include "Hospital.h"


int main(){

	Hospital *WhitPres = new Hospital();

	WhitPres->enter_data();
	WhitPres->run_simulation();
	WhitPres->show_data();	

}