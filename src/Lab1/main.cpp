#include <QApplication>
#include <QFile>
#include <QStyleFactory>

#include "controller/controller.h"
#include "model/model.h"
#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    application.setStyle(QStyleFactory::create("Fusion"));

    QFile themeFile(":/styles/dark-theme.qss");
    if (themeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        application.setStyleSheet(QString::fromUtf8(themeFile.readAll()));
    }

    PasswordModel model;
    MainWindow view;
    AppController controller(&model, &view);

    QObject::connect(&model, &PasswordModel::passwordsUpdated,
                     &view, &MainWindow::displayPasswords);

    view.show();
    return application.exec();
}