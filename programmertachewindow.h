#ifndef PROGRAMMERTACHE_H
#define PROGRAMMERTACHE_H

#include <QDialog>

namespace Ui {
class ProgrammerTache;
}

class ProgrammerTache : public QDialog
{
    Q_OBJECT

public:
    explicit ProgrammerTache(QWidget *parent = 0);
    ~ProgrammerTache();

private:
    Ui::ProgrammerTache *ui;
private slots:
    void envoyerProgrammation();
};

#endif // PROGRAMMERTACHE_H
