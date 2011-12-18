#include "thaihighlighter.h"
#include "ui_thaihighlighter.h"
#include <QtGui>
#include <QRegExp>
#include <QVector>
#include <QSettings>


ThaiHighlighter::ThaiHighlighter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ThaiHighlighter)
{
    ui->setupUi(this);

}

ThaiHighlighter::~ThaiHighlighter()
{
    delete ui;
}

void ThaiHighlighter::on_loadFileButton_clicked()
{
    QString fileName;

    fileName = QFileDialog::getOpenFileName(this,
            tr("Open File"), "", "Text Files (*.txt)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
            ui->mainTextEdit->setPlainText(file.readAll());
    }
}

void ThaiHighlighter::on_loadDicButton_clicked()
{
    QString dicfilename;
    QSettings settings("Remi Soft", "Thai Highlighter");
    /* Testing ini
    QSettings wordlist("wordlist.ini", QSettings::IniFormat);
    wordlist.setValue("Words","Test123");
    wordlist.setValue("Words/1","Test123");
    wordlist.setValue("Words/2","Test12345");
    // End Testing ini*/
    dicfilename = settings.value("dicfile","").toString();
    dicfilename = QFileDialog::getOpenFileName(this,
        tr("Open Dictionary File"),dicfilename,tr("All files (*.*)"));

    if (!dicfilename.isEmpty()) {
        QFile dicfile(dicfilename);
        // dicfile.setCodec( "UTF-8" );
        settings.setValue("dicfile", dicfilename);

        if (dicfile.open(QFile::ReadOnly)){
            //ui->dicOutput->setPlainText(dicfile.readAll());
            QTextStream in(&dicfile);
            in.setCodec("utf8");
            //ui->dicOutput->setPlainText(in.readAll());
            //int i=0;
            //QString sI;
            QString inputtext;
            dic.clear();

            while (!in.atEnd()) {
                //i++;
                //sI.setNum(i);
                //ui->dicOutput->insertPlainText(sI);
                inputtext.append(in.read(1000));
                //process_inputtext(inputtext);
            }
            // Change . to \.
            inputtext.replace(".", "\\.");
            QRegExp filter("#");
            //QVector<QString> dic;
            int index1 = 0;
            int index2 = filter.indexIn(inputtext);
            while (index2 >= 0) {
                //int length = filter.matchedLength();

                dic.append(inputtext.mid(index1, index2 - index1));
                index1 = index2 + 1;
                index2 = filter.indexIn(inputtext, index1);
            }
            QString nDic;
            nDic.setNum(dic.size());
            nDic.prepend(" Number of entries in dic: ");
            nDic.prepend(dic[dic.size() - 1]);
            nDic.prepend(" ");
            nDic.prepend(dic[0]);
            ui->dicOutput->setText(nDic);
        }
    }
    //dicfile.open()
}

void ThaiHighlighter::on_highlightButton_clicked()
{
    orig_text = ui->mainTextEdit->toPlainText();


    foreach (const QString &thaiword, dic){
        QString notFirstChar = "(\\x0E31|\\x0E33|\\x0E34|\\x0E35|\\x0E36|\\x0E37|\\x0E38|\\x0E39|\\x0E3A|\\x0E47|\\x0E48|\\x0E49|\\x0E4A|\\x0E4B|\\x0E4C|\\x0E4E)";
        QRegExp rNotFirstChar(notFirstChar);
        QString regExpAddition = "(?!((\\w|\\.)*\\]))";
        regExpAddition.prepend(thaiword);
        QRegExp thaiw(regExpAddition);
        int index = thaiw.indexIn(orig_text);
        while (index >= 0) {
            int length = thaiw.matchedLength();
            QString nextChar = " ";
            if ((index+length) < orig_text.length()){
                nextChar = orig_text.at(index + length);
                }
            //int foundLast = nextChar.count(rNotFirstChar);
            if (!nextChar.contains(rNotFirstChar)){
                orig_text.insert(index + length,"]");
                orig_text.insert(index,"[");
            }
            index = thaiw.indexIn(orig_text, index + length + 2);
        }
    }

    ui->dicOutput->setText(orig_text);
}

void ThaiHighlighter::on_changeUserButton_clicked()
{

}
