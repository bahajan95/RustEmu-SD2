/* Copyright (C) 2006 - 2013 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Guards
SD%Complete: 100
SDComment: CombatAI should be organized better for future.
SDCategory: Guards
EndScriptData */

/* ContentData
guard_azuremyst
guard_bluffwatcher
guard_contested
guard_darnassus
guard_dunmorogh
guard_durotar
guard_elwynnforest
guard_eversong
guard_exodar
guard_ironforge
guard_mulgore
guard_orgrimmar
guard_shattrath
guard_shattrath_aldor
guard_shattrath_scryer
guard_silvermoon
guard_stormwind
guard_teldrassil
guard_tirisfal
guard_undercity
EndContentData */

#include "precompiled.h"
#include "guard_ai.h"

CreatureAI* GetAI_guard_azuremyst(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_bluffwatcher(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_contested(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_darnassus(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_dunmorogh(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_durotar(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_elwynnforest(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_eversong(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_exodar(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_ironforge(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_mulgore(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_orgrimmar(Creature* pCreature)
{
    return new guardAI_orgrimmar(pCreature);
}

CreatureAI* GetAI_guard_shattrath(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_shattrath_aldor
 *******************************************************/

struct guard_shattrath_aldorAI : public guardAI
{
    guard_shattrath_aldorAI(Creature* pCreature) : guardAI(pCreature) { Reset(); }

    uint32 m_uiExile_Timer;
    uint32 m_uiBanish_Timer;
    ObjectGuid m_playerGuid;
    bool m_bCanTeleport;

    void Reset() override
    {
        m_uiBanish_Timer = 5000;
        m_uiExile_Timer = 8500;
        m_playerGuid.Clear();
        m_bCanTeleport = false;
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_bCanTeleport)
        {
            if (m_uiExile_Timer < uiDiff)
            {
                if (Player* pTarget = m_creature->GetMap()->GetPlayer(m_playerGuid))
                {
                    pTarget->CastSpell(pTarget, SPELL_EXILE, true);
                    pTarget->CastSpell(pTarget, SPELL_BANISH_TELEPORT, true);
                }

                m_playerGuid.Clear();
                m_uiExile_Timer = 8500;
                m_bCanTeleport = false;
            }
            else
                m_uiExile_Timer -= uiDiff;
        }
        else if (m_uiBanish_Timer < uiDiff)
        {
            Unit* pVictim = m_creature->getVictim();

            if (pVictim && pVictim->GetTypeId() == TYPEID_PLAYER)
            {
                DoCastSpellIfCan(pVictim, SPELL_BANISHED_SHATTRATH_A);
                m_uiBanish_Timer = 9000;
                m_playerGuid = pVictim->GetObjectGuid();
                m_bCanTeleport = true;
            }
        }
        else
            m_uiBanish_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_guard_shattrath_aldor(Creature* pCreature)
{
    return new guard_shattrath_aldorAI(pCreature);
}

/*******************************************************
 * guard_shattrath_scryer
 *******************************************************/

struct guard_shattrath_scryerAI : public guardAI
{
    guard_shattrath_scryerAI(Creature* pCreature) : guardAI(pCreature) { Reset(); }

    uint32 m_uiExile_Timer;
    uint32 m_uiBanish_Timer;
    ObjectGuid m_playerGuid;
    bool m_bCanTeleport;

    void Reset() override
    {
        m_uiBanish_Timer = 5000;
        m_uiExile_Timer = 8500;
        m_playerGuid.Clear();
        m_bCanTeleport = false;
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_bCanTeleport)
        {
            if (m_uiExile_Timer < uiDiff)
            {
                if (Player* pTarget = m_creature->GetMap()->GetPlayer(m_playerGuid))
                {
                    pTarget->CastSpell(pTarget, SPELL_EXILE, true);
                    pTarget->CastSpell(pTarget, SPELL_BANISH_TELEPORT, true);
                }

                m_playerGuid.Clear();
                m_uiExile_Timer = 8500;
                m_bCanTeleport = false;
            }
            else
                m_uiExile_Timer -= uiDiff;
        }
        else if (m_uiBanish_Timer < uiDiff)
        {
            Unit* pVictim = m_creature->getVictim();

            if (pVictim && pVictim->GetTypeId() == TYPEID_PLAYER)
            {
                DoCastSpellIfCan(pVictim, SPELL_BANISHED_SHATTRATH_S);
                m_uiBanish_Timer = 9000;
                m_playerGuid = pVictim->GetObjectGuid();
                m_bCanTeleport = true;
            }
        }
        else
            m_uiBanish_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_guard_shattrath_scryer(Creature* pCreature)
{
    return new guard_shattrath_scryerAI(pCreature);
}

CreatureAI* GetAI_guard_silvermoon(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_stormwind(Creature* pCreature)
{
    return new guardAI_stormwind(pCreature);
}

CreatureAI* GetAI_guard_teldrassil(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_tirisfal(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_undercity(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
* quests 13188 / 13189
*******************************************************/

enum
{
    SPELL_RETURN_ORGRIMMAR = 58552,
    SPELL_RETURN_STORMWIND = 58533,

    SPELL_TOSS_APPLE = 58509,
    SPELL_TOSS_BANANA = 58513,
    SPELL_SPIT = 58520,

    EMOTE_APPLE = -1609081,
    EMOTE_BANANA = -1609082,
    EMOTE_SPIT = -1609083,
    SAY_RANDOM_1 = -1609084,
    SAY_RANDOM_2 = -1609085,
    SAY_RANDOM_3 = -1609086,
    SAY_RANDOM_4 = -1609087,
    SAY_RANDOM_5 = -1609088,
    SAY_RANDOM_6 = -1609287,
    SAY_RANDOM_7 = -1609288,
    SAY_RANDOM_8 = -1609289,
};

bool EffectDummyCreature_npc_city_guard(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Creature* pCreatureTarget, ObjectGuid /*originalCasterGuid*/)
{
    // check spell ids; creature ids are defined in script target
    if ((uiSpellId == SPELL_RETURN_ORGRIMMAR || uiSpellId == SPELL_RETURN_STORMWIND) && uiEffIndex == EFFECT_INDEX_0)
    {
        // random action
        switch (urand(0, 10))
        {
        case 0:
            pCreatureTarget->CastSpell(pCaster, SPELL_TOSS_APPLE, true);
            DoScriptText(EMOTE_APPLE, pCreatureTarget, pCaster);
            break;
        case 1:
            pCreatureTarget->CastSpell(pCaster, SPELL_TOSS_BANANA, true);
            DoScriptText(EMOTE_BANANA, pCreatureTarget, pCaster);
            break;
        case 2:
            pCreatureTarget->CastSpell(pCaster, SPELL_SPIT, true);
            DoScriptText(EMOTE_SPIT, pCreatureTarget, pCaster);
            break;
        case 3: DoScriptText(SAY_RANDOM_1, pCreatureTarget, pCaster); break;
        case 4: DoScriptText(SAY_RANDOM_2, pCreatureTarget, pCaster); break;
        case 5: DoScriptText(SAY_RANDOM_3, pCreatureTarget, pCaster); break;
        case 6: DoScriptText(SAY_RANDOM_4, pCreatureTarget, pCaster); break;
        case 7: DoScriptText(SAY_RANDOM_5, pCreatureTarget, pCaster); break;
        case 8: DoScriptText(SAY_RANDOM_6, pCreatureTarget, pCaster); break;
        case 9: DoScriptText(SAY_RANDOM_7, pCreatureTarget, pCaster); break;
        case 10: DoScriptText(SAY_RANDOM_8, pCreatureTarget, pCaster); break;
        }

        // return true as we don't need further script handling in DB
        return true;
    }

    return false;
}

void AddSC_guards()
{
    AutoScript s;

    s.newScript("guard_azuremyst");
    s->GetAI = &GetAI_guard_azuremyst;

    s.newScript("guard_bluffwatcher");
    s->GetAI = &GetAI_guard_bluffwatcher;

    s.newScript("guard_contested");
    s->GetAI = &GetAI_guard_contested;

    s.newScript("guard_darnassus");
    s->GetAI = &GetAI_guard_darnassus;

    s.newScript("guard_dunmorogh");
    s->GetAI = &GetAI_guard_dunmorogh;

    s.newScript("guard_durotar");
    s->GetAI = &GetAI_guard_durotar;

    s.newScript("guard_elwynnforest");
    s->GetAI = &GetAI_guard_elwynnforest;

    s.newScript("guard_eversong");
    s->GetAI = &GetAI_guard_eversong;

    s.newScript("guard_exodar");
    s->GetAI = &GetAI_guard_exodar;

    s.newScript("guard_ironforge");
    s->GetAI = &GetAI_guard_ironforge;

    s.newScript("guard_mulgore");
    s->GetAI = &GetAI_guard_mulgore;

    s.newScript("guard_orgrimmar");
    s->GetAI = &GetAI_guard_orgrimmar;
    s->pEffectDummyNPC = &EffectDummyCreature_npc_city_guard;

    s.newScript("guard_shattrath");
    s->GetAI = &GetAI_guard_shattrath;

    s.newScript("guard_shattrath_aldor");
    s->GetAI = &GetAI_guard_shattrath_aldor;

    s.newScript("guard_shattrath_scryer");
    s->GetAI = &GetAI_guard_shattrath_scryer;

    s.newScript("guard_silvermoon");
    s->GetAI = &GetAI_guard_silvermoon;

    s.newScript("guard_stormwind");
    s->GetAI = &GetAI_guard_stormwind;
    s->pEffectDummyNPC = &EffectDummyCreature_npc_city_guard;

    s.newScript("guard_teldrassil");
    s->GetAI = &GetAI_guard_teldrassil;

    s.newScript("guard_tirisfal");
    s->GetAI = &GetAI_guard_tirisfal;

    s.newScript("guard_undercity");
    s->GetAI = &GetAI_guard_undercity;
}
