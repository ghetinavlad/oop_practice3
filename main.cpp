#include "Testing.h"
#include <QtWidgets/QApplication>
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller actionController("issues.txt");
    actionController.loadUsersFromFile("users.txt");
    actionController.loadIssuesFromFile("issues.txt");
    Model* idea_model = new Model(actionController);
    std::vector<Testing*> windows;
    int i = 0;
    for (auto user : actionController.getAllUsers())
    {
        Testing* testing = new Testing(idea_model, actionController, user);
        windows.push_back(testing);
        actionController.add(testing);
        windows[i]->show();
        i++;

    }
    return a.exec();
}
