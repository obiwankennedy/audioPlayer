/***************************************************************************
 *   Copyright (C) 2007 by Renaud Guezennec   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "pl_pdfdoc.h"
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QTextStream>

PL_PdfDoc::PL_PdfDoc() : PL_Document() {}

PL_PdfDoc::~PL_PdfDoc() {}

void PL_PdfDoc::write()
{
    QString html;

    if(model != NULL)
    {
        html+= "<table>";

        html+= "<tr>";
        for(int k= 0; k < map->size(); k++)
        {
            html+= "<td>" + model->getHeaderData(map->at(k)).toString() + "</td>";
        }
        html+= "</tr>";

        for(int i= 0; i < model->rowCount(); i++)
        {
            html+= "<tr>";
            for(int j= 0; j < map->size(); j++)
            {
                html+= "<td>" + model->getData(i, map->at(j)).toString() + "</td>";
            }
            html+= "</tr>";
        }
        html+= "</table>";
    }

    QPrinter printer;
    printer.setOutputFileName(*filename);
    printer.setOutputFormat(QPrinter::PdfFormat);

    printer.setColorMode(QPrinter::GrayScale);
    printer.setCreator(QObject::tr("Play list Generator."));
    printer.setDocName(QObject::tr("Play list PDF File."));
    printer.setDoubleSidedPrinting(false);
    printer.setFontEmbeddingEnabled(true);
    printer.setFromTo(0, 0);
    printer.setFullPage(true);
    printer.setNumCopies(1);
    printer.setOrientation(QPrinter::Portrait);

    printer.setPageOrder(QPrinter::FirstPageFirst);
    printer.setPageSize(QPrinter::A4);
    printer.setPaperSource(QPrinter::Auto);

    printer.setPrintRange(QPrinter::AllPages);

    printer.setResolution(100);

    QTextDocument doc;
    doc.setHtml(html);
    doc.print(&printer);
}
