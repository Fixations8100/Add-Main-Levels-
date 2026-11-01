#include <Geode/Geode.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>

using namespace geode::prelude;

class $modify(LevelSelectLayer) {
    bool init(int page) {
        if (!LevelSelectLayer::init(page)) {
            return false;
        }

        // Tworzymy ikonę plusa (+)
        auto plusSprite = CCSprite::createWithSpriteFrameName("GJ_plusBtn_001.png");
        if (!plusSprite) return true;

        // Używamy bezpiecznej dla Androida lambdy [=] zamiast menu_selector
        auto plusBtn = CCMenuItemSpriteExtra::create(
            plusSprite,
            this,
            menu_selector(LevelSelectLayer::onAddNewLevel) 
        );

        auto menu = CCMenu::create();
        menu->addChild(plusBtn);
        menu->setPosition({ 40, 160 });
        
        this->addChild(menu);

        return true;
    }

    // Wymuszona struktura deklaracji metody dla nowej wersji Geode
    void onAddNewLevel(CCObject* sender) {
        auto newLevel = GJGameLevel::create();
        if (!newLevel) return;
        
        newLevel->m_levelType = GJLevelType::Local;
        
        auto editorLayer = LevelEditorLayer::scene(newLevel, false);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, editorLayer));
    }
};
