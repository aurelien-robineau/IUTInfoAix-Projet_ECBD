#include "mafenetre.h"
#include "charger_csv.h"

MaFenetre::MaFenetre(QWidget *parent /* = nullptr */) : QMainWindow(parent)
{
    setFixedSize(800,600);

    m_bou = new QPushButton("Quitter", this);
    m_bou->setGeometry(600,400,80,40);

    read_csv (m_mat, m_vet, "data.csv");
    CMatString columns = getColumns(m_mat);

    int marginLeft = 200;
    for(unsigned i = 0; i < m_vet.size() - 1; i++) {
        labels.push_back(new QLabel(QString::fromStdString(m_vet[i]), this));
        labels[i]->setFont(QFont("Arial", 12, QFont::Bold, true));
        labels[i]->move(marginLeft, 125);

        combo_boxes.push_back(new QComboBox(this));
        combo_boxes[i]->setGeometry(marginLeft,150,100,30);

        for (string str: columns[i]) {
            combo_boxes[i]->addItem(QString::fromStdString(str));
        }

        marginLeft += 150;
    }

    connect(m_bou, SIGNAL(clicked()), this, SLOT(setQuitter()));
    //connect(m_com, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(setCouleur()));
}

void MaFenetre::setQuitter() {
    exit(0);
}

void MaFenetre::setCouleur() {
    couleur = m_com->currentText();
    m_tra->setText(">> " + couleur + " <<");
}

CMatString MaFenetre::getColumns(const CMatString &mat) {
    CMatString columns;

    for(unsigned i = 0; i < mat[0].size() - 1; i++) {
        CVString line;
        line.push_back("NULL");

        for (unsigned j = 0; j < mat.size(); j++) {

            bool isAlreadyInMat = false;
            for(unsigned k = 0; k < line.size(); k++){
                 if(mat[j][i] == line[k]){
                     isAlreadyInMat = true;
                     break;
                 }
            }

            if(!isAlreadyInMat) {
                line.push_back(mat[j][i]);
            }
        }
        columns.push_back(line);
    }

    return columns;
}
