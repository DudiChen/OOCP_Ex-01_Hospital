#include "Hospital.h"
#include "doctor.h"
#include "nurse.h"
#include "Patient.h"

// C'tor:
Hospital::Hospital()
	:  allDoctors(nullptr), allNurses(nullptr), allPatients(nullptr)
{
	logSizeOfDepartments = logSizeDoctors = logSizeNurses = 
	logSizeOfPatients = phySizeDoctors = phySizeNurses = phySizeOfPatients = 0;
}

// D'tor:
//
//
Hospital::~Hospital()
{
	for(int i=0;i<logSizeDoctors;i++)
		delete[]allDoctors[logSizeDoctors];
	delete[]allDoctors;
	for (int i = 0; i<logSizeNurses; i++)
			delete[]allNurses[logSizeNurses];
	delete[]allNurses;
	for (int i = 0; i<logSizeOfDepartments; i++)
		delete[]allDepartments[logSizeOfDepartments];
	delete[]allDepartments;
	for (int i = 0; i<logSizeOfPatients; i++)
		delete[]allPatients[logSizeOfPatients];
	delete[]allPatients;
}


bool Hospital::allocDepartmentsArr()
{
	Department** newArr = new Department*[phySizeOfDepartments];
	for (int i = 0; i < logSizeOfDepartments; i++)
		newArr[i] = allDepartments[i];
	delete[]allDepartments;
	allDepartments = newArr;
	return true;
}


bool Hospital::addDepartment(Department& inDep)
{
	if (phySizeOfDepartments == 0) //if the first researcher
	{
		allDepartments = new Department*;
		phySizeOfDepartments++;
	}
	else if (logSizeOfDepartments == phySizeOfDepartments) //if there is no place in the array
	{
		phySizeOfDepartments *= 2;
		allocDepartmentsArr();  //to reallocte the array to the new size
	}

	if (logSizeOfDepartments < phySizeOfDepartments)
	{
		allDepartments[logSizeOfDepartments] = &inDep;
		logSizeOfDepartments++;
	}
	return true;
}

bool Hospital::addResearcher(Researcher& inResearcher)
{
	researchInst.addResearcher(inResearcher);
	return true;
}

bool Hospital::allocDocArr()
{
	Doctor** newArr = new Doctor*[phySizeDoctors];
	for (int i = 0; i < logSizeDoctors; i++)
		newArr[i] = allDoctors[i];
	delete[]allDoctors;
	allDoctors = newArr;
	return true;
}

bool Hospital::addDoctor(Doctor& inDoc)
{
	if (phySizeDoctors == 0) //if the first researcher
	{
		allDoctors = new Doctor*;
		phySizeDoctors++;
	}
	else if (logSizeDoctors == phySizeDoctors) //if there is no place in the array
	{
		phySizeDoctors *= 2;
		allocDocArr();  //to reallocte the array to the new size
	}

	if (logSizeDoctors < phySizeDoctors)
	{
		allDoctors[logSizeDoctors] = &inDoc;
		logSizeDoctors++;
	}
	return true;
}


bool Hospital::allocNursesArr()
{
	Nurse** newArr = new Nurse*[phySizeNurses];
	for (int i = 0; i < logSizeNurses; i++)
		newArr[i] = allNurses[i];
	delete[]allNurses;
	allNurses = newArr;
	return true;
}

bool Hospital::addNurse(Nurse& inNurse)
{
	if (phySizeNurses == 0) //if the first researcher
	{
		allNurses = new Nurse*;
		phySizeNurses++;
	}
	else if (logSizeNurses == phySizeNurses) //if there is no place in the array
	{
		phySizeNurses *= 2;
		allocNursesArr();  //to reallocte the array to the new size
	}

	if (logSizeNurses < phySizeNurses)
	{
		allNurses[logSizeNurses] = &inNurse;
		logSizeNurses++;
	}
	return true;
}


bool Hospital::allocPatientsArr()
{
	if (phySizeOfPatients == 0) // If this is the 1st Patient
	{
		allPatients = new Patient*;
		phySizeOfPatients++;
		return true;
	}
	else if (logSizeOfPatients == phySizeOfPatients) //if there is no more room in the array
	{
		phySizeOfPatients *= 2;
		Patient** newArr = new Patient*[phySizeOfPatients];
		for (int i = 0; i < logSizeOfPatients; i++)
		{
			newArr[i] = allPatients[i];
		}
		delete[] allPatients;
		allPatients = newArr;
		return true;
	}
	else
		return true;
}

bool Hospital::addPatient(Patient& inPatient, const char* inDep)
{
	allocPatientsArr();
	allPatients[logSizeOfPatients] = &inPatient;
	logSizeOfPatients++;
	return true;
}

void Hospital::showPatientInSpecificDep(const int &index) const
{
	allDepartments[index]->showPatients();
	cout << "****************************************" << endl;;

}

void Hospital::showStaffMembers() const
{
	if (logSizeDoctors || logSizeNurses)
	{
		for (int i = 0; i < logSizeOfDepartments; i++)
		{
			allDepartments[logSizeOfDepartments]->showStaffMembers();
		}
	}
	else
		cout << "There is no persons in the medical staff " << endl;
	cout << "*******************************" << endl;
}

void Hospital::showResearchers() const
{
	researchInst.showResearchers();
	cout << "********************************" << endl;
}

void Hospital::showPatientByID(char* inID) const
{

} 

void Hospital::showDepartments() const
{
	for (int i = 0; i < logSizeOfDepartments; i++)
	{
		cout << '\t' << i + 1 << ". " << allDepartments[i]->getName() << endl;
	}
}

/////////////////////////////////////////
bool Hospital::getDepartmentByName(char* depName, Department* resDepartment)
{
	return binDepartmentByName(allDepartments, logSizeOfDepartments, depName, resDepartment);
}

bool Hospital::binDepartmentByName(Department** arr, int size, char* depName, Department* resDep)
{
	Department* midDep = arr[size / 2];
	int res = strcmp(depName, midDep->getName());
	if (size == 1)
	{
		if (res == 0) {
			resDep = midDep;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (res == 0)
		{
			resDep = midDep;
			return true;
		}
		else if (res < 0)
			return binDepartmentByName(arr, size / 2, depName, resDep);
		else if (res > 0)
			return binDepartmentByName(arr+size/2, size - (size / 2), depName, resDep);
	}
}

////////////////////////////////////////

const char * Hospital::getDepartmentNameByIndex(int ind)
{
	return allDepartments[ind]->getName();
}

Department* Hospital::getDepartmentByIndex(int ind)
{
	if ((ind >= 0) && (ind < logSizeOfDepartments))
		return allDepartments[ind];
}

int Hospital::getNumOfDepartments()
{
	return logSizeOfDepartments;
}

bool Hospital::getPatientByID(char* inID, Patient* resPatient)
{
	if (phySizeOfPatients == 0)
		return false;
	else
		return binSearchPatientByID(allPatients, logSizeOfPatients, inID, resPatient);
}



bool Hospital::binSearchPatientByID(Patient** arr, int size, char* id, Patient* resPat)
{
	Patient* midPat = arr[size/2] ;
	int res = strcmp(id, midPat->getId());
	if (size == 1)
	{
		if (res == 0) 
		{
			resPat = midPat;
			return true;
		}
		else 
			return false;
	
	}
	else
	{
		int leftSize = size / 2;
		int rightSize = size - leftSize - 1;
		if (res == 0)
		{
			resPat = midPat;
			return true;
		}
		if (res < 0) // left side recursion
			return binSearchPatientByID(arr, leftSize, id, resPat);
		else if (res > 0) // right side recursion
			return binSearchPatientByID(arr+leftSize+1, rightSize, id, resPat);
	}
}

bool Hospital::validationEmployeeId(const int& employeeID)
{
	bool existDocId = false;
	bool existNurseId = false;
	if (logSizeDoctors)
		existDocId = veryfactionDoctorEmployeeIdBinSearch(allDoctors, logSizeDoctors, employeeID);
	if(logSizeNurses)
		existNurseId= veryfactionNurseEmployeeIdBinSearch(allNurses, logSizeNurses, employeeID);
	return (existDocId||existNurseId);
}

bool Hospital::veryfactionDoctorEmployeeIdBinSearch(Doctor** arr,int size,const int &employeeID)
{
	Doctor* midDoc = allDoctors[logSizeDoctors / 2];
	if (logSizeDoctors == 1)
	{
		if (midDoc->getEmployeeIDNum() == employeeID) 
			return true;
		else 
			return false;
	}
	else
	{
		if (midDoc->getEmployeeIDNum() == employeeID)
			return true;
		int mid = logSizeDoctors / 2;
		int firstSize = mid;
		int secondSize = size - mid-1;
		Doctor** firstArr = arr;
		Doctor** secondArr = arr + mid+1;
		if (midDoc->getEmployeeIDNum() > employeeID)
			return veryfactionDoctorEmployeeIdBinSearch(firstArr, firstSize, employeeID);
		else if(midDoc->getEmployeeIDNum() < employeeID)
			return veryfactionDoctorEmployeeIdBinSearch(secondArr, secondSize, employeeID);
		
	}
}

bool Hospital::veryfactionNurseEmployeeIdBinSearch(Nurse** arr, int size, const int &employeeID)
{
	if (size == 0)
		return false;
	Nurse* midNurse = arr[size / 2];
	if (size == 1)
	{
		if (midNurse->getEmployeeIDNum() == employeeID)
			return true;
		else
			return false;
	}
	else
	{
		if (midNurse->getEmployeeIDNum() == employeeID)
			return true;
		int mid = size / 2;
		int firstSize = mid;
		int secondSize = size - mid-1;
		Nurse** firstArr = arr;
		Nurse** secondArr = arr + mid+1;
		if (midNurse->getEmployeeIDNum() > employeeID)
			return veryfactionNurseEmployeeIdBinSearch(firstArr, firstSize, employeeID);
		else if (midNurse->getEmployeeIDNum() < employeeID)
			return veryfactionNurseEmployeeIdBinSearch(secondArr, secondSize, employeeID);

	}
}
int Hospital::findTheIndexOfDepNameInDepArr(char*str) const
{
	for (int i = 0; i < logSizeOfDepartments; i++)
	{
		if(strcmp(allDepartments[i]->getName(),str)==0)
			return i;
	}
	return -1;
}

bool Hospital:: addNurseToSpecificDepartment(Nurse & nurse, int indexToIn)
{
	allDepartments[indexToIn]->addNurse(nurse);
	return true;
}

bool Hospital::addDoctorToSpecificDepartment(Doctor & doctor, int indexToIn)
{
	allDepartments[indexToIn]->addDoctor(doctor);
	return true;

}

bool Hospital::findResearcherAccordingToName(const char*name, Researcher*researcher)
{
	return researchInst.getResearcherByName(name, researcher);
}

bool Hospital::addArticleToResearcher(Article & art, Researcher*researcher)
{
	return researchInst.addArticeToResearcher(art, researcher);
}


