#ifndef MESSAGELIST_H
#define MESSAGELIST_H

#include <QStringListModel>

class MessageList : public QStringListModel
{
public:
    void prepend (const QString& string);
};

#endif // MESSAGELIST_H
