#include "mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    treeView = new QTreeView(this);
    model = new QStandardItemModel(this);
    treeView->setModel(model);

    QPushButton *uploadButton = new QPushButton("Upload JSON", this);
    uploadButton->setMinimumSize(100, 100);
    connect(uploadButton, &QPushButton::clicked, this, &MainWindow::openJsonFile);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(uploadButton);
    layout->addWidget(treeView);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

void MainWindow::openJsonFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open JSON File", "", "JSON Files (*.json)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QByteArray jsonData = file.readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
            QJsonObject obj = jsonDoc.object();
            if (!jsonDoc.isNull()) {
                QStandardItem *rootItem = new QStandardItem(file.fileName());
                model->clear();
                if (jsonDoc.isArray()) {
                    QJsonValue rootValue = jsonDoc.array();
                    model->clear();
                    model->appendRow(rootItem);
                    parseJson(rootValue, rootItem);
                } else {
                model->appendRow(rootItem);
                parseJson(obj, rootItem);
                }
            } else {
                qDebug() << "Error: Invalid JSON data.";
            }
            file.close();
        } else {
            qDebug() << "Error: Unable to open file.";
        }
    } else {
        qDebug() << "Error: Empty file path.";
    }
}

void MainWindow::parseJson(const QJsonValue &value, QStandardItem *parentItem) {
    if (value.isArray()) {
        QJsonArray jsonArray = value.toArray();
        for (int i = 0; i < jsonArray.size(); ++i) {
            QJsonValue arrayValue = jsonArray.at(i);
            QStandardItem *arrayItem = new QStandardItem(QString("[%1]").arg(i));
            parentItem->appendRow(arrayItem);
            parseJson(arrayValue, arrayItem);
        }
    } else if (value.isObject()) {
        QJsonObject jsonObj = value.toObject();
        for (const QString &key : jsonObj.keys()) {
            QJsonValue childValue = jsonObj.value(key);
            QStandardItem *childItem = new QStandardItem(key);
            parentItem->appendRow(childItem);
            parseJson(childValue, childItem);
        }
    } else {
        parentItem->appendRow(new QStandardItem(value.toVariant().toString()));
    }
}

MainWindow::~MainWindow() {
    delete model;
}
