
/*
 * DO NOT EDIT THIS FILE!
 * It is generated automatically by ctpdb
 */
#include "c3.h"
#include "MapRecord.h"

#include <algorithm>
#include "BitArray.h"
#include "c3errors.h"
#include "CTPDatabase.h"
#include "DBLexer.h"
#include "DBTokens.h"
#include "StrDB.h"


CTPDatabase<MapRecord> *g_theMapDB = NULL;

void MapRecord::Init()
{
    m_Settings = NULL;
    m_numSettings = 0;
    m_Width = 0;
    m_Height = 0;
    m_CityLimitModifyer = 1.000000;
    //GovMod Specific flag initialization
    m_hasGovernmentsModified = false;
}

void MapRecord::Serialize(CivArchive &archive)
{
    if(archive.IsStoring()) {
        archive << m_index;
        if(m_name >= 0){
            archive << GetIDText();
        }
        else{
            archive << static_cast<MBCHAR*>(NULL);
        }

        {
            archive << m_numSettings;
            for(sint32 i = 0; i < m_numSettings; ++i){
                m_Settings[i].Serialize(archive);
            }
        }

        archive << m_Width;
        archive << m_Height;
        archive << m_CityLimitModifyer;
    } else {
        //GovMod Specific flag initialization
        m_hasGovernmentsModified = false;

        archive >> m_index;
        {
            MBCHAR* tmpStr = NULL;
            archive >> tmpStr;
            g_theStringDB->GetStringID(tmpStr, m_name);
            SetTextName(g_theStringDB->GetNameStr(m_name));
        }

        {
            archive >> m_numSettings;
            m_Settings = new Settings[m_numSettings];
            for(sint32 i = 0; i < m_numSettings; ++i){
                m_Settings[i].Serialize(archive);
            }
        }

        archive >> m_Width;
        archive >> m_Height;
        archive >> m_CityLimitModifyer;
    }
}

MapRecord::~MapRecord()
{
    delete [] m_Settings;
}

MapRecord const & MapRecord::operator = (MapRecord const & rval)
{
    if (this != &rval)
    {
        m_index = rval.m_index;
        m_hasGovernmentsModified = rval.m_hasGovernmentsModified;

        delete [] m_Settings;
        m_Settings = NULL;
        if (rval.m_numSettings > 0)
        {
            m_Settings = new Settings [rval.m_numSettings];
            std::copy(rval.m_Settings, rval.m_Settings + rval.m_numSettings, m_Settings);
        }
        m_numSettings = rval.m_numSettings;

        m_Width = rval.m_Width;

        m_Height = rval.m_Height;

        m_CityLimitModifyer = rval.m_CityLimitModifyer;

    }

    return *this;
}

const char *g_Map_Tokens[] =
{
    "Settings",
    "Width",
    "Height",
    "CityLimitModifyer",
};

MapRecordAccessorInfo g_MapRecord_Accessors[] =
{
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL }, /* Settings */
    { &MapRecord::GetWidth, NULL, NULL, NULL, NULL, NULL, NULL },
    { &MapRecord::GetHeight, NULL, NULL, NULL, NULL, NULL, NULL },
    { NULL, NULL, &MapRecord::GetCityLimitModifyer, NULL, NULL, NULL, NULL },
};

#define k_Token_Map_Settings                     ((k_Token_Custom_Base) + 0)
#define k_Token_Map_Width                        ((k_Token_Custom_Base) + 1)
#define k_Token_Map_Height                       ((k_Token_Custom_Base) + 2)
#define k_Token_Map_CityLimitModifyer            ((k_Token_Custom_Base) + 3)
#define k_Token_Map_Max                          ((k_Token_Custom_Base) + 4)


static BitArray s_ParsedTokens(4);
void MapRecord::CheckRequiredFields(DBLexer *lex)
{
    if(!s_ParsedTokens.Bit(k_Token_Map_Width - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field Width missing"));
    }
    if(!s_ParsedTokens.Bit(k_Token_Map_Height - k_Token_Custom_Base)) {
        DBERROR(("Warning: required field Height missing"));
    }
}

sint32 MapRecord::Parse(DBLexer *lex, sint32 numRecords)
{
    bool done = false;
    sint32 result = 0;
    sint32 tok;
    s_ParsedTokens.Clear();
    lex->SetTokens(g_Map_Tokens, k_Token_Map_Max);
    tok = lex->GetToken();
    if(tok == k_Token_Int) {
        tok = lex->GetToken(); // Accept number to make new db compatible with the old database format
    }
    if(tok != k_Token_Name) {
        char newName[256];
        sprintf(newName, "MAP_%i", numRecords);
        if(!g_theStringDB->GetStringID(newName, m_name)) {
            g_theStringDB->InsertStr(newName, newName);
            if(!g_theStringDB->GetStringID(newName, m_name))
                SetTextName(newName);
        }
    }
    else{
        if(!g_theStringDB->GetStringID(lex->GetTokenText(), m_name)) {
            g_theStringDB->InsertStr(lex->GetTokenText(), lex->GetTokenText());
            if(!g_theStringDB->GetStringID(lex->GetTokenText(), m_name))
                SetTextName(lex->GetTokenText());
        }
        tok = lex->GetToken();
    }

    if(tok == k_Token_Int) {
        s_ParsedTokens.SetBit(k_Token_Map_Width - k_Token_Custom_Base);
        m_Width = atoi(lex->GetTokenText());
        tok = lex->GetToken();
    }
    if(tok == k_Token_Int) {
        s_ParsedTokens.SetBit(k_Token_Map_Height - k_Token_Custom_Base);
        m_Height = atoi(lex->GetTokenText());
        tok = lex->GetToken();
    }

    if(tok != k_Token_OpenBrace) {
        DBERROR(("Missing open brace"));
        return 0;
    }

    while(!done) {
        tok = lex->GetToken();
        if(tok >= k_Token_Custom_Base && tok < k_Token_Map_Max) {
            s_ParsedTokens.SetBit(tok - k_Token_Custom_Base);
        }
        switch(tok) {
            case k_Token_Map_Settings:
                if(!MapRecord::Settings::ParseInArray(lex, &m_Settings, &m_numSettings))
                {
                    done = true; break;
                }
                break;
            case k_Token_Map_Width:
                if(!lex->GetIntAssignment(m_Width)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_Map_Height:
                if(!lex->GetIntAssignment(m_Height)) {
                    DBERROR(("Expected integer"));
                    done = true; break;
                }
                break;
            case k_Token_Map_CityLimitModifyer:
                if(!lex->GetFloatAssignment(m_CityLimitModifyer)) {
                    DBERROR(("Expected number"));
                    done = true; break;
                }
                break;
            case k_Token_CloseBrace:
                done = true;
                result = 1;
                break;
            default:
                if(!MapRecord::Settings::ParseInArray(lex, &m_Settings, &m_numSettings)) {
                    DBERROR(("Unknown token"));
                    done = true; break;
                }
                break;
        }
    }
    CheckRequiredFields(lex);
    lex->RestoreTokens();
    return result;
}

void MapRecord::ResolveDBReferences()
{
    {
        sint32 i;
        for(i = 0; i < m_numSettings; i++) {
            m_Settings[i].ResolveDBReferences();
        }
    }
}

MapRecord::Settings::Settings()
{
    m_NumContinents = 0.000000;
    m_MinWidth = 0.000000;
    m_MinHeight = 0.000000;
    m_MaxWidth = 0.000000;
    m_MaxHeight = 0.000000;
    m_BumpSize = 0.000000;
    m_MinSubcontinents = 0.000000;
    m_MaxSubcontinents = 0.000000;
    m_SubcontinentSize = 0.000000;
    m_SubcontinentHeight = 0.000000;
    m_BorderSize = 0.000000;
    m_FaultLines = 0.000000;
    m_FaultLength = 0.000000;
    m_NSBorderSize = 0.000000;
}

MapRecord::Settings::~Settings()
{
}

MapRecord::Settings const & MapRecord::Settings::operator = (Settings const & rval)
{
    if (this != &rval)
    {

        m_NumContinents = rval.m_NumContinents;

        m_MinWidth = rval.m_MinWidth;

        m_MinHeight = rval.m_MinHeight;

        m_MaxWidth = rval.m_MaxWidth;

        m_MaxHeight = rval.m_MaxHeight;

        m_BumpSize = rval.m_BumpSize;

        m_MinSubcontinents = rval.m_MinSubcontinents;

        m_MaxSubcontinents = rval.m_MaxSubcontinents;

        m_SubcontinentSize = rval.m_SubcontinentSize;

        m_SubcontinentHeight = rval.m_SubcontinentHeight;

        m_BorderSize = rval.m_BorderSize;

        m_FaultLines = rval.m_FaultLines;

        m_FaultLength = rval.m_FaultLength;

        m_NSBorderSize = rval.m_NSBorderSize;

    }

    return *this;
}

void MapRecord::Settings::Serialize(CivArchive &archive)
{
    if(archive.IsStoring()) {
        archive << m_NumContinents;
        archive << m_MinWidth;
        archive << m_MinHeight;
        archive << m_MaxWidth;
        archive << m_MaxHeight;
        archive << m_BumpSize;
        archive << m_MinSubcontinents;
        archive << m_MaxSubcontinents;
        archive << m_SubcontinentSize;
        archive << m_SubcontinentHeight;
        archive << m_BorderSize;
        archive << m_FaultLines;
        archive << m_FaultLength;
        archive << m_NSBorderSize;
    } else {
        archive >> m_NumContinents;
        archive >> m_MinWidth;
        archive >> m_MinHeight;
        archive >> m_MaxWidth;
        archive >> m_MaxHeight;
        archive >> m_BumpSize;
        archive >> m_MinSubcontinents;
        archive >> m_MaxSubcontinents;
        archive >> m_SubcontinentSize;
        archive >> m_SubcontinentHeight;
        archive >> m_BorderSize;
        archive >> m_FaultLines;
        archive >> m_FaultLength;
        archive >> m_NSBorderSize;
    }
}

static const char *s_Map_Settings_Tokens[] = {
    "NumContinents",
    "MinWidth",
    "MinHeight",
    "MaxWidth",
    "MaxHeight",
    "BumpSize",
    "MinSubcontinents",
    "MaxSubcontinents",
    "SubcontinentSize",
    "SubcontinentHeight",
    "BorderSize",
    "FaultLines",
    "FaultLength",
    "NSBorderSize",
    "MAP_NUM_CONTINENTS",
    "MAP_MIN_WIDTH",
    "MAP_MIN_HEIGHT",
    "MAP_MAX_WIDTH",
    "MAP_MAX_HEIGHT",
    "MAP_BUMP_SIZE",
    "MAP_MIN_SUBCONTINENTS",
    "MAP_MAX_SUBCONTINENTS",
    "MAP_SUBCONTINENT_SIZE",
    "MAP_SUBCONTINENT_HEIGHT",
    "MAP_BORDER_SIZE",
    "MAP_FAULT_LINES",
    "MAP_FAULT_LENGTH",
    "MAP_NS_BORDER_SIZE",
};
#define k_Token_Map_Settings_NumContinents       ((k_Token_Custom_Base) + 0)
#define k_Token_Map_Settings_MinWidth            ((k_Token_Custom_Base) + 1)
#define k_Token_Map_Settings_MinHeight           ((k_Token_Custom_Base) + 2)
#define k_Token_Map_Settings_MaxWidth            ((k_Token_Custom_Base) + 3)
#define k_Token_Map_Settings_MaxHeight           ((k_Token_Custom_Base) + 4)
#define k_Token_Map_Settings_BumpSize            ((k_Token_Custom_Base) + 5)
#define k_Token_Map_Settings_MinSubcontinents    ((k_Token_Custom_Base) + 6)
#define k_Token_Map_Settings_MaxSubcontinents    ((k_Token_Custom_Base) + 7)
#define k_Token_Map_Settings_SubcontinentSize    ((k_Token_Custom_Base) + 8)
#define k_Token_Map_Settings_SubcontinentHeight  ((k_Token_Custom_Base) + 9)
#define k_Token_Map_Settings_BorderSize          ((k_Token_Custom_Base) + 10)
#define k_Token_Map_Settings_FaultLines          ((k_Token_Custom_Base) + 11)
#define k_Token_Map_Settings_FaultLength         ((k_Token_Custom_Base) + 12)
#define k_Token_Map_Settings_NSBorderSize        ((k_Token_Custom_Base) + 13)
#define k_Token_Map_Settings_MAP_NUM_CONTINENTS  ((k_Token_Custom_Base) + 14)
#define k_Token_Map_Settings_MAP_MIN_WIDTH       ((k_Token_Custom_Base) + 15)
#define k_Token_Map_Settings_MAP_MIN_HEIGHT      ((k_Token_Custom_Base) + 16)
#define k_Token_Map_Settings_MAP_MAX_WIDTH       ((k_Token_Custom_Base) + 17)
#define k_Token_Map_Settings_MAP_MAX_HEIGHT      ((k_Token_Custom_Base) + 18)
#define k_Token_Map_Settings_MAP_BUMP_SIZE       ((k_Token_Custom_Base) + 19)
#define k_Token_Map_Settings_MAP_MIN_SUBCONTINENTS ((k_Token_Custom_Base) + 20)
#define k_Token_Map_Settings_MAP_MAX_SUBCONTINENTS ((k_Token_Custom_Base) + 21)
#define k_Token_Map_Settings_MAP_SUBCONTINENT_SIZE ((k_Token_Custom_Base) + 22)
#define k_Token_Map_Settings_MAP_SUBCONTINENT_HEIGHT ((k_Token_Custom_Base) + 23)
#define k_Token_Map_Settings_MAP_BORDER_SIZE     ((k_Token_Custom_Base) + 24)
#define k_Token_Map_Settings_MAP_FAULT_LINES     ((k_Token_Custom_Base) + 25)
#define k_Token_Map_Settings_MAP_FAULT_LENGTH    ((k_Token_Custom_Base) + 26)
#define k_Token_Map_Settings_MAP_NS_BORDER_SIZE  ((k_Token_Custom_Base) + 27)
#define k_Token_Map_Settings_Max ((k_Token_Custom_Base) + 28)
sint32 MapRecord::Settings::ParseSequential(DBLexer *lex)
{
    if(!lex->GetFloatAssignment(m_NumContinents)) {
        DBERROR(("Expected number"));
        return 0;
    }
    if(!lex->GetFloatAssignment(m_MinWidth)) {
        DBERROR(("Expected number"));
        return 0;
    }
    if(!lex->GetFloatAssignment(m_MinHeight)) {
        DBERROR(("Expected number"));
        return 0;
    }
    if(!lex->GetFloatAssignment(m_MaxWidth)) {
        DBERROR(("Expected number"));
        return 0;
    }
    if(!lex->GetFloatAssignment(m_MaxHeight)) {
        DBERROR(("Expected number"));
        return 0;
    }
    if(!lex->GetFloatAssignment(m_BumpSize)) {
        DBERROR(("Expected number"));
        return 0;
    }
    if(!lex->GetFloatAssignment(m_MinSubcontinents)) {
        DBERROR(("Expected number"));
        return 0;
    }
    if(!lex->GetFloatAssignment(m_MaxSubcontinents)) {
        DBERROR(("Expected number"));
        return 0;
    }
    if(!lex->GetFloatAssignment(m_SubcontinentSize)) {
        DBERROR(("Expected number"));
        return 0;
    }
    if(!lex->GetFloatAssignment(m_SubcontinentHeight)) {
        DBERROR(("Expected number"));
        return 0;
    }
    if(!lex->GetFloatAssignment(m_BorderSize)) {
        DBERROR(("Expected number"));
        return 0;
    }
    if(!lex->GetFloatAssignment(m_FaultLines)) {
        DBERROR(("Expected number"));
        return 0;
    }
    if(!lex->GetFloatAssignment(m_FaultLength)) {
        DBERROR(("Expected number"));
        return 0;
    }
    if(!lex->GetFloatAssignment(m_NSBorderSize)) {
        DBERROR(("Expected number"));
        return 0;
    }
    return 1;
}

sint32 MapRecord::Settings::ParseFullySequential(DBLexer *lex)
{
    if(!lex->GetFloat(m_NumContinents)) {
        DBERROR(("Expected number"));
        return 0;
    }
    lex->GetToken();
    if(!lex->GetFloat(m_MinWidth)) {
        DBERROR(("Expected number"));
        return 0;
    }
    lex->GetToken();
    if(!lex->GetFloat(m_MinHeight)) {
        DBERROR(("Expected number"));
        return 0;
    }
    lex->GetToken();
    if(!lex->GetFloat(m_MaxWidth)) {
        DBERROR(("Expected number"));
        return 0;
    }
    lex->GetToken();
    if(!lex->GetFloat(m_MaxHeight)) {
        DBERROR(("Expected number"));
        return 0;
    }
    lex->GetToken();
    if(!lex->GetFloat(m_BumpSize)) {
        DBERROR(("Expected number"));
        return 0;
    }
    lex->GetToken();
    if(!lex->GetFloat(m_MinSubcontinents)) {
        DBERROR(("Expected number"));
        return 0;
    }
    lex->GetToken();
    if(!lex->GetFloat(m_MaxSubcontinents)) {
        DBERROR(("Expected number"));
        return 0;
    }
    lex->GetToken();
    if(!lex->GetFloat(m_SubcontinentSize)) {
        DBERROR(("Expected number"));
        return 0;
    }
    lex->GetToken();
    if(!lex->GetFloat(m_SubcontinentHeight)) {
        DBERROR(("Expected number"));
        return 0;
    }
    lex->GetToken();
    if(!lex->GetFloat(m_BorderSize)) {
        DBERROR(("Expected number"));
        return 0;
    }
    lex->GetToken();
    if(!lex->GetFloat(m_FaultLines)) {
        DBERROR(("Expected number"));
        return 0;
    }
    lex->GetToken();
    if(!lex->GetFloat(m_FaultLength)) {
        DBERROR(("Expected number"));
        return 0;
    }
    lex->GetToken();
    if(!lex->GetFloat(m_NSBorderSize)) {
        DBERROR(("Expected number"));
        return 0;
    }
    return 1;
}

sint32 MapRecord::Settings::Parse(DBLexer *lex)
{
    bool done = false;
    sint32 tok;
    sint32 result = 0;
    tok = lex->PeekAhead();
    if(tok != k_Token_OpenBrace) {
        if(lex->GetCurrentToken() != k_Token_OpenBrace) {
            if(ParseSequential(lex)) {
                return 1;
            }
            DBERROR(("Expected open brace for Settings"));
            return 0;
        }
    }
    else {
        tok = lex->GetToken();
    }
    lex->SetTokens(s_Map_Settings_Tokens, k_Token_Map_Settings_Max);
    while(!done) {
        tok = lex->GetToken();
        switch(tok) {
            case k_Token_Map_Settings_NumContinents:
            case k_Token_Map_Settings_MAP_NUM_CONTINENTS:
                if(!lex->GetFloatAssignment(m_NumContinents)) {
                    done = true; break;
                }
                break;
            case k_Token_Map_Settings_MinWidth:
            case k_Token_Map_Settings_MAP_MIN_WIDTH:
                if(!lex->GetFloatAssignment(m_MinWidth)) {
                    done = true; break;
                }
                break;
            case k_Token_Map_Settings_MinHeight:
            case k_Token_Map_Settings_MAP_MIN_HEIGHT:
                if(!lex->GetFloatAssignment(m_MinHeight)) {
                    done = true; break;
                }
                break;
            case k_Token_Map_Settings_MaxWidth:
            case k_Token_Map_Settings_MAP_MAX_WIDTH:
                if(!lex->GetFloatAssignment(m_MaxWidth)) {
                    done = true; break;
                }
                break;
            case k_Token_Map_Settings_MaxHeight:
            case k_Token_Map_Settings_MAP_MAX_HEIGHT:
                if(!lex->GetFloatAssignment(m_MaxHeight)) {
                    done = true; break;
                }
                break;
            case k_Token_Map_Settings_BumpSize:
            case k_Token_Map_Settings_MAP_BUMP_SIZE:
                if(!lex->GetFloatAssignment(m_BumpSize)) {
                    done = true; break;
                }
                break;
            case k_Token_Map_Settings_MinSubcontinents:
            case k_Token_Map_Settings_MAP_MIN_SUBCONTINENTS:
                if(!lex->GetFloatAssignment(m_MinSubcontinents)) {
                    done = true; break;
                }
                break;
            case k_Token_Map_Settings_MaxSubcontinents:
            case k_Token_Map_Settings_MAP_MAX_SUBCONTINENTS:
                if(!lex->GetFloatAssignment(m_MaxSubcontinents)) {
                    done = true; break;
                }
                break;
            case k_Token_Map_Settings_SubcontinentSize:
            case k_Token_Map_Settings_MAP_SUBCONTINENT_SIZE:
                if(!lex->GetFloatAssignment(m_SubcontinentSize)) {
                    done = true; break;
                }
                break;
            case k_Token_Map_Settings_SubcontinentHeight:
            case k_Token_Map_Settings_MAP_SUBCONTINENT_HEIGHT:
                if(!lex->GetFloatAssignment(m_SubcontinentHeight)) {
                    done = true; break;
                }
                break;
            case k_Token_Map_Settings_BorderSize:
            case k_Token_Map_Settings_MAP_BORDER_SIZE:
                if(!lex->GetFloatAssignment(m_BorderSize)) {
                    done = true; break;
                }
                break;
            case k_Token_Map_Settings_FaultLines:
            case k_Token_Map_Settings_MAP_FAULT_LINES:
                if(!lex->GetFloatAssignment(m_FaultLines)) {
                    done = true; break;
                }
                break;
            case k_Token_Map_Settings_FaultLength:
            case k_Token_Map_Settings_MAP_FAULT_LENGTH:
                if(!lex->GetFloatAssignment(m_FaultLength)) {
                    done = true; break;
                }
                break;
            case k_Token_Map_Settings_NSBorderSize:
            case k_Token_Map_Settings_MAP_NS_BORDER_SIZE:
                if(!lex->GetFloatAssignment(m_NSBorderSize)) {
                    done = true; break;
                }
                break;
            case k_Token_CloseBrace:
                done = true;
                result = 1;
                break;
            default:
                if(!lex->GetFloat(m_NumContinents)) {
                    DBERROR(("Unknown token"));
                    done = true; break;
                }
                break;
        }
    }
    lex->RestoreTokens();
    return result;
}

sint32 MapRecord::Settings::ParseInArray(DBLexer *lex, Settings **array, sint32 *numElements)
{
    if(*numElements > 0) {
        Settings *oldArray = *array;
        *array = new Settings[(*numElements) + 1];
        for (int i=0; i < (*numElements); i++)
             (*array)[i] = oldArray[i];
        delete [] oldArray;
    } else {
        *array = new Settings[1];
    }
    (*array)[*numElements].Parse(lex);
    *numElements += 1;
    return 1;
}

sint32 MapRecord::Settings::ParseInArray(DBLexer *lex, Settings *array, sint32 *numElements, sint32 maxSize)
{
    if(*numElements >= maxSize) {
        return 0;
    }
    array[*numElements].Parse(lex);
    *numElements += 1;
    return 1;
}

sint32 MapRecord::Settings::ParseInArraySequential(DBLexer *lex, Settings **array, sint32 *numElements)
{
    if(*numElements > 0) {
        Settings *oldArray = *array;
        *array = new Settings[(*numElements) + 1];
        for (int i=0; i < (*numElements); i++)
             (*array)[i] = oldArray[i];
        delete [] oldArray;
    } else {
        *array = new Settings[1];
    }
    (*array)[*numElements].ParseFullySequential(lex);
    *numElements += 1;
    return 1;
}

sint32 MapRecord::Settings::ParseInArraySequential(DBLexer *lex, Settings *array, sint32 *numElements, sint32 maxSize)
{
    if(*numElements >= maxSize) {
        return 0;
    }
    array[*numElements].ParseFullySequential(lex);
    *numElements += 1;
    return 1;
}

void MapRecord::Settings::ResolveDBReferences()
{
}

void MapRecord::Merge(const MapRecord & rval){
    // replace struct elements of m_Settings
    for (sint32 index_Settings = 0; index_Settings < m_numSettings; ++index_Settings)
    {
        // find matching struct element and replace it
        for (sint32 obj_index = 0; obj_index < rval.m_numSettings; ++obj_index)
            if (m_Settings[index_Settings] == rval.m_Settings[obj_index]){
                m_Settings[index_Settings] = rval.m_Settings[obj_index];
            }
    }
}

MapRecord::Settings const * MapRecord::GetSettings(sint32 index) const
{
    Assert(index >= 0);
    Assert(index < m_numSettings);
    if((index < 0) || (index >= m_numSettings)) {
        return 0;
    }
    return &m_Settings[index];
}

