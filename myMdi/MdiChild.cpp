#include "MdiChild.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>
#include <QApplication>
#include <QFileDialog>
#include <QCloseEvent>
#include <QPushButton>

MdiChild::MdiChild(QWidget *parent)
{
	setAttribute(Qt::WA_DeleteOnClose); //���Ӵ��ڹر�ʱ������Ķ���

	isUntitled = true;  //
	//resize(2000, 2000);
}

void MdiChild::newFile(){
	//���ô��ڱ��
	static int sequenceNumber = 1;
	//�½��ĵ�û�б������
	isUntitled = true;

	//����ǰ�ļ�����Ϊδ�����ĵ��ӱ��
	curFile = tr("δ�����ĵ� %1.txt").arg(sequenceNumber++);

	//���ô��ڱ���
	setWindowTitle(curFile + "[*]" + tr("-���ĵ��༭��"));

	//�ĵ�����ʱ���͸����ź�,ִ��documentWasModified()��
	connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));

}

void MdiChild::documentWasModified(){
	setWindowModified(document()->isModified());
}

bool MdiChild::loadFile(const QString &fileName){
	//�½�QFile����
	QFile file(fileName);
	//ֻ����ʽ���ļ�����������ʾ
	if (!file.open(QFile::ReadOnly | QFile::Text)){
		QMessageBox::warning(this, tr("���ĵ��༭��"), tr("�޷���ȡ�ļ� %1:\n%2.")
			.arg(fileName).arg(file.errorString()));
		return false;
	}
	//�½��ı�������
	QTextStream in(&file);
	//�������״̬Ϊ�ȴ�״̬
	QApplication::setOverrideCursor(Qt::WaitCursor);
	setPlainText(in.readAll());
	//�ظ����״̬
	QApplication::restoreOverrideCursor();
	//���õ�ǰ�ļ�
	setCurrentFile(fileName);
	connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));

	return true;
}

void MdiChild::setCurrentFile(const QString &fileName){
	curFile = QFileInfo(fileName).canonicalFilePath();

	//�ļ��Ѿ����������
	isUntitled = false;
	//�ĵ�û�б��޸Ĺ�
	document()->setModified(false);

	//���ڲ���ʾ�����ı�־
	setWindowModified(false);

	//���ô��ڱ���,userFriendlyCurrentFile�����ļ���
	setWindowTitle(userFriendlyCurrentFile() + "[ * ]");
}

QString MdiChild::userFriendlyCurrentFile(){
	//���ļ�·������ȡ�ļ�����
	return QFileInfo(curFile).fileName();
}

/*----------�������----------*/
bool MdiChild::save(){
	//����ļ�δ�������ִ�����Ϊ������ֱ�ӱ���
	if (isUntitled){
		return saveAs();
	}
	else{
		return saveFile(curFile);
	}
}

bool MdiChild::saveAs(){
	QString fileName = QFileDialog::getSaveFileName(this, tr("���Ϊ"), curFile);
	//��ȡ�ļ�·�������Ϊ�գ��򷵻�false,���򱣴��ļ�
	if (fileName.isEmpty()){
		return false;
	}
	return saveFile(fileName);
}

bool MdiChild::saveFile(const QString &fileName){
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)){
		QMessageBox::warning(this, tr("���ĵ��༭��"), tr("�޷�д���ļ� %1:\n %2")
			.arg(fileName).arg(file.errorString()));
		return false;
	}
	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	//�Դ��ı���ʽд��
	out << toPlainText();
	QApplication::restoreOverrideCursor();
	setCurrentFile(fileName);
	return true;
}

void MdiChild::closeEvent(QCloseEvent *event){
	//����true��رմ��ڣ�����Ļ����Ը��¼�
	if (maybeSave()){
		event->accept();
	}
	else{
		event->ignore();
	}
}

bool MdiChild::maybeSave(){
	//����ĵ������Ĺ�
	if (document()->isModified()){
		QMessageBox box;
		box.setWindowTitle(tr("���ĵ��༭��"));
		box.setText(tr("�Ƿ񱣴��%1�ĸ��ģ�").arg(userFriendlyCurrentFile()));
		box.setIcon(QMessageBox::Warning);
		//��Ӱ�ť��QMessageBox::YesRole���Ա��������ť����Ϊ
		QPushButton *yesBtn = box.addButton(tr("��(&Y)"), QMessageBox::YesRole);
		box.addButton(tr("��(&N)"), QMessageBox::NoRole);
		QPushButton *cancelBtn = box.addButton(tr("ȡ��"), QMessageBox::RejectRole);
		//�����Ի������û�ѡ���Ƿ񱣴��޸ģ�����ȡ���رղ���
		box.exec();
		//����û�ѡ���ǣ��򷵻ر�������Ľ�������ѡ��ȡ�����򷵻�false
		if (box.clickedButton() == yesBtn)
			return save();
		else if (box.clickedButton() == cancelBtn)
			return false;
	}
	//����ĵ�û�б��޸Ĺ���ֱ�ӷ���true
	return true;
}

void MdiChild::contextMenuEvent(QContextMenuEvent* e){
	//�����˵�������������Ӷ���
	QMenu *menu = new QMenu();
	QAction *undo = menu->addAction(tr("����(&U)"), this, SLOT(undo()), QKeySequence::Undo);
	undo->setEnabled(document()->isUndoAvailable());

	QAction *redo = menu->addAction(tr("�ָ�(&R)"), this, SLOT(redo()), QKeySequence::Redo);
	redo->setEnabled(document()->isRedoAvailable());
	menu->addSeparator();

	QAction *cut = menu->addAction(tr("����(&T)"), this, SLOT(cut()), QKeySequence::Cut);
	cut->setEnabled(textCursor().hasSelection());

	QAction *copy = menu->addAction(tr("����(&C)"), this, SLOT(copy()), QKeySequence::Copy);
	copy->setEnabled(textCursor().hasSelection());

	menu->addAction(tr("ճ��(&P)"), this, SLOT(paste()), QKeySequence::Paste);
	QAction *clear = menu->addAction(tr("���"), this, SLOT(clear()));
	clear->setEnabled(!document()->isEmpty());
	menu->addSeparator();

	QAction *select = menu->addAction(tr("ȫѡ"), this, SLOT(selectAll()), QKeySequence::SelectAll);
	select->setEnabled(!document()->isEmpty());

	//��ȡ����λ�ò���ʾ�˵�
	menu->exec(e->globalPos());

	//������ٲ˵�
	delete menu;
}
