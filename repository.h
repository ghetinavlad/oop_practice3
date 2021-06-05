#include <vector>
#include "domain.h"


class Repository {
private:
	std::vector <User> users;
	std::vector <Issue> issues;

public:
	Repository();
	std::vector <User> getAllUsers();
	std::vector <Issue> getAllIssues();
	void loadUsersFromFile(std::string filePath);
	void loadIssuesFromFile(std::string filePath);
	void addIssue(std::string description, std::string name);
	void removeIssue(std::string description);
	void resolveIssue(Issue issue);


	~Repository();
};