#include "sudokuGUI.h"
#include <QtWidgets/QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <qstring.h>
#include <solver.h>
const int width = 50, height = 50;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	sudokuGUI w;
	w.show();
	return app.exec();
}
