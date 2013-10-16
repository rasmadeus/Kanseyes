#ifndef COMMAND_H
#define COMMAND_H

#include <QPointF>

class Command
{
public:
    virtual ~Command();
    virtual void append(const QPointF& point) = 0;
    virtual void setMaxSize(int maxSize) = 0;
    virtual void clear() = 0;
};

#endif // COMMAND_H
