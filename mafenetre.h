#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QString>

#include "charger_csv.h"

class MaFenetre : public QMainWindow {
    Q_OBJECT // Macro OBLIGATOIRE

    public slots :
        void setQuitter();
        void setCouleur();

    public :
        MaFenetre(QWidget *parent = nullptr);

    private :
        QPushButton *m_bou;
        QComboBox *m_com;
        QLabel *m_tra;
        QString couleur;
        CVString m_vet;
        CMatString m_mat;
        vector <QComboBox*> combo_boxes;
        vector <QLabel*> labels;

        CMatString getColumns(const CMatString &mat);
};

#endif // MAFENETRE_H
