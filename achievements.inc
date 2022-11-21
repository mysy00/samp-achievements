#include <YSI_Data\y_iterate>
#include <YSI_Core\y_utils>

#if !defined INVALID_ACHIEVEMENT_ID
  #define INVALID_ACHIEVEMENT_ID  (Achievement:-1)
#endif

#if !defined MAX_ACHIEVEMENTS
  #define MAX_ACHIEVEMENTS        (100)
#endif

#if !defined MAX_ACHIEVEMENT_NAME
  #define MAX_ACHIEVEMENT_NAME    (64)
#endif

#if !defined MAX_ACHIEVEMENT_DESC
  #define MAX_ACHIEVEMENT_DESC    (256)
#endif

forward Achievement:Achievement_Define(const string:name[], const string:desc[], points);
forward bool:Achievement_IsValid(Achievement:id);
forward bool:Achievement_GetName(Achievement:id, string:name[]);
forward bool:Achievement_GetDesc(Achievement:id, string:desc[]);

// Necessary points to complete the achievement.
forward Achievement_GetPoints(Achievement:id);

static enum E_ACHIEVEMENT_DATA {
    string:E_ACH_NAME[MAX_ACHIEVEMENT_NAME + 1 char],
    string:E_ACH_DESC[MAX_ACHIEVEMENT_DESC + 1 char],
    E_ACH_POINTS // Necessary points to complete the achievement
};

static achievementData[MAX_ACHIEVEMENTS][E_ACHIEVEMENT_DATA];

new Iterator:Achievement < MAX_ACHIEVEMENTS > ;

stock Achievement:Achievement_Define(const string:name[], const string:desc[], points) {
    new id = Iter_Alloc(Achievement);

    if (id == INVALID_ITERATOR_SLOT) {
        return INVALID_ACHIEVEMENT_ID;
    }

    strcopy(achievementData[id][E_ACH_NAME], name);
    strcopy(achievementData[id][E_ACH_DESC], desc);
    achievementData[id][E_ACH_POINTS] = points;

    return Achievement:id;
}

stock bool:Achievement_IsValid(Achievement:id) {
    return Iter_Contains(Achievement, _:id);
}

stock bool:Achievement_GetName(Achievement:id, string:name[]) {
    if (!Achievement_IsValid(id)) {
        return false;
    }

    name[0] = EOS;
    strcat(name, achievementData[_:id][E_ACH_NAME], MAX_ACHIEVEMENT_NAME);

    return true;
}

stock bool:Achievement_GetDesc(Achievement:id, string:desc[]) {
    if (!Achievement_IsValid(id)) {
        return false;
    }

    desc[0] = EOS;
    strcat(desc, achievementData[_:id][E_ACH_DESC], MAX_ACHIEVEMENT_DESC);

    return true;
}

stock Achievement_GetPoints(Achievement:id) {
    if (!Achievement_IsValid(id)) {
        return 0;
    }

    return achievementData[_:id][E_ACH_POINTS];
}

#include "achievements-player"
