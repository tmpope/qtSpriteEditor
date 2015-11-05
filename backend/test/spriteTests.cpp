#include "sprite.h"
#include "gtest/gtest.h"
#include <iostream>

int main(int argc, char** argv) 
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


void printPixel(Sprite& s, int x, int y) 
{
	std::cout << "-----------" << std::endl;
	for (int i = 0; i < s.getFrameCount(); i++) 
	{
		std::cout 
		<< s.getPixel(x, y, i).r 
		<< s.getPixel(x, y, i).g 
		<< s.getPixel(x, y, i).b 
		<< s.getPixel(x, y, i).a 
		<< std::endl;
	}
}

TEST(BasicCases, Instantiate) 
{
	Sprite sprite(10,10);
	EXPECT_EQ(10, sprite.getHeight());
	EXPECT_EQ(10, sprite.getWidth());
	EXPECT_EQ(1, sprite.getFrameCount());
}

TEST(BasicCases, Pointer) 
{
	Sprite* sprite;
	sprite = new Sprite(10,10);
	EXPECT_EQ(10, sprite->getHeight());
	EXPECT_EQ(10, sprite->getWidth());
	EXPECT_EQ(1, sprite->getFrameCount());
	delete sprite;
}

TEST(BasicCases, PointerReallocate) 
{
	Sprite* sprite;
	sprite = new Sprite(10,10);
	EXPECT_EQ(10, sprite->getHeight());
	EXPECT_EQ(10, sprite->getWidth());
	EXPECT_EQ(1, sprite->getFrameCount());
	delete sprite;
	sprite = new Sprite(4, 23436);
	sprite->addFrame();
	EXPECT_EQ(4, sprite->getHeight());
	EXPECT_EQ(23436, sprite->getWidth());
	EXPECT_EQ(2, sprite->getFrameCount());
	delete sprite;
}

TEST(Frames, RemoveEndFrames) 
{
	Sprite s(10, 10);
	EXPECT_EQ(1, s.getFrameCount());
	s.addFrame();
	s.addFrame();
	EXPECT_EQ(3, s.getFrameCount());
	s.removeFrame(2);
	EXPECT_EQ(2, s.getFrameCount());
	s.removeFrame(1);
	EXPECT_EQ(1, s.getFrameCount());
	s.removeFrame(0);
	EXPECT_EQ(0, s.getFrameCount());
}

TEST(Frames, RemoveMiddleFrames) 
{
	Sprite s(7, 32);
	EXPECT_EQ(1, s.getFrameCount());
	s.addFrame();
	s.addFrame();
	EXPECT_EQ(3, s.getFrameCount());
	s.removeFrame(1);
	EXPECT_EQ(2, s.getFrameCount());
}

TEST(Frames, RemoveBeginingFrames) 
{
	Sprite s(3, 100);
	EXPECT_EQ(1, s.getFrameCount());
	s.addFrame();
	s.addFrame();
	EXPECT_EQ(3, s.getFrameCount());
	s.removeFrame(0);
	EXPECT_EQ(2, s.getFrameCount());
	s.removeFrame(0);
	EXPECT_EQ(1, s.getFrameCount());
	s.removeFrame(0);
	EXPECT_EQ(0, s.getFrameCount());
}

TEST(Frames, RemoveCorrectFrames) 
{
	Sprite s(1, 1);
	s.addFrame();
	s.addFrame();
	s.setPixel(0, 0, 1, 5, 5, 5, 5);
	s.setPixel(0, 0, 2, 55, 55, 55, 55);
	struct Sprite::color defaultColor(255,255,255,0);
	struct Sprite::color frameOneColor(5, 5, 5, 5);
	struct Sprite::color frameTwoColor(55, 55, 55, 55);
	EXPECT_EQ(defaultColor, s.getPixel(0,0,0));
	EXPECT_EQ(frameOneColor, s.getPixel(0,0,1));
	EXPECT_EQ(frameTwoColor, s.getPixel(0,0,2));
	EXPECT_EQ(3, s.getFrameCount());
	s.removeFrame(0);
	EXPECT_EQ(2, s.getFrameCount());
	EXPECT_EQ(frameOneColor, s.getPixel(0,0,0));
	EXPECT_EQ(frameTwoColor, s.getPixel(0,0,1));
	s.addFrame();
	EXPECT_EQ(3, s.getFrameCount());
	EXPECT_EQ(frameOneColor, s.getPixel(0,0,0));
	EXPECT_EQ(frameTwoColor, s.getPixel(0,0,1));
	EXPECT_EQ(defaultColor, s.getPixel(0,0,2));
	s.removeFrame(1);
	EXPECT_EQ(2, s.getFrameCount());
	EXPECT_EQ(frameOneColor, s.getPixel(0,0,0));
	EXPECT_EQ(defaultColor, s.getPixel(0,0,1));
}

TEST(SetPixel, BasicSet) 
{
	Sprite s(5, 5);
	s.addFrame();
	s.addFrame();
	for (int i = 0; i < s.getFrameCount(); i++) 
	{
		for (int j = 0; j < s.getWidth(); j++)
		{
			for (int k = 0; k < s.getHeight(); k++)
			{
				s.setPixel(j, k, i, j, k, i, 0);
			}
		}
	}
	for (int i = 0; i < s.getFrameCount(); i++) 
	{
		for (int j = 0; j < s.getWidth(); j++)
		{
			for (int k = 0; k < s.getHeight(); k++)
			{
				struct Sprite::color check(j, k, i, 0);
				EXPECT_EQ(check, s.getPixel(j, k, i));
			}
		}
	}
}

TEST(Fill, FillBlankFrame) 
{
	Sprite s(3, 3);
	struct Sprite::color defaultColor(255,255,255,0);
	struct Sprite::color newColor(70, 70, 70, 70);
	for (int i = 0; i < s.getWidth(); i++) 
	{
		for (int j = 0; j < s.getHeight(); j++)
		{
			EXPECT_EQ(defaultColor, s.getPixel(i, j, 0));
		}
	}
	s.fillPixel(0, 0, 0, newColor);
	for (int i = 0; i < s.getWidth(); i++) 
	{
		for (int j = 0; j < s.getHeight(); j++)
		{
			EXPECT_EQ(newColor, s.getPixel(i, j, 0));
		}
	}
}

TEST(Export, GifExport) 
{
	FAIL(); //needs to be implemented to test somehow.
}

TEST(Export, ColorToString)
{
	struct Sprite::color c(1, 23, 249, 0);
	EXPECT_EQ("1 23 249 0", c.toString());
}

TEST(Export, ToString)
{
	Sprite s(2, 2);
	s.setPixel(0, 0, 0, 01, 02, 03, 04);
	s.setPixel(1, 0, 0, 21, 22, 23, 24);
	s.setPixel(0, 1, 0, 11, 12, 13, 14);
	s.setPixel(1, 1, 0, 31, 32, 33, 34);
	std::string expected("2 2\n1\n1 2 3 4 21 22 23 24\n11 12 13 14 31 32 33 34");
	EXPECT_EQ(expected, s.toString());
}

// TEST(BasicCases, AddSeveralUsers) {
// 	Students students = setup();
// 	EXPECT_EQ(1, students.idForName("Taylor"));
// 	EXPECT_EQ(2, students.idForName("Michael"));
// 	EXPECT_EQ(3, students.idForName("A"));
// 	EXPECT_EQ(4, students.idForName("B"));
// 	EXPECT_EQ(5, students.idForName("C"));
// 	EXPECT_EQ(6, students.idForName("D"));
// 	EXPECT_EQ(7, students.idForName("E"));
// 	EXPECT_EQ(8, students.idForName("F"));
// 	EXPECT_EQ(9, students.idForName("G"));
// 	EXPECT_EQ(10, students.idForName("H"));
// 	EXPECT_EQ(11, students.idForName("I"));
// 	EXPECT_EQ(12, students.idForName("J"));
// 	EXPECT_EQ(13, students.idForName("K"));
// 	EXPECT_EQ(14, students.idForName("L"));
// 	EXPECT_EQ(15, students.idForName("M"));
// }

// TEST(BasicCases, DuplicateName) {
// 	Students students = setup();
// 	students.addUser("Taylor", 15);
// 	EXPECT_EQ(1, students.idForName("Taylor"));
// 	EXPECT_EQ(2, students.idForName("Michael"));
// 	EXPECT_EQ(3, students.idForName("A"));
// 	EXPECT_EQ(4, students.idForName("B"));
// 	EXPECT_EQ(5, students.idForName("C"));
// 	EXPECT_EQ(6, students.idForName("D"));
// 	EXPECT_EQ(7, students.idForName("E"));
// 	EXPECT_EQ(8, students.idForName("F"));
// 	EXPECT_EQ(9, students.idForName("G"));
// 	EXPECT_EQ(10, students.idForName("H"));
// 	EXPECT_EQ(11, students.idForName("I"));
// 	EXPECT_EQ(12, students.idForName("J"));
// 	EXPECT_EQ(13, students.idForName("K"));
// 	EXPECT_EQ(14, students.idForName("L"));
// 	EXPECT_EQ(15, students.idForName("Taylor"));
// }

// TEST(BasicCases, addPhoneNumbers) {
// 	Students students = setup();
// 	students.addPhoneNumbers(1, "801-997-8550");
// 	students.addPhoneNumbers(2, "801-450-6886");
// 	EXPECT_EQ("801-997-8550", students.phoneForName("Taylor"));
// 	EXPECT_EQ("801-450-6886", students.phoneForName("Michael"));
// }

// TEST(BasicCases, addGrade) {
// 	Students students = setup();
// 	students.addGrade(1, 'A');
// 	students.addGrade(2, 'B');
// 	students.addGrade(5, 'C');
// 	students.addGrade(6, 'D');
// 	students.addGrade(7, 'E');
// 	students.addGrade(8, 'F');
// 	students.addGrade(9, 'G');
// 	students.addGrade(10, 'H');
// 	students.addGrade(11, 'I');
// 	students.addGrade(12, 'J');
// 	students.addGrade(13, 'K');
// 	students.addGrade(14, '*');
// 	EXPECT_EQ('A', students.gradeForName("Taylor"));
// 	EXPECT_EQ('B', students.gradeForName("Michael"));
// 	EXPECT_EQ('C', students.gradeForName("C"));
// 	EXPECT_EQ('D', students.gradeForName("D"));
// 	EXPECT_EQ('E', students.gradeForName("E"));
// 	EXPECT_EQ('F', students.gradeForName("F"));
// 	EXPECT_EQ('G', students.gradeForName("G"));
// 	EXPECT_EQ('H', students.gradeForName("H"));
// 	EXPECT_EQ('I', students.gradeForName("I"));
// 	EXPECT_EQ('J', students.gradeForName("J"));
// 	EXPECT_EQ('K', students.gradeForName("K"));
// 	EXPECT_EQ('*', students.gradeForName("L"));
// }

// TEST(BasicCases, nameExists) {
// 	Students students = setup();
// 	EXPECT_EQ(true, students.nameExists("Taylor"));
// 	EXPECT_EQ(true, students.nameExists("Michael"));
// 	EXPECT_EQ(true, students.nameExists("C"));
// 	EXPECT_EQ(true, students.nameExists("D"));
// 	EXPECT_EQ(true, students.nameExists("E"));
// 	EXPECT_EQ(true, students.nameExists("F"));
// 	EXPECT_EQ(true, students.nameExists("G"));
// 	EXPECT_EQ(true, students.nameExists("H"));
// 	EXPECT_EQ(true, students.nameExists("I"));
// 	EXPECT_EQ(true, students.nameExists("J"));
// 	EXPECT_EQ(true, students.nameExists("K"));
// 	EXPECT_EQ(true, students.nameExists("L"));
// 	EXPECT_EQ(true, !students.nameExists("notH"));
// 	EXPECT_EQ(true, !students.nameExists("notI"));
// 	EXPECT_EQ(true, !students.nameExists("notJ"));
// 	EXPECT_EQ(true, !students.nameExists("notK"));
// 	EXPECT_EQ(true, !students.nameExists("notL"));
// }

// TEST(BasicCases, fullRecord) {
// 	Students students = setup();
// 	unsigned int id = 0;
// 	std::string phoneNumber;
// 	char grade;
// 	EXPECT_EQ(true, !students.fullRecord("Taylor", id, phoneNumber, grade));
// 	students.addPhoneNumbers(1, "Phone");
// 	students.addGrade(1, 'A');
// 	EXPECT_EQ(true, students.fullRecord("Taylor", id, phoneNumber, grade));
// 	EXPECT_EQ(students.idForName("Taylor"), id);
// 	EXPECT_EQ(students.phoneForName("Taylor"), phoneNumber);
// 	EXPECT_EQ('A', grade);
// }

// TEST(BasicCases, numberOfNames) {
// 	Students students = setup();
// 	EXPECT_EQ(15, students.numberOfNames());
// }

// TEST(BasicCases, removeStudentAndNumberOfNames) {
// 	Students students = setup();
// 	students.removeStudent("Taylor");
// 	students.removeStudent("A");
// 	students.removeStudent("B");
// 	students.removeStudent("C");
// 	students.removeStudent("D");
// 	students.removeStudent("E");
// 	students.removeStudent("F");
// 	students.removeStudent("G");
// 	students.removeStudent("H");
// 	EXPECT_EQ(6, students.numberOfNames());
// }

// TEST(BasicCases, removeList) {
// 	Students students = setup();
// 	std::vector<std::string> names;
// 	EXPECT_EQ(15, students.numberOfNames());
// 	names.push_back("Taylor");
// 	names.push_back("A");
// 	names.push_back("B");
// 	names.push_back("C");
// 	names.push_back("D");
// 	names.push_back("E");
// 	names.push_back("F");
// 	names.push_back("G");
// 	names.push_back("H");
// 	students.removeList(names);
// 	EXPECT_EQ(9, names.size());
// 	EXPECT_EQ(6, students.numberOfNames());
// }

// TEST(BasicCases, removeListOfOne) {
// 	Students students;
// 	students.addUser("Taylor", 1);
// 	std::vector<std::string> names;
// 	EXPECT_EQ(1, students.numberOfNames());
// 	names.push_back("Taylor");
// 	students.removeList(names);
// 	EXPECT_EQ(1, names.size());
// 	EXPECT_EQ(0, students.numberOfNames());
// }

// TEST(BasicCases, removeListOfTwo) {
// 	Students students;
// 	students.addUser("Taylor", 1);
// 	students.addUser("Michael", 2);
// 	std::vector<std::string> names;
// 	EXPECT_EQ(1, students.numberOfNames());
// 	names.push_back("Taylor");
// 	names.push_back("Michael");
// 	students.removeList(names);
// 	EXPECT_EQ(2, names.size());
// 	EXPECT_EQ(0, students.numberOfNames());
// }

// TEST(EdgeCase, doubleRemove) {
// 	Students students = setup();
// 	try {
// 		students.removeStudent("Taylor");
// 		students.removeStudent("Taylor");
// 		FAIL();
// 	}
// 	catch(...) {

// 	}
// }

// TEST(EdgeCase, getIdRemovedUser) {
// 	Students students = setup();
// 	students.addPhoneNumbers(1, "Phone");
// 	students.addGrade(1, 'A');
// 	students.removeStudent("Taylor");
// 	EXPECT_EQ(14, students.numberOfNames());
// 	try {
// 		int id = students.idForName("Taylor");
// 		FAIL();
// 	}
// 	catch(...) {

// 	}
// }

// TEST(EdgeCase, thowExceptionOnPhoneForNameUndefined) {
// 	Students students;
// 	EXPECT_EQ(0, students.numberOfNames());
// 	try {
// 		std::string s = students.phoneForName("Taylor");
// 		FAIL();
// 	}
// 	catch(...) {

// 	}
// }

// TEST(EdgeCase, thowExceptionOnIdForNameUndefined) {
// 	Students students;
// 	EXPECT_EQ(0, students.numberOfNames());
// 	try {
// 		int id = students.idForName("Taylor");
// 		FAIL();
// 	}
// 	catch(...) {

// 	}
// }

// TEST(EdgeCase, thowExceptionOnGradeForNameUndefined) {
// 	Students students;
// 	EXPECT_EQ(0, students.numberOfNames());
// 	try {
// 		char c = students.gradeForName("Taylor");
// 		FAIL();
// 	}
// 	catch(...) {

// 	}
// }