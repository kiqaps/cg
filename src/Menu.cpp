
#include "config.h"
#include "Menu.h"
#include "Utils.h"

Menu::Menu() { }
Menu::~Menu() 
{
    SDL_DestroyTexture(this->submenuMark);
    for (int i = 0; i < this->entries.size(); i++)
    {
        delete this->entries[i];
    }
}

Menu::Menu(SDL_Renderer* render, TTF_Font* font)
{
    this->render = render;
    this->font = font;
    this->height = 0;
    this->width = 0;

    Utils::CreateText(render, font, " >", {0x0, 0x0, 0x0}, &this->submenuMark, &this->submenuRect);
}

void Menu::Show(int x, int y)
{
    int fix_X = (x + this->width) - WINDOW_WIDTH,
        fix_Y = (y + this->height) - WINDOW_HEIGHT;

    fix_X = fix_X < 0 ? 0 : fix_X;
    fix_Y = fix_Y < 0 ? 0 : fix_Y;

    this->x = x - fix_X;
    this->y = y - fix_Y;
    this->showing = true;

    Uint32 sTicks;
    while (this->showing)
    {
        sTicks = SDL_GetTicks();

        this->ProcessInput();
        this->Draw();
        this->Update();

        Uint32 espera = 30 - (SDL_GetTicks() - sTicks);
        SDL_Delay(espera > 30 ? 30 : espera);
    }
}

void Menu::ProcessInput()
{
    SDL_Event evt;
    while (SDL_PollEvent(&evt))
    {
        if ((evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE) || (evt.type == SDL_MOUSEBUTTONDOWN && !(evt.button.x > this->x && evt.button.x < (this->x + this->width) && evt.button.y > this->y && evt.button.y < (this->y + this->height))))
            this->showing = false;
        else if (evt.type == SDL_MOUSEBUTTONDOWN && evt.button.button == SDL_BUTTON_LEFT && !this->clicked)
        {
            this->clicked = true;
            this->clickedX = evt.button.x;
            this->clickedY = evt.button.y;
        }
        else if (evt.type == SDL_MOUSEBUTTONUP && evt.button.button == SDL_BUTTON_LEFT && this->clicked)
        {
            int xx = this->x, yy = this->y;
            for (int i = 0; i < this->entries.size(); i++)
            {
                if (this->clickedX > xx && this->clickedX < xx + this->width && this->clickedY > yy && this->clickedY < yy + FONT_SIZE + 10)
                {
                    if (this->entries[i]->submenu)
                    {
                        Poligono clear(4);
                        clear[0] = { this->x - 1, this->y - 1 };
                        clear[1] = { this->x + this->width + 1 , this->y - 1 };
                        clear[2] = { this->x + this->width + 1, this->y + this->height + 1};
                        clear[3] = { this->x - 1, this->y + this->height + 1 };
                        clear.fill(this->render, 0xFF, 0xFF, 0xFF);
                        this->entries[i]->submenu->Show(this->x, this->y);
                    }
                    else
                        this->entries[i]->callback();
                    this->showing = false;
                    break;
                }
                yy += FONT_SIZE + 10;
            }
            this->clicked = false;
        }
        else if (evt.type == SDL_MOUSEMOTION)
        {
            this->curX = evt.motion.x;
            this->curY = evt.motion.y;
        }
    }
}

void Menu::Update()
{
    SDL_RenderPresent(this->render);
}

MenuEntry* Menu::AddNewEntry(std::string text)
{
    MenuEntry* entry = new MenuEntry(this, text);

    this->width = std::max(this->width, entry->getRect().w + 6 + this->submenuRect.w);
    this->height += FONT_SIZE + 10;
    this->entries.push_back(entry);
    return entry;
}

MenuEntry* Menu::AddNewEntry(std::string text, Menu* menu)
{
    menu->parent = this;
    MenuEntry* entry = new MenuEntry(this, text);
    entry->submenu = menu;

    this->width = std::max(this->width, entry->getRect().w + 6 + this->submenuRect.w);
    this->height += FONT_SIZE + 10;
    this->entries.push_back(entry);
    return entry;
}

MenuEntry* Menu::AddNewEntry(std::string text, std::function<void()> callback)
{
    MenuEntry* entry = new MenuEntry(this, text, callback);

    this->width = std::max(this->width, entry->getRect().w + 6 + this->submenuRect.w);
    this->height += FONT_SIZE + 10;
    this->entries.push_back(entry);
    return entry;
}

void Menu::Draw()
{
    if (this->showing)
    {
        int xx = this->x, yy = this->y;
        for (int i = 0; i < this->entries.size(); i++)
        {
            SDL_Rect dstRect = this->entries[i]->getRect();
            dstRect.x = xx + 3;
            dstRect.y = yy + 4;
    
            Poligono h(4);
            h[0] = {xx, yy};
            h[1] = {xx + this->width, yy};
            h[2] = {xx + this->width, yy + FONT_SIZE + 10};
            h[3] = {xx, yy + FONT_SIZE + 10};
    
            if (this->curX > xx && this->curX < xx + this->width && this->curY > yy && this->curY < yy + FONT_SIZE + 10)
                h.fill(this->render, 0xe7,0xe7,0xe8);
            else
                h.fill(this->render, 0xc4, 0xc6, 0xc7);
    
            if (this->clicked && (this->clickedX > xx && this->clickedX < xx + this->width && this->clickedY > yy && this->clickedY < yy + FONT_SIZE + 10))
                h.fill(this->render, 0x7e, 0x7e, 0x7f);
    
            h.draw(this->render, 0x3f, 0x40, 0x40);        
    
            SDL_RenderCopy(this->render, this->entries[i]->getTexture(), NULL, &dstRect);

            if (this->entries[i]->submenu)
            {
                SDL_Rect subdstRect = { xx + this->width - (this->submenuRect.w + 3), yy + 4, this->submenuRect.w, this->submenuRect.h };
                SDL_RenderCopy(this->render, this->submenuMark, NULL, &subdstRect);
            }

            yy += FONT_SIZE + 10;
        }
    }
}

SDL_Renderer* Menu::getRender() { return this->render; }
TTF_Font* Menu::getFont() { return this->font; }

MenuEntry::MenuEntry (Menu* menu, std::string text)
{
    this->menu = menu;
    this->text = text;

    this->callback = [] { /* callback vazio */ };

    Utils::CreateText(this->menu->getRender(), this->menu->getFont(), this->text.c_str(), {0x0, 0x0, 0x0, 0x0}, &(this->texture), &(this->rect));
}

MenuEntry::MenuEntry (Menu* menu, std::string text, std::function<void()> callback)
{
    this->menu = menu;
    this->text = text;
    this->callback = callback;

    Utils::CreateText(this->menu->getRender(), this->menu->getFont(), this->text.c_str(), {0x0, 0x0, 0x0, 0x0}, &(this->texture), &(this->rect));
}

MenuEntry::~MenuEntry()
{
    if (this->texture)
        SDL_DestroyTexture(this->texture);
    if (this->submenu)
        delete this->submenu;
}

std::string MenuEntry::getText()
{
    return this->text;
}

SDL_Texture* MenuEntry::getTexture() { return this->texture; }
SDL_Rect MenuEntry::getRect() { return this->rect; }