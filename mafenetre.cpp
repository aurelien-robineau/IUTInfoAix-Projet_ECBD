#include <string>
#include <map>

#include "mafenetre.h"
#include "charger_csv.h"

MaFenetre::MaFenetre(Medecin medecin, QWidget *parent /* = nullptr */) : QMainWindow(parent)
{
    // Initialisation des attributs
    m_medecin = medecin;
    read_csv (m_mat, m_vet, "data.csv");

    setFixedSize(800,600);

    // Titre de la fenêtre
    m_title = new QLabel("CLASSIFICATION DES PATIENTS : PREDICTION", this);
    m_title->setFont(QFont("Arial", 20, QFont::Bold));
    m_title->setGeometry(0, 0, 800, 50);
    m_title->setStyleSheet("background-color: #1E90FF;"
                           "color:white;padding: 10;"
                           "padding-left: 70");

    // Entrée du nom
    lastNameLabel = new QLabel("Nom : ", this);
    lastNameLabel->setFont(QFont("Arial", 12));
    lastNameLabel->move(20, 70);

    m_lastName = new QLineEdit(this);
    m_lastName->setGeometry(100, 70, 200, 30);

    // Entrée du prénom
    firstNameLabel = new QLabel("Prénom : ", this);
    firstNameLabel->setFont(QFont("Arial", 12));
    firstNameLabel->move(20, 105);

    m_firstName = new QLineEdit(this);
    m_firstName->setGeometry(100, 105, 200, 30);

    // Label de selection des symptomes
    m_select_Label = new QLabel("Sélectionnez vos symptômes : ", this);
    m_select_Label->setFont(QFont("Arial", 12));
    m_select_Label->setGeometry(20, 175, 200, 30);

    // Extraction des valeurs possibles pour chaque critère
    CMatString columns = getColumns(m_mat);

    int marginLeft = 250;
    // Pour tous les critères
    for(unsigned i = 0; i < m_vet.size() - 1; i++) {
        // Nouvelle combo box
        m_combo_boxes_labels.push_back(new QLabel(QString::fromStdString(m_vet[i]), this));
        m_combo_boxes_labels[i]->setFont(QFont("Arial", 12, QFont::Normal));
        m_combo_boxes_labels[i]->move(marginLeft, 150);

        m_combo_boxes.push_back(new QComboBox(this));
        m_combo_boxes[i]->setGeometry(marginLeft,175,100,30);

        // Qu'on rempli avec les valeurs possibles
        for (string str: columns[i]) {
            m_combo_boxes[i]->addItem(QString::fromStdString(str));
        }

        // On décale la prochaine combo box pour l'affichage
        marginLeft += 105;
    }

    // Bouton de prédiction
    m_bou = new QPushButton("Prédire", this);
    m_bou->setGeometry(20,220,80,40);
    connect(m_bou, SIGNAL(clicked()), this, SLOT(displayResult()));

    // Label affichage du résultat
    m_result = new QLabel(this);
    m_result->setFont(QFont("Arial", 12, QFont::Bold));
    m_result->setGeometry(110,225,580,30);

    // Tableau des données
    m_table = new QTableWidget(int(m_mat.size()), int(m_mat[0].size()), this);
    m_table->setGeometry(150, 300, 500, 250);

    // Nom des colonnes
    QStringList horizontalLabels;
    for(string label: m_vet) {
        horizontalLabels.push_back(QString::fromStdString(label));
    }
    m_table->setHorizontalHeaderLabels(horizontalLabels);

    // Nom des lignes
    QStringList verticalLabels;
    for(unsigned i = 0; i < m_mat.size(); i++) {
        verticalLabels.push_back(QString::fromStdString("Patient " + std::to_string(i)));
    }
    m_table->setVerticalHeaderLabels(verticalLabels);

    // Valeur des champs
    for(unsigned line = 0; line < m_mat.size(); line++) {
        for(unsigned word = 0; word < m_mat[line].size(); word++) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(m_mat[line][word]), 0);
            m_table->setItem(int(line), int(word), item);
        }
    }
} // constructor ()

// Comparateur de pair<string, double> pour sélection du score maximal
bool comp(pair<string, double> a, pair<string, double> b) { return a.second<b.second; }

void MaFenetre::displayResult() {
    // Calcul des socres pour chaque maladie
    map< string, double > scores;
    scores = m_medecin.predire(m_mat, m_vet, this->getComboBoxValues());

    // Affichage de la maladie de score maximum
    map<string, double>::iterator maxScore = std::max_element(scores.begin(), scores.end(), comp);
    m_result->setText(QString::fromStdString(maxScore->first));
}

// GETTERS

CMatString MaFenetre::getColumns(const CMatString &mat) {
    CMatString columns;

    // Pour chaque colonne
    for(unsigned i = 0; i < mat[0].size() - 1; i++) {
        CVString line;
        // Ajout de la valeur NULL au début pour chaque critere
        line.push_back("NULL");

        // Pour chaque ligne
        for (unsigned j = 0; j < mat.size(); j++) {

            // On regarde si la valeur a déjà été enregistrée
            bool isAlreadyInMat = false;
            for(unsigned k = 0; k < line.size(); k++){
                 if(mat[j][i] == line[k]){
                     isAlreadyInMat = true;
                     break;
                 }
            }

            // Si non, on l'enregistre
            if(!isAlreadyInMat) {
                line.push_back(mat[j][i]);
            }
        }
        columns.push_back(line);
    }

    return columns;
}

CVString MaFenetre::getComboBoxValues() {
    CVString values;
    for(QComboBox *box: m_combo_boxes) {
        values.push_back(box->currentText().toStdString());
    }

    return values;
}
