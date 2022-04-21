/**************************************************************************
* Otter Browser: Web browser controlled by the user, not vice-versa.
* Copyright (C) 2013 - 2021 Michal Dutkiewicz aka Emdek <michal@emdek.pl>
* Copyright (C) 2014 Jan Bajer aka bajasoft <jbajer@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**************************************************************************/

#include "Utils.h"
//#include "Application.h"
//#include "PlatformIntegration.h"
//#include "TransfersManager.h"
//#include "../ui/MainWindow.h"

#include <QtCore/QBuffer>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QMimeDatabase>
#include <QtCore/QRegularExpression>
#include <QtCore/QTextStream>
#include <QtCore/QTime>
#include <QtCore/QtMath>
#include <QtGui/QDesktopServices>
#include <QtGui/QDrag>
#include <QtWidgets/QApplication>
//#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>


QUrl normalizeUrl(QUrl url)
{   
    url = url.adjusted(QUrl::RemoveFragment | QUrl::NormalizePathSegments | QUrl::StripTrailingSlash);

    if (url.path() == QLatin1String("/"))
    {
        url.setPath({});
    }

    return url;
}
