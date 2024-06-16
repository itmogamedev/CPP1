
#ifndef AssetManager_hpp
#define AssetManager_hpp
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio.hpp>

class AssetManager
{

public:
    AssetManager();

    static sf::Texture& GetTexture(std::string const& filename);
    static sf::SoundBuffer& GetSoundBuffer(std::string const& filename);
    static sf::Font& GetFont(std::string const& filename);
private:

    std::map<std::string, sf::Texture> m_Textures;
    std::map<std::string, sf::SoundBuffer> m_SoundBuffer;
    std::map<std::string, sf::Font> m_Fonts;

    static AssetManager* sInstance;
};
#endif /* AssetManager_hpp */
