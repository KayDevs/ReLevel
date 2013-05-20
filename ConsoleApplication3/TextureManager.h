#pragma once
#include "sfml.h"
#include <iostream>
/*
 * ImageManager class from LaurentGomila's SFML tutorial
 * https://github.com/LaurentGomila
 *
 * edited slightly: 
 * uses textures, and uses my preferred coding style rather than theirs
 * */

class TextureManager
{
	public:
		TextureManager();
		~TextureManager();
	private:
		TextureManager(const TextureManager&);
		TextureManager& operator =(const TextureManager&);
	public:
		const sf::Texture& getTexture(const std::string& filename);
		void deleteTexture(const sf::Texture& texture);
		void deleteTexture(const std::string& filename);
	private:
		std::map<std::string, sf::Texture> textures_;
};
