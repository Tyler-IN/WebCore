/*
 * Copyright (C) 2016 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "CSSNamespaceRule.h"

#include "CSSMarkup.h"
#include "StyleRule.h"
#include <wtf/text/StringBuilder.h>

namespace WebCore {

CSSNamespaceRule::CSSNamespaceRule(StyleRuleNamespace& namespaceRule, CSSStyleSheet* parent)
    : CSSRule(parent)
    , m_namespaceRule(namespaceRule)
{
}

CSSNamespaceRule::~CSSNamespaceRule()
{
}

AtomicString CSSNamespaceRule::namespaceURI() const
{
    return m_namespaceRule->uri();
}
    
AtomicString CSSNamespaceRule::prefix() const
{
    return m_namespaceRule->prefix();
}

String CSSNamespaceRule::cssText() const
{
    StringBuilder result;
    result.appendLiteral("@namespace ");
    serializeIdentifier(prefix(), result);
    if (!prefix().isEmpty())
        result.append(' ');
    result.append("url(");
    result.append(serializeString(namespaceURI()));
    result.append(");");
    return result.toString();
}

void CSSNamespaceRule::reattach(StyleRuleBase&)
{
}

} // namespace WebCore
