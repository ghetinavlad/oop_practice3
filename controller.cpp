#pragma once
#include "controller.h"
#include <algorithm>
#include <fstream>

Controller::Controller(std::string taskFilePath) {
	this->taskFilePath = taskFilePath;
}

std::vector <User> Controller::getAllUsers() {
	return this->elements.getAllUsers();
}

std::vector<Issue> Controller::getAllIssues() {
	std::vector<Issue>allIssues = this->elements.getAllIssues();
	sort(allIssues.begin(), allIssues.end(), [](Issue first, Issue second)
		{
			if (first.getStatus() == second.getStatus()) {
				return first.getDescription() < second.getDescription();
			}
			else {
				return first.getStatus() < second.getStatus();
			}

		}
	);
	return allIssues;
}


Controller::~Controller() {
	if (taskFilePath.length() != 0) {
		this->updateFile(taskFilePath);
	}
}

void Controller::loadUsersFromFile(std::string filePath) {
	this->elements.loadUsersFromFile(filePath);
}

void Controller::loadIssuesFromFile(std::string filePath) {
	this->elements.loadIssuesFromFile(filePath);
}

void Controller::updateFile(std::string filePath) {
	std::fstream outputStream(filePath);
	std::vector<Issue> allIssues = this->elements.getAllIssues();

	for (auto issue : allIssues) {
		outputStream << issue.toString() << "\n";
	}

	outputStream.close();
}

void Controller::addIssue(std::string description, std::string name) {
	this->elements.addIssue(description, name);
	this->updateFile("issues.txt");
	this->notify();
}

void Controller::removeIssue(std::string description) {
	this->elements.removeIssue(description);
	this->updateFile("issues.txt");
	this->notify();
}

void Controller::resolveIssue(Issue issue) {
	this->elements.resolveIssue(issue);
	this->updateFile("issues.txt");
	this->notify();
}




