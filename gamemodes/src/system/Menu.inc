/*      [ ПУНКТЫ В МЕНЮ ]      */
/*      [ MENU ITEMS ]      */
new const Strings_Menu[2][] = {
    "Статистика",
    "Настройки"
};

/*      [ ========== ========== ========== ========== ========== ]      */

dCreate:Dlg_Player_Menu(playerid)
{
    new temp[26+(-2+2)+(-2+(MAX_PLAYER_NAME*2))];
    new string[sizeof(temp)*sizeof(Strings_Menu)];
    for(new i = 0; i < sizeof(Strings_Menu); i++)
    {
        format(temp, sizeof(temp), ""C_GRAY"[%d] "C_WHITE"%s\n", i+1, Strings_Menu[i]);
        strcat(string, temp, sizeof(string));
    }
    return Dialog_Open(playerid, Dialog:Dlg_Player_Menu, DIALOG_STYLE_LIST, ""C_WHITE"Меню", string, "Выбрать", "Выход");
}

dResponse:Dlg_Player_Menu(playerid)
{
    if(response)
    {
        switch(listitem)
        {
            case 0: Dialog_Show(playerid, Dialog:Dlg_Menu_Stats);
            default: SCM(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Данный раздел находится в разработке.");
        }
    }
    else
        CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = false;
    return 1;
}

dCreate:Dlg_Menu_Stats(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\cСтатистика персонажа\n\
    "C_WHITE"\\c%s %s\n\n\
    "C_WHITE"\\cУровень: %d\n\
    "C_WHITE"\\cОпыт: %d/%d\n\n\
    "C_WHITE"\\cНаличные: %d$\n\
    "C_WHITE"\\cБанковский счёт: %d$\n\n";
    new string[sizeof(message)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+3)+(-2+3)+(-2+3)+(-2+9)+(-2+11)];
    format(string, sizeof(string), message, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], CInfo[playerid][PInfo[playerid][CharacterSelect]][Level], CInfo[playerid][PInfo[playerid][CharacterSelect]][Exp], Level_Need_Exp(playerid, PInfo[playerid][CharacterSelect]), CInfo[playerid][PInfo[playerid][CharacterSelect]][Money], 0);
    return Dialog_Open(playerid, Dialog:Dlg_Menu_Stats, DIALOG_STYLE_MSGBOX, ""C_WHITE"Статистика", string, "Назад", "Выход");
}

dResponse:Dlg_Menu_Stats(playerid)
{
    if(response)
        Dialog_Show(playerid, Dialog:Dlg_Player_Menu);
    else
        CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = false;
    return 1;
}