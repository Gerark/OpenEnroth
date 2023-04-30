#pragma once
#include <vector>
#include <string>

#include "GUI/GUIWindow.h"

class GUIWindow_CharacterRecord : public GUIWindow {
 public:
    GUIWindow_CharacterRecord(unsigned int uActiveCharacter, CURRENT_SCREEN screen);
    virtual ~GUIWindow_CharacterRecord() {}

    virtual void Update();

    void ShowStatsTab();
    void ShowSkillsTab();
    void ShowInventoryTab();
    void ShowAwardsTab();
    void ToggleRingsOverlay();

 protected:
    void CharacterUI_StatsTab_Draw(struct Player *);
    void CharacterUI_SkillsTab_Draw(struct Player *);

    /**
     * @offset 0x41A000
     */
    void CharacterUI_AwardsTab_Draw(struct Player *);

    void CharacterUI_SkillsTab_CreateButtons();

    /**
     * @offset 0x419100
     */
    void fillAwardsData();

    std::string getAchievedAwardsString(int idx);
    void scrollAwardsUp(GUIWindow &window);
    void scrollAwardsDown(GUIWindow &window);

 private:
    int awardsCharacterId = -1;
    int startAwardElem = 0;
    bool awardLimitReached = false;
    std::vector<int> achievedAwardsList;
};

bool ringscreenactive();
static void CharacterUI_DrawItem(int x, int y, ItemGen *item, int id, Texture *item_texture = nullptr, bool doZDraw = false);

class Image;
extern Image *ui_character_skills_background;
extern Image *ui_character_awards_background;
extern Image *ui_character_stats_background;
extern Image *ui_character_inventory_background;
extern Image *ui_character_inventory_background_strip;
extern Image *ui_character_inventory_paperdoll_background;

extern std::array<Image *, 16> paperdoll_dbrds;
extern bool awardButtonUpClicked;
extern bool awardButtonDownClicked;
extern bool awardScrollUpClicked;
extern bool awardScrollDownClicked;
