#include "convertdialog.h"
#include "data.h"
#include "ZtoXYZTab.h"
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

ZtoXYZTab::ZtoXYZTab(QWidget *parent)
  : QWidget(parent)
{
  QLabel *infoLabel = new QLabel(tr("Enter data in z-matrix format, load a z-matrix\nfile, or use the z-matrix builder"));
  QPushButton *loadZmatrixButton = new QPushButton(tr("Load z-matrix file")); //connect to loadZmatrixFile()
  QPushButton *exampleButton = new QPushButton(tr("Load example file")); //connect to loadExampleZmatrixFile()
  QPushButton *builderButton = new QPushButton(tr("Open z-matrix builder")); //connect to zmatrixBuilder()
  QLabel *infoLabel2 = new QLabel(tr("Enter data here:"));
  zmatrixTextEdit = new QTextEdit();
  QPushButton *convertButton = new QPushButton(tr("Convert to xyz format")); //connect to ConvertZtoXYZ
  QLabel *infoLabel3 = new QLabel(tr("Corresponding xyz-format data:"));
  xyzTextEdit = new QTextEdit();
  QPushButton *saveButton = new QPushButton(tr("Save to .xyz file")); //connect to writeXyzFile()

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(infoLabel);
  mainLayout->addWidget(loadZmatrixButton);
  mainLayout->addWidget(exampleButton);
  mainLayout->addWidget(builderButton);
  mainLayout->addWidget(infoLabel2);
  mainLayout->addWidget(zmatrixTextEdit);
  mainLayout->addWidget(convertButton);
  mainLayout->addWidget(infoLabel3);
  mainLayout->addWidget(xyzTextEdit);
  mainLayout->addWidget(saveButton);
  setLayout(mainLayout);

  connect(convertButton, SIGNAL(clicked()), this, SLOT(convertZtoXYZ()));
  connect(loadZmatrixButton, SIGNAL(clicked()), this, SLOT(loadZmatrixFile()));
  connect(exampleButton, SIGNAL(clicked()), this, SLOT(loadExampleZmatrixFile()));
  connect(saveButton, SIGNAL(clicked()), this, SLOT(writeXyzFile()));
}

void ZtoXYZTab::loadZmatrixFile()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                              QString(), tr("z-matrix files (*)"));
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly))
  {
    std::cerr << "Cannot open z-matrix file: " << qPrintable(file.errorString()) << std::endl;
    return;
  }

  QTextStream in(&file);
  QString zmatrixString;
  zmatrixString=" ";
  while (!in.atEnd()) 
  {
    QString line = in.readLine();
    zmatrixString+=line;
    zmatrixString+="\n";
  }
  zmatrixTextEdit->setPlainText(zmatrixString);
};

void ZtoXYZTab::writeXyzFile()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Open File..."),
                                              QString(), tr("z-matrix files (*)"));
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly))
  {
    std::cerr << "Cannot open .xyz file " << qPrintable(file.errorString()) << " for writing."<< std::endl;
    return;
  }
  QTextStream out(&file);
  QString xyzString=xyzTextEdit->toPlainText();
  out<<xyzString;
};

void ZtoXYZTab::convertZtoXYZ()
{
  //get contents of texteditInput
  QString zString,xyzString;
  zString = zmatrixTextEdit->toPlainText();
  std::string inputString = zString.toStdString();
  //store contents of texteditInput
  Data data;
  data.getZdataFromString(inputString);
  //convert to xyz format
  data.convertZdataToXYZdata();
  std::string outputString = data.outputXYZdataToString();
  //set contents of texteditOutput
  xyzString = QString(outputString.c_str());
  xyzTextEdit->setPlainText(xyzString);
};

void ZtoXYZTab::loadExampleZmatrixFile()
{
  std::string cstring= "7\n#acetaldehyde\nC1\nO2  1  1.22\nH3  1  1.09  2  120.0\nC4  1  1.54  2  120.0  3  180.0\nH5  4  1.09  1  110.0  2  000.0\nH6  4  1.09  1  110.0  2  120.0\nH7  4  1.09  1  110.0  2  -120.0";
  QString exampleString = QString(cstring.c_str());
  zmatrixTextEdit->setPlainText(exampleString);
};

