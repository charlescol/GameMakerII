#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QObject>
#include <QPlainTextEdit>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;


class DCodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    DCodeEditor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *m_lineNumberArea;
};


class DLineNumberArea : public QWidget
{
public:
    DLineNumberArea(DCodeEditor *editor) : QWidget(editor) {
        m_codeEditor = editor;
    }

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(m_codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
        m_codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    DCodeEditor *m_codeEditor;
};

#endif // CODEEDITOR_H
