#include "principal.h"

#include <QApplication>

//añadimos las siguientes librerias
#include <QTranslator>
#include <QInputDialog>
#include <QLocale>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Creo objeto para manejar las traducciones
       QTranslator traducion;
    // Solicito al usuario que seleccione un idioma del programa
       QStringList idiomas;
       idiomas << "Japones" << "Ruso";
       QString idiomaSeleccionado = QInputDialog::getItem(NULL,
                                  "Idioma",
                                  "Seleccione un idioma",
                                  idiomas);

     // Dependiendo del idioma que elija se cargara el archivo de traducción (.qm)
       if(idiomaSeleccionado == "Japones"){
           traducion.load(":/Traducion-Salario_ja_JP.qm");
       }else if( idiomaSeleccionado == "Ruso"){
           traducion.load(":/Traducion-Salario_ru_RU.qm");
       }

      // Si es diferente de español, se instala la traducción en TODA la aplicación
           if (idiomaSeleccionado != "Español"){
               a.installTranslator(&traducion);
           }


    // MUESTRA LA VENTANA PRINCIPAL
    Principal w;
    w.show();
    //Cambio de nombre de la ventana
    //w.setWindowTitle("Salario - Qt");
    return a.exec();
}


