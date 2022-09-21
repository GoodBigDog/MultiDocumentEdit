#include "mainwindow.h"
#include <QMdiSubWindow>
#include <QSignalMapper>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//���Ӳ�-�½��ļ�
	connect(
		ui.actionNew,//����1
		SIGNAL(clicked(bool)),//����1�źţ��̶��ĺ����Ͳ���
		this,//����2
		SLOT(on_actionNew_triggered())//����2�Ĳۺ������Զ���ĺ���
	);

	//���Ӳ�-���ļ�
	connect(
		ui.actionOpen,//����1
		SIGNAL(clicked(bool)),//����1�źţ��̶��ĺ����Ͳ���
		this,//����2
		SLOT(on_actionOpen_triggered())//����2�Ĳۺ������Զ���ĺ���
		);

	//���Ӳ�-�����ļ�
	connect(
		ui.actionSave,//����1
		SIGNAL(clicked(bool)),//����1�źţ��̶��ĺ����Ͳ���
		this,//����2
		SLOT(on_actionSave_triggered())//����2�Ĳۺ������Զ���ĺ���
		);

	connect(
		ui.actionSaveAs,//����1
		SIGNAL(clicked(bool)),//����1�źţ��̶��ĺ����Ͳ���
		this,//����2
		SLOT(on_actionSaveAs_triggered())//����2�Ĳۺ������Զ���ĺ���
		);

	//���Ӳ�-�����ļ�
	connect(
		ui.actionUndo,//����1
		SIGNAL(clicked(bool)),//����1�źţ��̶��ĺ����Ͳ���
		this,//����2
		SLOT(on_actionUndo_triggered())//����2�Ĳۺ������Զ���ĺ���
		);

	//���Ӳ�-�ر��ļ�
	connect(
		ui.actionClose,//����1
		SIGNAL(clicked(bool)),//����1�źţ��̶��ĺ����Ͳ���
		this,//����2
		SLOT(on_actionClose_triggered())//����2�Ĳۺ������Զ���ĺ���
		);

	//���Ӳ�-�ָ��ļ�
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

	//�����������������������ü����
	actionSeparator = new QAction(this);
	actionSeparator->setSeparator(true);
	//���²˵�
	updateMenus();
	//���л����ʱ���²˵�
	connect(ui.mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)), this, SLOT(updateMenus()));

	//�����ź�ӳ����
	windowMapper = new QSignalMapper(this);
	//ӳ�������·����źţ������ź����û����
	connect(windowMapper, SIGNAL(mapped(QWidget*)), this, SLOT(setActiveSubWindow(QWidget*)));
	//���´��ڲ˵�
	updateWindowMenu();
	connect(ui.menu_W, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

	//��ȡ����
	readSettings();  //��ʼ����ʱ��ȡ����������Ϣ
	initWindow();
}

MainWindow::~MainWindow()
{

}

void MainWindow::updateMenus(){
	//�����Ƿ��л���������ø��������Ƿ����
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

	//���ü�����Ƿ���ʾ
	actionSeparator->setVisible(hasMdiChild);

	//�л�������б�ѡ����ı������и��Ʋ�����
	bool hasSelection = (activeMdiChild() && activeMdiChild()->textCursor().hasSelection());
	ui.actionCut->setEnabled(hasSelection);
	ui.actionCopy->setEnabled(hasSelection);

	//�л�������ĵ��г���������ʱ������������
	ui.actionUndo->setEnabled(activeMdiChild() && activeMdiChild()->document()->isUndoAvailable());
	//�л�������ĵ��лָ����ܶ�������
	ui.actionRedo->setEnabled(activeMdiChild() && activeMdiChild()->document()->isRedoAvailable());
}

MdiChild* MainWindow::activeMdiChild(){
	//����л���ڣ������ڵ����Ĳ���ת��ΪMdiChild���ͣ�û����ֱ�ӷ���0
	if (QMdiSubWindow *activeSubWindow = ui.mdiArea->activeSubWindow()){
		return qobject_cast<MdiChild*>(activeSubWindow->widget());
	}
	return 0;
}

MdiChild* MainWindow::createMdiChild(){
	//����MdiChild����
	MdiChild* child = new MdiChild();
	//����ĵ���������Ӵ��ڣ�childΪ���Ĳ���
	ui.mdiArea->addSubWindow(child);
	//����QTextEdit����Ƿ���Ը����ź����ü��и��ƶ����Ƿ����
	connect(child, SIGNAL(copyAvailable(bool)), ui.actionCut, SLOT(setEnabled(bool)));
	connect(child, SIGNAL(copyAvailable(bool)), ui.actionCopy, SLOT(setEnabled(bool)));
	//���ó����ظ������Ƿ����
	connect(child->document(), SIGNAL(redoAvailable(bool)), ui.actionRedo, SLOT(setEnabled(bool)));
	connect(child->document(), SIGNAL(undoAvailable(bool)), ui.actionUndo, SLOT(setEnabled(bool)));
	connect(child, SIGNAL(cursorPositionChanged()), this, SLOT(showTextRowAndCol()));

	return child;
}

QMdiSubWindow *MainWindow::findMdiChild(const QString &fileName){
	QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();
	//����foreach�������Ӵ����б�������ļ�·����Ҫ���ҵ�·����ͬ���򷵻ظô���
	foreach(QMdiSubWindow*window, ui.mdiArea->subWindowList()){
		MdiChild*mdichild = qobject_cast<MdiChild*>(window->widget());
		if (mdichild->currentFile() == canonicalFilePath)
			return window;
	}
	return 0;
}

void MainWindow::setActiveSubWindow(QWidget*window){
	//��������˴��ڲ�������������Ϊ�����
	if (!window)
		return;
	ui.mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow*>(window));
}

void MainWindow::updateWindowMenu(){
	//����ղ˵���Ȼ����Ӹ����˵�����
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

	//����л��������ʾ�����
	QList<QMdiSubWindow*> windows = ui.mdiArea->subWindowList();
	actionSeparator->setVisible(!windows.isEmpty());

	//���������Ӵ���
	for (int i = 0; i < windows.size(); i++){
		MdiChild *child = qobject_cast<MdiChild*>(windows.at(i)->widget());
		QString text;
		//���������ĿС��9�������ñ��Ϊ��ݼ�
		if (i < 9){
			text = tr("&%1 %2").arg(i + 1).arg(child->userFriendlyCurrentFile());
		}
		else{
			text = tr("%1 %2").arg(i + 1).arg(child->userFriendlyCurrentFile());
		}
		//��Ӷ������˵������ö�������ѡ��
		QAction *action = ui.menu_W->addAction(text);
		action->setCheckable(true);
		//���õ�ǰ����ڶ���Ϊѡ��״̬
		action->setChecked(child == activeMdiChild());
		//���������Ĵ����źŵ��ź�ӳ������map�ۣ�����ۻᴥ��mapped�ź�
		connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
		//���������Ӧ�Ĵ��ڲ�������ӳ��,
		//�ڷ���mapped()�ź�ʱ�ͻ���������ڲ���Ϊ����
		windowMapper->setMapping(action, windows.at(i));
	}

}

//�ر��¼��Ĵ������Ķ���
void MainWindow::closeEvent(QCloseEvent*event){
	//��ִ�ж��ĵ�����Ĺرղ���
	ui.mdiArea->closeAllSubWindows();
	//������д���û�йرգ�����Ը��¼�
	if (ui.mdiArea->currentSubWindow()){
		event->ignore();
	}
	else{
		//�ڹر�ǰд�봰������
		writeSettings();
		event->accept();
	}
}

//д�봰������
void MainWindow::writeSettings(){
	QSettings settings("BigDog-vs2013-qt", "myMdi");
	//д��λ����Ϣ�ʹ�С��Ϣ
	settings.setValue("pos", pos());
	settings.setValue("size", size());
}

//��ȡ��������
void MainWindow::readSettings(){
	QSettings settings("BigDog-vs2013-qt", "myMdi");
	QPoint pos = settings.value("pos", QPoint(1920/2, 1080/2)).toPoint();
	QSize size = settings.value("size", QSize(800, 800)).toSize();
	move(pos);
	resize(size);
}

void MainWindow:: on_actionNew_triggered(){
	//����MdiChild
	MdiChild *child = createMdiChild();
	////���ĵ���������Ӵ���
	//ui.mdiArea->addSubWindow(child);

	//�½��ļ�
	child->newFile();
	//��ʾ�Ӵ���
	child->show();
}

void MainWindow::on_actionOpen_triggered(){
	//��ȡ�ļ�·��
	QString fileName = QFileDialog::getOpenFileName(this);
	//���·����Ϊ�գ���鿴���ļ��Ƿ��Ѿ���
	if (!fileName.isEmpty()){
		QMdiSubWindow *existing = findMdiChild(fileName);
		//����Ѿ����ڣ��򽫶�Ӧ���Ӵ�������Ϊ�����
		if (existing){
			ui.mdiArea->setActiveSubWindow(existing);
			return;
		}
		//���û�д򿪣����½��Ӵ���
		MdiChild*child = createMdiChild();
		if (child->loadFile(fileName)){
			ui.statusBar->showMessage(tr("���ļ��ɹ�"), 2000);
			child->show();
		}
		else{
			child->close();
		}
	}
}
//�����ļ�
void MainWindow::on_actionSave_triggered(){
	if (activeMdiChild() && activeMdiChild()->save()){
		ui.statusBar->showMessage(tr("�ļ�����ɹ�"), 2000);
	}
}

//���Ϊ�ļ�
void MainWindow::on_actionSaveAs_triggered(){
	if (activeMdiChild() && activeMdiChild()->save()){
		ui.statusBar->showMessage(tr("�ļ����Ϊ�ɹ�"), 2000);
	}
}
//�����ļ�
void MainWindow::on_actionUndo_triggered(){
	if (activeMdiChild())
		activeMdiChild()->undo();
}

//�ָ��ļ�
void MainWindow::on_actionRedo_triggered(){
	if (activeMdiChild())
		activeMdiChild()->redo();
}

//�����ļ�
void MainWindow::on_actionCut_triggered(){
	if (activeMdiChild())
		activeMdiChild()->cut();
}
//�����ļ�
void MainWindow::on_actionCopy_triggered(){
	if (activeMdiChild())
		activeMdiChild()->copy();
}
//ճ���ļ�
void MainWindow::on_actionPaste_triggered(){
	if (activeMdiChild())
		activeMdiChild()->paste();
}

//�ر��ļ�
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
	QMessageBox::about(this, "����", "Created Time:2022/09/20 By BigDog");
}

void MainWindow::on_actionAboutQt_triggered(){
	QMessageBox::about(this, "����Qt", "qt��һ��ܺ��õĹ���");
}

void MainWindow::on_actionExit_triggered(){
	qApp->closeAllWindows();
}

//��꺯�����к��к�
void MainWindow::showTextRowAndCol(){
	if (activeMdiChild()){
		int rowNum = activeMdiChild()->textCursor().blockNumber() + 1;
		int colNum = activeMdiChild()->textCursor().columnNumber() + 1;
		ui.statusBar->showMessage(tr("%1 �� %2��").arg(rowNum).arg(colNum), 2000);
	}
}

//��ʼ������
void MainWindow::initWindow(){
	setWindowTitle(tr("���ĵ��༭��"));
	//�ڹ��������һ�ʱ,���Թرչ�����
	ui.mainToolBar->setWindowTitle(tr("������"));
	//�����ĵ���������ݳ�����������󣬳��ֹ�����
	ui.mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	ui.mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	ui.statusBar->showMessage(tr("��ӭʹ�ö��ĵ��༭��"));
	QLabel *label = new QLabel(this);
	label->setFrameStyle(QFrame::Box | QFrame::Sunken);
	label->setText(tr("Created By BigDog"));
	ui.statusBar->addPermanentWidget(label);
	ui.actionNew->setStatusTip(tr("����һ���ļ�"));
	//todo: ����������ʾ
}