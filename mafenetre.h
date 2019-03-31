#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <QLineEdit>
#include <QTableWidget>

#include "medecin.h"

typedef vector<string> CVString;
typedef vector <vector<string>> CMatString;
typedef pair<unsigned, unsigned> fileSize;

class MaFenetre : public QMainWindow {
    Q_OBJECT // Macro OBLIGATOIRE

    public slots :
        void displayResult();

    public :
        MaFenetre(Medecin medecin, QWidget *parent = nullptr);

    private :
        // Medecin associé à la fenetre
        Medecin m_medecin;

        // Données à traiter
        CVString m_vet;
        CMatString m_mat;

        // Elements graphiques
        QLabel*             m_title;

        QLabel*             lastNameLabel;
        QLineEdit*          m_lastName;

        QLabel*             firstNameLabel;
        QLineEdit*          m_firstName;

        QPushButton*        m_bou;

        QLabel*             m_result;

        QLabel*             m_select_Label;
        vector <QComboBox*> m_combo_boxes;
        vector <QLabel*>    m_combo_boxes_labels;

        QTableWidget*       m_table;

        // Methodes
        CMatString getColumns(const CMatString &mat);
        CVString   getComboBoxValues();
};

#endif // MAFENETRE_H
