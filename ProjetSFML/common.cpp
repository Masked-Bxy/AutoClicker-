#include "common.h"

const std::string_view fragmentShader = \
"uniform sampler2D texture;" \
"uniform vec3 color;" \
"void main()" \
"{" \
"vec2 texCoord = gl_TexCoord[0].xy;"\
"vec3 sceneCol = texture2D(texture, texCoord).rgb;"\
"   gl_FragColor = vec4(color*sceneCol, 1);  " \
"}";

float Clamp(float _current, float _min, float _max)
{
	if (_current < _min)
	{
		return _min;
	}
	else if (_current > _max)
	{
		return  _max;
	}
	return _current;
}

int Clamp(int _current, int _min, int _max)
{
	if (_current < _min)
	{
		return _min;
	}
	else if (_current > _max)
	{
		return  _max;
	}
	return _current;
}

sf::Vector2f Normalize(sf::Vector2f _vec)
{
	float length = sqrt(_vec.x * _vec.x + _vec.y * _vec.y); 
	std::cout << length << "long" << std::endl;
	if (length != 0) 
	{
		return _vec / length;
	}
	return sf::Vector2f(0,0);
}

std::string_view GetShader()
{
	return fragmentShader;
}

sf::Sprite LoadSprite(const std::string _path, bool _isCentered)
{
	//Création et chargement de la texture
	sf::Texture* tempTex = new sf::Texture(); //Nécessaire dynamiquement
	tempTex->loadFromFile(_path);

	//Création et configuration du sprite
	sf::Sprite tempSprite(*tempTex);

	if (_isCentered) //Centrage du sprite
	{
		sf::Vector2u tempTaille = tempTex->getSize();
		sf::Vector2f tempOrigin = sf::Vector2f(tempTaille.x / 2, tempTaille.y / 2);
		tempSprite.setOrigin(tempOrigin);
	}

	return tempSprite;
}

void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, float _angle, sf::Color _color, sf::RenderWindow& _window)
{
	_sprite.setRotation(sf::degrees(_angle));
	_sprite.setPosition(_pos);
	_sprite.setColor(_color);
	_window.draw(_sprite);
}

sf::Vector2f LerpV2F(sf::Vector2f _current, sf::Vector2f _target, float _t)
{
	return _current + _t * (_target - _current);
}

sf::Color GetColorFromPer(float _r, float _g, float _b, float _a)
{
	uint8_t r = _r * 255;
	uint8_t g = _g * 255;
	uint8_t b = _b * 255;
	uint8_t a = _a * 255;
	return sf::Color{r,g,b,a};
}
