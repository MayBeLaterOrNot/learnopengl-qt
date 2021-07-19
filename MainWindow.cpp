#include "MainWindow.h"

#include <QGridLayout>
#include <QMessageBox>
#include <QListView>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent),
      m_openglWidget(nullptr),
      m_layout(nullptr),
      m_combox(new QComboBox(this))
{
    registerMetaObject();

    m_container = new QWidget;
    this->setCentralWidget(m_container);

    m_layout = new QGridLayout(m_container);
    m_layout->addWidget(m_combox, 1, 1, 1, 1);

    showGLWindows(0);

    QListView *view = new QListView(m_combox);
    view->setStyleSheet("QListView::item{height: 30px}");
    m_combox->setView(view);
    connect(m_combox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::showGLWindows);
}

MainWindow::~MainWindow()
{
}

void MainWindow::showGLWindows(int index)
{
    if(m_openglWidget){
        m_layout->removeWidget(m_openglWidget);
        delete m_openglWidget;
        m_openglWidget = nullptr;
    }
    //根据名字创建对应的类
    if(m_metaObjectMap.find(m_combox->currentText()) == m_metaObjectMap.end()){
        QMessageBox::warning(this, "waring", QString("can not find widget : %1").arg(m_combox->currentText()));
        return;
    }
    const QMetaObject * myMetaObject = m_metaObjectMap[m_combox->currentText()];
    m_openglWidget = static_cast<QOpenGLWidget*>(myMetaObject->newInstance());

    m_layout->addWidget(m_openglWidget, 2, 1, 10, 1);
}

void MainWindow::registerMetaObject()
{
    //1.getting_started
    m_metaObjectList << &HelloWindow::staticMetaObject;
    m_metaObjectList << &HelloTriangle::staticMetaObject;
    m_metaObjectList << &HelloTriangleIndexed::staticMetaObject;
    m_metaObjectList << &HelloTriangleExercise1::staticMetaObject;
    m_metaObjectList << &HelloTriangleExercise2::staticMetaObject;
    m_metaObjectList << &HelloTriangleExercise3::staticMetaObject;
    m_metaObjectList << &ShadersInterpolation::staticMetaObject;
    m_metaObjectList << &Textures::staticMetaObject;
    m_metaObjectList << &TexturesExercise2::staticMetaObject;
    m_metaObjectList << &TexturesExercise3::staticMetaObject;
    m_metaObjectList << &TexturesExercise4::staticMetaObject;
    m_metaObjectList << &Transformations::staticMetaObject;
    m_metaObjectList << &CoordinateSystems::staticMetaObject;
    m_metaObjectList << &CoordinateSystemsDepth::staticMetaObject;
    m_metaObjectList << &CoordinateSystemsExercise::staticMetaObject;
    m_metaObjectList << &CameraCircle::staticMetaObject;
    m_metaObjectList << &CameraInteract::staticMetaObject;
    m_metaObjectList << &CameraClass::staticMetaObject;
    //2.lighting
    m_metaObjectList << &Colors::staticMetaObject;
    m_metaObjectList << &BasicLightingDiffuse::staticMetaObject;
    m_metaObjectList << &BasicLightingSpecular::staticMetaObject;
    m_metaObjectList << &BasicLightingExercise1::staticMetaObject;
    m_metaObjectList << &BasicLightingExercise3::staticMetaObject;
    m_metaObjectList << &Materials::staticMetaObject;
    m_metaObjectList << &LightingMapsDiffuseMap::staticMetaObject;
    m_metaObjectList << &LightingMapsSpecularMap::staticMetaObject;
    m_metaObjectList << &LightingMapsExercise2::staticMetaObject;
    m_metaObjectList << &LightingMapsExercise4::staticMetaObject;
    m_metaObjectList << &LightCastersDirectional::staticMetaObject;
    m_metaObjectList << &LightCastersPoint::staticMetaObject;
    m_metaObjectList << &LightCastersSpot::staticMetaObject;

    //add QMetaObject to map and combox
    for(const QMetaObject* mo : m_metaObjectList){
        m_metaObjectMap.insert(mo->className(), mo);
        m_combox->addItem(mo->className());
    }
}

