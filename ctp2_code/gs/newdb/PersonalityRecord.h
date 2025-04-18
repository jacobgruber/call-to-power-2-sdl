
/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */

#if defined(HAVE_PRAGMA_ONCE)
#pragma once
#endif

#ifndef PERSONALITY_RECORD_H__
#define PERSONALITY_RECORD_H__

class PersonalityRecord;

#include "CTPDatabase.h"
#include "CTPRecord.h"
class CivArchive;
class StrategyRecord;
class StrategyRecord;

#define k_Num_PersonalityRecord_Tokens 61

//
// m_flags0: Personality
#define k_Personality_IslandNationStrategy_Bit   0x00000001
#define k_Personality_StartStrategy_Bit          0x00000002
#define k_Personality_StartLowDefenceStrategy_Bit 0x00000004
#define k_Personality_StartHighDefenceStrategy_Bit 0x00000008
#define k_Personality_DefenceNoneStrategy_Bit    0x00000010
#define k_Personality_DefenceVeryLowStrategy_Bit 0x00000020
#define k_Personality_DefenceLowStrategy_Bit     0x00000040
#define k_Personality_DefenceMediumStrategy_Bit  0x00000080
#define k_Personality_DefenceHighStrategy_Bit    0x00000100
#define k_Personality_DefenceVeryHighStrategy_Bit 0x00000200
#define k_Personality_ExplorationStrategy_Bit    0x00000400
#define k_Personality_ExpansionStrategy_Bit      0x00000800
#define k_Personality_DiscoveryStrategy_Bit      0x00001000
#define k_Personality_FullAttackStrategy_Bit     0x00002000
#define k_Personality_BuildupStrengthStrategy_Bit 0x00004000
#define k_Personality_SeigeCitiesStrategy_Bit    0x00008000
#define k_Personality_NuclearStrikeStrategy_Bit  0x00010000
#define k_Personality_MinimumNukesStrategy_Bit   0x00020000
#define k_Personality_LowNukesStrategy_Bit       0x00040000
#define k_Personality_AverageNukesStrategy_Bit   0x00080000
#define k_Personality_MaximumNukesStrategy_Bit   0x00100000
#define k_Personality_ReduceSettlers_Bit         0x00200000
#define k_Personality_OverCityLimitStrategy_Bit  0x00400000
#define k_Personality_NoRevolutionStrategy_Bit   0x00800000
//
// m_Exploration bit group
#define k_Personality_Exploration_Wide_Bit       0x00000001
#define k_Personality_Exploration_Medium_Bit     0x00000002
#define k_Personality_Exploration_Minimal_Bit    0x00000004
//
// m_Conquest bit group
#define k_Personality_Conquest_Agressive_Bit     0x00000001
#define k_Personality_Conquest_Neutral_Bit       0x00000002
#define k_Personality_Conquest_Passive_Bit       0x00000004
//
// m_Expansion bit group
#define k_Personality_Expansion_Maximum_Bit      0x00000001
#define k_Personality_Expansion_Average_Bit      0x00000002
#define k_Personality_Expansion_Minimum_Bit      0x00000004
//
// m_Discovery bit group
#define k_Personality_Discovery_Scientist_Bit    0x00000001
#define k_Personality_Discovery_Military_Bit     0x00000002
#define k_Personality_Discovery_Economic_Bit     0x00000004
#define k_Personality_Discovery_Ecotopian_Bit    0x00000008
#define k_Personality_Discovery_Diplomatic_Bit   0x00000010
//
// m_Trustworthiness bit group
#define k_Personality_Trustworthiness_Chaotic_Bit 0x00000001
#define k_Personality_Trustworthiness_Neutral_Bit 0x00000002
#define k_Personality_Trustworthiness_Lawful_Bit 0x00000004
//
// m_Alignment bit group
#define k_Personality_Alignment_Evil_Bit         0x00000001
#define k_Personality_Alignment_Neutral_Bit      0x00000002
#define k_Personality_Alignment_Good_Bit         0x00000004

class PersonalityRecord : public CTPRecord
{
public:
    typedef sint32 (PersonalityRecord::*IntAccessor)() const;
    typedef bool   (PersonalityRecord::*BoolAccessor)() const;
    typedef double (PersonalityRecord::*FloatAccessor)() const ;
    typedef bool   (PersonalityRecord::*BitIntAccessor)(sint32 &val) const;
    typedef bool   (PersonalityRecord::*BitFloatAccessor)(double &val) const;
    typedef sint32 (PersonalityRecord::*IntArrayAccessor)(sint32 index) const;
    typedef double (PersonalityRecord::*FloatArrayAccessor)(sint32 index) const;

    class StrategyData {
    private:
        sint32            m_Strategy; // Index into Strategy database
        sint32            m_Priority;

    public:
        StrategyData();
        StrategyData(CivArchive & archive){ Serialize(archive); };
        ~StrategyData();
        StrategyData const & operator = (StrategyData const & rval);
        bool operator == (StrategyData const & rval) {
          if (m_Strategy != rval.m_Strategy)
             return false;
          return true;
        }

        void Serialize(CivArchive &archive);
        sint32 Parse(DBLexer *lex);
        sint32 ParseSequential(DBLexer *lex);
        sint32 ParseFullySequential(DBLexer *lex);
        static sint32 ParseInArray(DBLexer *lex, StrategyData **array, sint32 *numElements);
        static sint32 ParseInArray(DBLexer *lex, StrategyData *array, sint32 *numElements, sint32 maxSize);
        static sint32 ParseInArraySequential(DBLexer *lex, StrategyData **array, sint32 *numElements);
        static sint32 ParseInArraySequential(DBLexer *lex, StrategyData *array, sint32 *numElements, sint32 maxSize);
        void ResolveDBReferences();

        sint32           GetStrategyIndex() const { return m_Strategy; }
        StrategyRecord const * GetStrategy() const;
        sint32 GetPriority() const { return m_Priority; }

    }; /* class StrategyData */

private:
    uint32 m_flags0;
    sint32            m_DefaultStrategy; // Index into Strategy database
    sint32            m_MaxIslandSize;
    StrategyData      m_IslandNationStrategyValue;
    StrategyData      m_StartStrategyValue;
    StrategyData      m_StartLowDefenceStrategyValue;
    StrategyData      m_StartHighDefenceStrategyValue;
    sint32            m_LastStartTurn;
    StrategyData      m_DefenceNoneStrategyValue;
    StrategyData      m_DefenceVeryLowStrategyValue;
    StrategyData      m_DefenceLowStrategyValue;
    StrategyData      m_DefenceMediumStrategyValue;
    StrategyData      m_DefenceHighStrategyValue;
    StrategyData      m_DefenceVeryHighStrategyValue;
    StrategyData      m_ExplorationStrategyValue;
    StrategyData      m_ExpansionStrategyValue;
    StrategyData      m_DiscoveryStrategyValue;
    StrategyData      m_FullAttackStrategyValue;
    StrategyData      m_BuildupStrengthStrategyValue;
    StrategyData      m_SeigeCitiesStrategyValue;
    StrategyData      m_NuclearStrikeStrategyValue;
    StrategyData      m_MinimumNukesStrategyValue;
    StrategyData      m_LowNukesStrategyValue;
    StrategyData      m_AverageNukesStrategyValue;
    StrategyData      m_MaximumNukesStrategyValue;
    sint32            m_CitiesOverLimit;
    StrategyData      m_OverCityLimitStrategyValue;
    StrategyData      m_NoRevolutionStrategyValue;
    uint32            m_Exploration;
    uint32            m_Conquest;
    uint32            m_Expansion;
    uint32            m_Discovery;
    uint32            m_Trustworthiness;
    uint32            m_Alignment;
    sint32            m_StrongGreeting;
    sint32            m_WeakGreeting;
    double            m_ThreatFollowThrough;
    sint32            m_Description;
    bool m_hasGovernmentsModified; // GovMod specific flag

public:
    PersonalityRecord() { Init(); };
    PersonalityRecord(CivArchive &archive) { Serialize(archive); };
    PersonalityRecord(PersonalityRecord const & rval) { Init(); *this = rval; }
    ~PersonalityRecord();
    PersonalityRecord const & operator = (PersonalityRecord const & rval);

    void Init();
    void Serialize(CivArchive &archive);

    void CheckRequiredFields(DBLexer *lex);
    sint32 Parse(DBLexer *lex, sint32 numRecords);

    void ResolveDBReferences();
    void Merge(const PersonalityRecord & rval);
    sint32 ParseExplorationBit(DBLexer *lex);
    sint32 ParseConquestBit(DBLexer *lex);
    sint32 ParseExpansionBit(DBLexer *lex);
    sint32 ParseDiscoveryBit(DBLexer *lex);
    sint32 ParseTrustworthinessBit(DBLexer *lex);
    sint32 ParseAlignmentBit(DBLexer *lex);

    sint32           GetDefaultStrategyIndex() const { return m_DefaultStrategy; }
    StrategyRecord const * GetDefaultStrategy() const;
    sint32 GetMaxIslandSize() const { return m_MaxIslandSize; }
    bool HasIslandNationStrategy() const { return (m_flags0 & k_Personality_IslandNationStrategy_Bit) != 0; }
    bool GetIslandNationStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_IslandNationStrategy_Bit) ? &m_IslandNationStrategyValue : NULL;
        return (m_flags0 & k_Personality_IslandNationStrategy_Bit) != 0;
    }
    const StrategyData * GetIslandNationStrategyPtr() const
    {
        return (m_flags0 & k_Personality_IslandNationStrategy_Bit) ? &m_IslandNationStrategyValue : NULL;
    }
    bool HasStartStrategy() const { return (m_flags0 & k_Personality_StartStrategy_Bit) != 0; }
    bool GetStartStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_StartStrategy_Bit) ? &m_StartStrategyValue : NULL;
        return (m_flags0 & k_Personality_StartStrategy_Bit) != 0;
    }
    const StrategyData * GetStartStrategyPtr() const
    {
        return (m_flags0 & k_Personality_StartStrategy_Bit) ? &m_StartStrategyValue : NULL;
    }
    bool HasStartLowDefenceStrategy() const { return (m_flags0 & k_Personality_StartLowDefenceStrategy_Bit) != 0; }
    bool GetStartLowDefenceStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_StartLowDefenceStrategy_Bit) ? &m_StartLowDefenceStrategyValue : NULL;
        return (m_flags0 & k_Personality_StartLowDefenceStrategy_Bit) != 0;
    }
    const StrategyData * GetStartLowDefenceStrategyPtr() const
    {
        return (m_flags0 & k_Personality_StartLowDefenceStrategy_Bit) ? &m_StartLowDefenceStrategyValue : NULL;
    }
    bool HasStartHighDefenceStrategy() const { return (m_flags0 & k_Personality_StartHighDefenceStrategy_Bit) != 0; }
    bool GetStartHighDefenceStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_StartHighDefenceStrategy_Bit) ? &m_StartHighDefenceStrategyValue : NULL;
        return (m_flags0 & k_Personality_StartHighDefenceStrategy_Bit) != 0;
    }
    const StrategyData * GetStartHighDefenceStrategyPtr() const
    {
        return (m_flags0 & k_Personality_StartHighDefenceStrategy_Bit) ? &m_StartHighDefenceStrategyValue : NULL;
    }
    sint32 GetLastStartTurn() const { return m_LastStartTurn; }
    bool HasDefenceNoneStrategy() const { return (m_flags0 & k_Personality_DefenceNoneStrategy_Bit) != 0; }
    bool GetDefenceNoneStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_DefenceNoneStrategy_Bit) ? &m_DefenceNoneStrategyValue : NULL;
        return (m_flags0 & k_Personality_DefenceNoneStrategy_Bit) != 0;
    }
    const StrategyData * GetDefenceNoneStrategyPtr() const
    {
        return (m_flags0 & k_Personality_DefenceNoneStrategy_Bit) ? &m_DefenceNoneStrategyValue : NULL;
    }
    bool HasDefenceVeryLowStrategy() const { return (m_flags0 & k_Personality_DefenceVeryLowStrategy_Bit) != 0; }
    bool GetDefenceVeryLowStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_DefenceVeryLowStrategy_Bit) ? &m_DefenceVeryLowStrategyValue : NULL;
        return (m_flags0 & k_Personality_DefenceVeryLowStrategy_Bit) != 0;
    }
    const StrategyData * GetDefenceVeryLowStrategyPtr() const
    {
        return (m_flags0 & k_Personality_DefenceVeryLowStrategy_Bit) ? &m_DefenceVeryLowStrategyValue : NULL;
    }
    bool HasDefenceLowStrategy() const { return (m_flags0 & k_Personality_DefenceLowStrategy_Bit) != 0; }
    bool GetDefenceLowStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_DefenceLowStrategy_Bit) ? &m_DefenceLowStrategyValue : NULL;
        return (m_flags0 & k_Personality_DefenceLowStrategy_Bit) != 0;
    }
    const StrategyData * GetDefenceLowStrategyPtr() const
    {
        return (m_flags0 & k_Personality_DefenceLowStrategy_Bit) ? &m_DefenceLowStrategyValue : NULL;
    }
    bool HasDefenceMediumStrategy() const { return (m_flags0 & k_Personality_DefenceMediumStrategy_Bit) != 0; }
    bool GetDefenceMediumStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_DefenceMediumStrategy_Bit) ? &m_DefenceMediumStrategyValue : NULL;
        return (m_flags0 & k_Personality_DefenceMediumStrategy_Bit) != 0;
    }
    const StrategyData * GetDefenceMediumStrategyPtr() const
    {
        return (m_flags0 & k_Personality_DefenceMediumStrategy_Bit) ? &m_DefenceMediumStrategyValue : NULL;
    }
    bool HasDefenceHighStrategy() const { return (m_flags0 & k_Personality_DefenceHighStrategy_Bit) != 0; }
    bool GetDefenceHighStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_DefenceHighStrategy_Bit) ? &m_DefenceHighStrategyValue : NULL;
        return (m_flags0 & k_Personality_DefenceHighStrategy_Bit) != 0;
    }
    const StrategyData * GetDefenceHighStrategyPtr() const
    {
        return (m_flags0 & k_Personality_DefenceHighStrategy_Bit) ? &m_DefenceHighStrategyValue : NULL;
    }
    bool HasDefenceVeryHighStrategy() const { return (m_flags0 & k_Personality_DefenceVeryHighStrategy_Bit) != 0; }
    bool GetDefenceVeryHighStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_DefenceVeryHighStrategy_Bit) ? &m_DefenceVeryHighStrategyValue : NULL;
        return (m_flags0 & k_Personality_DefenceVeryHighStrategy_Bit) != 0;
    }
    const StrategyData * GetDefenceVeryHighStrategyPtr() const
    {
        return (m_flags0 & k_Personality_DefenceVeryHighStrategy_Bit) ? &m_DefenceVeryHighStrategyValue : NULL;
    }
    bool HasExplorationStrategy() const { return (m_flags0 & k_Personality_ExplorationStrategy_Bit) != 0; }
    bool GetExplorationStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_ExplorationStrategy_Bit) ? &m_ExplorationStrategyValue : NULL;
        return (m_flags0 & k_Personality_ExplorationStrategy_Bit) != 0;
    }
    const StrategyData * GetExplorationStrategyPtr() const
    {
        return (m_flags0 & k_Personality_ExplorationStrategy_Bit) ? &m_ExplorationStrategyValue : NULL;
    }
    bool HasExpansionStrategy() const { return (m_flags0 & k_Personality_ExpansionStrategy_Bit) != 0; }
    bool GetExpansionStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_ExpansionStrategy_Bit) ? &m_ExpansionStrategyValue : NULL;
        return (m_flags0 & k_Personality_ExpansionStrategy_Bit) != 0;
    }
    const StrategyData * GetExpansionStrategyPtr() const
    {
        return (m_flags0 & k_Personality_ExpansionStrategy_Bit) ? &m_ExpansionStrategyValue : NULL;
    }
    bool HasDiscoveryStrategy() const { return (m_flags0 & k_Personality_DiscoveryStrategy_Bit) != 0; }
    bool GetDiscoveryStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_DiscoveryStrategy_Bit) ? &m_DiscoveryStrategyValue : NULL;
        return (m_flags0 & k_Personality_DiscoveryStrategy_Bit) != 0;
    }
    const StrategyData * GetDiscoveryStrategyPtr() const
    {
        return (m_flags0 & k_Personality_DiscoveryStrategy_Bit) ? &m_DiscoveryStrategyValue : NULL;
    }
    bool HasFullAttackStrategy() const { return (m_flags0 & k_Personality_FullAttackStrategy_Bit) != 0; }
    bool GetFullAttackStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_FullAttackStrategy_Bit) ? &m_FullAttackStrategyValue : NULL;
        return (m_flags0 & k_Personality_FullAttackStrategy_Bit) != 0;
    }
    const StrategyData * GetFullAttackStrategyPtr() const
    {
        return (m_flags0 & k_Personality_FullAttackStrategy_Bit) ? &m_FullAttackStrategyValue : NULL;
    }
    bool HasBuildupStrengthStrategy() const { return (m_flags0 & k_Personality_BuildupStrengthStrategy_Bit) != 0; }
    bool GetBuildupStrengthStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_BuildupStrengthStrategy_Bit) ? &m_BuildupStrengthStrategyValue : NULL;
        return (m_flags0 & k_Personality_BuildupStrengthStrategy_Bit) != 0;
    }
    const StrategyData * GetBuildupStrengthStrategyPtr() const
    {
        return (m_flags0 & k_Personality_BuildupStrengthStrategy_Bit) ? &m_BuildupStrengthStrategyValue : NULL;
    }
    bool HasSeigeCitiesStrategy() const { return (m_flags0 & k_Personality_SeigeCitiesStrategy_Bit) != 0; }
    bool GetSeigeCitiesStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_SeigeCitiesStrategy_Bit) ? &m_SeigeCitiesStrategyValue : NULL;
        return (m_flags0 & k_Personality_SeigeCitiesStrategy_Bit) != 0;
    }
    const StrategyData * GetSeigeCitiesStrategyPtr() const
    {
        return (m_flags0 & k_Personality_SeigeCitiesStrategy_Bit) ? &m_SeigeCitiesStrategyValue : NULL;
    }
    bool HasNuclearStrikeStrategy() const { return (m_flags0 & k_Personality_NuclearStrikeStrategy_Bit) != 0; }
    bool GetNuclearStrikeStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_NuclearStrikeStrategy_Bit) ? &m_NuclearStrikeStrategyValue : NULL;
        return (m_flags0 & k_Personality_NuclearStrikeStrategy_Bit) != 0;
    }
    const StrategyData * GetNuclearStrikeStrategyPtr() const
    {
        return (m_flags0 & k_Personality_NuclearStrikeStrategy_Bit) ? &m_NuclearStrikeStrategyValue : NULL;
    }
    bool HasMinimumNukesStrategy() const { return (m_flags0 & k_Personality_MinimumNukesStrategy_Bit) != 0; }
    bool GetMinimumNukesStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_MinimumNukesStrategy_Bit) ? &m_MinimumNukesStrategyValue : NULL;
        return (m_flags0 & k_Personality_MinimumNukesStrategy_Bit) != 0;
    }
    const StrategyData * GetMinimumNukesStrategyPtr() const
    {
        return (m_flags0 & k_Personality_MinimumNukesStrategy_Bit) ? &m_MinimumNukesStrategyValue : NULL;
    }
    bool HasLowNukesStrategy() const { return (m_flags0 & k_Personality_LowNukesStrategy_Bit) != 0; }
    bool GetLowNukesStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_LowNukesStrategy_Bit) ? &m_LowNukesStrategyValue : NULL;
        return (m_flags0 & k_Personality_LowNukesStrategy_Bit) != 0;
    }
    const StrategyData * GetLowNukesStrategyPtr() const
    {
        return (m_flags0 & k_Personality_LowNukesStrategy_Bit) ? &m_LowNukesStrategyValue : NULL;
    }
    bool HasAverageNukesStrategy() const { return (m_flags0 & k_Personality_AverageNukesStrategy_Bit) != 0; }
    bool GetAverageNukesStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_AverageNukesStrategy_Bit) ? &m_AverageNukesStrategyValue : NULL;
        return (m_flags0 & k_Personality_AverageNukesStrategy_Bit) != 0;
    }
    const StrategyData * GetAverageNukesStrategyPtr() const
    {
        return (m_flags0 & k_Personality_AverageNukesStrategy_Bit) ? &m_AverageNukesStrategyValue : NULL;
    }
    bool HasMaximumNukesStrategy() const { return (m_flags0 & k_Personality_MaximumNukesStrategy_Bit) != 0; }
    bool GetMaximumNukesStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_MaximumNukesStrategy_Bit) ? &m_MaximumNukesStrategyValue : NULL;
        return (m_flags0 & k_Personality_MaximumNukesStrategy_Bit) != 0;
    }
    const StrategyData * GetMaximumNukesStrategyPtr() const
    {
        return (m_flags0 & k_Personality_MaximumNukesStrategy_Bit) ? &m_MaximumNukesStrategyValue : NULL;
    }
    bool GetReduceSettlers() const { return (m_flags0 & k_Personality_ReduceSettlers_Bit) != 0; }
    sint32 GetCitiesOverLimit() const { return m_CitiesOverLimit; }
    bool HasOverCityLimitStrategy() const { return (m_flags0 & k_Personality_OverCityLimitStrategy_Bit) != 0; }
    bool GetOverCityLimitStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_OverCityLimitStrategy_Bit) ? &m_OverCityLimitStrategyValue : NULL;
        return (m_flags0 & k_Personality_OverCityLimitStrategy_Bit) != 0;
    }
    const StrategyData * GetOverCityLimitStrategyPtr() const
    {
        return (m_flags0 & k_Personality_OverCityLimitStrategy_Bit) ? &m_OverCityLimitStrategyValue : NULL;
    }
    bool HasNoRevolutionStrategy() const { return (m_flags0 & k_Personality_NoRevolutionStrategy_Bit) != 0; }
    bool GetNoRevolutionStrategy(const StrategyData *&ptr) const
    {
        ptr = (m_flags0 & k_Personality_NoRevolutionStrategy_Bit) ? &m_NoRevolutionStrategyValue : NULL;
        return (m_flags0 & k_Personality_NoRevolutionStrategy_Bit) != 0;
    }
    const StrategyData * GetNoRevolutionStrategyPtr() const
    {
        return (m_flags0 & k_Personality_NoRevolutionStrategy_Bit) ? &m_NoRevolutionStrategyValue : NULL;
    }
    uint32           GetExploration() const { return m_Exploration; }
    bool             GetExplorationWide() const { return (m_Exploration & k_Personality_Exploration_Wide_Bit) != 0; }
    bool             GetExplorationMedium() const { return (m_Exploration & k_Personality_Exploration_Medium_Bit) != 0; }
    bool             GetExplorationMinimal() const { return (m_Exploration & k_Personality_Exploration_Minimal_Bit) != 0; }
    uint32           GetConquest() const { return m_Conquest; }
    bool             GetConquestAgressive() const { return (m_Conquest & k_Personality_Conquest_Agressive_Bit) != 0; }
    bool             GetConquestNeutral() const { return (m_Conquest & k_Personality_Conquest_Neutral_Bit) != 0; }
    bool             GetConquestPassive() const { return (m_Conquest & k_Personality_Conquest_Passive_Bit) != 0; }
    uint32           GetExpansion() const { return m_Expansion; }
    bool             GetExpansionMaximum() const { return (m_Expansion & k_Personality_Expansion_Maximum_Bit) != 0; }
    bool             GetExpansionAverage() const { return (m_Expansion & k_Personality_Expansion_Average_Bit) != 0; }
    bool             GetExpansionMinimum() const { return (m_Expansion & k_Personality_Expansion_Minimum_Bit) != 0; }
    uint32           GetDiscovery() const { return m_Discovery; }
    bool             GetDiscoveryScientist() const { return (m_Discovery & k_Personality_Discovery_Scientist_Bit) != 0; }
    bool             GetDiscoveryMilitary() const { return (m_Discovery & k_Personality_Discovery_Military_Bit) != 0; }
    bool             GetDiscoveryEconomic() const { return (m_Discovery & k_Personality_Discovery_Economic_Bit) != 0; }
    bool             GetDiscoveryEcotopian() const { return (m_Discovery & k_Personality_Discovery_Ecotopian_Bit) != 0; }
    bool             GetDiscoveryDiplomatic() const { return (m_Discovery & k_Personality_Discovery_Diplomatic_Bit) != 0; }
    uint32           GetTrustworthiness() const { return m_Trustworthiness; }
    bool             GetTrustworthinessChaotic() const { return (m_Trustworthiness & k_Personality_Trustworthiness_Chaotic_Bit) != 0; }
    bool             GetTrustworthinessNeutral() const { return (m_Trustworthiness & k_Personality_Trustworthiness_Neutral_Bit) != 0; }
    bool             GetTrustworthinessLawful() const { return (m_Trustworthiness & k_Personality_Trustworthiness_Lawful_Bit) != 0; }
    uint32           GetAlignment() const { return m_Alignment; }
    bool             GetAlignmentEvil() const { return (m_Alignment & k_Personality_Alignment_Evil_Bit) != 0; }
    bool             GetAlignmentNeutral() const { return (m_Alignment & k_Personality_Alignment_Neutral_Bit) != 0; }
    bool             GetAlignmentGood() const { return (m_Alignment & k_Personality_Alignment_Good_Bit) != 0; }
    sint32 GetStrongGreeting() const { return m_StrongGreeting; }
    sint32 GetWeakGreeting() const { return m_WeakGreeting; }
    double GetThreatFollowThrough() const { return m_ThreatFollowThrough; }
    sint32 GetDescription() const { return m_Description; }
    bool GetHasGovernmentsModified() const { return m_hasGovernmentsModified; }
    sint32 GenericGetNumGovernmentsModified() const { return 0; }
    sint32 GenericGetGovernmentsModifiedIndex(sint32 index) const { return -1; }

}; /* PersonalityRecord */

struct PersonalityRecordAccessorInfo
{
    PersonalityRecord::IntAccessor        m_intAccessor;
    PersonalityRecord::BoolAccessor       m_boolAccessor;
    PersonalityRecord::FloatAccessor      m_floatAccessor;
    PersonalityRecord::BitIntAccessor     m_bitIntAccessor;
    PersonalityRecord::BitFloatAccessor   m_bitFloatAccessor;
    PersonalityRecord::IntArrayAccessor   m_intArrayAccessor;
    PersonalityRecord::FloatArrayAccessor m_floatArrayAccessor;
};

extern PersonalityRecordAccessorInfo      g_PersonalityRecord_Accessors[];
extern CTPDatabase<PersonalityRecord> *   g_thePersonalityDB;

extern const char * g_Personality_Tokens[];

#endif
