#include "TextureManager.h"

const sf::Texture& TextureManager::getTexture(const std::string& filename)
{
	for(auto it = textures_.begin(); it!= textures_.end(); ++it)
	{
		if(filename == it->first)
		{
			std::cout << "USING EXISTING TEXTURE."<<std::endl;
			return it->second;
		}
	}

	sf::Texture texture;
	if(texture.loadFromFile(filename))
	{
		textures_[filename] = texture;
		std::cout << "LOADING TEXTURE."<<std::endl;
		return textures_[filename];
	}

	std::cout << "ERROR: Texture not found. Empty texture put in place."<<std::endl;
	textures_[filename] = texture;
	return textures_[filename];
}

void TextureManager::deleteTexture(const sf::Texture& texture)
{
	for(auto it = textures_.begin(); it !=  textures_.end(); ++it)
	{
		if(&texture == &it->second)
		{
			textures_.erase(it);
			return;
		}
	}
}

void TextureManager::deleteTexture(const std::string& filename)
{
	auto it = textures_.find(filename);
	if(it != textures_.end())
		textures_.erase(it);
}
