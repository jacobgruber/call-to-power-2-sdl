
/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */

#if defined(HAVE_PRAGMA_ONCE)
#pragma once
#endif

#ifndef POP_RECORD_H__
#define POP_RECORD_H__

class PopRecord;

#include "CTPDatabase.h"
#include "CTPRecord.h"
class CivArchive;
class AdvanceRecord;
class GovernmentRecord;

#define k_Num_PopRecord_Tokens 9


class PopRecord : public CTPRecord
{
public:
    typedef sint32 (PopRecord::*IntAccessor)() const;
    typedef bool   (PopRecord::*BoolAccessor)() const;
    typedef double (PopRecord::*FloatAccessor)() const ;
    typedef bool   (PopRecord::*BitIntAccessor)(sint32 &val) const;
    typedef bool   (PopRecord::*BitFloatAccessor)(double &val) const;
    typedef sint32 (PopRecord::*IntArrayAccessor)(sint32 index) const;
    typedef double (PopRecord::*FloatArrayAccessor)(sint32 index) const;

private:
    sint32            m_EnableAdvance; // Index into Advance database
    sint32          * m_GovernmentsModified; // Index into Government database
    sint32            m_numGovernmentsModified;
    sint32            m_Science;
    sint32            m_Happiness;
    sint32            m_Food;
    sint32            m_Production;
    sint32            m_Commerce;
    sint32            m_Culture;
    sint32            m_Defense;
    bool m_hasGovernmentsModified; // GovMod specific flag

public:
    PopRecord() { Init(); };
    PopRecord(CivArchive &archive) { Serialize(archive); };
    PopRecord(PopRecord const & rval) { Init(); *this = rval; }
    ~PopRecord();
    PopRecord const & operator = (PopRecord const & rval);

    void Init();
    void Serialize(CivArchive &archive);

    void CheckRequiredFields(DBLexer *lex);
    sint32 Parse(DBLexer *lex, sint32 numRecords);

    void ResolveDBReferences();
    void Merge(const PopRecord & rval);

    sint32           GetEnableAdvanceIndex() const { return m_EnableAdvance; }
    AdvanceRecord const * GetEnableAdvance() const;
    sint32 GetGovernmentsModifiedIndex(sint32 index) const;
    const GovernmentRecord * GetGovernmentsModified(sint32 index) const;
    sint32 GetNumGovernmentsModified() const { return m_numGovernmentsModified;}
    sint32 GetScience() const { return m_Science; }
    sint32 GetHappiness() const { return m_Happiness; }
    sint32 GetFood() const { return m_Food; }
    sint32 GetProduction() const { return m_Production; }
    sint32 GetCommerce() const { return m_Commerce; }
    sint32 GetCulture() const { return m_Culture; }
    sint32 GetDefense() const { return m_Defense; }
    bool GetHasGovernmentsModified() const { return m_hasGovernmentsModified; }
    sint32 GenericGetNumGovernmentsModified() const { return m_numGovernmentsModified; }
    sint32 GenericGetGovernmentsModifiedIndex(sint32 index) const { return GetGovernmentsModifiedIndex(index); }

}; /* PopRecord */

struct PopRecordAccessorInfo
{
    PopRecord::IntAccessor        m_intAccessor;
    PopRecord::BoolAccessor       m_boolAccessor;
    PopRecord::FloatAccessor      m_floatAccessor;
    PopRecord::BitIntAccessor     m_bitIntAccessor;
    PopRecord::BitFloatAccessor   m_bitFloatAccessor;
    PopRecord::IntArrayAccessor   m_intArrayAccessor;
    PopRecord::FloatArrayAccessor m_floatArrayAccessor;
};

extern PopRecordAccessorInfo      g_PopRecord_Accessors[];
extern CTPDatabase<PopRecord> *   g_thePopDB;

extern const char * g_Pop_Tokens[];

#endif
