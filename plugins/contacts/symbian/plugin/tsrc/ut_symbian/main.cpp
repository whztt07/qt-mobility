/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "testrunner.h"
#include "ut_cntsymbianengine.h"
#include "ut_cntfiltering.h"
#include "ut_matchphonenumber.h"
#include "ut_cntrelationship.h"
#include "ut_cntsymbiandatabase.h"
#include "ut_transformcontactdata.h"
#include "mt_cntsqlsort.h"

#include <QtTest/QtTest>

int main(int argc, char *argv[]) 
{
    /*bool promptOnExit(true);
    for (int i=0; i<argc; i++) {
        if (QString(argv[i]) == "-noprompt")
            promptOnExit = false;
    }*/
    printf("Running tests...\n");
            
    QApplication app(argc, argv);
    
    TestRunner testRunner("ut_symbian");

    TestSymbianEngine ut_symbainEngine;
    testRunner.runTests(ut_symbainEngine);
    
    TestFiltering ut_filtering;
    testRunner.runTests(ut_filtering);
    
    TestMatchPhoneNumber ut_matchphonenumber;
    testRunner.runTests(ut_matchphonenumber);
    
    TestCntRelationship ut_relationship;
    testRunner.runTests(ut_relationship);
    
    TestCntSymbianDatabase ut_symbianDatabase;
    testRunner.runTests(ut_symbianDatabase);
    
    TestCntTransformContactData ut_transformContactData;
    testRunner.runTests(ut_transformContactData);
    
    testRunner.printResults();

    /*if (promptOnExit) {
        printf("Press any key...\n");
        getchar(); 
    }*/
    return 0;   
}

