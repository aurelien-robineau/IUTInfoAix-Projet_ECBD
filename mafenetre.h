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

#include "charger_csv.h"
#include "medecin.h"

class MaFenetre : public QMainWindow {
    Q_OBJECT // Macro OBLIGATOIRE

    public slots :
        void displayResults();

    public :
        MaFenetre(Medecin medecin, QWidget *parent = nullptr);
        CMatString getMat();
        CVString getVet();
        CVString getValues();

    private :
        Medecin m_medecin;
        QLabel *m_title;
        QLabel *lastNameLabel;
        QLineEdit *m_lastName;
        QLabel *firstNameLabel;
        QLineEdit *m_firstName;
        QPushButton *m_bou;
        QComboBox *m_com;
        QLabel *m_tra;
        QString couleur;
        CVString m_vet;
        CMatString m_mat;
        QLabel *comboBoxesLabel;
        vector <QComboBox*> combo_boxes;
        vector <QLabel*> labels;
        QTableWidget *m_table;

        CMatString getColumns(const CMatString &mat);
};

#endif // MAFENETRE_H
