#ifndef BUTTON__H
#define BUTTON__H
#include "common.h"

class Button
{
	public:
		Button(sf::IntRect _rect, sf::Vector2f _position);
		~Button();

		void Update(sf::RenderWindow& _window, float _dt);
		bool Click(sf::RenderWindow& _window);
		void Release();


		static void SetSprite(sf::Sprite* _sprite);

		sf::Vector2f m_position;

		void Draw(sf::RenderTarget& _window);

		sf::Color m_color;
		
protected:
	bool Hovered(sf::RenderWindow& _window);
	sf::IntRect m_rect;
	bool m_isClicked;
	bool m_isReleased;
	bool m_overred;
	float m_timer;
	float m_timerMax;
};

#endif // !BUTTON__H
