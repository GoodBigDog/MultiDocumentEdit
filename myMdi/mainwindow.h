#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "MdiChild.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QCloseEvent>
#include <QLabel>

class QMdiSubWindow;  //ǰ������
class QSignalMapper;
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_actionNew_triggered(); //�½��˵�
	void on_actionOpen_triggered(); //�򿪲˵�
	void on_actionSave_triggered(); //����˵�
	void on_actionSaveAs_triggered(); //���Ϊ
	void on_actionUndo_triggered(); //����
	void on_actionRedo_triggered(); //�ָ�
	void on_actionCut_triggered(); //����
	void on_actionCopy_triggered(); //����
	void on_actionPaste_triggered(); //ճ��
	void on_actionClose_triggered(); //�ر�
	void on_actionCloseAll_triggered(); //�ر�����
	void on_actionTile_triggered(); //ƽ����ʾ
	void on_actionCascade_triggered(); //�����ʾ
	void on_actionNext_triggered(); //��һ��
	void on_actionPrevious_triggered(); //ǰһ��

	void on_actionExit_triggered();   //�˳�

	void on_actionAbout_triggered(); //����
	void on_actionAboutQt_triggered(); //����Qt

	void updateMenus();  //���²˵�
	MdiChild* createMdiChild();   //�����Ӵ���
	void setActiveSubWindow(QWidget* window);   //���û�Ӵ���
	void updateWindowMenu();  //���´��ڲ˵�

	void showTextRowAndCol();  //��ʾ�ı����кź��к�

private:
	Ui::MainWindowClass ui;
	QAction *actionSeparator;  //�����
	MdiChild *activeMdiChild();  //�����
	QMdiSubWindow* findMdiChild(const QString &fileName);  //�����Ӵ���
	QSignalMapper* windowMapper;  //�ź�ӳ����

	void readSettings();  //��ȡ��������
	void writeSettings(); //д�봰������

	void initWindow();  //��ʼ������

protected:
	void closeEvent(QCloseEvent*event);  //�ر��¼�
};

#endif // MAINWINDOW_H
