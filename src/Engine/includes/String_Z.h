#ifndef _STRING_Z_H_
#define _STRING_Z_H_
#include "Types_Z.h"
#include "Assert_Z.h"

Extern_Z "C" U32 strlen(const Char* str);
Extern_Z "C" char* strupr(Char* str);
Extern_Z "C" int strcmp(const Char* str1, const Char* str2);
Extern_Z "C" int strncmp(const Char* str1, const Char* str2, int n);
Extern_Z "C" int strcpy(Char* dest, const Char* src);
Extern_Z "C" int strcat(Char* dest, const Char* src);
Extern_Z "C" int vsprintf(const Char* i_Buf, const Char* i_Format, va_list i_Args);
Extern_Z "C" int strncpy(Char* dest, const Char* src, S32 count);
Bool fstricmp(const Char* a1, const Char* a2);
void fsprintfID(Char* a1, U32 a2, U32 a3);

template <S32 Size>
class String_Z {
public:
    String_Z<Size>() {
        Empty();
    }

    void Empty() {
        m_Str[0] = 0;
    }

    const Char* Get() const { return m_Str; }

    Char* Get() { return m_Str; }

    void StrCpy(const Char* i_Str) { strcpy(m_Str, i_Str); }

    void StrCat(const Char* i_Str) { strcat(m_Str, i_Str); }

    inline String_Z<Size>& operator=(const Char* i_Text) {
        StrCpy(i_Text);
        return *this;
    }

    operator const Char*() const {
        return m_Str;
    }

    operator Char*() {
        return m_Str;
    }

    Char* CStr() {
        return m_Str;
    }

    const Char* CStr() const {
        return m_Str;
    }

    S32 CpyTo(Char* i_Dst, S32 i_Size) {
        S32 i = 0;
        do {
            i_Dst[i] = m_Str[i];
            i++;
            i_Size--;
        } while (i_Size);
    }

    S32 StrnCpy(const Char* i_Src, S32 i_Count) {
        return strncpy(m_Str, i_Src, i_Count);
    }

    void Sprintf(const Char* i_Format, ...) {
        va_list l_Args;

        
        ASSERTLE_Z(i_Format != Get(),"",30,"_Str!=Get()");
        va_start(l_Args, i_Format);
        vsprintf(m_Str, i_Format, l_Args);

        va_end(args);
        return;
    }

    Char* Upr() {
        return strupr(m_Str);
    }

    S32 FStrCmp(const Char* i_Str) const {
        return fstricmp(m_Str, i_Str);
    }

    S32 StrCmp(const Char* i_Str) const {
        return strcmp(m_Str, i_Str);
    }

    S32 StrnCmp(const Char* i_Str, S32 i_N) const {
        return strncmp(m_Str, i_Str, i_N);
    }

    inline Char& operator[](S32 i_Index) {
        return m_Str[i_Index];
    }

    S32 StrLen() const {
        return (S32)strlen(m_Str);
    }

private:
    Char m_Str[Size];
};

#endif
