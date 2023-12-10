/*      [ ПУНКТЫ В МЕНЮ ]      */
/*      [ MENU ITEMS ]      */
new const StringsMenu[2][] = {
    "Статистика",
    "Настройки"
};

/*      [ ========== ========== ========== ========== ========== ]      */

dCreate:DlgPlayerMenu(playerid)
{
    new temp[26+(-2+2)+(-2+(MAX_PLAYER_NAME*2))];
    new string[sizeof(temp)*sizeof(StringsMenu)];
    for(new i = 0; i < sizeof(StringsMenu); i++)
    {
        format(temp, sizeof(temp), ""C_GRAY"[%d] "C_WHITE"%s\n", i+1, StringsMenu[i]);
        strcat(string, temp, sizeof(string));
    }
    return Dialog_Open(playerid, Dialog:DlgPlayerMenu, DIALOG_STYLE_LIST, ""C_WHITE"Меню", string, "Выбрать", "Выход");
}

dResponse:DlgPlayerMenu(playerid)
{
    if(response)
    {
        switch(listitem)
        {
            case 0: return Dialog_Show(playerid, Dialog:DlgMenuStats);
            default: SCM(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Данный раздел находится в разработке.");
        }
    }
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = false;
    return 1;
}

dCreate:DlgMenuStats(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\cСтатистика персонажа\n\
    "C_WHITE"\\c%s %s\n\n\
    "C_WHITE"\\cУровень: %d\n\
    "C_WHITE"\\cОпыт: %d/%d\n\n\
    "C_WHITE"\\cНаличные: %d$\n\
    "C_WHITE"\\cБанковский счёт: %d$\n\n";
    new string[sizeof(message)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+3)+(-2+3)+(-2+3)+(-2+9)+(-2+11)];
    format(string, sizeof(string), message, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], CInfo[playerid][PInfo[playerid][CharacterSelect]][Level], CInfo[playerid][PInfo[playerid][CharacterSelect]][Exp], LevelNeedExp(playerid, PInfo[playerid][CharacterSelect]), CInfo[playerid][PInfo[playerid][CharacterSelect]][Money], 0);
    return Dialog_Open(playerid, Dialog:DlgMenuStats, DIALOG_STYLE_MSGBOX, ""C_WHITE"Статистика", string, "Назад", "Выход");
}

dResponse:DlgMenuStats(playerid)
{
    if(response)
        Dialog_Show(playerid, Dialog:DlgPlayerMenu);
    else
        CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = false;
    return 1;
}