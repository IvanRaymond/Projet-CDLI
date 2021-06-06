/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

/*
 * Qt Interface
 * Modified by Eren Riviere & Ivan Raymond
 */

#include "spreadsheet.h"
#include "spreadsheetdelegate.h"
#include "spreadsheetitem.h"
#include "printview.h"

#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#endif

bool fileOpened = false;

SpreadSheet::SpreadSheet(int rows, int cols, QWidget *parent)
    : QMainWindow(parent),
      toolBar(new QToolBar(this)),
      cellLabel(new QLabel(toolBar)),
      table(new QTableWidget(rows, cols, this)),
      formulaInput(new QLineEdit(this))
{
    addToolBar(toolBar);

    cellLabel->setMinimumSize(80, 0);

    toolBar->addWidget(cellLabel);
    toolBar->addWidget(formulaInput);

    table->setSizeAdjustPolicy(QTableWidget::AdjustToContents);
    for (int c = 0; c < cols; ++c) {
        QString character(QChar('A' + c));
        table->setHorizontalHeaderItem(c, new QTableWidgetItem(character));
    }

    table->setItemPrototype(table->item(rows - 1, cols - 1));
    table->setItemDelegate(new SpreadSheetDelegate());

    createActions();
    updateColor(nullptr);
    setupMenuBar();
    setupContents();
    setupContextMenu();
    setCentralWidget(table);

    statusBar();
    connect(table, &QTableWidget::currentItemChanged,
            this, &SpreadSheet::updateStatus);
    connect(table, &QTableWidget::currentItemChanged,
            this, &SpreadSheet::updateColor);
    connect(table, &QTableWidget::currentItemChanged,
            this, &SpreadSheet::updateLineEdit);
    connect(table, &QTableWidget::itemChanged,
            this, &SpreadSheet::updateStatus);
    connect(formulaInput, &QLineEdit::returnPressed,
            this, &SpreadSheet::returnPressed);
    connect(table, &QTableWidget::itemChanged,
            this, &SpreadSheet::updateLineEdit);

    setWindowTitle(tr("Spreadsheet"));
}

void SpreadSheet::createActions()
{
    cell_sumAction = new QAction(tr("Le dernier bouton ou on veut faire des trucs"), this);
    connect(cell_sumAction, &QAction::triggered, this, &SpreadSheet::actionSum);

    cell_addAction = new QAction(tr("&Sum"), this);
    cell_addAction->setShortcut(Qt::CTRL | Qt::Key_Plus);
    connect(cell_addAction, &QAction::triggered, this, &SpreadSheet::actionAdd);

    cell_subAction = new QAction(tr("&Max"), this);
    cell_subAction->setShortcut(Qt::CTRL | Qt::Key_Minus);
    connect(cell_subAction, &QAction::triggered, this, &SpreadSheet::actionSubtract);

    cell_mulAction = new QAction(tr("&Average"), this);
    cell_mulAction->setShortcut(Qt::CTRL | Qt::Key_multiply);
    connect(cell_mulAction, &QAction::triggered, this, &SpreadSheet::actionMultiply);

    cell_divAction = new QAction(tr("&Median"), this);
    cell_divAction->setShortcut(Qt::CTRL | Qt::Key_division);
    connect(cell_divAction, &QAction::triggered, this, &SpreadSheet::actionDivide);

    fontAction = new QAction(tr("Font..."), this);
    fontAction->setShortcut(Qt::CTRL | Qt::Key_F);
    connect(fontAction, &QAction::triggered, this, &SpreadSheet::selectFont);

    colorAction = new QAction(QPixmap(16, 16), tr("Background &Color..."), this);
    connect(colorAction, &QAction::triggered, this, &SpreadSheet::selectColor);

    clearAction = new QAction(tr("Clear"), this);
    clearAction->setShortcut(Qt::Key_Delete);
    connect(clearAction, &QAction::triggered, this, &SpreadSheet::clear);

    aboutSpreadSheet = new QAction(tr("Repair data"), this);
    connect(aboutSpreadSheet, &QAction::triggered, this, &SpreadSheet::showAbout);

    exitAction = new QAction(tr("E&xit"), this);
    connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    printAction = new QAction(tr("&Print"), this);
    connect(printAction, &QAction::triggered, this, &SpreadSheet::print);

    openAction = new QAction(tr("&Open"), this);
    connect(openAction, &QAction::triggered, this, &SpreadSheet::open);

    saveAction = new QAction(tr("&Save"), this);
    connect(saveAction, &QAction::triggered, this, &SpreadSheet::save);

    firstSeparator = new QAction(this);
    firstSeparator->setSeparator(true);

    secondSeparator = new QAction(this);
    secondSeparator->setSeparator(true);
}

void SpreadSheet::setupMenuBar()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(printAction);
    fileMenu->addAction(exitAction);

    QMenu *cellMenu = menuBar()->addMenu(tr("&Cell"));
    cellMenu->addAction(cell_addAction);
    cellMenu->addAction(cell_subAction);
    cellMenu->addAction(cell_mulAction);
    cellMenu->addAction(cell_divAction);
//    cellMenu->addAction(cell_sumAction);
    cellMenu->addSeparator();
    cellMenu->addAction(colorAction);
    cellMenu->addAction(fontAction);

    menuBar()->addSeparator();

    QMenu *aboutMenu = menuBar()->addMenu(tr("&Preprocessing"));
    aboutMenu->addAction(aboutSpreadSheet);
}

void SpreadSheet::updateStatus(QTableWidgetItem *item)
{
    if (item && item == table->currentItem()) {
        statusBar()->showMessage(item->data(Qt::StatusTipRole).toString(), 1000);
        cellLabel->setText(tr("Cell: (%1)").arg(encode_pos(table->row(item), table->column(item))));
    }
}

void SpreadSheet::updateColor(QTableWidgetItem *item)
{
    QPixmap pix(16, 16);
    QColor col;
    if (item)
        col = item->background().color();
    if (!col.isValid())
        col = palette().base().color();

    QPainter pt(&pix);
    pt.fillRect(0, 0, 16, 16, col);

    QColor lighter = col.lighter();
    pt.setPen(lighter);
    QPoint lightFrame[] = { QPoint(0, 15), QPoint(0, 0), QPoint(15, 0) };
    pt.drawPolyline(lightFrame, 3);

    pt.setPen(col.darker());
    QPoint darkFrame[] = { QPoint(1, 15), QPoint(15, 15), QPoint(15, 1) };
    pt.drawPolyline(darkFrame, 3);

    pt.end();

    colorAction->setIcon(pix);
}

bool SpreadSheet::fileOpenSafety() {
    if(!fileOpened){
        QMessageBox msgBox;
        msgBox.setText("My dear user,\n\nWe are concerned that you are trying to modify a file that has not yet been opened which contradicts this software integrity. It is therefore with our profond apologies that we print you this error message.\n\nLove, the dev team.");
        msgBox.exec();
        return false;
    }
    return true;
}

void SpreadSheet::updateLineEdit(QTableWidgetItem *item)
{
    if (item != table->currentItem())
        return;
    if (item)
        formulaInput->setText(item->data(Qt::EditRole).toString());
    else
        formulaInput->clear();
}

void SpreadSheet::returnPressed()
{
    QString text = formulaInput->text();
    int row = table->currentRow();
    int col = table->currentColumn();
    QTableWidgetItem *item = table->item(row, col);
    if (!item)
        table->setItem(row, col, new SpreadSheetItem(text));
    else
        item->setData(Qt::EditRole, text);
    table->viewport()->update();
}

void SpreadSheet::selectColor()
{
    QTableWidgetItem *item = table->currentItem();
    QColor col = item ? item->background().color() : table->palette().base().color();
    col = QColorDialog::getColor(col, this);
    if (!col.isValid())
        return;

    const QList<QTableWidgetItem *> selected = table->selectedItems();
    if (selected.isEmpty())
        return;

    for (QTableWidgetItem *i : selected) {
        if (i)
            i->setBackground(col);
    }

    updateColor(table->currentItem());
}

void SpreadSheet::selectFont()
{
    const QList<QTableWidgetItem *> selected = table->selectedItems();
    if (selected.isEmpty())
        return;

    bool ok = false;
    QFont fnt = QFontDialog::getFont(&ok, font(), this);

    if (!ok)
        return;
    for (QTableWidgetItem *i : selected) {
        if (i)
            i->setFont(fnt);
    }
}

bool SpreadSheet::runInputDialog(const QString &title,
                                 const QString &c1Text,
                                 const QString &c2Text,
                                 const QString &opText,
                                 const QString &outText,
                                 QString *cell1, QString *cell2, QString *outCell)
{
    QStringList rows, cols;
    for (int c = 0; c < table->columnCount(); ++c)
        cols << QChar('A' + c);
    for (int r = 0; r < table->rowCount(); ++r)
        rows << QString::number(1 + r);

    QDialog addDialog(this);
    addDialog.setWindowTitle(title);

    QGroupBox group(title, &addDialog);
    group.setMinimumSize(250, 100);

    QLabel cell1Label(c1Text, &group);
    QComboBox cell1RowInput(&group);
    int c1Row, c1Col;
    decode_pos(*cell1, &c1Row, &c1Col);
    cell1RowInput.addItems(rows);
    cell1RowInput.setCurrentIndex(c1Row);

    QComboBox cell1ColInput(&group);
    cell1ColInput.addItems(cols);
    cell1ColInput.setCurrentIndex(c1Col);

    QLabel operatorLabel(opText, &group);
    operatorLabel.setAlignment(Qt::AlignHCenter);

    QLabel cell2Label(c2Text, &group);
    QComboBox cell2RowInput(&group);
    int c2Row, c2Col;
    decode_pos(*cell2, &c2Row, &c2Col);
    cell2RowInput.addItems(rows);
    cell2RowInput.setCurrentIndex(c2Row);
    QComboBox cell2ColInput(&group);
    cell2ColInput.addItems(cols);
    cell2ColInput.setCurrentIndex(c2Col);

    QLabel equalsLabel("=", &group);
    equalsLabel.setAlignment(Qt::AlignHCenter);

    QLabel outLabel(outText, &group);
    QComboBox outRowInput(&group);
    int outRow, outCol;
    decode_pos(*outCell, &outRow, &outCol);
    outRowInput.addItems(rows);
    outRowInput.setCurrentIndex(outRow);
    QComboBox outColInput(&group);
    outColInput.addItems(cols);
    outColInput.setCurrentIndex(outCol);

    QPushButton cancelButton(tr("Cancel"), &addDialog);
    connect(&cancelButton, &QAbstractButton::clicked, &addDialog, &QDialog::reject);

    QPushButton okButton(tr("OK"), &addDialog);
    okButton.setDefault(true);
    connect(&okButton, &QAbstractButton::clicked, &addDialog, &QDialog::accept);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(&okButton);
    buttonsLayout->addSpacing(10);
    buttonsLayout->addWidget(&cancelButton);

    QVBoxLayout *dialogLayout = new QVBoxLayout(&addDialog);
    dialogLayout->addWidget(&group);
    dialogLayout->addStretch(1);
    dialogLayout->addItem(buttonsLayout);

    QHBoxLayout *cell1Layout = new QHBoxLayout;
    cell1Layout->addWidget(&cell1Label);
    cell1Layout->addSpacing(10);
    cell1Layout->addWidget(&cell1ColInput);
    cell1Layout->addSpacing(10);
    cell1Layout->addWidget(&cell1RowInput);

    QHBoxLayout *cell2Layout = new QHBoxLayout;
    cell2Layout->addWidget(&cell2Label);
    cell2Layout->addSpacing(10);
    cell2Layout->addWidget(&cell2ColInput);
    cell2Layout->addSpacing(10);
    cell2Layout->addWidget(&cell2RowInput);

    QHBoxLayout *outLayout = new QHBoxLayout;
    outLayout->addWidget(&outLabel);
    outLayout->addSpacing(10);
    outLayout->addWidget(&outColInput);
    outLayout->addSpacing(10);
    outLayout->addWidget(&outRowInput);

    QVBoxLayout *vLayout = new QVBoxLayout(&group);
    vLayout->addItem(cell1Layout);
    vLayout->addWidget(&operatorLabel);
    vLayout->addItem(cell2Layout);
    vLayout->addWidget(&equalsLabel);
    vLayout->addStretch(1);
    vLayout->addItem(outLayout);

    if (addDialog.exec()) {
        *cell1 = cell1ColInput.currentText() + cell1RowInput.currentText();
        *cell2 = cell2ColInput.currentText() + cell2RowInput.currentText();
        *outCell = outColInput.currentText() + outRowInput.currentText();
        return true;
    }

    return false;
}

void SpreadSheet::actionSum()
{
    int row_first = 0;
    int row_last = 0;
    int row_cur = 0;

    int col_first = 0;
    int col_last = 0;
    int col_cur = 0;

    const QList<QTableWidgetItem *> selected = table->selectedItems();

    if (!selected.isEmpty()) {
        QTableWidgetItem *first = selected.first();
        QTableWidgetItem *last = selected.last();
        row_first = table->row(first);
        row_last = table->row(last);
        col_first = table->column(first);
        col_last = table->column(last);
    }

    const QTableWidgetItem *current = table->currentItem();

    if (current) {
        row_cur = table->row(current);
        col_cur = table->column(current);
    }

    QString cell1 = encode_pos(row_first, col_first);
    QString cell2 = encode_pos(row_last, col_last);
    QString out = encode_pos(row_cur, col_cur);

    if (runInputDialog(tr("Sum cells"), tr("First cell:"), tr("Last cell:"),
                       QString("%1").arg(QChar(0x03a3)), tr("Output to:"),
                       &cell1, &cell2, &out)) {
        int row;
        int col;
        decode_pos(out, &row, &col);
        table->item(row, col)->setText(tr("sum %1 %2").arg(cell1, cell2));
    }
}

QString executeOperation(matrix range, Operation &operation)
{
    QString result;
    result = QString::fromStdString(operation.calculate(range));
    return result;
}

void SpreadSheet::actionMath_helper2(const QString &title, Operation &operation)
{
    if(fileOpenSafety()) {
        const QTableWidgetItem *current = table->currentItem();
        QStringList rows, cols;
        for (int c = 0; c < table->columnCount(); ++c)
            cols << QChar('A' + c);
        for (int r = 1; r < table->rowCount(); ++r)
            rows << QString::number(1 + r);

        QDialog addDialog(this);
        addDialog.setWindowTitle(title);

        QGroupBox group(title, &addDialog);
        group.setMinimumSize(250, 100);

        QComboBox cell1RowInput(&group);
        cell1RowInput.addItems(rows);

        QComboBox cell1ColInput(&group);
        cell1ColInput.addItems(cols);

        QLabel radio1label("Act on", &group);
        QRadioButton radio1 (tr("&Columns"),&group);
        QRadioButton radio2 (tr("&Rows"),&group);

        radio1.setChecked(true);

        QPushButton cancelButton(tr("Cancel"), &addDialog);
        connect(&cancelButton, &QAbstractButton::clicked, &addDialog, &QDialog::reject);

        QPushButton okButton(tr("OK"), &addDialog);
        okButton.setDefault(true);
        connect(&okButton, &QAbstractButton::clicked, &addDialog, &QDialog::accept);

        QHBoxLayout *buttonsLayout = new QHBoxLayout;
        buttonsLayout->addStretch(1);
        buttonsLayout->addWidget(&okButton);
        buttonsLayout->addSpacing(10);
        buttonsLayout->addWidget(&cancelButton);

        QVBoxLayout *dialogLayout = new QVBoxLayout(&addDialog);
        dialogLayout->addWidget(&group);
        dialogLayout->addStretch(1);
        dialogLayout->addItem(buttonsLayout);

        QHBoxLayout *cell1Layout = new QHBoxLayout;
        cell1Layout->addSpacing(10);
        cell1Layout->addWidget(&cell1ColInput);
        cell1Layout->addSpacing(10);
        cell1Layout->addWidget(&cell1RowInput);

        QHBoxLayout *radio1Layout = new QHBoxLayout;
        radio1Layout->addWidget(&radio1label);
        radio1Layout->addSpacing(10);
        radio1Layout->addWidget(&radio1);
        radio1Layout->addSpacing(10);
        radio1Layout->addWidget(&radio2);

        QVBoxLayout *vLayout = new QVBoxLayout(&group);
        vLayout->addItem(cell1Layout);
        vLayout->addItem(radio1Layout);
        vLayout->addStretch(1);

        if (addDialog.exec()) {
            CalculateSum sum;
            QString result;
            QMessageBox msgBox;
            matrix convertedRange;
            if(radio1.isChecked())
                convertedRange = convertRange(cell1ColInput.currentText());
            else
                convertedRange = convertRange(cell1RowInput.currentText());
            msgBox.setText(executeOperation(convertedRange, operation));
            msgBox.exec();
        }
    }
}

void SpreadSheet::actionAdd()
{
    CalculateSum res;
    actionMath_helper2(tr("Addition"), res);
}

void SpreadSheet::actionSubtract()
{
    CalculateMax res;
    actionMath_helper2(tr("Max"), res);
}

void SpreadSheet::actionMultiply()
{
    CalculateAverage res;
    actionMath_helper2(tr("Average"), res);
}
void SpreadSheet::actionDivide()
{
    CalculateMedian res;
    actionMath_helper2(tr("Median"), res);
}

void SpreadSheet::clear()
{
    const QList<QTableWidgetItem *> selectedItems = table->selectedItems();
    for (QTableWidgetItem *i : selectedItems)
        i->setText(QString());
}

void SpreadSheet::setupContextMenu()
{
    addAction(cell_addAction);
    addAction(cell_subAction);
    addAction(cell_mulAction);
    addAction(cell_divAction);
    addAction(cell_sumAction);
    addAction(firstSeparator);
    addAction(colorAction);
    addAction(fontAction);
    addAction(secondSeparator);
    addAction(clearAction);
    setContextMenuPolicy(Qt::ActionsContextMenu);
}

void SpreadSheet::setupContents()
{

}

/*
 * Data Preprocessing menu
 */
void SpreadSheet::showAbout()
{
    if(fileOpenSafety()) {
        QDialog addDialog(this);
        addDialog.setWindowTitle("Data Repair Center");

        QGroupBox group("Let's do some wizarding", &addDialog);
        group.setMinimumSize(250, 100);

        QLabel radio1label("Choose your magic spell", &group);
        QRadioButton radio3 (tr("&Median"),&group);
        QRadioButton radio4 (tr("M&ean"),&group);

        radio3.setChecked(true);

        QPushButton cancelButton(tr("Cancel"), &addDialog);
        connect(&cancelButton, &QAbstractButton::clicked, &addDialog, &QDialog::reject);

        QPushButton okButton(tr("OK"), &addDialog);
        okButton.setDefault(true);
        connect(&okButton, &QAbstractButton::clicked, &addDialog, &QDialog::accept);

        QHBoxLayout *buttonsLayout = new QHBoxLayout;
        buttonsLayout->addStretch(1);
        buttonsLayout->addWidget(&okButton);
        buttonsLayout->addSpacing(10);
        buttonsLayout->addWidget(&cancelButton);

        QVBoxLayout *dialogLayout = new QVBoxLayout(&addDialog);
        dialogLayout->addWidget(&group);
        dialogLayout->addStretch(1);
        dialogLayout->addItem(buttonsLayout);

        QHBoxLayout *radio2Layout = new QHBoxLayout;
        radio2Layout->addWidget(&radio1label);
        radio2Layout->addSpacing(10);
        radio2Layout->addWidget(&radio3);
        radio2Layout->addSpacing(10);
        radio2Layout->addWidget(&radio4);

        QVBoxLayout *vLayout = new QVBoxLayout(&group);
        vLayout->addItem(radio2Layout);
        vLayout->addStretch(1);


        if (addDialog.exec()) {
            vector<vector<string>> data;
            data = convertTable(table, 0);
            if(radio3.isChecked())
            {
                ImputerMedian method;
                DataPreprocessor::SimpleImputer imputer(method);
                data = imputer.transform(data);
            }else{
                ImputerMean method;
                DataPreprocessor::SimpleImputer imputer(method);
                data = imputer.transform(data);
            }
            QVector<QVector<QString>> qData = convertStdVect(data);
            table->clear();
            for (int i = 0; i < data.size(); ++i)
                for (int j = 0; j < data[0].size(); ++j) {
                    table->setItem(j, i, new SpreadSheetItem(qData[i][j]));
                }
            QMessageBox msgBox;
            msgBox.setText("Yer a Wizard, Harry!");
            msgBox.exec();
        }
    }
}

void decode_pos(const QString &pos, int *row, int *col)
{
    if (pos.isEmpty()) {
        *col = -1;
        *row = -1;
    } else {
        *col = pos.at(0).toLatin1() - 'A';
        *row = pos.right(pos.size() - 1).toInt() - 1;
    }
}

QString encode_pos(int row, int col)
{
    char ch = col + 'A';
    return QString(ch) + QString::number(row + 1);
}

/*
 * Print the spreadsheet
 */
void SpreadSheet::print()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printpreviewdialog)
    QPrinter printer(QPrinter::ScreenResolution);
    QPrintPreviewDialog dlg(&printer);
    PrintView view;
    view.setModel(table->model());
    connect(&dlg, &QPrintPreviewDialog::paintRequested, &view, &PrintView::print);
    dlg.exec();
#endif
}

/*
 * Convert a 2D Vector into a 2D QVector
 */
QVector<QVector<QString>> convertStdVect(vector<vector<string>> data)
{
    vector<string> col;
    QVector<QString> qCol;
    QVector<QVector<QString>> result;

    for(int i = 0; i < data.size(); i++)
    {
        col = data[i];
        qCol.clear();

        for (int j = 0; j < col.size(); j++){
            qCol.push_back(QString::fromStdString(col[j]));
        }
        result.push_back(qCol);
    }

    return result;
}

/*
 * Convert a 2D QVector into a 2D Vector
 */
vector<vector<string>> convertQVect(QVector<QVector<QString>> data)
{
    vector<string> col;
    QVector<QString> qCol;
    vector<vector<string>> result;
    string content;

    for(int i = 0; i < data.size(); i++)
    {
        qCol = data[i];
        col.clear();

        for (int j = 0; j < qCol.size(); j++){
            content = qCol[j].toStdString();
            col.push_back(content);
        }
        result.push_back(col);
    }
    return result;
}

parser myParser;

/*
 * Convert a QWidgetTable into a 2D Vector
 */
vector<vector<string>> convertTable(QTableWidget *table, int start)
{
    vector<vector<string>> result;
    vector<string> col;

    int rows = myParser.getRowCount();
    int columns = myParser.getColumnCount();

    for (int i = 0; i < columns; i++) {
        col.clear();
        for (int j = start; j < rows; j++) {
             col.push_back(table->item(j,i)->text().toStdString());
        }
        result.push_back(col);
    }
    return result;
}

/*
 * Get a row at index row
 */
vector<vector<string>> getRow(vector<vector<string>> data, int row)
{
    row -= 2;
    vector<vector<string>> result;
    vector<string> col, temp;
    temp = data[0];

    // Check if row index is greater than the number of rows
    if (row < temp.size()){
         // Add each element of the row to a new 2D Vector
        for(int i = 0; i < data.size(); i++)
        {
            col.push_back(data[i][row]);
        }
        result.push_back(col);
    }
    return result;
}

/*
 * Get the column at the index col
 */
vector<vector<string>> getColumn(vector<vector<string>> data, int col)
{
    vector<vector<string>> result;

    if (col < data.size()) {
        result.push_back(data[col]);
    }

    return result;
}

/*
 * Fetch data from either a column or row
 * If range is numerical then a row is returned else a column is returned
 */
vector<vector<string>> SpreadSheet::convertRange(QString range)
{
    QMessageBox msgBox;

    vector<vector<string>> data, result;
    data = convertTable(table);
    bool ok;
    range.toInt(&ok);   //Ok set to True if range is numerical

    // Range is numerical so it is a row
    if(ok)
    {
        result = getRow(data, range.toInt());
    }
    else
    {
        //Convert the column letter to a char
        char ch = range.toStdString()[0];
        int col = ch;   //convert char to ASCII code
        col -= 65;      // convert col to the column number

        result = getColumn(data, col);
    }
    return result;
}

/*
 * Open a CSV file
 */
void SpreadSheet::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open CSV file"), "",
        tr("Your favorite CSV file (.csv) (*.csv);;All Files (*)"));
    if(!fileName.isEmpty()&& !fileName.isNull()){
        myParser.parse(fileName.toStdString());
        QVector<QVector<QString>> data = convertStdVect(myParser.getData());
        for (int i = 0; i < data.size(); ++i)
            for (int j = 0; j < data[0].size(); ++j) {
                table->setItem(j, i, new SpreadSheetItem(data[i][j]));
            }
        fileOpened = true;
    }    
    return;
}

/*
 * Save the spreadsheet into a CSV file
 */
void SpreadSheet::save()
{
     // file dialog box
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save CSV"), "",
        tr("CSV (*.csv);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        QTextStream out(&file);
        QString textData;

        // Get the count of rows and columns in the dataset
        int rows = myParser.getRowCount();
        int columns = myParser.getColumnCount();

        // Reverse parsing to save to file
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {

                textData += table->item(i,j)->text();
                if(j<columns-1){
                    textData += ";";    // for .csv file format
                }
            }
            textData += "\n";             // new line segmentation
        }
        out << textData;
    }
}



