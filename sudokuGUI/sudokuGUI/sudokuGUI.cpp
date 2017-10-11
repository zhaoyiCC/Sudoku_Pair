#include "sudokuGUI.h"
#include "solver.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include <QMessageBox>
#define width 50
#define height 50
#define borderDistance 50
void sudokuGUI::update() {
	for (int i = 0; i < matrixLen; i++)
		for (int j = 0; j < matrixLen; j++)
			if (empty[i][j]) {
				bool ok = false;
				int x = btnFill[i][j].text().toInt(&ok, 10);
				if (ok)
					matrix[i][j] = x;
				else
					matrix[i][j] = -1;
			}
	if (solver.checkMatrix(matrix)) {
		result.setText("right!");
		int finishTime = timerCnt;
		string res[3];
		readRecordFile(res);
		int temp = atoi(res[difficultyChosen].c_str());
		if (temp == 0 || temp > finishTime)
			res[difficultyChosen] = to_string(finishTime);
		writeRecordFile(res);
	}
	else {
		result.setText("wrong!");
	}
}
void sudokuGUI::keyboardButtonClicked() {
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	if (btnTarget != NULL) {
		int j = (btnTarget->x() - borderDistance) / (width + 1);
		int i = (btnTarget->y() - borderDistance) / (height + 1);
		if (empty[i][j] == 1) {
			if (btn->text() == HINT) {
				int puzzle[83] = { 0 };
				int solution[83] = { 0 };
				for (int i = 0; i < matrixLen; i++)
					for (int j = 0; j < matrixLen; j++) {
						bool ok = false;
						int x = btnFill[i][j].text().toInt(&ok, 10);
						puzzle[i*matrixLen + j] = ok ? x : 0;
					}
				bool ok = core.solve(puzzle, solution);
				if (ok) {
					btnTarget->setText(QString::number(solution[i*matrixLen + j], 10));
				}
				else {
					QMessageBox::critical(this, "warning", "No solution");
				}
			}
			else if (btn->text() == CLEAR) {
				btnFill[i][j].setText("");
			}
			else {
				btnFill[i][j].setText(btn->text());
			}
		}
	}
}
void sudokuGUI::sudokuButtonClicked() {
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	if (btnTarget != NULL) {
		int j = (btnTarget->x() - borderDistance) / (width + 1);
		int i = (btnTarget->y() - borderDistance) / (height + 1);
		QString styleSheet_temp = (empty[i][j] == 1) ? btnEmptyStyle : btnNotEmptyStyle;
		btnTarget->setStyleSheet(styleSheet_temp);
	}
	btnTarget = btn;
	btnTarget->setStyleSheet(btnTargetStyle);
}
void sudokuGUI::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.setPen(QPen(Qt::red, 1));
	for (int i = 0; i < 2; i++) {
		painter.drawLine(borderDistance, borderDistance + (i + 1)*(height + 1) * 3 - 1,
			borderDistance + matrixLen*(width + 1) - 1, borderDistance + (i + 1)*(height + 1) * 3 - 1);
	}
	for (int i = 0; i < 2; i++) {
		painter.drawLine(borderDistance + (i + 1)*(width + 1) * 3 - 1, borderDistance,
			borderDistance + (i + 1)*(width + 1) * 3 - 1, borderDistance + matrixLen*(height + 1) - 1);
	}
}
void sudokuGUI::updateTimerLabel() {
	timerCnt++;
	timerLabel.setText(QString::number(timerCnt, 10));
}
void sudokuGUI::showRecord() {
	string res[3];
	string outS = "";
	readRecordFile(res);
	for (int i = 0; i < difficultyNum; i++) {
		outS += difficultyTypes[i] + ": " + res[i] + "\n";
	}
	QMessageBox::about(this, "record", outS.c_str());
}
void sudokuGUI::readRecordFile(string res[3]) {
	FILE *recordFile = fopen(recordFileName.c_str(), "r");
	if (recordFile == NULL) {
		FILE * newFile = fopen(recordFileName.c_str(), "w");
		fclose(newFile);
		recordFile = fopen(recordFileName.c_str(), "r");
	}
	char s[500] = { 0 };
	for (int i = 0; i < difficultyNum; i++) {
		fgets(s, 100, recordFile);
		if (atoi(s) == 0) {
			res[i] = "";
		}
		else {
			res[i] = to_string(atoi(s));
		}
	}
	fclose(recordFile);
}
void sudokuGUI::writeRecordFile(string res[3]) {
	FILE *recordFile = fopen(recordFileName.c_str(), "w");
	for (int i = 0; i < difficultyNum; i++) {
		fputs((res[i] + "\n").c_str(), recordFile);
	}
	fclose(recordFile);
}
void sudokuGUI::initMatrix() {
	int res[1][83] = { 0 };
	core.generate(1, difficultyChosen + 1, res);
	for (int i = 0; i < matrixLen; i++)
		for (int j = 0; j < matrixLen; j++)
			matrix[i][j] = res[0][i*matrixLen + j];
}

void sudokuGUI::newGame() {
	if (QMessageBox::question(this, "new game?", "abort this and new game?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
		return;
	}
	QAction *type = qobject_cast<QAction*>(sender());
	for (int i = 0; i < difficultyNum; i++)
		if (type->text().toStdString() == difficultyTypes[i]) {
			difficultyChosen = i;
			break;
		}
	init();
}
void sudokuGUI::init() {
	initMatrix();
	for (int i = 0; i < matrixLen; i++)
		for (int j = 0; j < matrixLen; j++)
			empty[i][j] = matrix[i][j] == 0;
	this->setWindowTitle("sudoku: " + QString::fromStdString(difficultyTypes[difficultyChosen]));
	for (int i = 0; i < matrixLen; i++) {
		for (int j = 0; j < matrixLen; j++) {
			QString text_temp = matrix[i][j] == 0 ? " " : QString::number(matrix[i][j], 10);
			QString styleSheet_temp = matrix[i][j] == 0 ? btnEmptyStyle : btnNotEmptyStyle;
			btnFill[i][j].setText(text_temp);
			btnFill[i][j].setStyleSheet(styleSheet_temp);
			btnFill[i][j].show();
		}
	}
	result.setText("result");
	result.show();

	timerCnt = 0;
	timerLabel.setText("0");
}
sudokuGUI::sudokuGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	btnFont.setBold(true);
	btnFont.setPixelSize(20);
	this->setFixedSize(width*matrixLen + 2 * borderDistance, height*(matrixLen + 1) + 2 * borderDistance + height);
	for (int i = 0; i < matrixLen; i++) {
		for (int j = 0; j < matrixLen; j++) {
			btnFill[i][j].setParent(this);
			btnFill[i][j].setGeometry(borderDistance + j*width + j, borderDistance + i*height + i, width, height);
			btnFill[i][j].setFont(btnFont);
			QObject::connect(&btnFill[i][j], SIGNAL(clicked()), this, SLOT(sudokuButtonClicked()));
		}
	}
	for (int i = 0; i < keyboardKeysNum; i++) {
		btnChoice[i].setParent(this);
		btnChoice[i].setText(btnChoiceContent[i]);
		btnChoice[i].setGeometry(borderDistance + i*width * 4 / 5, borderDistance + matrixLen*height + 5 + matrixLen, width * 4 / 5, height * 4 / 5);
		//btnChoice[i].setFont(btnFont);
		btnChoice[i].show();
		QObject::connect(&btnChoice[i], SIGNAL(clicked()), this, SLOT(keyboardButtonClicked()));
	}

	result.setParent(this);
	result.setGeometry(borderDistance + 2 * width, borderDistance + (matrixLen + 1)*height + matrixLen, width * 2, height / 2);

	btnSubmit.setText("submit");
	btnSubmit.setParent(this);
	btnSubmit.setGeometry(borderDistance + 4 * width, borderDistance + (matrixLen + 1)*height + matrixLen, width, height / 2);
	btnSubmit.show();
	QObject::connect(&btnSubmit, SIGNAL(clicked()), this, SLOT(update()));

	timer.setParent(this);
	timerLabel.setParent(this);
	timerLabel.setGeometry(borderDistance + 6 * width, borderDistance + (matrixLen + 1)*height + matrixLen, width, height / 2);
	timer.setInterval(1000);
	timer.start();
	QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(updateTimerLabel()));

	btnRecord.setParent(this);
	btnRecord.setGeometry(borderDistance + 7 * width, borderDistance + (matrixLen + 1)*height + matrixLen, width, height / 2);
	btnRecord.setText("record");
	btnRecord.show();
	QObject::connect(&btnRecord, SIGNAL(clicked()), this, SLOT(showRecord()));

	QObject::connect(ui.action, SIGNAL(triggered(bool)), this, SLOT(newGame()));
	QObject::connect(ui.action_2, SIGNAL(triggered(bool)), this, SLOT(newGame()));
	QObject::connect(ui.action_3, SIGNAL(triggered(bool)), this, SLOT(newGame()));

	init();
}
