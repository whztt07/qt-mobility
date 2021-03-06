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

// Copyright (c) 2008 Roberto Raggi <roberto.raggi@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef CPLUSPLUS_ASTFWD_H
#define CPLUSPLUS_ASTFWD_H

#include "CPlusPlusForwardDeclarations.h"

namespace CPlusPlus {

template <typename _Tp> class List;

class AST;
class ASTVisitor;
class ASTMatcher;

class AccessDeclarationAST;
#ifdef ICHECK_BUILD
  class QPropertyDeclarationAST;
  class QEnumDeclarationAST;
  class QFlagsDeclarationAST;
  class QDeclareFlagsDeclarationAST;
#endif
class ArrayAccessAST;
class ArrayDeclaratorAST;
class ArrayInitializerAST;
class AsmDefinitionAST;
class AttributeAST;
class AttributeSpecifierAST;
class BaseSpecifierAST;
class BinaryExpressionAST;
class BoolLiteralAST;
class BreakStatementAST;
class CallAST;
class CaseStatementAST;
class CastExpressionAST;
class CatchClauseAST;
class ClassSpecifierAST;
class CompoundLiteralAST;
class CompoundStatementAST;
class ConditionAST;
class ConditionalExpressionAST;
class ContinueStatementAST;
class ConversionFunctionIdAST;
class CoreDeclaratorAST;
class CppCastExpressionAST;
class CtorInitializerAST;
class DeclarationAST;
class DeclarationStatementAST;
class DeclaratorAST;
class DeclaratorIdAST;
class DeleteExpressionAST;
class DestructorNameAST;
class DoStatementAST;
class ElaboratedTypeSpecifierAST;
class EmptyDeclarationAST;
class EnumSpecifierAST;
class EnumeratorAST;
class ExceptionDeclarationAST;
class ExceptionSpecificationAST;
class ExpressionAST;
class ExpressionOrDeclarationStatementAST;
class ExpressionStatementAST;
class ForStatementAST;
class ForeachStatementAST;
class FunctionDeclaratorAST;
class FunctionDefinitionAST;
class GotoStatementAST;
class IfStatementAST;
class LabeledStatementAST;
class LinkageBodyAST;
class LinkageSpecificationAST;
class MemInitializerAST;
class MemberAccessAST;
class NameAST;
class NamedTypeSpecifierAST;
class NamespaceAST;
class NamespaceAliasDefinitionAST;
class NestedDeclaratorAST;
class NestedExpressionAST;
class NestedNameSpecifierAST;
class NewArrayDeclaratorAST;
class NewExpressionAST;
class NewInitializerAST;
class NewPlacementAST;
class NewTypeIdAST;
class NumericLiteralAST;
class ObjCClassDeclarationAST;
class ObjCClassForwardDeclarationAST;
class ObjCDynamicPropertiesDeclarationAST;
class ObjCEncodeExpressionAST;
class ObjCFastEnumerationAST;
class ObjCInstanceVariablesDeclarationAST;
class ObjCMessageArgumentAST;
class ObjCMessageArgumentDeclarationAST;
class ObjCMessageExpressionAST;
class ObjCMethodDeclarationAST;
class ObjCMethodPrototypeAST;
class ObjCPropertyAttributeAST;
class ObjCPropertyDeclarationAST;
class ObjCProtocolDeclarationAST;
class ObjCProtocolExpressionAST;
class ObjCProtocolForwardDeclarationAST;
class ObjCProtocolRefsAST;
class ObjCSelectorAST;
class ObjCSelectorArgumentAST;
class ObjCSelectorExpressionAST;
class ObjCSelectorWithArgumentsAST;
class ObjCSelectorWithoutArgumentsAST;
class ObjCSynchronizedStatementAST;
class ObjCSynthesizedPropertiesDeclarationAST;
class ObjCSynthesizedPropertyAST;
class ObjCTypeNameAST;
class ObjCVisibilityDeclarationAST;
class OperatorAST;
class OperatorFunctionIdAST;
class ParameterDeclarationAST;
class ParameterDeclarationClauseAST;
class PointerAST;
class PointerToMemberAST;
class PostIncrDecrAST;
class PostfixAST;
class PostfixDeclaratorAST;
class PostfixExpressionAST;
class PtrOperatorAST;
class QtMemberDeclarationAST;
class QtMethodAST;
class QualifiedNameAST;
class ReferenceAST;
class ReturnStatementAST;
class SimpleDeclarationAST;
class SimpleNameAST;
class SimpleSpecifierAST;
class SizeofExpressionAST;
class SpecifierAST;
class StatementAST;
class StringLiteralAST;
class SwitchStatementAST;
class TemplateDeclarationAST;
class TemplateIdAST;
class TemplateTypeParameterAST;
class ThisExpressionAST;
class ThrowExpressionAST;
class TranslationUnitAST;
class TryBlockStatementAST;
class TypeConstructorCallAST;
class TypeIdAST;
class TypeidExpressionAST;
class TypenameCallExpressionAST;
class TypenameTypeParameterAST;
class TypeofSpecifierAST;
class UnaryExpressionAST;
class UsingAST;
class UsingDirectiveAST;
class WhileStatementAST;

typedef List<ExpressionAST *> ExpressionListAST;
typedef List<DeclarationAST *> DeclarationListAST;
typedef List<StatementAST *> StatementListAST;
typedef List<DeclaratorAST *> DeclaratorListAST;
typedef List<BaseSpecifierAST *> BaseSpecifierListAST;
typedef List<EnumeratorAST *> EnumeratorListAST;
typedef List<MemInitializerAST *> MemInitializerListAST;
typedef List<NewArrayDeclaratorAST *> NewArrayDeclaratorListAST;
typedef List<PostfixAST *> PostfixListAST;
typedef List<PostfixDeclaratorAST *> PostfixDeclaratorListAST;
typedef List<AttributeAST *> AttributeListAST;
typedef List<NestedNameSpecifierAST *> NestedNameSpecifierListAST;
typedef List<CatchClauseAST *> CatchClauseListAST;
typedef List<PtrOperatorAST *> PtrOperatorListAST;
typedef List<SpecifierAST *> SpecifierListAST;

typedef List<NameAST *> ObjCIdentifierListAST;
typedef List<ObjCMessageArgumentAST *> ObjCMessageArgumentListAST;
typedef List<ObjCSelectorArgumentAST *> ObjCSelectorArgumentListAST;
typedef List<ObjCPropertyAttributeAST *> ObjCPropertyAttributeListAST;
typedef List<ObjCMessageArgumentDeclarationAST *> ObjCMessageArgumentDeclarationListAST;
typedef List<ObjCSynthesizedPropertyAST *> ObjCSynthesizedPropertyListAST;

typedef ExpressionListAST TemplateArgumentListAST;

} // end of namespace CPlusPlus


#endif // CPLUSPLUS_ASTFWD_H
