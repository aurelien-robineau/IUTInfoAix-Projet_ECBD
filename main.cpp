#include <QApplication>
#include <QLabel>
#include <QFont>
#include <QWidget>
#include <QPushButton>

#include <mafenetre.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MaFenetre fenetre;
    fenetre.show();

    return app.exec();
}