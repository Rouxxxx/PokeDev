#pragma once
#include <SFML/Graphics.hpp>

class Window
{
public:
    Window(const std::string& windowName);
    void Update();

    void BeginDraw();
    void Draw(const sf::Drawable& drawable);
    void EndDraw();
    bool IsOpen() const;
    sf::Vector2u GetCentre() const;

    const sf::View& GetView() const;
    void SetView(const sf::View& view);
    sf::FloatRect GetViewSpace() const;
private:
    sf::RenderWindow window;
    sf::Vector2u centre;
};
