#pragma once
#include "repository.h"
#include "Subject.h"
#include <vector>

class Controller : public Subject {
private:
	Repository elements;
	std::string taskFilePath;

public:
	Controller(std::string taskFilePath);
	std::vector<User> getAllUsers();
	std::vector<Issue> getAllIssues();
	~Controller();
	void loadUsersFromFile(std::string filePath);
	void loadIssuesFromFile(std::string filePath);
	void addIssue(std::string description, std::string name);
	void removeIssue(std::string description);
	void resolveIssue(Issue issue);
	void updateFile(std::string filePath);

};