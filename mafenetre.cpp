#include <string>

#include "mafenetre.h"
#include "charger_csv.h"

MaFenetre::MaFenetre(Medecin medecin, QWidget *parent /* = nullptr */) : QMainWindow(parent)
{
    m_medecin = medecin;

    setFixedSize(800,600);

    m_title = new QLabel("CLASSIFICATION DES PATIENTS : PREDICTION", this);
    m_title->setFont(QFont("Arial", 20, QFont::Bold));
    m_title->setGeometry(0, 0, 800, 50);
    m_title->setStyleSheet("background-color:#1E90FF;color:white;padding: 10;padding-left:70");

    lastNameLabel = new QLabel("Nom : ", this);
    lastNameLabel->setFont(QFont("Arial", 12));
    lastNameLabel->move(20, 70);

    m_lastName = new QLineEdit(this);
    m_lastName->setGeometry(100, 70, 200, 30);

    firstNameLabel = new QLabel("Prénom : ", this);
    firstNameLabel->setFont(QFont("Arial", 12));
    firstNameLabel->move(20, 105);

    m_firstName = new QLineEdit(this);
    m_firstName->setGeometry(100, 105, 200, 30);

    comboBoxesLabel = new QLabel("Sélectionnez vos symptômes : ", this);
    comboBoxesLabel->setFont(QFont("Arial", 12));
    comboBoxesLabel->setGeometry(20, 175, 200, 30);

    read_csv (m_mat, m_vet, "data.csv");
    CMatString columns = getColumns(m_mat);

    int marginLeft = 250;
    for(unsigned i = 0; i < m_vet.size() - 1; i++) {
        labels.push_back(new QLabel(QString::fromStdString(m_vet[i]), this));
        labels[i]->setFont(QFont("Arial", 12, QFont::Normal));
        labels[i]->move(marginLeft, 150);

        combo_boxes.push_back(new QComboBox(this));
        combo_boxes[i]->setGeometry(marginLeft,175,100,30);

        for (string str: columns[i]) {
            combo_boxes[i]->addItem(QString::fromStdString(str));
        }

        marginLeft += 105;
    }

    m_bou = new QPushButton("Prédire", this);
    m_bou->setGeometry(20,220,80,40);

    m_table = new QTableWidget(m_mat.size(), m_mat[0].size(), this);
    m_table->setGeometry(150, 300, 500, 250);

    QStringList horizontalLabels;
    for(string label: m_vet) {
        horizontalLabels.push_back(QString::fromStdString(label));
    }
    m_table->setHorizontalHeaderLabels(horizontalLabels);

    QStringList verticalLabels;
    for(unsigned i = 0; i < m_mat.size(); i++) {
        verticalLabels.push_back(QString::fromStdString("Patient " + std::to_string(i)));
    }
    m_table->setVerticalHeaderLabels(verticalLabels);

    for(unsigned line = 0; line < m_mat.size(); line++) {
        for(unsigned word = 0; word < m_mat[line].size(); word++) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(m_mat[line][word]), 0);
            m_table->setItem(line, word, item);
        }
    }

    connect(m_bou, SIGNAL(clicked()), this, SLOT(displayResults()));
    //connect(m_com, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(setCouleur()));
}

void MaFenetre::displayResults() {
    m_medecin.predire(this->getMat(), this->getVet(), this->getValues());
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

CMatString MaFenetre::getMat() {
    return m_mat;
}

CVString MaFenetre::getVet() {
    return m_vet;
}

CVString MaFenetre::getValues() {
    CVString values;
    for(QComboBox *box: combo_boxes) {
        values.push_back(box->currentText().toStdString());
    }

    return values;
}
