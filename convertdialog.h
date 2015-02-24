#ifndef CONVERTDIALOG_H
#define CONVERTDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QTextEdit>

class QDialogButtonBox;
//class QFileInfo;
class QTabWidget;

class XYZtoZTab : public QWidget
{
    Q_OBJECT

public:
    XYZtoZTab(QWidget *parent = 0);

public slots:
//    void convertXYZtoZ();
};

class ZtoXYZTab : public QWidget
{
    Q_OBJECT

public:
    ZtoXYZTab(QWidget *parent = 0);

public slots:
    void convertZtoXYZ();
    void test();
    void loadExampleZmatrixFile();

private:
    QTextEdit *zmatrixTextEdit;
    QTextEdit *xyzTextEdit; 
};

class ConvertDialog : public QDialog
{
    Q_OBJECT

public:
    ConvertDialog(QWidget *parent = 0);

private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
};

#endif
