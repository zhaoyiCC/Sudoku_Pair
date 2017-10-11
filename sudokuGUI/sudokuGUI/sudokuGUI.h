#pragma once

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include "ui_sudokuGUI.h"
#include <solver.h>
#include <QPushButton>
#include <QPainter>
#include <QTimer>
#include <string>
#include <QStackedWidget>
#include "sudoku.h"
#define COVER_BUTTON_WIDTH 100
#define COVER_BUTTON_HEIGHT 50
class sudokuGUI : public QMainWindow
{
	Q_OBJECT

public:
	sudokuGUI(QWidget *parent = Q_NULLPTR);

private:
	const QString HINT = "hint";
	const QString CLEAR = "clear";
	const static int keyboardKeysNum = matrixLen + 2;
	const QString btnChoiceContent[keyboardKeysNum] = { "1","2","3","4","5","6","7","8","9",CLEAR,HINT };
	const QString btnTargetStyle = "QPushButton{background-color:gray; color: black;   border - radius: 10px;  border: 1px groove gray; border - style: outset;}" "QPushButton:hover{background-color:green; color: black;}""QPushButton:pressed{background-color:rgb(85, 170, 255);border - style: inset;}";
	const QString btnEmptyStyle = "background-color: #ffffff;";
	const QString btnNotEmptyStyle = "background-color: #DDDDDD;";		
	const string recordFileName = "record.txt";
	const static int difficultyNum = 3;
	const string difficultyTypes[difficultyNum] = { "easy","normal","hard" };
	Ui::sudokuGUIClass ui;
	int empty[matrixLen][matrixLen];
	int matrix[matrixLen][matrixLen];
	int difficultyChosen = 0;
	QStackedWidget m_widget;//负责多界面显示
	QMainWindow coverWindow;//封面
	QMainWindow gameWindow;//游戏进行的界面
	Solver solver;
	QPushButton btnStart;
	QPushButton btnSetting;
	QPushButton btnFill[matrixLen][matrixLen];
	QPushButton btnChoice[keyboardKeysNum];
	QPushButton btnHome;
	QLabel result;
	QPushButton btnSubmit;
	QPushButton *btnTarget = NULL;//选中的按钮	
	QPushButton btnRecord;

	QTimer timer;
	QLabel timerLabel;
	
	int timerCnt = 0;

	Core core;

	QFont btnFont;
	private slots:
	void gameStart();
	void gameSetting();
	void keyboardButtonClicked();
	void sudokuButtonClicked();
	void gameToCover();
	void update();
	void updateTimerLabel();
	void showRecord();
	void readRecordFile(string res[3]);
	void writeRecordFile(string res[3]);
	void initMatrix();
	void newGame();
	void init();
	void setDifficulty(int i);
protected:
	void paintEvent(QPaintEvent *event);
};
