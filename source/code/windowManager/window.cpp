#include "window.h"

Window::Window(const std::string& windowName)
    : window(sf::VideoMode(1034, 800), windowName, sf::Style::Titlebar | sf::Style::Close), size(window.getSize())
{
    window.setVerticalSyncEnabled(true);
    centre = sf::Vector2u(window.getSize().x / 2, window.getSize().y / 2);
}
void Window::Update() {
    sf::Event event;
    if (window.pollEvent(event))
        if (event.type == sf::Event::Closed)
            window.close();
}
void Window::BeginDraw() {
    window.clear(sf::Color::White);
}
void Window::Draw(const sf::Drawable& drawable) {
    window.draw(drawable);
}
void Window::EndDraw() {
    window.display();
}
bool Window::IsOpen() const {
    return window.isOpen();
}
sf::Vector2u Window::GetCentre() const {
    return centre;
}

const sf::View& Window::GetView() const {
    return window.getView();
}
void Window::SetView(const sf::View& view) {
    window.setView(view);
}

sf::FloatRect Window::GetViewSpace() const
{
    const sf::View& view = GetView();
    const sf::Vector2f& viewCenter = view.getCenter();
    const sf::Vector2f& viewSize = view.getSize();
    sf::Vector2f viewSizeHalf(viewSize.x * 0.5f, viewSize.y * 0.5f);
    sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
    return viewSpace;
}