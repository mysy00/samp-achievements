DEFINE_HOOK_REPLACEMENT(Achievement, Ach);

forward Achievement_GivePlayerProgress(playerid, Achievement:id, progress, bool:callProgress = true, callCompletion = true);
forward Achievement_SetPlayerProgress(playerid, Achievement:id, progress, bool:callProgress = true, callCompletion = true);
forward Achievement_GetPlayerProgress(playerid, Achievement:id);
forward bool:Achievement_HasPlayerCompleted(playerid, Achievement:id);

forward OnPlayerProgressAchievement(playerid, Achievement:id, progress);
forward OnPlayerCompleteAchievement(playerid, Achievement:id);

static s_playerAchievementProgress[MAX_PLAYERS][MAX_ACHIEVEMENTS];

Achievement_GivePlayerProgress(playerid, Achievement:id, progress, bool:callProgress = true, callCompletion = true) {
    new points = Achievement_GetPlayerProgress(playerid, id);

    new ret = Achievement_SetPlayerProgress(playerid, id, points + progress, callProgress, callCompletion);

    if (ret <= 0) {
        return ret;
    }

    return 1;
}

Achievement_SetPlayerProgress(playerid, Achievement:id, progress, bool:callProgress = true, callCompletion = true) {
    if (!IsPlayerConnected(playerid)) {
        return 0;
    }

    if (!Achievement_IsValid(id)) {
        return -1;
    }

    if (Achievement_HasPlayerCompleted(playerid, id)) {
        return -2;
    }

    new points = Achievement_GetPoints(id);

    s_playerAchievementProgress[playerid][_:id] = (progress = clamp(progress, 0, points));

    if (callProgress) {
        CallLocalFunction("OnPlayerProgressAchievement", "ddd", playerid, _:id, progress);
    }

    if (callCompletion && progress == points) {
        CallLocalFunction("OnPlayerCompleteAchievement", "dd", playerid, _:id);
    }

    return 1;
}

Achievement_GetPlayerProgress(playerid, Achievement:id) {
    if (!IsPlayerConnected(playerid)) {
        return 0;
    }

    if (!Achievement_IsValid(id)) {
        return -1;
    }

    return s_playerAchievementProgress[playerid][_:id];
}

bool:Achievement_HasPlayerCompleted(playerid, Achievement:id) {
    new points = Achievement_GetPoints(id);
    new playerProgress = Achievement_GetPlayerProgress(playerid, id);

    if (points == playerProgress) {
        return true;
    }

    return false;
}
