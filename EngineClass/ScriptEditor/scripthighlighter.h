#ifndef SCRIPTHIGHLIGHTER_H
#define SCRIPTHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class DScriptHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
     DScriptHighlighter(QTextDocument *parent = 0);

protected:
     void highlightBlock(const QString &text); //Déclaration en fonction protégé car c'est en protégé qu'elle est déclaré dans sa classe parente

private:
     struct HighlightingRule //Structure indiquant le regexp et le format du texte à colorier
     {
         QRegExp pattern;
         QTextCharFormat format;
     };
     QVector<HighlightingRule> m_highlightingRules;

     QTextCharFormat m_basicCodeFormat; // Format des mots-clés
     QTextCharFormat m_commentFormat;   // Format des commentaires simples
     QTextCharFormat m_operatorFormat;  // Format des opérateurs
     QTextCharFormat m_numberFormat;    // Format des chiffres
     QTextCharFormat m_functionFormat;  // Format des fonctions
     QTextCharFormat m_quotationFormat; // Format du contenu entre guillement
     QTextCharFormat m_caracterFormat;  // Format des caractères
     QTextCharFormat m_recurentFormat;  // Format pour self
     QTextCharFormat m_boolFormat;      // Format pour True et False
     QTextCharFormat m_definitionFormat;// Format des définition de fonctions et de classes
};

#endif // SCRIPTHIGHLIGHTER_H
