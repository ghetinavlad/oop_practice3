#include "domain.h"

User::User() {
	this->name = "";
	this->type = "";
}

User::User(std::string name, std::string type) {
	this->name = name;
	this->type = type;
}

std::string User::toString() {
	std::string representation;

	representation += (this->name  + " | ");
	representation += (this->type);


	return representation;
}

std::string User::getName() const {
	return this->name;
}

std::string User::getType() const {
	return this->type;
}


Issue::Issue() {
	this->description = "";
	this->status = "";
	this->reporter = "";
	this->solver = "";
}

Issue::Issue(std::string description, std::string status, std::string reporter, std::string solver) {
	this->description = description;
	this->status = status;
	this->reporter = reporter;
	this->solver = solver;
}

std::string Issue::toString() {
	std::string representation;

	representation += (this->description  + " | ");
	representation += (this->status  + " | ");
	representation += (this->reporter  + " | ");
	representation += (this->solver);


	return representation;
}

std::string Issue::getDescription() const {
	return this->description;
}

std::string Issue::getStatus() const {
	return this->status;
}

std::string Issue::getReporter() const {
	return this->reporter;
}

std::string Issue::getSolver() const {
	return this->solver;
}

void Issue::setSolver(std::string newSolver) {
	this->solver = newSolver;
}
