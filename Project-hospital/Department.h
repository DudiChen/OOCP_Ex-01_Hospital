#ifndef DEPARTMENT_H
#define DEPARTMENT_H

// #include "Patient"
#include "doctor.h"
#include "nurse.h"
#include "Patient.h"

class Department
{
private:
	char* name;
	Doctor** docArr;
	int numDocs;
	Nurse** nurseArr;
	int numNurses;
	Patient** patientArr;
	int numPatients;
	// Patiant** patientsArr;
	// int numPatients;


public:
	// C'tor:
	Department(const char* inName, Doctor** inDocArr, Nurse** inNurseArr);
	// Department(const char* inName, Doctor** inDocArr, Nurse** inNurseArr, Patient** inPatientArr);
	// Copy C'tor:
	Department(const Department& other) = delete;
	// D'tor:
	~Department();

	// Add doctor to the list of doctors:
	bool addDoctor(Doctor* doc);
	// Add nurse to the list of nurses:
	bool addNurse(Nurse* nurse);
	// // Add patient to the department list of patients:
	bool addPatint(Patient* patient);

	// Methods:
	// void showPatients() const;
	void showStaffMembers() const;

};

#endif