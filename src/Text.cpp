#include "Text.hpp"

#include <SFML/Graphics/Vertex.hpp>
#include <iostream>

Text::Text(const std::string& str) : m_text{str} {}

Text::Text(const std::string& str, const sf::Font& font, int size) :
  m_text{str},
  m_font{&font},
  m_fontSize{size},
  m_needUpdate{true}
{
}

void Text::setString(const std::string& str) {
  m_text = str;
  m_needUpdate = true;
}

void Text::setFontSize(int size) {
  m_fontSize = size;
  m_needUpdate = true;
}

void Text::setFont(const sf::Font* font) {
  m_font = font;
  m_needUpdate = true;
}

void Text::setFillColor(const sf::Color& color) {
  m_color = color;
  if (!m_needUpdate) {
    for (int i = 0; i < m_vertices.getVertexCount(); ++i) {
      m_vertices[i].color = m_color;
    }
  }
}

void Text::setWidth(float width) {
  m_textWidth = width;
  m_needUpdate = true;
}

void addGlyphQuad(sf::VertexArray& vertices, const sf::Glyph& glyph,
    const sf::Vector2f& pos, const sf::Color& color)
{
  static constexpr float padding = 1.f;
  float left = glyph.bounds.left - padding;
  float top = glyph.bounds.top - padding;
  float right = glyph.bounds.left + glyph.bounds.width + padding;
  float bottom = glyph.bounds.top + glyph.bounds.height + padding;

  float u1 = static_cast<float>(glyph.textureRect.left) - padding;
  float v1 = static_cast<float>(glyph.textureRect.top) - padding;
  float u2 = static_cast<float>(glyph.textureRect.left + glyph.textureRect.width) + padding;
  float v2 = static_cast<float>(glyph.textureRect.top  + glyph.textureRect.height) + padding;

  vertices.append(sf::Vertex(
        sf::Vector2f(pos.x + left, pos.y + top),
        color,
        sf::Vector2f(u1,v1)));
  vertices.append(sf::Vertex(
        sf::Vector2f(pos.x + right, pos.y + top),
        color,
        sf::Vector2f(u2,v1)));
  vertices.append(sf::Vertex(
        sf::Vector2f(pos.x + left, pos.y + bottom),
        color,
        sf::Vector2f(u1,v2)));


  vertices.append(sf::Vertex(
        sf::Vector2f(pos.x + left, pos.y + bottom),
        color,
        sf::Vector2f(u1,v2)));
  vertices.append(sf::Vertex(
        sf::Vector2f(pos.x + right, pos.y + top),
        color,
        sf::Vector2f(u2,v1)));
  vertices.append(sf::Vertex(
        sf::Vector2f(pos.x + right, pos.y + bottom),
        color,
        sf::Vector2f(u2,v2)));
  std::cout << "pos: " << pos.x << ", " << pos.y << "\n";
}

void Text::updateGeometrie() const {
  if (m_font &&
      ( m_needUpdate
        || m_fontTextureId != m_font->getTexture(m_fontSize).getNativeHandle())) {
    m_fontTextureId = m_font->getTexture(m_fontSize).getNativeHandle();
    m_needUpdate = false;

    m_vertices.clear();
    m_boundingBox = sf::Rect<float>();

    if(m_text.size() == 0) {
      return;
    }

    const float whiteSpaceWidth
       = m_font->getGlyph(L' ', m_fontSize, false).advance * 4.f/3.f;
    const float letterSpaceing = whiteSpaceWidth / 4.f;
    const float lineSpaceing = m_font->getLineSpacing(m_fontSize);

    sf::Vector2f pos(0,m_fontSize);
    uint32_t prevChar = 0;
    for (int i = 0; i < m_text.size(); ++i) {
      uint32_t curChar = m_text[i];
      if (curChar == '\r') {
        continue;
      }

      pos.x += m_font->getKerning(prevChar, curChar, m_fontSize);
      prevChar = curChar;

      if (curChar == '\t') {
        pos.x += whiteSpaceWidth * 4;
        continue;
      } else if (curChar == ' ') {
        pos.x += whiteSpaceWidth;
        continue;
      } else if (curChar == '\n') {
        pos.y += lineSpaceing;
        pos.x = 0;
        continue;
      }

      const sf::Glyph&  glyph = m_font->getGlyph(curChar, m_fontSize, false);
      addGlyphQuad(m_vertices, glyph, pos, m_color);
      pos.x += glyph.advance + letterSpaceing;

    }
  }
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (m_font) {
    updateGeometrie();
    states.transform *= getTransform();
    states.texture = &m_font->getTexture(m_fontSize);
    target.draw(m_vertices, states);
  }
}
