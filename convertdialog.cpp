#include "convertdialog.h"
#include "data.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QString>
#include <QTextEdit>
#include <QDebug>

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

XYZtoZTab::XYZtoZTab(QWidget *parent)
    : QWidget(parent)
{
     QLabel *infoLabel = new QLabel(tr("Enter data in xyz format, or load *.xyz file"));
     QPushButton *loadXYZButton = new QPushButton(tr("Load xyz file")); //connect to loadXYZFile()
     QPushButton *exampleButton = new QPushButton(tr("Load example file")); //connect to loadExampleXYZFile()
     QLabel *infoLabel2 = new QLabel(tr("Enter data here:"));
     QTextEdit *xyzTextEdit = new QTextEdit();
     QPushButton *convertButton = new QPushButton(tr("Convert to z-matrix")); //connect to ConvertXYZtoZ
     QLabel *infoLabel3 = new QLabel(tr("Corresponding z-matrix data:"));
     QTextEdit *zmatrixTextEdit = new QTextEdit();

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addWidget(infoLabel);
     mainLayout->addWidget(loadXYZButton);
     mainLayout->addWidget(exampleButton);
     mainLayout->addWidget(infoLabel2);
     mainLayout->addWidget(xyzTextEdit);
     mainLayout->addWidget(convertButton);
     mainLayout->addWidget(infoLabel3);
     mainLayout->addWidget(zmatrixTextEdit);
     setLayout(mainLayout);

}

//XYZtoZTab::ConvertXYZtoZ(vector<string> atomnames,vector<vector<float>> xyzData) {
//     int natoms = atomnames.size();
     
//}

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
     setLayout(mainLayout);

     connect(convertButton, SIGNAL(clicked()), this, SLOT(convertZtoXYZ()));
     connect(loadZmatrixButton, SIGNAL(clicked()), this, SLOT(test()));
     connect(exampleButton, SIGNAL(clicked()), this, SLOT(loadExampleZmatrixFile()));
}

void ZtoXYZTab::test()
{
qDebug() << "Test in test";
xyzTextEdit->setText("xxx");
};

void ZtoXYZTab::convertZtoXYZ()
{
  //xyzTextEdit->setText("xxx");
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
  std::string cstring= "7\nC1\nO2  1  1.22\nH3  1  1.09  2  120.0\nC4  1  1.54  2  120.0  3  180.0\nH5  4  1.09  1  110.0  2  000.0\nH6  4  1.09  1  110.0  2  120.0\nH7  4  1.09  1  110.0  2  -120.0";
  QString exampleString = QString(cstring.c_str());
  zmatrixTextEdit->setPlainText(exampleString);
};

/*tablabel = "xyz -> z-matrix"

QLabel "Enter data in xyz format, or load *.xyz file"
QPushButton loadXYZButton "Load xyz file", connect to loadXYZFile()
QPushButton exampleButton "Load example file", connect to loadExampleXYZFile()

QTextEdit xyzTextEdit

QPushButton convertToZmatrixButton "Convert to z-matrix", connect to convertToZmatrix()

loadExampleXYZFile() {
  QLabel "Format example:\n"
         "5"
         "#This is a molecule of ethanol"
         "C 3.4 1.5 0.5"
         "N"
  update xyzTextEdit
}

loadXYZFile() {


}



tablabel = "zmatrix -> xyx"*/

