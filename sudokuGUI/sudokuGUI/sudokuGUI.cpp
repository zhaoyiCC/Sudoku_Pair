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
	painter.setPen(QPen(Qt::blue, 1));
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
		}else {
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
sudokuGUI::sudokuGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	solver.buildMatrix(matrix);
	for (int i = 0; i < matrixLen; i++)
		for (int j = 0; j < matrixLen; j++)
			empty[i][j] = matrix[i][j] == 0;
	this->setWindowTitle("sudoku");
	this->setFixedSize(width*matrixLen + 2 * borderDistance, height*(matrixLen + 1) + 2 * borderDistance + height);
	for (int i = 0; i < matrixLen; i++) {
		for (int j = 0; j < matrixLen; j++) {
			btnFill[i][j].setParent(this);
			QString text_temp = matrix[i][j] == 0 ? " " : QString::number(matrix[i][j], 10);
			QString styleSheet_temp = matrix[i][j] == 0 ? btnEmptyStyle : btnNotEmptyStyle;
			btnFill[i][j].setText(text_temp);
			btnFill[i][j].setGeometry(borderDistance + j*width + j, borderDistance + i*height + i, width, height);
			//btnFill[i][j].setStyleSheet("QPushButton{background-color:gray; color: black;   border - radius: 10px;  border: 1px groove gray; border - style: outset;}" "QPushButton:hover{background-color:green; color: black;}""QPushButton:pressed{background-color:rgb(85, 170, 255);border - style: inset;}");
			btnFill[i][j].setStyleSheet(styleSheet_temp);
			btnFill[i][j].show();
			QObject::connect(&btnFill[i][j], SIGNAL(clicked()), this, SLOT(sudokuButtonClicked()));
		}
	}
	for (int i = 0; i < keyboardKeysNum; i++) {
		btnChoice[i].setParent(this);
		btnChoice[i].setText(btnChoiceContent[i]);
		btnChoice[i].setGeometry(borderDistance + i*width * 4 / 5, borderDistance + matrixLen*height + 5 + matrixLen, width * 4 / 5, height * 4 / 5);
		btnChoice[i].show();
		QObject::connect(&btnChoice[i], SIGNAL(clicked()), this, SLOT(keyboardButtonClicked()));
	}
	result.setText("result");
	result.setParent(this);
	result.setGeometry(borderDistance + 2 * width, borderDistance + (matrixLen + 1)*height + matrixLen, width * 2, height / 2);
	result.show();
	btnSubmit.setText("submit");
	btnSubmit.setParent(this);
	btnSubmit.setGeometry(borderDistance + 4 * width, borderDistance + (matrixLen + 1)*height + matrixLen, width, height / 2);
	btnSubmit.show();
	QObject::connect(&btnSubmit, SIGNAL(clicked()), this, SLOT(update()));
	timer.setParent(this);
	timerLabel.setParent(this);
	timerLabel.setGeometry(borderDistance + 6 * width, borderDistance + (matrixLen + 1)*height + matrixLen, width, height / 2);
	timerLabel.setText("0");
	timer.setInterval(1000);
	timer.start();
	QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(updateTimerLabel()));
	btnRecord.setParent(this);
	btnRecord.setGeometry(borderDistance + 7 * width, borderDistance + (matrixLen + 1)*height + matrixLen, width, height / 2);
	btnRecord.setText("record");
	QObject::connect(&btnRecord, SIGNAL(clicked()), this, SLOT(showRecord()));
}
