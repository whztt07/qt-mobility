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

//TESTED_COMPONENT=src/publishsubscribe

#include <qmallocpool_p.h>

#include <QtTest/QTest>

#include <QDebug>

QTM_USE_NAMESPACE
class tst_QMallocPool : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testConstructor();
    void testShared();
};

void tst_QMallocPool::initTestCase()
{
}

void tst_QMallocPool::cleanupTestCase()
{
}

void tst_QMallocPool::testConstructor()
{
    {
        QMallocPool invalidPool;
        QVERIFY(!invalidPool.isValid());
    }

    {
        QMallocPool invalidPool(0, 0, QMallocPool::NewShared);
        QVERIFY(!invalidPool.isValid());
    }

    {
        QMallocPool invalidPool(0, 0, QMallocPool::Shared);
        QVERIFY(!invalidPool.isValid());
    }

    {
        const unsigned int poolLength = 1024 * 1024;
        char *poolBase = new char[poolLength];
        for (unsigned int i = 0; i < poolLength; ++i)
            poolBase[i] = 'X';

        QMallocPool pool(poolBase, poolLength, QMallocPool::Owned);

        QVERIFY(pool.isValid());

        void *alloc;

        // test malloc
        alloc = pool.malloc(1024);
        QVERIFY(alloc != 0);
        QVERIFY(pool.size_of(alloc) >= 1024);
        QVERIFY(pool.memoryStatistics().inuseBytes >= 1024);
        pool.free(alloc);
        QVERIFY(pool.memoryStatistics().inuseBytes == 0);

        // test malloc of poolLength, should fail.
        alloc = pool.malloc(poolLength);
        QVERIFY(alloc == 0);
        QVERIFY(pool.memoryStatistics().inuseBytes == 0);

        // test malloc of poolLength + 1, should fail.
        alloc = pool.malloc(poolLength + 1);
        QVERIFY(alloc == 0);
        QVERIFY(pool.memoryStatistics().inuseBytes == 0);

        // test calloc
        alloc = pool.calloc(1024, sizeof(char));
        QVERIFY(alloc != 0);
        QVERIFY(pool.size_of(alloc) >= 1024);
        QVERIFY(pool.memoryStatistics().inuseBytes >= 1024);
        for (int i = 0; i < 1024; ++i)
            QVERIFY(reinterpret_cast<char *>(alloc)[i] == '\0');
        pool.free(alloc);
        QVERIFY(pool.memoryStatistics().inuseBytes == 0);

        // test realloc
        alloc = pool.malloc(1024);
        QVERIFY(alloc != 0);
        QVERIFY(pool.size_of(alloc) >= 1024);
        QVERIFY(pool.memoryStatistics().inuseBytes >= 1024);
        alloc = pool.realloc(alloc, 2048);
        QVERIFY(alloc != 0);
        QVERIFY(pool.size_of(alloc) >= 2048);
        QVERIFY(pool.memoryStatistics().inuseBytes >= 2048);
        pool.free(alloc);
        QVERIFY(pool.memoryStatistics().inuseBytes == 0);

        delete[] poolBase;
    }
}

void tst_QMallocPool::testShared()
{
    const unsigned int poolLength = 1024 * 1024;
    char *poolBase = new char[poolLength];
    for (unsigned int i = 0; i < poolLength; ++i)
        poolBase[i] = 'X';

    QMallocPool pool(poolBase, poolLength, QMallocPool::NewShared);
    QMallocPool pool2(poolBase, poolLength, QMallocPool::Shared);

    QVERIFY(pool.isValid());
    QVERIFY(pool2.isValid());

    void *alloc;

    // test malloc
    alloc = pool.malloc(1024);
    QVERIFY(alloc != 0);
    QVERIFY(pool.size_of(alloc) >= 1024);
    QVERIFY(pool.size_of(alloc) == pool2.size_of(alloc));
    pool.free(alloc);

    // test malloc of poolLength, should fail.
    alloc = pool.malloc(poolLength);
    QVERIFY(alloc == 0);

    // test malloc of poolLength + 1, should fail.
    alloc = pool.malloc(poolLength + 1);
    QVERIFY(alloc == 0);

    // test calloc
    alloc = pool.calloc(1024, sizeof(char));
    QVERIFY(alloc != 0);
    QVERIFY(pool.size_of(alloc) >= 1024);
    QVERIFY(pool.size_of(alloc) == pool2.size_of(alloc));
    for (int i = 0; i < 1024; ++i)
        QVERIFY(reinterpret_cast<char *>(alloc)[i] == '\0');
    pool.free(alloc);

    // test realloc
    alloc = pool.malloc(1024);
    QVERIFY(alloc != 0);
    QVERIFY(pool.size_of(alloc) >= 1024);
    QVERIFY(pool.size_of(alloc) == pool2.size_of(alloc));
    alloc = pool.realloc(alloc, 2048);
    QVERIFY(alloc != 0);
    QVERIFY(pool.size_of(alloc) >= 2048);
    QVERIFY(pool.size_of(alloc) == pool2.size_of(alloc));
    pool.free(alloc);

    delete[] poolBase;
}

QTEST_MAIN(tst_QMallocPool)
#include "tst_qmallocpool.moc"
