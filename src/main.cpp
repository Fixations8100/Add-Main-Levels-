#include <Geode/Geode.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>

using namespace geode::prelude;

// Modyfikujemy warstwę wyboru poziomów głównych (LevelSelectLayer)
class $modify(LevelSelectLayer) {
    bool init(int page) {
        // Najpierw ładujemy oryginalną zawartość menu gry
        if (!LevelSelectLayer::init(page)) {
            return false;
        }

        // Tworzymy ikonę plusa (+) z tekstur gry
        auto plusSprite = CCSprite::createWithSpriteFrameName("GJ_plusBtn_001.png");
        if (!plusSprite) return true;

        // Tworzymy przycisk, który po kliknięciu wywoła funkcję onAddNewLevel
        auto plusBtn = CCMenuItemSpriteExtra::create(
            plusSprite,
            this,
            menu_selector(LevelSelectLayer::onAddNewLevel)
        );

        // Tworzymy menu i ustawiamy przycisk po lewej stronie ekranu
        auto menu = CCMenu::create();
        menu->addChild(plusBtn);
        menu->setPosition({ 40, 160 }); // Pozycja X i Y na ekranie
        
        this->addChild(menu);

        return true;
    }

    // Funkcja wywoływana po kliknięciu plusa
    void onAddNewLevel(CCObject* sender) {
        auto newLevel = GJGameLevel::create();
        newLevel->m_levelType = GJLevelType::Local;
        
        auto editorLayer = LevelEditorLayer::scene(newLevel, false);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, editorLayer));
    }
};
