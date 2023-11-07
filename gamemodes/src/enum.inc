/*      [ ПЕРЕМЕННЫЕ ДЛЯ ИГРОКА ]      */
/*      [ PLAYER INFORMATION ]      */
enum PlayerInfo
{
    bool:IsConnection,
    bool:IsLogged,
    AuthorizationTime,
    AuthorizationCountTry,

    ID,
    Nick[MAX_PLAYER_NAME],
    Password[MAX_PASSWORD_LEN],
    Email[MAX_EMAIL_LEN],
    Donate,
    RegIP[16],
    LastIP[16],
    RegDate[22],
    LastDate[22],

    CharactersCount,
    CharacterSelect
}
new PInfo[MAX_PLAYERS][PlayerInfo];

/*      [ ПЕРЕМЕННЫЕ ТАЙМЕРА ДЛЯ ИГРОКА ]      */
/*      [ TIMER VARIABLES FOR THE PLAYER ]      */
enum PlayerTimerInfo
{
    Authorization,
    Kicks,
    Animation,

    Second
}
new PTimerInfo[MAX_PLAYERS][PlayerTimerInfo];

/*      [ ПЕРЕМЕННЫЕ КИКА ДЛЯ ИГРОКА ]      */
/*      [ KICK VARIABLES FOR THE PLAYER ]      */
enum PlayerKickInfo
{
    Author[MAX_PLAYER_NAME],
    Reason[MAX_PLAYER_NAME*2]
}
new PKickInfo[MAX_PLAYERS][PlayerKickInfo];

/*      [ ПЕРЕМЕННЫЕ С AFK ДЛЯ ИГРОКА ]      */
/*      [ VARIABLES WITH AFK FOR THE PLAYER ]      */
enum PlayerAFKInfo
{
    bool:IsTrue,
    Time,
    Float:Position[3]
}
new PAFKInfo[MAX_PLAYERS][PlayerAFKInfo];

/*      [ ПЕРЕМЕННЫЕ ДЛЯ ПЕРСОНАЖА ]      */
/*      [ VARIABLES FOR THE CHARACTER ]      */
enum CharacterInfo
{
    bool:IsSpawning,
    bool:IsDialogActive,

    ID,
    Login[MAX_PLAYER_NAME],
    FirstName[MAX_PLAYER_NAME],
    LastName[MAX_PLAYER_NAME],
    FullName[MAX_PLAYER_NAME],
    Age,
    Sex,
    Race,
    Skin,
    Level,
    Exp,
    ExpTime,
    RegIP[16],
    LastIP[16],
    RegDate[22],
    LastDate[22],
    Float:Position[3],
    Float:Rotation,
    Interior,
    VirtualWorld,
    Float:Health,
    Float:Armour,
    AdminLevel,
    AdminPassword,
    bool:IsAdmin,
    Money,
    MoneyTime,
    bool:Working,
    WorkingType
}
new CInfo[MAX_PLAYERS][MAX_CHARACTERS][CharacterInfo];

/*      [ ПЕРЕМЕННЫЕ АДМИНИСТРАТОРА ПРИ НАБЛЮДЕНИИ ]      */
/*      [ ADMINISTRATOR VARIABLES DURING MONITORING ]      */
enum AdminSpectateInfo
{
    bool:Toggle,
    Float:Position[3],
    Float:Rotation,
}
new ASInfo[MAX_PLAYERS][AdminSpectateInfo];