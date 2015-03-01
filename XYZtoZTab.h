#ifndef XYZTOZ_H
#define XYZTOZ_H

#include <QDialog>
#include <QTextEdit>

class XYZtoZTab : public QWidget
{
  Q_OBJECT

  public:
    XYZtoZTab(QWidget *parent = 0);

  public slots:
    void convertXYZtoZ();
    void loadExampleXyzFile();
    void loadXyzFile();
    void writeZmatrixFile();

  private:
    QTextEdit *zmatrixTextEdit;
    QTextEdit *xyzTextEdit; 
};

#endif
