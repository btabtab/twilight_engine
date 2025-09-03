#include "WizardPage.hpp"

WizardPage::WizardPage(Texture *wizard_texture, std::string new_page_title, std::vector<std::string> new_text_to_show)
{
    does_have_a_hole = false;
    is_the_holy_wizard_of_testing_visible = false;
    holy_testing_wizard_texture = wizard_texture;
    page_title = new_page_title;
    text_to_show = new_text_to_show;
    is_debug_page = false;
}
std::vector<std::string> *WizardPage::getText()
{
    return &text_to_show;
}
void WizardPage::toggleHole()
{
    does_have_a_hole = !does_have_a_hole;
}
void WizardPage::toggleDebugPage()
{
    is_debug_page = !is_debug_page;
}
bool WizardPage::isDebugPage()
{
    return is_debug_page;
}
void WizardPage::addText(std::string text_to_add)
{
    text_to_show.push_back(text_to_add);
}
bool WizardPage::heIsThere()
{
    return is_the_holy_wizard_of_testing_visible;
}
void WizardPage::summonOrUnsummonHim()
{
    is_the_holy_wizard_of_testing_visible = !is_the_holy_wizard_of_testing_visible;
}
void WizardPage::draw()
{
    DrawText("Wizard Panel", 0, 0, 5, BLACK);
    if (!does_have_a_hole && is_the_holy_wizard_of_testing_visible)
    {
        DrawTexture(*holy_testing_wizard_texture, (GetScreenWidth() / 2) - 128, (GetScreenHeight() / 2) - 128, RAYWHITE);
    }
    for (int i = 0; i != text_to_show.size(); i++)
    {
        DrawText(text_to_show.at(i).c_str(), 10, i * 10, 5, WHITE);
    }
}
bool WizardPage::isThereAHole()
{
    return does_have_a_hole;
}