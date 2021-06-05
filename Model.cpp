#include "Model.h"

int Model::rowCount(const QModelIndex& parent) const
{

	return controller.getAllIssues().size() + 1;
}

int Model::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant Model::data(const QModelIndex& index, int role) const
{
	int line = index.row();
	int column = index.column();

	if (line == rowCount() - 1)
	{
		return QVariant();
	}

	Issue issue = this->controller.getAllIssues().at(line);

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		if (column == 0)
		{
			return QString::fromStdString(issue.getDescription());
		}
		else if (column == 1)
		{
			return QString::fromStdString(issue.getStatus());
		}

		else if (column == 2)
		{
			return QString::fromStdString(issue.getReporter());
		}

		else if (column == 3)
		{
			return QString::fromStdString(issue.getSolver());
		}

	}

	return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		switch (section)
		{
		case 0:
			return QString::fromStdString("Description");
		case 1:
			return QString::fromStdString("Status");
		case 2:
			return QString::fromStdString("Reporter");
		case 3:
			return QString::fromStdString("Solver");
		default:
			break;
		}
	}

	return QVariant();
}

Qt::ItemFlags Model::flags(const QModelIndex& index) const {
	return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

void Model::insert_row()
{
	beginInsertRows(QModelIndex(), this->controller.getAllIssues().size(), this->controller.getAllIssues().size());
	endInsertRows();
}

void Model::remove_row()
{
	beginRemoveRows(QModelIndex(), this->controller.getAllIssues().size(), this->controller.getAllIssues().size());
	endRemoveRows();

}

