#ifndef THAIHIGHLIGHTER_H
#define THAIHIGHLIGHTER_H

#include <QMainWindow>

namespace Ui {
    class ThaiHighlighter;
}

class ThaiHighlighter : public QMainWindow
{
    Q_OBJECT

public:
    explicit ThaiHighlighter(QWidget *parent = 0);
    ~ThaiHighlighter();
    QVector<QString> dic;
    QString orig_text;

private:
    Ui::ThaiHighlighter *ui;
    void OpenUserFile(QString userfilename);

private slots:
    void on_changeUserButton_clicked();
    void on_highlightButton_clicked();
    void on_loadDicButton_clicked();
    void on_loadFileButton_clicked();
};

#endif // THAIHIGHLIGHTER_H
