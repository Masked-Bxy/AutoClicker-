#ifndef COMMON__H
#define COMMON__H

#include <iostream>
#include <time.h>
#include <stdio.h>

#include <Windows.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

float Clamp(float _current, float _min, float _max);
int Clamp(int _current, int _min, int _max);
sf::Vector2f Normalize(sf::Vector2f _vec);
std::string_view GetShader();
sf::Sprite LoadSprite(const std::string _path, bool _isCentered);
void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, float _angle, sf::Color _color, sf::RenderWindow& _window);
sf::Vector2f LerpV2F(sf::Vector2f _current, sf::Vector2f _target, float _t);
sf::Color GetColorFromPer(float _r, float _g, float _b, float _a);

#endif