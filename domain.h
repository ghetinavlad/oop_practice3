#pragma once
#include <string>

class User {
private:
	std::string name;
	std::string type;

public:
	User();
	User(std::string name, std::string type);
	std::string toString();
	std::string getName() const;
	std::string getType() const;
};

class Issue {
private:
	std::string description;
	std::string status;
	std::string reporter;
	std::string solver;

public:
	Issue();
	Issue(std::string description, std::string status, std::string reporter, std::string solver);
	std::string toString();
	std::string getDescription() const;
	std::string getStatus() const;
	std::string getReporter() const;
	std::string getSolver() const;
	void setSolver(std::string newSolver);
};