#include "Department.h"
#include "Hospital.h"
#include "Patient.h"
#include <string>

class Ui
{
private:
	Hospital *hospital;
public:
	Ui(Hospital *hos);
	void start();
	void printMainMenu() const;
	int inputYearsOfExprience() const;
	bool checkIfItFirstTimeInHospital() const;
	enum eGender inputGender()throw(FormatException);
	string getString(const string prompt);
	Patient* createPatient(string id);
	Doctor* createDoctor();
	int getInt(const string str);
	Nurse* createNurse();
	Article* createArticle(Date*date);
	void printSpaceLine() const;
	void printVisitationPorpuse(Patient* patient) const;
	VisitationRecord* createVisit(Patient & patient, Date* arrivalDate,int choice, Results& res);
	void compare2Researchers() const;

	// UI Flows:
	Results addNewDepartment();
	Results addNewNurse();
	Results addNewDoctor();
	Results addNewVisitation();
	void addNewResearcher();
	Results addArticleToResearcher();
	Results showPatientsInDepartment();

	// UI Warnings:
	void warnings(Results result);
};