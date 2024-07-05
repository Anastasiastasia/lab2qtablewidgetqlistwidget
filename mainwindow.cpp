#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QStringList"
#include "QMessageBox"
#include "QStandardItem"
#include <QFile>
#include <QTextStream>
#include <QListWidget>
#include <QListView>
#include<QListWidgetItem>
#include<QStringListModel>
#include<QLabel>
#include<QPixmap>
#include <QVBoxLayout>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->listWidget->setWrapping(true);
    //ui->listWidget->setFlow(QListView::LeftToRight);

    pict = QPixmap("D:\\1.jpg");
    model = new QStringListModel(this);

    QStringList dataList;

    // Чтение данных из текстового файла
    QFile files("D://5.txt");
    if(files.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream inz(&files);
        while (!inz.atEnd())
        {
            QString line = inz.readLine();
            dataList.append(line);
        }
        files.close();
    }
    // Заполняем нашу модель
    model->setStringList(dataList);

    // "Склеиваем"  model и listView вместе
    ui->listView->setModel(model);
    //model.setStringList(dataList);
     // QWidget *window = new QWidget;
    //QPushButton *button1 = new QPushButton("One");
   // QPushButton *button2 = new QPushButton("Two");
   // QPushButton *button3 = new QPushButton("Three");
   // QPushButton *button4 = new QPushButton("Four");
   // QPushButton *button5 = new QPushButton("Five");

   // QVBoxLayout *layout = new QVBoxLayout(window);
    //layout->addWidget(button1);
   // layout->addWidget(button2);
   // layout->addWidget(button3);
   // layout->addWidget(button4);
    //layout->addWidget(button5);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int x;
    QString S1=ui->lineEdit->text();
    x=S1.toInt();
    // добавляет новую строку, rowCount()-количество уже созданных строк :
    int ind=ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(ind + 1);
        // добавляет новые столбцы
    ui->tableWidget->setColumnCount(3);
    // Добавление заголовков:
    QStringList sl={"Фамилия", "Время","IP Адрес"};
    ui->tableWidget->setHorizontalHeaderLabels(sl);
        // расположение текста внутри ячейки:
    ui->tableWidget->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
    ui->tableWidget->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignHCenter);
    ui->tableWidget->horizontalHeaderItem(2)->setTextAlignment(Qt::AlignRight);
    QFile file("D://3.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this,tr("Ошибка"),tr("Не могу прочитать data.txt"));
        return;
    }
    QTextStream in(&file);
    int y=x;
    int row = 0;
    while (x!=0) {
        QString line = in.readLine();
        //вставка в listWidget
       // QListWidgetItem *item=new QListWidgetItem;
          //вставка в TableWidget
        QStringList data = line.split(","); // разделитель в файле, например, символ табуляции
        ui->tableWidget->insertRow(row);
        for (int column = 0; column < data.size(); ++column) {
            ui->tableWidget->setItem(row, column, new QTableWidgetItem(data[column]));
        }
        ++row;
        x--;

    }
    file.close();


    QFile filet("D://4.txt");
    if (!filet.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this,tr("Ошибка"),tr("Не могу прочитать data.txt"));
        return;
    }
    QTextStream ine(&filet);
    while (y!=0) {
        QString line = ine.readLine();
        //вставка в listWidget
        QListWidgetItem *item=new QListWidgetItem;
      QStringList data = line.split("|"); // разделитель в файле, например, символ табуляции
        for(int i=0;i<data.size();i++)
        {
            if(i==0)
            {
                item->setText(data[i]);
                ui->listWidget->addItem(item);
            }
            else
            {
                item->setData(Qt::UserRole+i,data[i]);
            }
        }
        y--;
     }
     filet.close();// ui->tableWidget->setColumnCount(4);
   // sl.append("Фото");
 //ui->tableWidget->setHorizontalHeaderLabels(sl);
    //QTableWidgetItem* item = new QTableWidgetItem;
        //вставить картинку в ячейку:
    //item-> setData(Qt::DecorationRole, pict);
   // item->setTextAlignment(Qt::AlignCenter);

}


void MainWindow::on_pushButton_2_clicked() //сортировка TableWidget
{
    ui->tableWidget->sortItems(0,Qt::AscendingOrder);
}


void MainWindow::on_pushButton_3_clicked()  //сортировка TableWidget
{
     ui->tableWidget->sortItems(0,Qt::DescendingOrder);
}
void MainWindow::on_pushButton_4_clicked() //удаление из listWidget выбранной строки
{
    QListWidgetItem *item=ui->listWidget->item(ui->listWidget->currentRow());
    if(!item)
    {
        QMessageBox::information(this,tr("Ошибка"),tr("Не выбран элемент в списке"));
        return;
    }
    ui->listWidget->takeItem(ui->listWidget->currentRow());
}



void MainWindow::on_pushButton_5_clicked()//сортировка listWidget
{
    static Qt::SortOrder order=Qt::AscendingOrder;
    ui->listWidget->sortItems(order);
    if(order==Qt::AscendingOrder)
        order=Qt::DescendingOrder;
    else order=Qt::AscendingOrder;
}


void MainWindow::on_pushButton_6_clicked()  //сортировка пузырьком для listWidget
{
   // void bubbleSort(QListWidget * listWidget)
        int n=ui->listWidget->count();
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            QListWidgetItem* item1=ui->listWidget->item(j);
            QListWidgetItem* item2=ui->listWidget->item(j+1);
            if(item1->text()>item2->text())
            {
                ui->listWidget->insertItem(j+1,item1->text());
                ui->listWidget->insertItem(j,item2->text());
                delete item1;
                delete item2;
            }
        }
    }
}
void MainWindow::on_pushButton_7_clicked()  //удаление tableWidget
{
    //получение номера строки и столбца у выделенного элемента:
    int indr= ui->tableWidget->currentRow();
        //удаление строки
    ui->tableWidget->removeRow(indr);

}



void MainWindow::on_pushButton_8_clicked()   //добавление строки в listWidget
{

    QModelIndexList indexes=ui->listView->selectionModel()->selectedIndexes();
    QStringList selectedItems;
    foreach(QModelIndex index,indexes)
    {
        selectedItems<<index.data(Qt::DisplayRole).toString();
    }
    foreach(QString item,selectedItems)
    {
        QListWidgetItem *listWidgetItem=new QListWidgetItem(item);
        ui->listWidget->addItem(listWidgetItem);
    }
}


void MainWindow::on_pushButton_9_clicked()
{
    //QTableWidgetItem* item= new QTableWidgetItem;
        //вставить картинку в ячейку:
    //ui->label->setPixmap(pict);
   // ui->label->setAlignment(Qt::AlignCenter);
   // item-> setData(Qt::DisplayRole, QPixmap::fromImage(pict.toImage()));
   // ui->tableWidget->setCellWidget(row,column,label);
    //item->setTextAlignment(Qt::AlignCenter);
    // добавляет новую строку, rowCount()-количество уже созданных строк :
    int ind=ui->tableWidget_2->rowCount();
    ui->tableWidget_2->setRowCount(ind + 1);
        // добавляет новые столбцы
    ui->tableWidget_2->setColumnCount(3);
    // Добавление заголовков:
    QStringList sl={"Header 1", "Header 2","Header 3"};
    ui->tableWidget_2->setHorizontalHeaderLabels(sl);
        // расположение текста внутри ячейки:
    ui->tableWidget_2->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
    ui->tableWidget_2->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignHCenter);
    ui->tableWidget_2->horizontalHeaderItem(2)->setTextAlignment(Qt::AlignRight);

    QTableWidgetItem* item = new QTableWidgetItem;
        //вставить картинку в ячейку:
    item-> setData(Qt::DecorationRole, pict);
    item->setTextAlignment(Qt::AlignCenter);
     ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 0, item);



}

