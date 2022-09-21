#include "mainwindow.h"
#include <QMdiSubWindow>
#include <QSignalMapper>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//连接槽-新建文件
	connect(
		ui.actionNew,//对象1
		SIGNAL(clicked(bool)),//对象1信号，固定的函数和参数
		this,//对象2
		SLOT(on_actionNew_triggered())//对象2的槽函数，自定义的函数
	);

	//连接槽-打开文件
	connect(
		ui.actionOpen,//对象1
		SIGNAL(clicked(bool)),//对象1信号，固定的函数和参数
		this,//对象2
		SLOT(on_actionOpen_triggered())//对象2的槽函数，自定义的函数
		);

	//连接槽-保存文件
	connect(
		ui.actionSave,//对象1
		SIGNAL(clicked(bool)),//对象1信号，固定的函数和参数
		this,//对象2
		SLOT(on_actionSave_triggered())//对象2的槽函数，自定义的函数
		);

	connect(
		ui.actionSaveAs,//对象1
		SIGNAL(clicked(bool)),//对象1信号，固定的函数和参数
		this,//对象2
		SLOT(on_actionSaveAs_triggered())//对象2的槽函数，自定义的函数
		);

	//连接槽-撤销文件
	connect(
		ui.actionUndo,//对象1
		SIGNAL(clicked(bool)),//对象1信号，固定的函数和参数
		this,//对象2
		SLOT(on_actionUndo_triggered())//对象2的槽函数，自定义的函数
		);

	//连接槽-关闭文件
	connect(
		ui.actionClose,//对象1
		SIGNAL(clicked(bool)),//对象1信号，固定的函数和参数
		this,//对象2
		SLOT(on_actionClose_triggered())//对象2的槽函数，自定义的函数
		);

	//连接槽-恢复文件
	connect(ui.actionRedo,SIGNAL(clicked(bool)),this,SLOT(on_actionRedo_triggered()));
	connect(ui.actionCut, SIGNAL(clicked(bool)), this, SLOT(on_actionCut_triggered()));
	connect(ui.actionCopy, SIGNAL(clicked(bool)), this, SLOT(on_actionCopy_triggered()));
	connect(ui.actionPaste, SIGNAL(clicked(bool)), this, SLOT(on_actionPaste_triggered()));

	connect(ui.actionCloseAll, SIGNAL(clicked(bool)), this, SLOT(on_actionCloseAll_triggered()));
	connect(ui.actionTile, SIGNAL(clicked(bool)), this, SLOT(on_actionTile_triggered()));
	connect(ui.actionCascade, SIGNAL(clicked(bool)), this, SLOT(on_actionCascade_triggered()));
	connect(ui.actionNext, SIGNAL(clicked(bool)), this, SLOT(on_actionNext_triggered()));
	connect(ui.actionPrevious, SIGNAL(clicked(bool)), this, SLOT(on_actionPrevious_triggered()));

	connect(ui.actionAbout, SIGNAL(clicked(bool)), this, SLOT(on_actionAbout_triggered()));
	connect(ui.actionAboutQt, SIGNAL(clicked(bool)), this, SLOT(on_actionAboutQt_triggered()));

	connect(ui.actionExit, SIGNAL(clicked(bool)), this, SLOT(on_actionExit_triggered()));

	//创造间隔器动作并在其中设置间隔器
	actionSeparator = new QAction(this);
	actionSeparator->setSeparator(true);
	//更新菜单
	updateMenus();
	//当有活动窗口时更新菜单
	connect(ui.mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)), this, SLOT(updateMenus()));

	//创建信号映射器
	windowMapper = new QSignalMapper(this);
	//映射器重新发射信号，根据信号设置活动窗口
	connect(windowMapper, SIGNAL(mapped(QWidget*)), this, SLOT(setActiveSubWindow(QWidget*)));
	//更新窗口菜单
	updateWindowMenu();
	connect(ui.menu_W, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

	//读取设置
	readSettings();  //初始窗口时读取窗口设置信息
	initWindow();
}

MainWindow::~MainWindow()
{

}

void MainWindow::updateMenus(){
	//根据是否有活动窗口来设置各个动作是否可用
	bool hasMdiChild = (activeMdiChild() != 0);
	ui.actionSave->setEnabled(hasMdiChild);
	ui.actionSaveAs->setEnabled(hasMdiChild);
	ui.actionPaste->setEnabled(hasMdiChild);
	ui.actionClose->setEnabled(hasMdiChild);
	ui.actionCloseAll->setEnabled(hasMdiChild);
	ui.actionTile->setEnabled(hasMdiChild);
	ui.actionCascade->setEnabled(hasMdiChild);
	ui.actionNext->setEnabled(hasMdiChild);
	ui.actionPrevious->setEnabled(hasMdiChild);

	//设置间隔器是否显示
	actionSeparator->setVisible(hasMdiChild);

	//有活动窗口且有被选择的文本，剪切复制才能用
	bool hasSelection = (activeMdiChild() && activeMdiChild()->textCursor().hasSelection());
	ui.actionCut->setEnabled(hasSelection);
	ui.actionCopy->setEnabled(hasSelection);

	//有活动窗口且文档有撤销操作的时候撤销动作可用
	ui.actionUndo->setEnabled(activeMdiChild() && activeMdiChild()->document()->isUndoAvailable());
	//有活动窗口且文档有恢复功能动作可用
	ui.actionRedo->setEnabled(activeMdiChild() && activeMdiChild()->document()->isRedoAvailable());
}

MdiChild* MainWindow::activeMdiChild(){
	//如果有活动窗口，则将其内的中心部件转换为MdiChild类型，没有则直接返回0
	if (QMdiSubWindow *activeSubWindow = ui.mdiArea->activeSubWindow()){
		return qobject_cast<MdiChild*>(activeSubWindow->widget());
	}
	return 0;
}

MdiChild* MainWindow::createMdiChild(){
	//创建MdiChild部件
	MdiChild* child = new MdiChild();
	//向多文档区域添加子窗口，child为中心部件
	ui.mdiArea->addSubWindow(child);
	//根据QTextEdit类的是否可以复制信号设置剪切复制动作是否可用
	connect(child, SIGNAL(copyAvailable(bool)), ui.actionCut, SLOT(setEnabled(bool)));
	connect(child, SIGNAL(copyAvailable(bool)), ui.actionCopy, SLOT(setEnabled(bool)));
	//设置撤销回复动作是否可用
	connect(child->document(), SIGNAL(redoAvailable(bool)), ui.actionRedo, SLOT(setEnabled(bool)));
	connect(child->document(), SIGNAL(undoAvailable(bool)), ui.actionUndo, SLOT(setEnabled(bool)));
	connect(child, SIGNAL(cursorPositionChanged()), this, SLOT(showTextRowAndCol()));

	return child;
}

QMdiSubWindow *MainWindow::findMdiChild(const QString &fileName){
	QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();
	//利用foreach语句遍历子窗口列表，如果其文件路径和要查找的路径相同，则返回该窗口
	foreach(QMdiSubWindow*window, ui.mdiArea->subWindowList()){
		MdiChild*mdichild = qobject_cast<MdiChild*>(window->widget());
		if (mdichild->currentFile() == canonicalFilePath)
			return window;
	}
	return 0;
}

void MainWindow::setActiveSubWindow(QWidget*window){
	//如果传递了窗口部件，则将其设置为活动窗口
	if (!window)
		return;
	ui.mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow*>(window));
}

void MainWindow::updateWindowMenu(){
	//先清空菜单，然后添加各个菜单动作
	ui.menu_W->clear();
	ui.menu_W->addAction(ui.actionClose);
	ui.menu_W->addAction(ui.actionCloseAll);
	ui.menu_W->addSeparator();
	ui.menu_W->addAction(ui.actionTile);
	ui.menu_W->addAction(ui.actionCascade);
	ui.menu_W->addSeparator();
	ui.menu_W->addAction(ui.actionNext);
	ui.menu_W->addAction(ui.actionPrevious);
	ui.menu_W->addAction(actionSeparator);

	//如果有活动窗口则显示间隔器
	QList<QMdiSubWindow*> windows = ui.mdiArea->subWindowList();
	actionSeparator->setVisible(!windows.isEmpty());

	//遍历各个子窗口
	for (int i = 0; i < windows.size(); i++){
		MdiChild *child = qobject_cast<MdiChild*>(windows.at(i)->widget());
		QString text;
		//如果窗口数目小于9，则设置编号为快捷键
		if (i < 9){
			text = tr("&%1 %2").arg(i + 1).arg(child->userFriendlyCurrentFile());
		}
		else{
			text = tr("%1 %2").arg(i + 1).arg(child->userFriendlyCurrentFile());
		}
		//添加动作到菜单，设置动作可以选择
		QAction *action = ui.menu_W->addAction(text);
		action->setCheckable(true);
		//设置当前活动窗口动作为选中状态
		action->setChecked(child == activeMdiChild());
		//关联动作的触发信号到信号映射器的map槽，这个槽会触发mapped信号
		connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
		//将动作与对应的窗口部件进行映射,
		//在发射mapped()信号时就会以这个窗口部件为参数
		windowMapper->setMapping(action, windows.at(i));
	}

}

//关闭事件的处理函数的定义
void MainWindow::closeEvent(QCloseEvent*event){
	//先执行多文档区域的关闭操作
	ui.mdiArea->closeAllSubWindows();
	//如果还有窗口没有关闭，则忽略该事件
	if (ui.mdiArea->currentSubWindow()){
		event->ignore();
	}
	else{
		//在关闭前写入窗口设置
		writeSettings();
		event->accept();
	}
}

//写入窗口设置
void MainWindow::writeSettings(){
	QSettings settings("BigDog-vs2013-qt", "myMdi");
	//写入位置信息和大小信息
	settings.setValue("pos", pos());
	settings.setValue("size", size());
}

//读取窗口设置
void MainWindow::readSettings(){
	QSettings settings("BigDog-vs2013-qt", "myMdi");
	QPoint pos = settings.value("pos", QPoint(1920/2, 1080/2)).toPoint();
	QSize size = settings.value("size", QSize(800, 800)).toSize();
	move(pos);
	resize(size);
}

void MainWindow:: on_actionNew_triggered(){
	//创建MdiChild
	MdiChild *child = createMdiChild();
	////多文档区域添加子窗口
	//ui.mdiArea->addSubWindow(child);

	//新建文件
	child->newFile();
	//显示子窗口
	child->show();
}

void MainWindow::on_actionOpen_triggered(){
	//获取文件路径
	QString fileName = QFileDialog::getOpenFileName(this);
	//如果路径不为空，则查看该文件是否已经打开
	if (!fileName.isEmpty()){
		QMdiSubWindow *existing = findMdiChild(fileName);
		//如果已经存在，则将对应的子窗口设置为活动窗口
		if (existing){
			ui.mdiArea->setActiveSubWindow(existing);
			return;
		}
		//如果没有打开，则新建子窗口
		MdiChild*child = createMdiChild();
		if (child->loadFile(fileName)){
			ui.statusBar->showMessage(tr("打开文件成功"), 2000);
			child->show();
		}
		else{
			child->close();
		}
	}
}
//保存文件
void MainWindow::on_actionSave_triggered(){
	if (activeMdiChild() && activeMdiChild()->save()){
		ui.statusBar->showMessage(tr("文件保存成功"), 2000);
	}
}

//另存为文件
void MainWindow::on_actionSaveAs_triggered(){
	if (activeMdiChild() && activeMdiChild()->save()){
		ui.statusBar->showMessage(tr("文件另存为成功"), 2000);
	}
}
//撤销文件
void MainWindow::on_actionUndo_triggered(){
	if (activeMdiChild())
		activeMdiChild()->undo();
}

//恢复文件
void MainWindow::on_actionRedo_triggered(){
	if (activeMdiChild())
		activeMdiChild()->redo();
}

//剪切文件
void MainWindow::on_actionCut_triggered(){
	if (activeMdiChild())
		activeMdiChild()->cut();
}
//复制文件
void MainWindow::on_actionCopy_triggered(){
	if (activeMdiChild())
		activeMdiChild()->copy();
}
//粘贴文件
void MainWindow::on_actionPaste_triggered(){
	if (activeMdiChild())
		activeMdiChild()->paste();
}

//关闭文件
void MainWindow::on_actionClose_triggered(){
	ui.mdiArea->closeActiveSubWindow();
}

void MainWindow::on_actionCloseAll_triggered(){
	ui.mdiArea->closeAllSubWindows();
}

void MainWindow::on_actionTile_triggered(){
	ui.mdiArea->tileSubWindows();
}

void MainWindow::on_actionCascade_triggered(){
	ui.mdiArea->cascadeSubWindows();
}

void MainWindow::on_actionNext_triggered(){
	ui.mdiArea->activateNextSubWindow();
}

void MainWindow::on_actionPrevious_triggered(){
	ui.mdiArea->activatePreviousSubWindow();
}

void MainWindow::on_actionAbout_triggered(){
	QMessageBox::about(this, "关于", "Created Time:2022/09/20 By BigDog");
}

void MainWindow::on_actionAboutQt_triggered(){
	QMessageBox::about(this, "关于Qt", "qt是一款很好用的工具");
}

void MainWindow::on_actionExit_triggered(){
	qApp->closeAllWindows();
}

//光标函数的行号列号
void MainWindow::showTextRowAndCol(){
	if (activeMdiChild()){
		int rowNum = activeMdiChild()->textCursor().blockNumber() + 1;
		int colNum = activeMdiChild()->textCursor().columnNumber() + 1;
		ui.statusBar->showMessage(tr("%1 行 %2列").arg(rowNum).arg(colNum), 2000);
	}
}

//初始化窗口
void MainWindow::initWindow(){
	setWindowTitle(tr("多文档编辑器"));
	//在工具栏上右击时,可以关闭工具栏
	ui.mainToolBar->setWindowTitle(tr("工具栏"));
	//当多文档区域的内容超出可视区域后，出现滚动条
	ui.mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	ui.mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	ui.statusBar->showMessage(tr("欢迎使用多文档编辑器"));
	QLabel *label = new QLabel(this);
	label->setFrameStyle(QFrame::Box | QFrame::Sunken);
	label->setText(tr("Created By BigDog"));
	ui.statusBar->addPermanentWidget(label);
	ui.actionNew->setStatusTip(tr("创建一个文件"));
	//todo: 其他动作提示
}