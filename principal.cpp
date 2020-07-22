#include "principal.h"
#include "ui_principal.h"

#include <QFileDialog>
#include <QDebug>

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);

    connect(ui->cmdCalcular, SIGNAL(released()),
            this, SLOT(calcular()));

    connect(ui->mnuCalcular, SIGNAL(triggered(bool)),
            this, SLOT(calcular()));
    connect(ui->mnuSalir, SIGNAL(triggered(bool)),
            this, SLOT(close()));
    connect(ui->mnuGuardar, SIGNAL(triggered(bool)),
              this, SLOT(guardar()));
    connect(ui->mnuNuevo, SIGNAL(triggered(bool)),
            this, SLOT(nuevo()));
    connect(ui->mnuAbrir, SIGNAL(triggered(bool)),
            this, SLOT(abrir()));
}

Principal::~Principal()
{
    delete ui;
}

void Principal::calcular()
{
    //obtener datos
    QString nombre = ui->inNombre->text();
    int horas= ui->inHoras->value();

    if(nombre == "" || horas == 0){
        ui->statusbar->showMessage("Nose ha ingresado datos.",4000);
        return ;
    }else{
        ui->statusbar->clearMessage();
    }

    float const HORA_EXTRA = 20.10;

    //Calcular horas extra
    int extra = 0;
    if(horas > 40){
        extra = horas - 40;
        horas = 40;
    }
    //Calcular el salario
    float salario = 0;
    if(ui->inMatutina->isChecked()){
        salario = horas * 5.15 + extra * HORA_EXTRA;
    }else if (ui->inVespirtina->isChecked()){
        salario = horas * 8.50 + extra * HORA_EXTRA;
    }else{
        salario = horas * 12.65 + extra * HORA_EXTRA;
    }

    // Calcular el descuento
    float descuento = salario * 9.5 / 100;
    float salario_neto = salario - descuento;

    // Imprimir resultados
    QString resultado = "\nObrero: " + nombre + "\n";
            resultado += "Salario: $" + QString::number(salario) + "\n";
            resultado += "Descuento (9.5%): $" + QString::number(descuento) + "\n";
            resultado += "Salario neto: $" + QString::number(salario_neto) + "\n";
            resultado += "--\n";

            ui->outCalcular->appendPlainText(resultado);
            limpiar();
}

void Principal::guardar()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Guardar datos", QDir::home().absolutePath(),"Archivo de txto(*.txt)");
    QFile data(fileName);

    if(data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream salida(&data);
        salida << ui->outCalcular->toPlainText();
        ui->statusbar->showMessage("Datos almacenados en " + fileName,5000);
    }
    /*QString fileName = QFileDialog::getSaveFileName(this,
                          "Guardar datos", QDir::home().absolutePath(), "Archivo de texto (*.txt)");
       QFile data(fileName);

       if (data.open(QFile::WriteOnly | QFile::Truncate)) {
           QTextStream salida(&data);
           salida << ui->outCalcular->toPlainText();
           ui->statusbar->showMessage("Datos almacenados en " + fileName,5000);
       }

       data.close();*/
}

void Principal::nuevo()
{
    ui->outCalcular->setPlainText("");
}

void Principal::abrir()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Abrir",QDir::home().absolutePath(),"Archivo de Texto(*.txt)");
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString linea = in.readAll();
            ui->outCalcular->setPlainText(linea);
        }
    }
}



void Principal::limpiar()
{
    ui->inNombre->setText("");
    ui->inHoras->setValue(0);
    ui->inMatutina->setChecked(true);

    ui->inNombre->setFocus();
}


void Principal::on_mnuAcerca_de_triggered()
{
    Informacion *ventanaA =  new Informacion(this);
    ventanaA->setModal(true);
    ventanaA->show();
}