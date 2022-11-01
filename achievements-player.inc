DEFINE_HOOK_REPLACEMENT(Achievement, Ach);

forward Player_GiveAchievementProgress(playerid, Achievement:id, progress, bool:call = true);
forward Player_SetAchievementProgress(playerid, Achievement:id, progress, bool:callProgress = true, callCompletion = true);
forward Player_GetAchievementProgress(playerid, Achievement:id);
forward bool:Player_IsAchievementCompleted(playerid, Achievement:id);

forward OnPlayerProgressAchievement(playerid, Achievement:id, progress);
forward OnPlayerCompleteAchievement(playerid, Achievement:id);

static playerAchievementProgress[MAX_PLAYERS][MAX_ACHIEVEMENTS];

Player_GiveAchievementProgress(playerid, Achievement:id, progress, bool:call = true) {
    new points = Player_GetAchievementProgress(playerid, id);

    new ret = Player_SetAchievementProgress(playerid, id, points + progress, call);

    if (ret <= 0) {
        return ret;
    }

    return 1;
}

Player_SetAchievementProgress(playerid, Achievement:id, progress, bool:callProgress = true, callCompletion = true) {
    if (!IsPlayerConnected(playerid)) {
        return 0;
    }

    if (!Achievement_IsValid(id)) {
        return -1;
    }

    if (Player_IsAchievementCompleted(playerid, id)) {
        return -2;
    }

    new points = Achievement_GetPoints(id);

    playerAchievementProgress[playerid][_:id] = (progress = clamp(progress, 0, points));

    if (callProgress) {
        CallLocalFunction("OnPlayerProgressAchievement", "ddd", playerid, _:id, progress);
    }

    if (callCompletion && progress == points) {
        CallLocalFunction("OnPlayerCompleteAchievement", "dd", playerid, _:id);
    }

    return 1;
}

Player_GetAchievementProgress(playerid, Achievement:id) {
    if (!IsPlayerConnected(playerid)) {
        return 0;
    }

    if (!Achievement_IsValid(id)) {
        return -1;
    }

    return playerAchievementProgress[playerid][_:id];
}

bool:Player_IsAchievementCompleted(playerid, Achievement:id) {
    new points = Achievement_GetPoints(id);
    new playerProgress = Player_GetAchievementProgress(playerid, id);

    if (points == playerProgress) {
        return true;
    }

    return false;
}
