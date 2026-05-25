#include "parser.h"
#include <QRegularExpression>

Parser::Parser()  {
}

QStringList Parser::buscarUrls( const QString & html, const QString & baseUrl )  {
    QStringList urls;
    QUrl base( baseUrl );

    // Busca atributos src="..." y href="..."
    QRegularExpression reSrcHref( "(?:src|href)\\s*=\\s*[\"']([^\"'#]+)[\"']",
                                  QRegularExpression::CaseInsensitiveOption );

    QRegularExpressionMatchIterator it = reSrcHref.globalMatch( html );

    while ( it.hasNext() )  {
        QRegularExpressionMatch match = it.next();
        QString url = match.captured( 1 ).trimmed();

        // Ignorar URLs vacías, data URIs y javascript
        if ( url.isEmpty() || url.startsWith( "data:" ) || url.startsWith( "javascript:" ) )
            continue;

        QUrl resuelta = base.resolved( QUrl( url ) );
        QString urlStr = resuelta.toString();

        if ( ! urls.contains( urlStr ) )  {
            urls.append( urlStr );
        }
    }

    // Busca url(...) dentro de estilos CSS embebidos
    QRegularExpression reCss( "url\\s*\\(\\s*[\"']?([^\"')\\s]+)[\"']?\\s*\\)",
                              QRegularExpression::CaseInsensitiveOption );

    QRegularExpressionMatchIterator itCss = reCss.globalMatch( html );

    while ( itCss.hasNext() )  {
        QRegularExpressionMatch match = itCss.next();
        QString url = match.captured( 1 ).trimmed();

        if ( url.isEmpty() || url.startsWith( "data:" ) )
            continue;

        QUrl resuelta = base.resolved( QUrl( url ) );
        QString urlStr = resuelta.toString();

        if ( ! urls.contains( urlStr ) )  {
            urls.append( urlStr );
        }
    }

    return urls;
}
