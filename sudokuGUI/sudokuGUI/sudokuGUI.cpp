#include "sudokuGUI.h"
#include "solver.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include <QMessageBox>
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
		int temp = btnTarget->objectName().toInt();
		int j = temp % 10;
		int i = temp / 10;
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
	int temp= btn->objectName().toInt();
	int j = temp % 10;
	int i = temp / 10;
	if (empty[i][j] == 0)
		return;
	if (btnTarget != NULL) {
		int temp = btnTarget->objectName().toInt();
		int j = temp % 10;
		int i = temp / 10;
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
	QMessageBox::about(&gameWindow, "result", result.text());
}

void sudokuGUI::updateTimerLabel() {
	timerCnt++;
	lbTimer.setText(QString::number(timerCnt, 10));
}
void sudokuGUI::showRecord() {
	string res[3];
	string outS = "";
	readRecordFile(res);
	for (int i = 0; i < difficultyNum; i++) {
		outS += difficultyTypes[i] + ": " + res[i] + "s" + "\n";
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

	timerCnt = 0;
	lbTimer.setText("0");
}
void sudokuGUI::setDifficulty(int i) {
	difficultyChosen = i;
	this->setWindowTitle("sudoku: " + QString::fromStdString(difficultyTypes[difficultyChosen]));
	init();
}
void sudokuGUI::setBackgroundImage(QLabel &l, QMainWindow &w, int x, int y, int width, int height, QString file) {
	QImage image(file);
	l.setParent(&w);
	l.setGeometry(x, y, width, height);
	QPixmap pixmap;
	pixmap.convertFromImage(image);
	pixmap = pixmap.scaled(l.width(), l.height(),
		Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小和label的长宽一致
	l.setPixmap(pixmap);
}
void sudokuGUI::setBtnZoomAction(QPushButton &btn) {
	QObject::connect(&btn, SIGNAL(pressed()), this, SLOT(setBtnZoomOut()));
	QObject::connect(&btn, SIGNAL(released()), this, SLOT(setBtnZoomIn()));
}
void sudokuGUI::setBtnZoomOut() {
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	int cx = btn->x() + btn->width() / 2;
	int cy = btn->y() + btn->height() / 2;
	int nw = btn->width()*ZOOM_OUT_RATIO;
	int nh = btn->height()*ZOOM_OUT_RATIO;
	btn->setGeometry(cx-nw/2, cy-nh/2,nw,nh);
}
void sudokuGUI::setBtnZoomIn() {
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	int cx = btn->x() + btn->width() / 2;
	int cy = btn->y() + btn->height() / 2;
	int nw = btn->width()/ZOOM_OUT_RATIO;
	int nh = btn->height()/ZOOM_OUT_RATIO;
	btn->setGeometry(cx - nw / 2, cy - nh / 2, nw, nh);
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
	btnFont.setPixelSize(26);
	btnFont.setFamily("Times New Roman");

	this->setFixedSize(GRID_WIDTH*matrixLen + 2 * BORDER_DISTANCE + 2 * JIUGONG_DISTANCE + 8, GRID_HEIGHT*(matrixLen + 1) + 2 * BORDER_DISTANCE + GRID_HEIGHT + 2 * JIUGONG_DISTANCE + 8);
	coverWindow.setFixedSize(GRID_WIDTH*matrixLen + 2 * BORDER_DISTANCE + 2 * JIUGONG_DISTANCE + 8, GRID_HEIGHT*(matrixLen + 1) + 2 * BORDER_DISTANCE + GRID_HEIGHT + 2 * JIUGONG_DISTANCE + 8);
	gameWindow.setFixedSize(coverWindow.width(), coverWindow.height());
	//coverWindow.setStyleSheet("background-image: url(:/new/src/1.png);");
	//coverWindow.setStyleSheet("background-color:blue;");

	setBackgroundImage(lbCover, coverWindow, 0, 0, coverWindow.width(), coverWindow.height(), ":/new/src/picture/coverBackground2.jpg");
	setBackgroundImage(lbGame, gameWindow, 0, 23, gameWindow.width(), gameWindow.height() + 23, ":/new/src/picture/coverBackground2.jpg");
	setBackgroundImage(lbSudoku, coverWindow, coverWindow.width() / 2 - COVER_TITLE_WIDTH / 2, BORDER_DISTANCE, COVER_TITLE_WIDTH, COVER_TITLE_HEIGHT, ":/new/src/picture/sudoku.png");


	btnStart.setParent(&coverWindow);
	btnStart.setGeometry(coverWindow.width() / 2 - COVER_BUTTON_WIDTH / 2, coverWindow.height() / 2 - 0.5*COVER_BUTTON_HEIGHT, COVER_BUTTON_WIDTH, COVER_BUTTON_HEIGHT);


	btnStart.setText("Start");
	btnStart.setFont(btnFont);
	btnStart.setParent(&coverWindow);
	btnStart.setGeometry(coverWindow.width() / 2 - COVER_BUTTON_WIDTH / 2, coverWindow.height() / 2 - 0.5*COVER_BUTTON_HEIGHT, COVER_BUTTON_WIDTH, COVER_BUTTON_HEIGHT);
	setBtnZoomAction(btnStart);
	btnStart.show();	
	QObject::connect(&btnStart, SIGNAL(clicked()), this, SLOT(gameStart()));

	btnRecord.setParent(&coverWindow);
	btnRecord.setGeometry(coverWindow.width() / 2 - COVER_BUTTON_WIDTH / 2, coverWindow.height() / 2 + 1 * COVER_BUTTON_HEIGHT, COVER_BUTTON_WIDTH, COVER_BUTTON_HEIGHT);
	btnRecord.setFont(btnFont);
	btnRecord.setText("Record");
	setBtnZoomAction(btnRecord);
	btnRecord.show();
	QObject::connect(&btnRecord, SIGNAL(clicked()), this, SLOT(showRecord()));

	btnSetting.setText("Setting");
	btnSetting.setFont(btnFont);
	btnSetting.setParent(&coverWindow);
	btnSetting.setGeometry(coverWindow.width() / 2 - COVER_BUTTON_WIDTH / 2, coverWindow.height() / 2 + 2.5* COVER_BUTTON_HEIGHT, COVER_BUTTON_WIDTH, COVER_BUTTON_HEIGHT);
	setBtnZoomAction(btnSetting);
	btnSetting.show();
	QObject::connect(&btnSetting, SIGNAL(clicked()), this, SLOT(gameSetting()));


	for (int i = 0; i < matrixLen; i++) {
		for (int j = 0; j < matrixLen; j++) {
			btnFill[i][j].setParent(&gameWindow);
			btnFill[i][j].setGeometry(BORDER_DISTANCE + j*GRID_WIDTH + j + j / 3 * JIUGONG_DISTANCE, BORDER_DISTANCE + i*GRID_HEIGHT + i + i / 3 * JIUGONG_DISTANCE
				, GRID_WIDTH, GRID_HEIGHT);
			btnFill[i][j].setFont(btnFont);
			btnFill[i][j].setObjectName(QString::number(i * 10 + j, 10));//将标号存储在objectName里
			setBtnZoomAction(btnFill[i][j]);//按下变大松开变小
			QObject::connect(&btnFill[i][j], SIGNAL(clicked()), this, SLOT(sudokuButtonClicked()));
		}
	}

	btnChoiceFont.setBold(true);
	btnChoiceFont.setPixelSize(18);
	btnChoiceFont.setFamily("Times New Roman");

	for (int i = 0; i < keyboardKeysNum - 2; i++) {
		btnChoice[i].setParent(&gameWindow);
		btnChoice[i].setText(btnChoiceContent[i]);
		btnChoice[i].setGeometry(BORDER_DISTANCE + i*GRID_CHOICE_WIDTH, BORDER_DISTANCE + matrixLen*GRID_HEIGHT + matrixLen + 2 * JIUGONG_DISTANCE + 20
			, GRID_CHOICE_WIDTH, GRID_CHOICE_HEIGHT);		
		btnChoice[i].setFont(btnChoiceFont);
		btnChoice[i].setStyleSheet(btnChoiceStyle);
		btnChoice[i].show();
		setBtnZoomAction(btnChoice[i]);
		QObject::connect(&btnChoice[i], SIGNAL(clicked()), this, SLOT(keyboardButtonClicked()));
	}
	for (int i = keyboardKeysNum - 2; i < keyboardKeysNum; i++) {
		btnChoice[i].setParent(&gameWindow);
		btnChoice[i].setText(btnChoiceContent[i]);
		btnChoice[i].setGeometry(gameWindow.width() - BORDER_DISTANCE - 2 * GRID_CHOICE_WIDTH + (i - keyboardKeysNum + 2)*GRID_CHOICE_WIDTH, BORDER_DISTANCE + matrixLen*GRID_HEIGHT + matrixLen + 2 * JIUGONG_DISTANCE + 20
			, GRID_CHOICE_WIDTH, GRID_CHOICE_HEIGHT);		
		btnChoice[i].setFont(btnChoiceFont);
		btnChoice[i].setStyleSheet(btnChoiceStyle);
		btnChoice[i].show();
		setBtnZoomAction(btnChoice[i]);
		QObject::connect(&btnChoice[i], SIGNAL(clicked()), this, SLOT(keyboardButtonClicked()));
	}
	btnChoice[10].setFlat(true);

	btnClock;	
	btnClock.setParent(&gameWindow);
	btnClock.setGeometry(BORDER_DISTANCE + 0 * GRID_WIDTH, BORDER_DISTANCE + (matrixLen + 1)*GRID_HEIGHT + matrixLen + 2 * JIUGONG_DISTANCE + 20 + (GRID_CHOICE_HEIGHT - BTN_SUBMIT_HEIGHT)
		, BTN_SUBMIT_HEIGHT, BTN_SUBMIT_HEIGHT);
	btnClock.setStyleSheet(btnClockStyle);	
		
	timer.setParent(&gameWindow);
	lbTimer.setParent(&gameWindow);
	lbTimer.setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	lbTimer.setFont(btnChoiceFont);
	lbTimer.setGeometry(btnClock.x()+btnClock.width()+5, BORDER_DISTANCE + (matrixLen + 1)*GRID_HEIGHT + matrixLen + 2 * JIUGONG_DISTANCE + 20 + (GRID_CHOICE_HEIGHT - BTN_SUBMIT_HEIGHT)
		, GRID_CHOICE_WIDTH, BTN_SUBMIT_HEIGHT);	
	timer.setInterval(1000);
	QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(updateTimerLabel()));

	result.setParent(&gameWindow);
	result.setAlignment(Qt::AlignCenter);
	result.setGeometry(BORDER_DISTANCE + 2 * GRID_WIDTH, lbTimer.y()
		, GRID_WIDTH * 2, BTN_SUBMIT_HEIGHT);
	result.setVisible(false);
	
	btnSubmit.setText("submit");
	btnSubmit.setParent(&gameWindow);
	btnSubmit.setGeometry(BORDER_DISTANCE + 4 * GRID_WIDTH, lbTimer.y(), BTN_SUBMIT_WIDTH, BTN_SUBMIT_HEIGHT);
	btnSubmit.setFont(btnChoiceFont);
	btnSubmit.setStyleSheet(btnSubmitStyle);
	setBtnZoomAction(btnSubmit);
	btnSubmit.show();
	QObject::connect(&btnSubmit, SIGNAL(clicked()), this, SLOT(update()));

	//btnHome.setText("home");
	btnHome.setParent(&gameWindow);
	btnHome.setGeometry(coverWindow.width() - BORDER_DISTANCE - GRID_CHOICE_WIDTH, BORDER_DISTANCE + (matrixLen + 1)*GRID_HEIGHT + matrixLen + 2 * JIUGONG_DISTANCE + 20
		, GRID_CHOICE_WIDTH, GRID_CHOICE_HEIGHT);
	btnHome.setStyleSheet(btnHomeStyle);
	setBtnZoomAction(btnHome);
	btnHome.show();
	QObject::connect(&btnHome, SIGNAL(clicked()), this, SLOT(gameToCover()));

	QObject::connect(ui.action, SIGNAL(triggered(bool)), this, SLOT(newGame()));
	QObject::connect(ui.action_2, SIGNAL(triggered(bool)), this, SLOT(newGame()));
	QObject::connect(ui.action_3, SIGNAL(triggered(bool)), this, SLOT(newGame()));

	init();
}
