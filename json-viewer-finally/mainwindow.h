#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QStandardItemModel>
#include <QFileDialog>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void openJsonFile();
private:
    QTreeView *treeView;
    QStandardItemModel *model;
    void parseJson(const QJsonValue &value, QStandardItem *parentItem);
};

#endif // MAINWINDOW_H
