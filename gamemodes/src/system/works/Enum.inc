/*      [ ГРУЗЧИК (ЛВ) ]      */
/*      [ LOADER (LV) ]      */
enum WorkLoaderLVInfo // Сервер | Server
{
    ActorID,
    STREAMER_TAG_3D_TEXT_LABEL:Actor3DText
}
new WLLVInfo[MAX_INITIAL_WORKS][WorkLoaderLVInfo];

enum PlayerWorkLoaderLVInfo // Игрок | Player
{
    MovedBoxCount,
    STREAMER_TAG_CP:Checkpoint,
    bool:IsPickup
}
new PlayerWLLVInfo[MAX_PLAYERS][PlayerWorkLoaderLVInfo];

/*      [ ФЕРМЕР (ЛВ) ]      */
/*      [ FARMER (LV) ]      */
enum WorkFarmerLVInfo // Сервер | Server
{
    ActorID,
    STREAMER_TAG_3D_TEXT_LABEL:Actor3DText
}
new WFLVInfo[MAX_INITIAL_WORKS][WorkFarmerLVInfo];

enum PlayerWorkFarmerLVInfo // Игрок | Player
{
    MovedHayCount,
    STREAMER_TAG_CP:Checkpoint,
    bool:IsPickup
}
new PlayerWFLVInfo[MAX_PLAYERS][PlayerWorkFarmerLVInfo];