#include "researcher.h"


Researcher::Researcher(const char inName[MAX_NAME]) 
	: StaffMember(inName)
{
	articleStock = nullptr;
	logSizeOfArticles = 0;
	phySizeOfArticles = 0;
}

Researcher::Researcher(const Researcher& other) :
	StaffMember(other)
{
	if (this != &other)
	{
		int i;
		for (i = 0; i < logSizeOfArticles; i++)
			delete articleStock[i];
		delete []articleStock;
		this->logSizeOfArticles = other.logSizeOfArticles;
		this->phySizeOfArticles = other.phySizeOfArticles;
		for (i = 0; i < logSizeOfArticles; i++)
			articleStock[i]=new Article(*(other.articleStock[i]));
	}
}


Researcher::~Researcher()
{
	for (int i = 0; i < logSizeOfArticles; i++)
		delete articleStock[i];
	delete[] articleStock;
}

void Researcher::addArticle(Article& art)
{
	allocationArticlesArr();
	articleStock[logSizeOfArticles] = &art;
	logSizeOfArticles++;
}

void Researcher:: allocationArticlesArr()
{
	if (phySizeOfArticles == 0) // If this is the 1st Department
	{
		articleStock = new Article*;
		phySizeOfArticles++;
	}
	else if (logSizeOfArticles == phySizeOfArticles) //if there is no place in the array
	{
		phySizeOfArticles *= 2;
		Article** newArr = new Article*[phySizeOfArticles];
		for (int i = 0; i < logSizeOfArticles; i++)
		{
			newArr[i] = articleStock[i];
		}
		delete[] articleStock;
		articleStock = newArr;
	}
	else
		return;
}

void Researcher::showArticles() const
{
	if (logSizeOfArticles)
	{
		for (int i = 0; i < logSizeOfArticles; i++)
		{
			cout << "Article name: " << articleStock[i]->getName() << endl;
			cout << "Magazine in which was published: " << articleStock[i]->getMagazineName() << endl;;
			cout << "Publication date: ";
			articleStock[i]->showDate();
			cout << endl;
		}
	}
	else
		cout << "There is no article for this researcher" << endl;
}

bool Researcher::operator>(const Researcher& other) const
{
	return (this->logSizeOfArticles > other.logSizeOfArticles);
}

void Researcher::print(ostream& os) const
{
	StaffMember::print(os);
	os << "\tRole: Researcher." << "\n\tResearchers Published: " << this->logSizeOfArticles;
}





