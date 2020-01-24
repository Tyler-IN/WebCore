/*
 * Copyright (C) 2019 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(WEBGPU)

#include "WHLSLExpression.h"
#include "WHLSLLexer.h"
#include "WHLSLNullLiteralType.h"

namespace WebCore {

namespace WHLSL {

namespace AST {

class NullLiteral : public Expression {
public:
    NullLiteral(CodeLocation location)
        : Expression(location)
    {
    }

    virtual ~NullLiteral() = default;

    NullLiteral(const NullLiteral&) = delete;
    NullLiteral(NullLiteral&&) = default;

    NullLiteral& operator=(const NullLiteral&) = delete;
    NullLiteral& operator=(NullLiteral&&) = default;

    NullLiteralType& type() { return m_type; }

    bool isNullLiteral() const override { return true; }

    NullLiteral clone() const
    {
        auto result = NullLiteral(codeLocation());
        if (auto* resolvedType = m_type.maybeResolvedType())
            result.m_type.resolve(resolvedType->clone());
        copyTypeTo(result);
        return result;
    }

private:
    NullLiteralType m_type;
};

} // namespace AST

}

}

SPECIALIZE_TYPE_TRAITS_WHLSL_EXPRESSION(NullLiteral, isNullLiteral())

#endif