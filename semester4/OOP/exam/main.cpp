#include "mainwindow.h"
#include "sorters.h"
#include <QApplication>

int main(int argc, char *argv[]){

    std::cout << "shit happens" << std::endl;

    std::vector s{7, 3, 2, 5, 6};
    QuickSorter<std::vector<int>::iterator> q;
    q.sort_starting_from_percentage(s.begin(), s.end(), 20);

    for(auto i : s){
        std::cout << i << " ";
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
