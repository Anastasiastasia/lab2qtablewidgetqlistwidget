#include "mainwindow.h"

#include <QApplication>
#include<QVBoxLayout>
#include<QPushButton>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QWidget window;
    window.setWindowTitle("Пример использования QVBoxLayout");

    // Создаем QVBoxLayout и устанавливаем его в качестве макета для окна
    QVBoxLayout layout;
    window.setLayout(&layout);

    // Создаем несколько кнопок и добавляем их в QVBoxLayout
    QPushButton button1("Кнопка 1");
    layout.addWidget(&button1);

    QPushButton button2("Кнопка 2");
    layout.addWidget(&button2);

    QPushButton button3("Кнопка 3");
    layout.addWidget(&button3);

    // Показываем окно
    window.show();
    return a.exec();
}
