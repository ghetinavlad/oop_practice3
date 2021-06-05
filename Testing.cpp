#include "Testing.h"
#include <qmessagebox.h>
#include <qboxlayout.h>

Testing::Testing(Model* idea_model, Controller& controller, User user, QWidget* parent)
	: controller{ controller }, user{ user }, idea_model{ idea_model }, QMainWindow(parent)
{
	ui.setupUi(this);

	this->setWindowTitle(QString::fromStdString(user.getName() + " " +  user.getType()));

	if (user.getType() == "tester") {
		this->ui.add_button->setVisible(true);
		this->ui.resolve_button->setVisible(false);
	}
	else {
		this->ui.add_button->setVisible(false);
		this->ui.resolve_button->setVisible(true);
	}


	this->connectSignals();
	this->ui.tableView->setModel(idea_model);
	ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	this->ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	this->ui.tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
}

void Testing::connectSignals()
{
	QObject::connect(this->ui.add_button, &QPushButton::clicked, this, &Testing::add_issue);
	QObject::connect(this->ui.remove_button, &QPushButton::clicked, this, &Testing::remove_issue);
	QObject::connect(this->ui.resolve_button, &QPushButton::clicked, this, &Testing::resolve_issue);
	QObject::connect(this->ui.tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(toggleButton(QModelIndex)));
	//QObject::connect(this->ui.priceSlider, &QSlider::valueChanged, this, &GUI::filter_products);

}
void Testing::update()
{
}

void Testing::add_issue() //takes what it needs from the window and calls Service::add_star() if no exceptions are thrown
{


	try
	{
		std::string description = this->ui.description_line_edit->text().toStdString();
	
		try {
			this->controller.addIssue(description, user.getName());
		}
		catch (const std::exception& exception)
		{
			QMessageBox::critical(this, "Error", "Invalid Input!");

		}
		this->idea_model->insert_row();
		emit this->idea_model->dataChanged(this->idea_model->index(0, 0), this->idea_model->index(this->controller.getAllIssues().size() + 1, 3));
	}
	catch (const std::exception& exception)
	{
		QMessageBox::critical(this, "Error", "Invalid Input!");

	}

}

void Testing::remove_issue() //takes what it needs from the window and calls Service::add_star() if no exceptions are thrown
{


	try
	{
		std::string description = this->ui.description_line_edit->text().toStdString();

		try {
			this->controller.removeIssue(description);
		}
		catch (const std::exception& exception)
		{
			QMessageBox::critical(this, "Error", "Invalid Input!");
			
		}
		this->idea_model->remove_row();
		emit this->idea_model->dataChanged(this->idea_model->index(0, 0), this->idea_model->index(this->controller.getAllIssues().size() + 1, 3));
	}
	catch (const std::exception& exception)
	{
		QMessageBox::critical(this, "Error", "Invalid Input!");

	}

}
void Testing::toggleButton(const QModelIndex& index)
{
	Issue issue = this->getSelectedIssue();
	if (issue.getStatus() == "open") {
		this->ui.resolve_button->setEnabled(true);
	}
	else {
		this->ui.resolve_button->setEnabled(false);
	}
	
}

Issue Testing::getSelectedIssue() {
	QModelIndexList selection = this->ui.tableView->selectionModel()->selectedIndexes();

	if (selection.count() == 0) {
		return Issue();
	}

	// in initializeGUI we have set the selection model to single selection,
	//so we know there is exactly 1 element selected at a time
	QModelIndex index = selection.at(0);
	int row = index.row(); // the row of the element is the index of the element in the list

	// if we have the constellation mode, we will need to check another list
	

	return this->controller.getAllIssues()[row];
}
void Testing::resolve_issue()
{
	Issue issue = this->getSelectedIssue();
	std::string description = issue.getDescription();
	std::string solver = user.getName();
	std::string reporter = issue.getReporter();
	std::string status = issue.getStatus();
	Issue newIssue = Issue(description, status, reporter, solver);
	this->controller.resolveIssue(newIssue);
	emit this->idea_model->dataChanged(this->idea_model->index(0, 0), this->idea_model->index(this->controller.getAllIssues().size() + 1, 3));
}
