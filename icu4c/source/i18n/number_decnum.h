// © 2017 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html

#include "unicode/utypes.h"

#if !UCONFIG_NO_FORMATTING
#ifndef __NUMBER_DECNUM_H__
#define __NUMBER_DECNUM_H__

#include "decNumber.h"
#include "charstr.h"
#include "cmemory.h"

U_NAMESPACE_BEGIN

#define DECNUM_INITIAL_CAPACITY 34

// An explicit template instantiation of MaybeStackHeaderAndArray that is
// used as a data member below is defined in number_decimalquantity.cpp.
extern template class U_IMPORT MaybeStackHeaderAndArray<decNumber, char, DECNUM_INITIAL_CAPACITY>;

namespace number {
namespace impl {

/** A very thin C++ wrapper around decNumber.h */
// Exported as U_I18N_API for tests
class U_I18N_API DecNum : public UMemory {
  public:
    DecNum();  // leaves object in valid but undefined state

    // Copy-like constructor; use the default move operators.
    DecNum(const DecNum& other, UErrorCode& status);

    /** Sets the decNumber to the StringPiece. */
    void setTo(StringPiece str, UErrorCode& status);

    /** Sets the decNumber to the NUL-terminated char string. */
    void setTo(const char* str, UErrorCode& status);

    /** Uses double_conversion to set this decNumber to the given double. */
    void setTo(double d, UErrorCode& status);

    /** Sets the decNumber to the BCD representation. */
    void setTo(const uint8_t* bcd, int32_t length, int32_t scale, bool isNegative, UErrorCode& status);

    void normalize();

    void multiplyBy(const DecNum& rhs, UErrorCode& status);

    void divideBy(const DecNum& rhs, UErrorCode& status);

    bool isNegative() const;

    bool isZero() const;

    inline const decNumber* getRawDecNumber() const {
        return fData.getAlias();
    }

  private:
    static constexpr int32_t kDefaultDigits = DECNUM_INITIAL_CAPACITY;
    MaybeStackHeaderAndArray<decNumber, char, kDefaultDigits> fData;
    decContext fContext;

    void _setTo(const char* str, int32_t maxDigits, UErrorCode& status);
};

} // namespace impl
} // namespace number

U_NAMESPACE_END

#endif // __NUMBER_DECNUM_H__

#endif /* #if !UCONFIG_NO_FORMATTING */
