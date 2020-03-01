#include "graphviewturing.h"
#include <QInputDialog>

GraphViewTuring::GraphViewTuring(QWidget* parent):GraphViewDfa(parent)
{

}

QString GraphViewTuring::setEdgeValueInputDialog(){
    QString first = QInputDialog::getText( this ,"" ,"مقدار اول یال را وارد کنید" );
    QString second = QInputDialog::getText( this ,"" ,"مقدار دوم یال را وارد کنید" );
    QString third = QInputDialog::getText( this ,"" ,"مقدار سوم یال را وارد کنید" );

    first = ( first == tr("") ? tr("#") : first ) + tr(" ; ");
    second = ( second == tr("") ? tr("#") : second ) + tr(" : ");
    third = ( third != tr("R") && third != tr("L" ) ? tr("R") : third );

    QString edgeValue = first + second + third;
    return edgeValue;
}
