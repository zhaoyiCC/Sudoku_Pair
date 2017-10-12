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
#define COVER_BUTTON_WIDTH 140
#define COVER_BUTTON_HEIGHT 60
#define COVER_TITLE_WIDTH (582*0.9)
#define COVER_TITLE_HEIGHT (131*0.9)
#define GRID_WIDTH 50
#define GRID_HEIGHT 50
#define GRID_CHOICE_WIDTH 40
#define GRID_CHOICE_HEIGHT 40
#define BTN_SUBMIT_WIDTH 80
#define BTN_SUBMIT_HEIGHT 30
#define BORDER_DISTANCE 50
#define JIUGONG_DISTANCE 5
#define ZOOM_OUT_RATIO 1.2

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
	//const QString btnTargetStyle = "QPushButton{background-color:gray; color: black;   border - radius: 10px;  border: 1px groove gray; border - style: outset;}" "QPushButton:hover{background-color:green; color: black;}""QPushButton:pressed{background-color:rgb(85, 170, 255);border - style: inset;}";
	const QString btnTargetStyle = "color:white;border-image:url(:/new/src/picture/gridDeepGreen.png)";
	//const QString btnEmptyStyle = "background-color: #ffffff;";
	const QString btnOtherEmptyStyle = "color:white;border-image:url(:/new/src/picture/gridDeepBlue.png)";
	const QString btnEmptyStyle = "color:white;border-image:url(:/new/src/picture/gridRed.png)";
	//const QString btnNotEmptyStyle = "background-color: #DDDDDD;";		
	const QString btnNotEmptyStyle = "color:white;border-image:url(:/new/src/picture/gridBlack.png)";
	const QString btnChoiceStyle = "color:black;border-image:url(:/new/src/picture/gridYellow.png)";
	const QString btnClockStyle = "color:black;border-image:url(:/new/src/picture/clock.png)";
	const QString btnSubmitStyle = "color:black;border-image:url(:/new/src/picture/gridBlue.png)";
	const QString btnHomeStyle = "color:black;border-image:url(:/new/src/picture/home10.png)";
	const string recordFileName = "record.txt";
	const static int difficultyNum = 3;
	const string difficultyTypes[difficultyNum] = { "Easy","Normal","Hard" };
	Ui::sudokuGUIClass ui;
	int empty[matrixLen][matrixLen];
	int matrix[matrixLen][matrixLen];
	int difficultyChosen = 0;
	QStackedWidget m_widget;//负责多界面显示
	QMainWindow coverWindow;//封面
	QMainWindow gameWindow;//游戏进行的界面
	Solver solver;
	QLabel lbSudoku;
	QLabel lbCover;
	QLabel lbGame;
	QPushButton btnStart;
	QPushButton btnSetting;
	QPushButton btnFill[matrixLen][matrixLen];
	QPushButton btnChoice[keyboardKeysNum];
	QPushButton btnClock;
	QLabel result;
	QPushButton btnSubmit;
	QPushButton btnHome;
	QPushButton *btnTarget = NULL;//选中的按钮	
	QPushButton btnRecord;

	QTimer timer;
	QLabel lbTimer;

	int timerCnt = 0;

	Core core;

	QFont btnFont;
	QFont btnChoiceFont;
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
	void setBackgroundImage(QLabel &a, QMainWindow &w, int x, int y, int width, int height, QString file);
	void setBtnZoomAction(QPushButton &btn);
	void setBtnZoomOut();
	void setBtnZoomIn();	
	void setRowStyleSheet(int o, QString styleSheet);
	void setColumnStyleSheet(int o, QString styleSheet);
	void setJiugongStyleSheet(int r,int c, QString styleSheet);
	void showAbout();
};
