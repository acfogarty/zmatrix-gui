#ifndef CONVERTDIALOG_H
#define CONVERTDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QTextEdit>

class QTabWidget;

class ConvertDialog : public QDialog
{
  Q_OBJECT

  public:
    ConvertDialog(QWidget *parent = 0);

  private:
    QTabWidget *tabWidget;
};

#endif
