#include "convertdialog.h"
#include "data.h"
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

XYZtoZTab::XYZtoZTab(QWidget *parent)
  : QWidget(parent)
{
  QLabel *infoLabel = new QLabel(tr("Enter data in xyz format, or load *.xyz file"));
  QPushButton *loadXYZButton = new QPushButton(tr("Load xyz file")); //connect to loadXYZFile()
  QPushButton *exampleButton = new QPushButton(tr("Load example file")); //connect to loadExampleXYZFile()
  QLabel *infoLabel2 = new QLabel(tr("Enter data here:"));
  xyzTextEdit = new QTextEdit();
  QPushButton *convertButton = new QPushButton(tr("Convert to z-matrix")); //connect to ConvertXYZtoZ
  QLabel *infoLabel3 = new QLabel(tr("Corresponding z-matrix data:"));
  zmatrixTextEdit = new QTextEdit();
  QPushButton *saveButton = new QPushButton(tr("Save to z-matrix file")); //connect to writeZmatrixFile()

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(infoLabel);
  mainLayout->addWidget(loadXYZButton);
  mainLayout->addWidget(exampleButton);
  mainLayout->addWidget(infoLabel2);
  mainLayout->addWidget(xyzTextEdit);
  mainLayout->addWidget(convertButton);
  mainLayout->addWidget(infoLabel3);
  mainLayout->addWidget(zmatrixTextEdit);
  mainLayout->addWidget(saveButton);
  setLayout(mainLayout);

  connect(convertButton, SIGNAL(clicked()), this, SLOT(convertXYZtoZ()));
  connect(loadXYZButton, SIGNAL(clicked()), this, SLOT(loadXyzFile()));
  connect(exampleButton, SIGNAL(clicked()), this, SLOT(loadExampleXyzFile()));
  connect(saveButton, SIGNAL(clicked()), this, SLOT(writeZmatrixFile()));
}

void XYZtoZTab::loadXyzFile() //almost identical to loadZmatrixFile, should refactor
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                              QString(), tr("(*), *.xyz"));
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly))
  {
    std::cerr << "Cannot open .xyz file: " << qPrintable(file.errorString()) << std::endl;
    return;
  }

  QTextStream in(&file);
  QString xyzString;
  xyzString=" ";
  while (!in.atEnd()) 
  {
    QString line = in.readLine();
    xyzString+=line;
    xyzString+="\n";
  }
  xyzTextEdit->setPlainText(xyzString);
};

void XYZtoZTab::writeZmatrixFile()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save File..."),
                                              QString(), tr("(*)"));
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly))
  {
    std::cerr << "Cannot open z-matrix file " << qPrintable(file.errorString()) << " for writing."<< std::endl;
    return;
  }
  QTextStream out(&file);
  QString zmatrixString=zmatrixTextEdit->toPlainText();
  out<<zmatrixString;
}

void XYZtoZTab::convertXYZtoZ()
{
  //get contents of texteditInput
  QString zString,xyzString;
  xyzString = xyzTextEdit->toPlainText();
  std::string inputString = xyzString.toStdString();
  //store contents of texteditInput
  Data data;
  data.getXyzdataFromString(inputString);
  //convert to zmatrix format
  data.convertXYZdataToZdata();
  std::string outputString = data.outputZdataToString();
  //set contents of texteditOutput
  zString = QString(outputString.c_str());
  zmatrixTextEdit->setPlainText(zString);
};

void XYZtoZTab::loadExampleXyzFile()
{
  std::string cstring= "7\n#acetaldehyde\nC1 0.0 0.0 0.0\nO2 0.0 0.0 1.22\nH3 0 0.943969 -0.544998\nC4 0.0 -1.33368 -0.769998\nH5 0.0 -2.16867 -0.0693563\nH6 0.887037 -1.40047 -1.39992\nH7 -0.887045 -1.40047 -1.39992";
  QString exampleString = QString(cstring.c_str());
  xyzTextEdit->setPlainText(exampleString);
};
