#include "sudokuGUI.h"
#include "solver.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include <QMessageBox>
#define GRID_WIDTH 50
#define GRID_HEIGHT 50
#define borderDistance 50
void sudokuGUI::gameStart() {
	timer.start();
	m_widget.setCurrentIndex(1);
	btnStart.setText("Resume");
	btnSetting.setVisible(false);
}
void sudokuGUI::gameSetting() {
	QMessageBox mess(QMessageBox::Information, tr("Setting"), tr("Set difficulty"));
	QPushButton *btn[difficultyNum];
	for (int i = 0; i < difficultyNum; i++)
		btn[i] = (mess.addButton(difficultyTypes[i].c_str(), QMessageBox::AcceptRole));
	mess.exec();
	for (int i = 0; i < difficultyNum; i++)
		if (btn[i] == mess.clickedButton()) {
			setDifficulty(i);
			break;
		}
}
void sudokuGUI::keyboardButtonClicked() {
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	if (btnTarget != NULL) {
		int j = (btnTarget->x() - borderDistance) / (GRID_WIDTH + 1);
		int i = (btnTarget->y() - borderDistance) / (GRID_HEIGHT + 1);
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
					QMessageBox::critical(&gameWindow, "warning", "No solution");
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
		int j = (btnTarget->x() - borderDistance) / (GRID_WIDTH + 1);
		int i = (btnTarget->y() - borderDistance) / (GRID_HEIGHT + 1);
		QString styleSheet_temp = (empty[i][j] == 1) ? btnEmptyStyle : btnNotEmptyStyle;
		btnTarget->setStyleSheet(styleSheet_temp);
	}
	btnTarget = btn;
	btnTarget->setStyleSheet(btnTargetStyle);
}

void sudokuGUI::gameToCover() {
	m_widget.setCurrentIndex(0);
	timer.stop();
}

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
		timer.stop();
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

void sudokuGUI::paintEvent(QPaintEvent *event) {
	QPainter painter(&gameWindow);
	painter.setPen(QPen(Qt::blue, 1));
	for (int i = 0; i < 2; i++) {
		painter.drawLine(borderDistance, borderDistance + (i + 1)*(GRID_HEIGHT + 1) * 3 - 1,
			borderDistance + matrixLen*(GRID_WIDTH + 1) - 1, borderDistance + (i + 1)*(GRID_HEIGHT + 1) * 3 - 1);
	}
	for (int i = 0; i < 2; i++) {
		painter.drawLine(borderDistance + (i + 1)*(GRID_WIDTH + 1) * 3 - 1, borderDistance,
			borderDistance + (i + 1)*(GRID_WIDTH + 1) * 3 - 1, borderDistance + matrixLen*(GRID_HEIGHT + 1) - 1);
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
		outS += difficultyTypes[i] + ": " + res[i] + "s"+"\n";
	}
	QMessageBox::about(&gameWindow, "record", outS.c_str());
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
	if (QMessageBox::question(&gameWindow, "new game?", "abort this and new game?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
		return;
	}
	QAction *type = qobject_cast<QAction*>(sender());
	for (int i = 0; i < difficultyNum; i++)
		if (type->text().toStdString() == difficultyTypes[i]) {
			setDifficulty(i);
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
void sudokuGUI::setDifficulty(int i) {
	difficultyChosen = i;
	this->setWindowTitle("sudoku: " + QString::fromStdString(difficultyTypes[difficultyChosen]));
}
sudokuGUI::sudokuGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(&gameWindow);
	m_widget.addWidget(&coverWindow);//index==0 封面界面
	m_widget.addWidget(&gameWindow);//index==1 游戏界面
	m_widget.setCurrentIndex(0);
	this->setCentralWidget(&m_widget);

	btnFont.setBold(true);
	btnFont.setPixelSize(20);

	coverWindow.setFixedSize(GRID_WIDTH*matrixLen + 2 * borderDistance, GRID_HEIGHT*(matrixLen + 1) + 2 * borderDistance + GRID_HEIGHT);
	gameWindow.setFixedSize(GRID_WIDTH*matrixLen + 2 * borderDistance, GRID_HEIGHT*(matrixLen + 1) + 2 * borderDistance + GRID_HEIGHT);

	btnStart.setText("Start");
	btnStart.setFont(btnFont);
	btnStart.setParent(&coverWindow);
	btnStart.setGeometry(coverWindow.width() / 2 - COVER_BUTTON_WIDTH / 2, coverWindow.height() / 2 - 0.5*COVER_BUTTON_HEIGHT, COVER_BUTTON_WIDTH, COVER_BUTTON_HEIGHT);
	btnStart.show();
	QObject::connect(&btnStart, SIGNAL(clicked()), this, SLOT(gameStart()));

	btnRecord.setParent(&coverWindow);
	btnRecord.setGeometry(coverWindow.width() / 2 - COVER_BUTTON_WIDTH / 2, coverWindow.height() / 2 + 0.7* COVER_BUTTON_HEIGHT, COVER_BUTTON_WIDTH, COVER_BUTTON_HEIGHT);
	btnRecord.setFont(btnFont);
	btnRecord.setText("Record");
	btnRecord.show();
	QObject::connect(&btnRecord, SIGNAL(clicked()), this, SLOT(showRecord()));

	btnSetting.setText("Setting");
	btnSetting.setFont(btnFont);
	btnSetting.setParent(&coverWindow);
	btnSetting.setGeometry(coverWindow.width() / 2 - COVER_BUTTON_WIDTH / 2, coverWindow.height() / 2 + 1.9* COVER_BUTTON_HEIGHT, COVER_BUTTON_WIDTH, COVER_BUTTON_HEIGHT);
	btnSetting.show();
	QObject::connect(&btnSetting, SIGNAL(clicked()), this, SLOT(gameSetting()));


	for (int i = 0; i < matrixLen; i++) {
		for (int j = 0; j < matrixLen; j++) {
			btnFill[i][j].setParent(&gameWindow);
			btnFill[i][j].setGeometry(borderDistance + j*GRID_WIDTH + j, borderDistance + i*GRID_HEIGHT + i, GRID_WIDTH, GRID_HEIGHT);
			btnFill[i][j].setFont(btnFont);
			QObject::connect(&btnFill[i][j], SIGNAL(clicked()), this, SLOT(sudokuButtonClicked()));
		}
	}
	for (int i = 0; i < keyboardKeysNum; i++) {
		btnChoice[i].setParent(&gameWindow);
		btnChoice[i].setText(btnChoiceContent[i]);
		btnChoice[i].setGeometry(borderDistance + i*GRID_WIDTH * 4 / 5, borderDistance + matrixLen*GRID_HEIGHT + 5 + matrixLen, GRID_WIDTH * 4 / 5, GRID_HEIGHT * 4 / 5);
		//btnChoice[i].setFont(btnFont);
		btnChoice[i].show();
		QObject::connect(&btnChoice[i], SIGNAL(clicked()), this, SLOT(keyboardButtonClicked()));
	}

	btnHome.setText("home");
	btnHome.setParent(&gameWindow);
	btnHome.setGeometry(borderDistance + 0 * GRID_WIDTH, borderDistance + (matrixLen + 1)*GRID_HEIGHT + matrixLen, GRID_WIDTH, GRID_HEIGHT / 2);
	btnHome.show();
	QObject::connect(&btnHome, SIGNAL(clicked()), this, SLOT(gameToCover()));


	result.setParent(&gameWindow);
	result.setGeometry(borderDistance + 2 * GRID_WIDTH, borderDistance + (matrixLen + 1)*GRID_HEIGHT + matrixLen, GRID_WIDTH * 2, GRID_HEIGHT / 2);

	btnSubmit.setText("submit");
	btnSubmit.setParent(&gameWindow);
	btnSubmit.setGeometry(borderDistance + 4 * GRID_WIDTH, borderDistance + (matrixLen + 1)*GRID_HEIGHT + matrixLen, GRID_WIDTH, GRID_HEIGHT / 2);
	btnSubmit.show();
	QObject::connect(&btnSubmit, SIGNAL(clicked()), this, SLOT(update()));

	timer.setParent(&gameWindow);
	timerLabel.setParent(&gameWindow);
	timerLabel.setGeometry(borderDistance + 6 * GRID_WIDTH, borderDistance + (matrixLen + 1)*GRID_HEIGHT + matrixLen, GRID_WIDTH, GRID_HEIGHT / 2);
	timer.setInterval(1000);

	QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(updateTimerLabel()));

	QObject::connect(ui.action, SIGNAL(triggered(bool)), this, SLOT(newGame()));
	QObject::connect(ui.action_2, SIGNAL(triggered(bool)), this, SLOT(newGame()));
	QObject::connect(ui.action_3, SIGNAL(triggered(bool)), this, SLOT(newGame()));

	init();
}
