#include "c3.h"
#include "battleviewwindow.h"

#include "aui_control.h"
#include "ctp2_Static.h"
#include "ctp2_button.h"
#include "c3_icon.h"
#include "c3ui.h"
#include "aui_uniqueid.h"
#include "aui_ldl.h"
#include "aui_stringtable.h"
#include "aui_blitter.h"
#include "pixelutils.h"
#include "primitives.h"
#include "tileset.h"
#include "tiledmap.h"
#include "battleviewactor.h"
#include "battleview.h"
#include "battle.h"
#include "World.h"                  // g_theWorld
#include "director.h"               // g_director
#include "CTP2Combat.h"
#include "GameEventManager.h"
#include "SelItem.h"
#include "network.h"
#include "TerrainRecord.h"
#include "soundmanager.h"

#include "ldl_data.hpp"
#include "ldl_file.hpp"

extern C3UI		*g_c3ui;
extern sint32	g_modalWindow;

BattleViewWindow			*g_battleViewWindow = NULL;


void battleview_ExitButtonActionCallback( aui_Control *control, uint32 action, uint32 data, void *cookie )
{

	if ( action != (uint32)AUI_BUTTON_ACTION_EXECUTE ) return;

	AUI_ERRCODE auiErr = g_c3ui->RemoveWindow(g_battleViewWindow->Id());
	Assert( auiErr == AUI_ERRCODE_OK );
	if ( auiErr != AUI_ERRCODE_OK ) return;

	RemoveBattleViewAction	*actionObj = new RemoveBattleViewAction(g_theCurrentBattle && g_battleViewWindow && g_battleViewWindow->GetBattleView() &&
																	g_battleViewWindow->GetBattleView()->IsCurrentBattle(g_theCurrentBattle->GetBattle()));
	g_c3ui->AddAction(actionObj);

}

void battleview_RetreatButtonActionCallback(aui_Control *control, uint32 action,
											uint32 data, void *cookie)
{

	if(action != (uint32)AUI_BUTTON_ACTION_EXECUTE)
		return;

	control->Enable(false);

	if(g_theCurrentBattle)
		g_theCurrentBattle->Retreat();
}


void RemoveBattleViewAction::Execute(aui_Control *control, uint32 action, uint32 data)
{

	if(g_theCurrentBattle && m_killBattle)
		g_theCurrentBattle->KillBattle();


	g_gevManager->GotUserInput();




	BattleViewWindow::Cleanup();
}


void BattleViewWindow::Initialize()
{
	AUI_ERRCODE		errcode;

	if (g_battleViewWindow)
		Cleanup();

	g_battleViewWindow = new BattleViewWindow( &errcode, aui_UniqueId(), "BattleViewWindow", 16,
											AUI_WINDOW_TYPE_POPUP);

	g_modalWindow++;

	Assert(g_battleViewWindow != NULL);
}


void BattleViewWindow::Cleanup(void)
{
	if (g_battleViewWindow) {
		g_c3ui->RemoveWindow(g_battleViewWindow->Id());

		delete g_battleViewWindow;
		g_battleViewWindow = NULL;
	}

	g_modalWindow--;

	g_director->ExternalActionFinished(DEA_BATTLE_WINDOW);
}


BattleViewWindow::BattleViewWindow
(
	AUI_ERRCODE *   retval,
	uint32          id,
	const MBCHAR *  ldlBlock,
	sint32          bpp,
	AUI_WINDOW_TYPE type
)
:
	C3Window                (retval, id, ldlBlock, bpp, type),
	m_battleView            (NULL),
//	RECT					m_battleViewRect;
	m_topBorder             (NULL),
    m_leftBorder            (NULL),
    m_rightBorder           (NULL),
    m_bottomBorder          (NULL),
    m_exitButton            (NULL),
    m_retreatButton         (NULL),
    m_titleText             (NULL),
    m_attackersText         (NULL),
    m_attackersName         (NULL),
    m_attackersFlag         (NULL),
    m_defendersText         (NULL),
    m_defendersName         (NULL),
    m_defendersFlag         (NULL),
    m_terrainBonusText      (NULL),
    m_terrainBonusValue     (NULL),
    m_cityBonusText         (NULL),
    m_cityBonusValue        (NULL),
    m_citylandattackBonusText (NULL),
    m_citylandattackBonusValue (NULL),
    m_cityairattackBonusText (NULL),
    m_cityairattackBonusValue (NULL),
    m_cityseaattackBonusText (NULL),
    m_cityseaattackBonusValue (NULL),
    m_cityName              (NULL),
    m_fortBonusText         (NULL),
    m_fortBonusValue        (NULL),
    m_fortBonusImage        (NULL),
    m_fortifiedBonusText    (NULL),
    m_fortifiedBonusValue   (NULL)
{
	InitCommonLdl(ldlBlock);
}

BattleViewWindow::~BattleViewWindow()
{
	delete m_battleView;
	delete m_topBorder;
	delete m_leftBorder;
	delete m_rightBorder;
	delete m_bottomBorder;
	delete m_exitButton;
	delete m_retreatButton;
	delete m_titleText;
	delete m_attackersText;
	delete m_attackersName;
	delete m_attackersFlag;
	delete m_defendersText;
	delete m_defendersName;
	delete m_defendersFlag;
	delete m_terrainBonusText;
	delete m_terrainBonusValue;
	delete m_cityBonusText;
	delete m_cityBonusValue;
	delete m_citylandattackBonusText;
	delete m_citylandattackBonusValue;
	delete m_cityairattackBonusText;
	delete m_cityairattackBonusValue;
	delete m_cityseaattackBonusText;
	delete m_cityseaattackBonusValue;
	delete m_cityName;
	delete m_fortBonusText;
	delete m_fortBonusValue;
	delete m_fortBonusImage;
	delete m_fortifiedBonusText;
	delete m_fortifiedBonusValue;

	Assert(this == g_battleViewWindow);
	if (this == g_battleViewWindow)
	{
		g_battleViewWindow = NULL;
	}
}

AUI_ERRCODE BattleViewWindow::InitCommonLdl(const MBCHAR *ldlBlock)
{
	MBCHAR			buttonBlock[ k_AUI_LDL_MAXBLOCK + 1 ];
	AUI_ERRCODE		errcode;

	m_battleView = new BattleView();
	Assert(m_battleView != NULL);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "TitleText");
	m_titleText = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_titleText);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "AttackersText");
	m_attackersText = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_attackersText);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "AttackersName");
	m_attackersName = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_attackersName);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "AttackersFlag");
	m_attackersFlag = new c3_Icon(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_attackersFlag);
	m_attackersFlag->SetMapIcon( MAPICON_FLAG );

	sprintf(buttonBlock, "%s.%s", ldlBlock, "DefendersText");
	m_defendersText = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_defendersText);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "DefendersName");
	m_defendersName = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_defendersName);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "DefendersFlag");
	m_defendersFlag = new c3_Icon(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_defendersFlag);
	m_defendersFlag->SetMapIcon( MAPICON_FLAG );

	sprintf(buttonBlock, "%s.%s", ldlBlock, "TerrainBonusText");
	m_terrainBonusText = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_terrainBonusText);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "TerrainBonusValue");
	m_terrainBonusValue = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_terrainBonusValue);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "CityBonusText");
	m_cityBonusText = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_cityBonusText);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "CityBonusValue");
	m_cityBonusValue = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_cityBonusValue);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "CityLandAttackBonusText");
	m_citylandattackBonusText = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_citylandattackBonusText);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "CityLandAttackBonusValue");
	m_citylandattackBonusValue = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_citylandattackBonusValue);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "CityAirAttackBonusText");
	m_cityairattackBonusText = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_cityairattackBonusText);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "CityAirAttackBonusValue");
	m_cityairattackBonusValue = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_cityairattackBonusValue);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "CitySeaAttackBonusText");
	m_cityseaattackBonusText = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_cityseaattackBonusText);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "CitySeaAttackBonusValue");
	m_cityseaattackBonusValue = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_cityseaattackBonusValue);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "CityName");
	m_cityName = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_cityName);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "FortBonusText");
	m_fortBonusText = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_fortBonusText);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "FortBonusValue");
	m_fortBonusValue = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_fortBonusValue);

	m_fortBonusImage = NULL;

	sprintf(buttonBlock, "%s.%s", ldlBlock, "FortifiedBonusText");
	m_fortifiedBonusText = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_fortifiedBonusText);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "FortifiedBonusValue");
	m_fortifiedBonusValue = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_fortifiedBonusValue);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "ExitButton");
	m_exitButton = new ctp2_Button(&errcode, aui_UniqueId(), buttonBlock,
		battleview_ExitButtonActionCallback);
	Assert(m_exitButton != NULL);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "RetreatButton");
	m_retreatButton = new ctp2_Button(&errcode, aui_UniqueId(), buttonBlock,
		battleview_RetreatButtonActionCallback);
	Assert(m_retreatButton != NULL);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "TopBorder");
	m_topBorder = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_topBorder);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "LeftBorder");
	m_leftBorder = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_leftBorder);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "RightBorder");
	m_rightBorder = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_rightBorder);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "BottomBorder");
	m_bottomBorder = new ctp2_Static(&errcode, aui_UniqueId(), buttonBlock);
	Assert(m_bottomBorder);

	sprintf(buttonBlock, "%s.%s", ldlBlock, "BattleViewArea");

	ldl_datablock *block = aui_Ldl::GetLdl()->FindDataBlock( buttonBlock );
	Assert(block);
	if (!block) return AUI_ERRCODE_OK;

	if ( block->GetAttributeType( k_AUI_LDL_HABSPOSITION ) == ATTRIBUTE_TYPE_INT )	{
		m_battleViewRect.left = block->GetInt( k_AUI_LDL_HABSPOSITION );
	}

	if ( block->GetAttributeType( k_AUI_LDL_VABSPOSITION ) == ATTRIBUTE_TYPE_INT )	{
		m_battleViewRect.top = block->GetInt( k_AUI_LDL_VABSPOSITION );
	}

	if ( block->GetAttributeType( k_AUI_LDL_HABSSIZE ) == ATTRIBUTE_TYPE_INT )	{
		m_battleViewRect.right = m_battleViewRect.left + block->GetInt( k_AUI_LDL_HABSSIZE );
	}

	if ( block->GetAttributeType( k_AUI_LDL_VABSSIZE ) == ATTRIBUTE_TYPE_INT )	{
		m_battleViewRect.bottom = m_battleViewRect.top + block->GetInt( k_AUI_LDL_VABSSIZE );
	}

	errcode = aui_Ldl::SetupHeirarchyFromRoot( ldlBlock );

	return AUI_ERRCODE_OK;
}

void BattleViewWindow::SetupBattle(Battle *battle)
{
	if(!m_battleView)
		return;
	if(!battle)
		return;
	if(!g_theCurrentBattle)
		return;

	if (g_theCurrentBattle->GetAttacker() ==
		    g_selected_item->GetVisiblePlayer()
	    && !g_network.IsActive()
	   )
	{
		m_retreatButton->Show();
		m_retreatButton->Enable(true);
	}
	else
	{
		m_retreatButton->Hide();
	}

	RECT battleRect = m_battleViewRect;
	OffsetRect(&battleRect, -battleRect.left, -battleRect.top);

	m_battleView->Initialize(battleRect);
	m_battleView->SetBattle(battle);

	sint32	terrainType = battle->GetTerrainType();
	sint32  attackerTerrain = battle->GetAttackersTerrainType();

	AUI_ERRCODE	errcode = AUI_ERRCODE_OK;
	aui_StringTable	*table = new aui_StringTable(&errcode, "BattleViewTerrainTable");
	Assert(errcode == AUI_ERRCODE_OK);
	const MBCHAR *imageName = NULL;

	const TerrainRecord *defTerrRec = g_theTerrainDB->Get(terrainType);
	const TerrainRecord *attackTerrRec = g_theTerrainDB->Get(attackerTerrain);

	bool useSplit = false;

	if(!defTerrRec->GetMovementTypeSea() && attackTerrRec->GetMovementTypeSea()) {
		useSplit = true;
		imageName = "UPBG006.TGA";
	} else {
		imageName = table->GetString(terrainType);
	}

	aui_Image *image = g_c3ui->LoadImage(imageName);
	Assert(image);
	if(image)
		m_battleView->SetBackgroundImage(image);

	delete table;

	double bonus = battle->GetTerrainBonus();
	MBCHAR s[k_MAX_NAME_LEN];
	sprintf(s, "+%d%%", (sint32)(bonus * 100.0));
	m_terrainBonusValue->SetText(s);

	if(battle->GetCityImage() != -1) {

		aui_StringTable	*cityTable = new aui_StringTable(&errcode, "BattleViewCityTable");
		Assert(errcode == AUI_ERRCODE_OK);
		Assert(cityTable);

		aui_Image *cityImage = g_c3ui->LoadImage(useSplit ? "UPBO006.tga" : cityTable->GetString(terrainType));
		m_battleView->SetCityImage(cityImage);
		delete cityTable;

		m_cityName->SetText(battle->GetCityName());
		m_cityName->Show();

	} else {

		m_cityName->Hide();

	}

	bonus = battle->GetCityBonus();
	sprintf(s, "+%d", (sint32)bonus);
	m_cityBonusValue->SetText(s);

	bonus = battle->GetCityLandAttackBonus();
	sprintf(s, "+%d", (sint32)bonus);
	m_citylandattackBonusValue->SetText(s);

	bonus = battle->GetCityAirAttackBonus();
	sprintf(s, "+%d", (sint32)bonus);
	m_cityairattackBonusValue->SetText(s);

	bonus = battle->GetCitySeaAttackBonus();
	sprintf(s, "+%d", (sint32)bonus);
	m_cityseaattackBonusValue->SetText(s);

	bonus = battle->GetFortBonus();
	sprintf(s, "+%d%%", (sint32)(bonus * 100.0));
	m_fortBonusValue->SetText(s);

	bonus = battle->GetFortifiedBonus();
	sprintf(s, "+%d%%", (sint32)(bonus * 100.0));
	m_fortifiedBonusValue->SetText(s);

	m_attackersFlag->SetColor( battle->GetAttackersColor() );
	m_defendersFlag->SetColor( battle->GetDefendersColor() );

	MBCHAR name[_MAX_PATH];
	battle->GetAttackersName(name);
	m_attackersName->SetText(name);
	battle->GetDefendersName(name);
	m_defendersName->SetText(name);

	if(g_soundManager) {
		g_soundManager->TerminateAllLoopingSounds(SOUNDTYPE_SFX);
		g_soundManager->TerminateAllLoopingSounds(SOUNDTYPE_VOICE);
	}
}

void BattleViewWindow::UpdateBattle(Battle *battle)
{

	if(!m_battleView)
		return;
	if(!battle)
		return;

	m_battleView->UpdateBattle(battle);
}

void BattleViewWindow::EndBattle()
{

	m_retreatButton->Enable(false);
}

void BattleViewWindow::RemoveActor(BattleViewActor *actor)
{
	Assert(m_battleView);
	if (!m_battleView) return;
	m_battleView->RemoveActor(actor);
}


AUI_ERRCODE BattleViewWindow::DrawThis(aui_Surface *surface, sint32 x, sint32 y)
{

	if ( IsHidden() ) return AUI_ERRCODE_OK;

	C3Window::DrawThis(surface, x, y);

	if (!surface) surface = TheSurface();

	RECT rect = {0, 0, Width(), Height()};

	rect = m_battleViewRect;
	OffsetRect(&rect, -rect.left, -rect.top);

	if (m_battleView && m_battleView->GetBattleSurface())
		g_c3ui->TheBlitter()->Blt(surface, m_battleViewRect.left, m_battleViewRect.top,
			m_battleView->GetBattleSurface(), &rect, k_AUI_BLITTER_FLAG_COPY);

	m_dirtyList->AddRect( &rect );

	rect = m_battleViewRect;
	InflateRect(&rect, 5, 5);
	primitives_BevelRect16( surface, &rect, 5,1, 16, 16 );

	m_dirtyList->AddRect( &rect );

	return AUI_ERRCODE_OK;
}




AUI_ERRCODE BattleViewWindow::Idle(void)
{
	if(!g_tiledMap) {

		return AUI_ERRCODE_OK;
	}

	g_director->UpdateTimingClock();

	Refresh();

	return AUI_ERRCODE_OK;
}

#define k_BATTLE_VIEW_FRAME_TIME		50

void BattleViewWindow::Refresh(void)
{
	if(!m_battleView)
		return;

	static uint32 lastUpdate = 0;

	if (GetTickCount64() > (lastUpdate + k_BATTLE_VIEW_FRAME_TIME)) {
		m_battleView->Process();

		lastUpdate = GetTickCount64();

		m_battleView->UpdateDisplay();

		ShouldDraw(TRUE);
	}
}

void BattleViewWindow::GetAttackerPos(sint32 column, sint32 row, sint32 *x, sint32 *y)
{
	Assert(m_battleView);

	if (m_battleView)
		m_battleView->GetAttackerPos(column, row, x, y);
}

void BattleViewWindow::GetDefenderPos(sint32 column, sint32 row, sint32 *x, sint32 *y)
{
	Assert(m_battleView);

	if (m_battleView)
		m_battleView->GetDefenderPos(column, row, x, y);
}
