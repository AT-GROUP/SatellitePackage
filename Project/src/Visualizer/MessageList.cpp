#include "MessageList.h"

void MessageList::prepend(const QString& string)
{
    insertRows(0, 1);
    setData(index(0), string);
    if(rowCount() > 300)
        removeRow(rowCount() - 1);
}
