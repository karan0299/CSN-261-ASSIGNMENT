#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    loadData();
    ui->setupUi(this);
    connect(ui->SearchButton, SIGNAL(clicked()), this, SLOT(on_SearchButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void
MainWindow::loadData()
{
  dictionary.loadDataInTrie();
}

void
MainWindow::on_SearchButton_clicked()
{
  QString word = ui->WordLine->text();
  if (word.isEmpty()) {
          QMessageBox::information(this, tr("Empty Search Field"),
                  "The search field is empty. Please enter a word and click Find.");
  } else {

        QString meaning = dictionary.getMeaning(word);

        if(meaning == "")
            QMessageBox::information(this, tr("Word Not Found"),
                    "The word Searched in not present in Dictionary");
        else
            ui->MeaningTextBox->setText(meaning);

  }
}
