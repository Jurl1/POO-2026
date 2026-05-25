#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QStringList>
#include <QUrl>

class Parser  {

public:
    Parser();

    QStringList buscarUrls( const QString & html, const QString & baseUrl );
};

#endif // PARSER_H
