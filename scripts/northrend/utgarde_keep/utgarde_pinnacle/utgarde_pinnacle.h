/* Copyright (C) 2006 - 2013 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_UTG_PINNACLE_H
#define DEF_UTG_PINNACLE_H

enum
{
    MAX_ENCOUNTER                   = 4,
    MAX_SPECIAL_ACHIEV_CRITS        = 3,

    TYPE_SVALA                      = 0,
    TYPE_GORTOK                     = 1,
    TYPE_SKADI                      = 2,
    TYPE_YMIRON                     = 3,

    TYPE_ACHIEV_INCREDIBLE_HULK     = 0,
    TYPE_ACHIEV_LOVE_SKADI          = 1,
    TYPE_ACHIEV_KINGS_BANE          = 2,

    GO_STASIS_GENERATOR             = 188593,
    GO_DOOR_SKADI                   = 192173,
    GO_DOOR_YMIRON                  = 192174,

    NPC_WORLD_TRIGGER               = 22515,

    NPC_FURBOLG                     = 26684,
    NPC_WORGEN                      = 26683,
    NPC_JORMUNGAR                   = 26685,
    NPC_RHINO                       = 26686,

    // Ymiron spirits
    NPC_BJORN                       = 27303,            // front right
    NPC_HALDOR                      = 27307,            // front left
    NPC_RANULF                      = 27308,            // back left
    NPC_TORGYN                      = 27309,            // back right

    ACHIEV_CRIT_INCREDIBLE_HULK     = 7322,             // Svala, achiev - 2043
    ACHIEV_CRIT_GIRL_LOVES_SKADI    = 7595,             // Skadi, achiev - 2156
    ACHIEV_CRIT_KINGS_BANE          = 7598,             // Ymiron, achiev - 2157

    ACHIEV_START_SKADI_ID           = 17726,            // Starts Skadi timed achiev - 1873

    // Gortok event spells
    SPELL_ORB_VISUAL                = 48044,
    SPELL_AWAKEN_SUBBOSS            = 47669,
    SPELL_AWAKEN_GORTOK             = 47670,
};

static const float aOrbPositions[2][3] =
{
    {238.6077f, -460.7103f, 112.5671f},                 // Orb lift up
    {279.26f,   -452.1f,    110.0f},                    // Orb center stop
};

static const uint32 aGortokMiniBosses[MAX_ENCOUNTER] = {NPC_WORGEN, NPC_FURBOLG, NPC_JORMUNGAR, NPC_RHINO};

class MANGOS_DLL_DECL instance_pinnacle : public ScriptedInstance
{
    public:
        instance_pinnacle(Map* pMap);

        void Initialize() override;

        void OnCreatureCreate(Creature* pCreature) override;
        void OnObjectCreate(GameObject* pGo) override;

        void OnCreatureEvade(Creature* pCreature);
        void OnCreatureDeath(Creature* pCreature) override;

        void SetData(uint32 uiType, uint32 uiData) override;
        uint32 GetData(uint32 uiType) const override;

        void SetSpecialAchievementCriteria(uint32 uiType, bool bIsMet);
        bool CheckAchievementCriteriaMeet(uint32 uiCriteriaId, Player const* pSource, Unit const* pTarget, uint32 uiMiscValue1 /* = 0*/) const override;

        void SetGortokEventStarter(ObjectGuid playerGuid) { m_gortokEventStarterGuid = playerGuid; }
        ObjectGuid GetGortokEventStarter() { return m_gortokEventStarterGuid; }

        const char* Save() const override { return m_strInstData.c_str(); }
        void Load(const char* chrIn) override;

        void Update(uint32 uiDiff) override;

    private:
        uint32 m_auiEncounter[MAX_ENCOUNTER];
        bool m_abAchievCriteria[MAX_SPECIAL_ACHIEV_CRITS];
        std::string m_strInstData;

        uint32 m_uiGortokOrbTimer;
        uint8 m_uiGortokOrbPhase;

        ObjectGuid m_gortokEventTriggerGuid;
        ObjectGuid m_gortokEventStarterGuid;
};

#endif
