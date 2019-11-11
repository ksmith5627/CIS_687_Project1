// Filename		: TestObject.h
// Summary		: Defines the object that'll hold the deserialized XML for each test within the test request.
// Description	: Since the test request contains a TestDriver and a series of TestedCodes, this file declares
//				  the class that can hold that data, and uses the boost::serialization library to deserialize
//				  the XML into an object instance.
//				  It also provides a static method to deserialize XML into a list of test objects.

//				  Most of the code on this file was inspired by the boost documentation at
//				  https://www.boost.org/doc/libs/1_67_0/libs/serialization/doc/serialization.html


#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/list.hpp>
#include <boost/archive/xml_iarchive.hpp>

#include <iostream>
#include <fstream>

class TestObject
{
	friend class boost::serialization::access;
	std::list<std::string> TestDrivers;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int) {
		ar	& BOOST_SERIALIZATION_NVP(TestDrivers);
	}

public:
	TestObject() {};
	TestObject(std::list<std::string> drivers) :
		TestDrivers(drivers){};

	static TestObject DeserializeXml(const char* pathToXml)
	{
		std::ifstream inputFile(pathToXml);
		assert(inputFile.good());
		boost::archive::xml_iarchive archive(inputFile, boost::archive::no_header);
		TestObject testObject;
		archive >> BOOST_SERIALIZATION_NVP(testObject);

		return testObject;
	}

	std::list<std::string> GetTestDrivers()
	{
		return TestDrivers;
	}
};

BOOST_CLASS_IMPLEMENTATION(TestObject, boost::serialization::object_serializable);
BOOST_CLASS_IMPLEMENTATION(std::list<std::string>, boost::serialization::object_serializable);
BOOST_CLASS_IMPLEMENTATION(std::list<TestObject>, boost::serialization::object_serializable);

BOOST_CLASS_TRACKING(TestObject, boost::serialization::track_never);
BOOST_CLASS_TRACKING(std::list<std::string>, boost::serialization::track_never);
BOOST_CLASS_TRACKING(std::list<TestObject>, boost::serialization::track_never);

#endif // !TESTOBJECT_H