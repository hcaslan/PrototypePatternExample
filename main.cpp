/**
* Example of 'Prototype' design pattern.
* The original of the study= https://refactoring.guru/design-patterns/factory-method/cpp/example
* This is a simplified and comment lines translated version of original.
*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
/** Record temel prototip */
class Record
{
public:
	virtual ~Record() {}
	virtual void print() = 0;
	virtual std::unique_ptr<Record> clone() = 0;
};

/** CarRecord somut prototip */
class CarRecord : public Record
{
private:
	std::string m_carName;
	int m_ID;

public:
	CarRecord(std::string carName, int ID) : m_carName(carName), m_ID(ID)
	{
	}

	void print() override
	{
		std::cout << "Car Record" << std::endl
			<< "Name  : " << m_carName << std::endl
			<< "Number: " << m_ID << std::endl << std::endl;
	}

	std::unique_ptr<Record> clone() override
	{
		return std::make_unique<CarRecord>(*this);
	}
};

/** BikeRecord somut prototip */
class BikeRecord : public Record
{
private:
	std::string m_bikeName;
	int m_ID;

public:
	BikeRecord(std::string bikeName, int ID) : m_bikeName(bikeName), m_ID(ID)
	{
	}

	void print() override
	{
		std::cout << "Bike Record" << std::endl
			<< "Name  : " << m_bikeName << std::endl
			<< "Number: " << m_ID << std::endl << std::endl;
	}

	std::unique_ptr<Record> clone() override
	{
		return std::make_unique<BikeRecord>(*this);
	}
};

/** PersonRecord somut prototip */
class PersonRecord : public Record
{
private:
	std::string m_personName;
	int m_age;

public:
	PersonRecord(std::string personName, int age) : m_personName(personName), m_age(age)
	{
	}

	void print() override
	{
		std::cout << "Person Record" << std::endl
			<< "Name : " << m_personName << std::endl
			<< "Age  : " << m_age << std::endl << std::endl;
	}

	std::unique_ptr<Record> clone() override
	{
		return std::make_unique<PersonRecord>(*this);
	}
};

/** Opak kayýt tipi, somut uygulamalarý ortaya çýkarmaktan kaçýnýr */
enum RecordType
{
	CAR,
	BIKE,
	PERSON
};

/**RecordFactory istemcidir */
class RecordFactory
{
private:
	std::unordered_map<RecordType, std::unique_ptr<Record>, std::hash<int> > m_records;

public:
	RecordFactory()
	{
		m_records[CAR] = std::make_unique<CarRecord>("Ferrari", 5050);
		m_records[BIKE] = std::make_unique<BikeRecord>("Yamaha", 2525);
		m_records[PERSON] = std::make_unique<PersonRecord>("Tom", 25);
	}

	std::unique_ptr<Record> createRecord(RecordType recordType)
	{
		return m_records[recordType]->clone();
	}
};

int main()
{
	RecordFactory recordFactory;

	auto record = recordFactory.createRecord(CAR);
	record->print();

	record = recordFactory.createRecord(BIKE);
	record->print();

	record = recordFactory.createRecord(PERSON);
	record->print();
}