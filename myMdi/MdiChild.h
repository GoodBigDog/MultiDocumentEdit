#pragma once
#include <QTextEdit>
#include <QMenu>
#pragma execution_character_set("utf-8")

class MdiChild :
	public QTextEdit
{
Q_OBJECT
public:
	explicit MdiChild(QWidget *parent = 0);
	void newFile();
	bool loadFile(const QString &fileName);
	bool save();
	bool saveAs();
	bool saveFile(const QString &fileName);
	QString userFriendlyCurrentFile();
	QString currentFile(){ return curFile; }
	//~MdiChild();
protected:
	void closeEvent(QCloseEvent *event);
	void contextMenuEvent(QContextMenuEvent*e);  //ÓÒ¼ü²Ëµ¥ÊÂ¼þ

private slots:
void documentWasModified();

private:
	bool maybeSave();
	void setCurrentFile(const QString &fileName);
	QString curFile;
	bool isUntitled;
};

