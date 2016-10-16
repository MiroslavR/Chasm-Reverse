#include "menu.hpp"

namespace PanzerChasm
{

/*
CONSOLE.CEL
FONT256.CEL // Chars, keys
M_NETWORK.CEL
LFONT2.CEL // only numbers
LOADING.CEL
M_MAIN.CEL
M_NETWORK.CEL
M_NEW.CEL
M_PAUSE.CEL
M_TILE1.CEL

*/

using KeyCode= SystemEvent::KeyEvent::KeyCode;

// Menu base

class MenuBase
{
public:
	MenuBase( MenuBase* const parent_menu );
	virtual ~MenuBase();

	MenuBase* GetParent() const;

	virtual void Draw() = 0;

	// Returns next menu after event
	virtual MenuBase* ProcessEvent( const SystemEvent& event )= 0;

private:
	MenuBase* const parent_menu_;
};

MenuBase::MenuBase( MenuBase* const parent_menu )
	: parent_menu_(parent_menu)
{}

MenuBase::~MenuBase()
{}

MenuBase* MenuBase::GetParent() const
{
	return parent_menu_;
}

// Main menu

class MainMenu final : public MenuBase
{
public:
	MainMenu();
	~MainMenu() override;

	virtual void Draw() override;
	virtual MenuBase* ProcessEvent( const SystemEvent& event ) override;
private:
};

MainMenu::MainMenu()
	: MenuBase( nullptr )
{}

MainMenu::~MainMenu()
{}

void MainMenu::Draw()
{
}

MenuBase* MainMenu::ProcessEvent( const SystemEvent& event )
{
	return this;
}

// Quit Menu

class QuitMenu final : public MenuBase
{
public:
	QuitMenu();
	~QuitMenu() override;

	virtual void Draw() override;
	virtual MenuBase* ProcessEvent( const SystemEvent& event ) override;
private:
};

QuitMenu::QuitMenu()
	: MenuBase( nullptr )
{}

QuitMenu::~QuitMenu()
{}

void QuitMenu::Draw()
{}

MenuBase* QuitMenu::ProcessEvent( const SystemEvent& event )
{
	switch( event.type )
	{
	case SystemEvent::Type::Key:
		if(
			event.event.key.pressed &&
			event.event.key.key_code == KeyCode::Enter )
		{
			// TODO - quit here
		}
		break;

	default:
		break;
	}

	return this;
}

// Menu

Menu::Menu(
	unsigned int viewport_width ,
	unsigned int viewport_height,
	const GameResourcesPtr& game_resources )
	: text_draw_( viewport_width, viewport_height, *game_resources )
{
}

Menu::~Menu()
{
}

void Menu::ProcessEvents( const SystemEvents& events )
{
	for( const SystemEvent& event : events )
	{
		switch( event.type )
		{
		case SystemEvent::Type::Key:
			if(
				event.event.key.pressed &&
				event.event.key.key_code == KeyCode::Escape )
			{
				if( current_menu_ != nullptr )
					current_menu_= current_menu_->GetParent();
				else
					current_menu_= current_menu_->GetParent();
			}
			break;

		case SystemEvent::Type::MouseKey: break;
		case SystemEvent::Type::MouseMove: break;
		case SystemEvent::Type::Wheel: break;
		case SystemEvent::Type::Quit: break;
		};

		if( current_menu_ != nullptr )
			current_menu_= current_menu_->ProcessEvent( event );
	}
}

void Menu::Draw()
{
	if( current_menu_ )
		current_menu_->Draw();

	int y= 0;

	text_draw_.Print( 10, y, "QUICK BROWN FOX JUMPS OVER THE LAZY DOG", 3 );
	y+= text_draw_.GetLineWidth() * 3 ;
	text_draw_.Print( 10, y, "Quick brown fox jumps over the lazy dog", 3 );
	y+= text_draw_.GetLineWidth() * 3 ;
	text_draw_.Print( 10, y, "123456789", 3 );
	y+= text_draw_.GetLineWidth() * 3 ;
	text_draw_.Print( 10, y, "level 1  health 100", 3 );
}

} // namespace PanzerChasm