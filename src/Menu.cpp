#include "config.h"
#include "Menu.h"
#include "Utils.h"

Menu::Menu(SDL_Renderer* render, TTF_Font* font)
{
    this->render = render;
    this->font = font;
    this->height = 0;
    this->width = 0;
}

void Menu::AddNewEntry(MenuEntry entry)
{
    int size = entry.getText().size();
    this->width = std::max(this->width, (size * FONT_SIZE) + 10);
    this->height += FONT_SIZE + 10;
    this->entries.push_back(entry);
    this->_textures.push_back(NULL);
    this->_rects.push_back({0,0,0,0});
}

void Menu::Draw(int x, int y)
{
    int xx = x, yy = y;
    for (int i = 0; i < this->entries.size(); i++)
    {
        Poligono h(4);
        h[0] = {xx, yy};
        h[1] = {xx + this->width, yy};
        h[2] = {xx + this->width, yy + FONT_SIZE + 10};
        h[3] = {xx, yy + FONT_SIZE + 10};
        h.fill(this->render, 0xc4, 0xc6, 0xc7);
        h.draw(this->render, 0x3f, 0x40, 0x40);

        Utils::CreateText(this->render, this->font, this->entries[i].getText().c_str(), {0x0, 0x0, 0x0, 0x0}, &(this->_textures[i]), &(this->_rects[i]));
        this->_rects[i].x = xx + 3;
        this->_rects[i].y = yy + 4;
        SDL_RenderCopy(this->render, this->_textures[i], NULL, &(this->_rects[i]));

        yy += FONT_SIZE + 10;
    }
}

MenuEntry::MenuEntry (Menu* menu, std::string text)
{
    this->menu = menu;
    this->text = text;
    this->hasChild = false;
    this->child = NULL;
}

std::string MenuEntry::getText()
{
    return this->text;
}