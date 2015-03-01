#ifndef ZTOXYZ_H
#define ZTOXYZ_H

#include <QDialog>
#include <QTextEdit>

class ZtoXYZTab : public QWidget
{
  Q_OBJECT

  public:
    ZtoXYZTab(QWidget *parent = 0);

  public slots:
    void convertZtoXYZ();
    void loadExampleZmatrixFile();
    void loadZmatrixFile();
    void writeXyzFile();

  private:
    QTextEdit *zmatrixTextEdit;
    QTextEdit *xyzTextEdit; 
};

#endif
