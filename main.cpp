#include <QApplication>

#include "mafenetre.h"
#include "medecin.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Medecin medecin;

    MaFenetre fenetre(medecin);
    fenetre.show();

    return app.exec();
}
