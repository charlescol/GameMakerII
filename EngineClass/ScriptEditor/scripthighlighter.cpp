#include "scripthighlighter.h"
#include <QtGui>
#include <QString>
#include <QDebug>

DScriptHighlighter::DScriptHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) //HÃ©ritage de la classe QSyntaxHighlight
{
    HighlightingRule rule;

    /*Nous indiquons une couleur et un format de police aux mots-clés.
    Nous créons ensuite une liste (stringlist, ici un QStringList) contenant les mots-clés sous forme de regexp.
    Nous faisons ensuite une boucle pour inscrire dans notre structure chaque mot-clé en regexp avec le format.
    Nous appelons ensuite une fonction faisant un petit traitement et qui appel ensuite highlightingBlock.*/

    /* 1) LES MOTS BASIQUES */

    m_basicCodeFormat.setForeground(QColor(185 , 38 , 89));
    QFile basicCodeFile("PythonCodeFile\\SyntaxHighlighting\\Type.txt");// Fichier à ouvrire contenant les noms de types
    basicCodeFile.open(QIODevice::ReadOnly);
    QString typesString =  basicCodeFile.readAll();// On récupere le contenu du fichier texte
    QStringList keywordPatterns;
    keywordPatterns = typesString.split(',');// On met le contenu du fichier dans une liste

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = m_basicCodeFormat;
        m_highlightingRules.append(rule);
    }

    /* 2) SELF */

    m_recurentFormat.setForeground(QColor(253 , 151 , 32));
    m_recurentFormat.setFontItalic(true);
    QStringList keywordPatterns3;
    keywordPatterns3 << "self";
    foreach (const QString &pattern, keywordPatterns3) {
        rule.pattern = QRegExp(pattern);
        rule.format = m_recurentFormat;
        m_highlightingRules.append(rule);
    }

    /* 2) TRUE & FALSE */

    m_boolFormat.setForeground(QColor(174, 129, 255));
    QStringList keywordPatterns4;
    keywordPatterns4 << "True" << "False";
    foreach (const QString &pattern, keywordPatterns4) {
        rule.pattern = QRegExp(pattern);
        rule.format = m_boolFormat;
        m_highlightingRules.append(rule);
    }

    /* 2) LES OPERATEURS */

    m_operatorFormat.setForeground(QColor(185 , 38 , 89));
    QStringList keywordPatterns2;
    keywordPatterns2 << "\\+" << "\\=" << "\\>" << "\\<" << "\\*" << "\\-" << "\\%" << "\\!";
    foreach (const QString &pattern, keywordPatterns2) {
        rule.pattern = QRegExp(pattern);
        rule.format = m_operatorFormat;
        m_highlightingRules.append(rule);
    }


    /* 3) LES NOMBRES */

    m_numberFormat.setForeground(QColor(174, 129, 255));
    rule.pattern = QRegExp("\\b[0-9]+\\b");
    rule.format = m_numberFormat;
    m_highlightingRules.append(rule);

    /* 4) LES FONCTIONS */

    m_functionFormat.setForeground(QColor(92 , 217 , 208));
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = m_functionFormat;
    m_highlightingRules.append(rule);


    /* 5) LES CARACTERES */

    m_caracterFormat.setForeground(QColor(230 , 219 , 116));
    rule.pattern = QRegExp("\'.*\'");
    rule.format = m_caracterFormat;
    m_highlightingRules.append(rule);



    /* 6) LES DEFINITIONS DE CLASSES */


    m_definitionFormat.setForeground(QColor(106, 198, 46));
    rule.pattern = QRegExp("(class)\\s[A-Za-z0-9]*");
    rule.format = m_definitionFormat;
    m_highlightingRules.append(rule);



    /* 7) LES COMMENTAIRES */

    /*Comme ci-dessus pour les mots-clés, mais ici comme c'est des commentaires sur une ligne (donc simple),
    il n'y a pas besoin de faire un foreach ni stringList.*/
    m_commentFormat.setForeground(Qt::darkGray);
    rule.pattern = QRegExp("#[^\n]*");
    rule.format = m_commentFormat;
    m_highlightingRules.append(rule);


    /* 8) LE CONETENU ENTRE GUILLEMETS */

    m_quotationFormat.setForeground(QColor(230 , 219 , 116));
    rule.pattern = QRegExp("\".*\"");
    rule.format = m_quotationFormat;
    m_highlightingRules.append(rule);
}

/*La fonction va rechercher le ou les mots suivant le regexp.
Elle lui applique la couleur désiré ainsi que le format.
Elle indique ensuite qu'elle à  terminé le traitement.*/
void DScriptHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, m_highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);
}
