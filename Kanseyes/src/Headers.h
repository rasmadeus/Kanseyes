#ifndef HEADERS_H
#define HEADERS_H

#include <QWidget>

class HeadersModel;
#include <QSettings>

namespace Ui {
class Headers;
}

class Headers : public QWidget
{
    Q_OBJECT
    
public:
    explicit Headers(QWidget *parent = 0);
    ~Headers();
    void save(QSettings& s) const;
    void read(QSettings& s);
private:
    Ui::Headers *ui;
};

#endif // HEADERS_H
