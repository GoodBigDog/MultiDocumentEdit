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

class QMdiSubWindow;  //前置声明
class QSignalMapper;
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_actionNew_triggered(); //新建菜单
	void on_actionOpen_triggered(); //打开菜单
	void on_actionSave_triggered(); //保存菜单
	void on_actionSaveAs_triggered(); //另存为
	void on_actionUndo_triggered(); //撤销
	void on_actionRedo_triggered(); //恢复
	void on_actionCut_triggered(); //剪切
	void on_actionCopy_triggered(); //复制
	void on_actionPaste_triggered(); //粘贴
	void on_actionClose_triggered(); //关闭
	void on_actionCloseAll_triggered(); //关闭所有
	void on_actionTile_triggered(); //平埔显示
	void on_actionCascade_triggered(); //层叠显示
	void on_actionNext_triggered(); //下一个
	void on_actionPrevious_triggered(); //前一个

	void on_actionExit_triggered();   //退出

	void on_actionAbout_triggered(); //关于
	void on_actionAboutQt_triggered(); //关于Qt

	void updateMenus();  //更新菜单
	MdiChild* createMdiChild();   //创建子窗口
	void setActiveSubWindow(QWidget* window);   //设置活动子窗口
	void updateWindowMenu();  //更新窗口菜单

	void showTextRowAndCol();  //显示文本的行号和列号

private:
	Ui::MainWindowClass ui;
	QAction *actionSeparator;  //间隔器
	MdiChild *activeMdiChild();  //活动窗口
	QMdiSubWindow* findMdiChild(const QString &fileName);  //查找子窗口
	QSignalMapper* windowMapper;  //信号映射器

	void readSettings();  //读取窗口设置
	void writeSettings(); //写入窗口设置

	void initWindow();  //初始化窗口

protected:
	void closeEvent(QCloseEvent*event);  //关闭事件
};

#endif // MAINWINDOW_H
