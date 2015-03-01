#include "convertdialog.h"
#include "data.h"
#include "ZtoXYZTab.h"
#include "XYZtoZTab.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QString>
#include <QTextEdit>
#include <QDebug>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>

ConvertDialog::ConvertDialog(QWidget *parent)
     : QDialog(parent)
{
  setWindowTitle(tr("Convert between xyz and z-matrix"));

  tabWidget = new QTabWidget;
  tabWidget->addTab(new XYZtoZTab(), tr("xyz -> z-matrix"));
  tabWidget->addTab(new ZtoXYZTab(), tr("z-matrix -> xyz"));

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(tabWidget);
  setLayout(mainLayout);
}

