#ifndef AssetManager_hpp
#define AssetManager_hpp

#include "includes.h"

class AssetManager {

public:
    AssetManager();

    static sf::Texture &GetTexture(std::string const &filename);

    static sf::Font &GetFont(std::string const &filename);

private:

    std::map<std::string, sf::Texture> m_Textures;
    std::map<std::string, sf::Font> m_Fonts;

    static AssetManager *sInstance;
};

#endif
