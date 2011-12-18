#include <QtGui/QApplication>
#include "thaihighlighter.h"
#include <QVector>
#include <QString>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ThaiHighlighter w;
    w.show();

    return a.exec();
}
