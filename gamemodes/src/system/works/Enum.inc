/*      [ ПЕРЕМЕННЫЕ РАБОТЫ ГРУЗЧИКА (сервер) ]      */
/*      [ LOADER'S WORK VARIABLES (server) ]      */
enum WorkLoaderInfo
{
    ActorID,
    STREAMER_TAG_3D_TEXT_LABEL:Actor3DText
}
new WLInfo[MAX_INITIAL_WORKS][WorkLoaderInfo];

/*      [ ПЕРЕМЕННЫЕ РАБОТЫ ГРУЗЧИКА (игрок) ]      */
/*      [ LOADER'S WORK VARIABLES (player) ]      */
enum PlayerWorkLoaderInfo
{
    MovedBoxCount,
    STREAMER_TAG_CP:Checkpoint,
    bool:IsBoxPickup
}
new PlayerWLInfo[MAX_PLAYERS][PlayerWorkLoaderInfo];