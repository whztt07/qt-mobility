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

#ifndef CPLUSPLUS_PP_CLIENT_H
#define CPLUSPLUS_PP_CLIENT_H

#include <CPlusPlusForwardDeclarations.h>
#include <QVector>

QT_BEGIN_NAMESPACE
class QByteArray;
class QString;
QT_END_NAMESPACE

namespace CPlusPlus {

class Macro;

class CPLUSPLUS_EXPORT MacroArgumentReference
{
  unsigned _position;
  unsigned _length;

public:
  MacroArgumentReference(unsigned position = 0, unsigned length = 0)
    : _position(position), _length(length)
  { }

  unsigned position() const
  { return _position; }

  unsigned length() const
  { return _length; }
};

class CPLUSPLUS_EXPORT Client
{
  Client(const Client &other);
  void operator=(const Client &other);

public:
  enum IncludeType {
    IncludeLocal,
    IncludeGlobal
  };

public:
  Client();
  virtual ~Client();

  virtual void macroAdded(const Macro &macro) = 0;

  virtual void passedMacroDefinitionCheck(unsigned offset, const Macro &macro) = 0;
  virtual void failedMacroDefinitionCheck(unsigned offset, const QByteArray &name) = 0;

  virtual void startExpandingMacro(unsigned offset,
                                   const Macro &macro,
                                   const QByteArray &originalText,
                                   bool inCondition = false,
                                   const QVector<MacroArgumentReference> &actuals
                                            = QVector<MacroArgumentReference>()) = 0;

  virtual void stopExpandingMacro(unsigned offset,
                                  const Macro &macro) = 0;

  virtual void startSkippingBlocks(unsigned offset) = 0;
  virtual void stopSkippingBlocks(unsigned offset) = 0;

  virtual void sourceNeeded(QString &fileName, IncludeType mode,
                            unsigned line) = 0; // ### FIX the signature.
};

} // namespace CPlusPlus

#endif // CPLUSPLUS_PP_CLIENT_H
