#pragma once
#include "Controller.h"
#include <QtWidgets/QMainWindow>
#include "ui_Testing.h"
#include "Model.h"

class Testing : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    Testing(Model* idea_model, Controller& controller, User user,  QWidget* parent = Q_NULLPTR);
    void update() override;

private:
    Ui::TestingClass ui;
    Controller& controller;
    User user;
    Model* idea_model;
    void connectSignals();

public slots:
    void add_issue();
    void remove_issue();
    void resolve_issue();
    void toggleButton(const QModelIndex& index);
    Issue getSelectedIssue();
    //void search_by_name();

};