#include "repository.h"
#include <fstream>

Repository::Repository() {
	;
}

std::vector <User> Repository::getAllUsers() {
	return this->users;
}

std::vector <Issue> Repository::getAllIssues() {
	return this->issues;
}


void Repository::loadUsersFromFile(std::string filePath) {
	const int NAME_POSITION = 0;
	

	std::fstream inputStream(filePath);
	std::string currentLine;

	std::string name;
	std::string type;

	this->users.clear();

	while (std::getline(inputStream, currentLine)) {
		int separatorPosition = currentLine.find("|");
		int propertyPosition = 0;

		while (separatorPosition != std::string::npos) {
			// subtract 1 from the separator position because there is a space between the property and the separator;
			// this substr will stop just before "separatorPosition - 1" => it will include the entire property
			// and nothing else
			std::string currentProperty = currentLine.substr(0, separatorPosition - 1);

			// add 2 to the separator position because there is a space between the separator and the next property
			// we then subtract 1 from "currentLine.length() - separatorPosition" in order to avoid that space
			currentLine = currentLine.substr(separatorPosition + 2, currentLine.length() - separatorPosition - 1);
			separatorPosition = currentLine.find("|");

			if (propertyPosition == NAME_POSITION) {
				name = currentProperty;
			}
		

			propertyPosition++;
		}

		// the last property remains outside the while loop, we treat it separately
		type = currentLine;

		this->users.push_back(User(name,type));
	}

	inputStream.close();
}


void Repository::loadIssuesFromFile(std::string filePath) {
	const int DESCRIPTION_POSITION = 0;
	const int STATUS_POSITION = 1;
	const int REPORTER_POSITION = 2;

	std::fstream inputStream(filePath);
	std::string currentLine;

	std::string description;
	std::string status;
	std::string reporter;
	std::string solver;

	this->issues.clear();

	while (std::getline(inputStream, currentLine)) {
		int separatorPosition = currentLine.find("|");
		int propertyPosition = 0;

		while (separatorPosition != std::string::npos) {
			// subtract 1 from the separator position because there is a space between the property and the separator;
			// this substr will stop just before "separatorPosition - 1" => it will include the entire property
			// and nothing else
			std::string currentProperty = currentLine.substr(0, separatorPosition - 1);

			// add 2 to the separator position because there is a space between the separator and the next property
			// we then subtract 1 from "currentLine.length() - separatorPosition" in order to avoid that space
			currentLine = currentLine.substr(separatorPosition + 2, currentLine.length() - separatorPosition - 1);
			separatorPosition = currentLine.find("|");

			if (propertyPosition == DESCRIPTION_POSITION) {
				description = currentProperty;
			}
			else if (propertyPosition == STATUS_POSITION) {
				status = currentProperty;
			}
			else if (propertyPosition == REPORTER_POSITION) {
				reporter = currentProperty;
			}

			propertyPosition++;
		}

		// the last property remains outside the while loop, we treat it separately
		solver = currentLine;

		this->issues.push_back(Issue(description, status, reporter, solver));
	}

	inputStream.close();
}

void Repository::addIssue(std::string description, std::string name) {
	if (description == "")
		throw std::exception("Description must not be empty");

	for (auto issue : this->issues) {
		if (issue.getDescription() == description) {
			throw std::exception("Issue already exists");
		}
	}

	this->issues.push_back(Issue(description, "open", name, ""));
}

void Repository::removeIssue(std::string description) {
	if (description == "")
		throw std::exception("Description must not be empty");

	int i = 0;
	for (auto issue : this->issues) {
		if (issue.getDescription() == description && issue.getStatus() == "closed") {
			this->issues.erase(this->issues.begin() + i);
			break;
		}
		i++;
	}
}
void Repository::resolveIssue(Issue newIssue) {
	
	int i = 0;
	for (auto issue : this->issues) {
		if (issue.getDescription() == newIssue.getDescription() ) {
			this->issues.erase(this->issues.begin() + i);
			break;
		}
		i++;
	}
	this->issues.push_back(newIssue);
}

Repository::~Repository() {
	;
}