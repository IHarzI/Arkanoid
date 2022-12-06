
#include <vector>
#include <stdlib.h> 

#include "Framework.h"
#include "GameWorld.h"
#include "Window.h"
#include "TextureManager.h"

#include <regex>
/* Test Framework realization */
// made by T-T


#define BACKGROUNDTEXTUREPATH "Textures/Background.png"

class GameFramework : public Framework {

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen) override
	{
		bool IsWindowSizeSetted = false;
		while (!IsWindowSizeSetted)
		{
			int option = 0;
			std::printf("\n[1024x768 -- 1]\n[1280x1024 -- 2]\n[1366x768 -- 3]\n[1600x900 -- 4]\n[1920x1080 -- 5]\nChoose screen resolution: ");
			char str{};
			std::cin >> str;
			switch (str)
			{
			case '1':
				window.PreInit(1024, 768);
				IsWindowSizeSetted = true;
				break;
			case '2':
				window.PreInit(1280, 1024);
				IsWindowSizeSetted = true;
				break;
			case '3':
				window.PreInit(1366, 768);
				IsWindowSizeSetted = true;
				break;
			case '4':
				window.PreInit(1600, 900);
				IsWindowSizeSetted = true;
				break;
			case '5':
				window.PreInit(1920, 1080);
				IsWindowSizeSetted = true;
				break;
			default:
				std::printf("\n########### Invalid optin ###########\n");
				break;
			}
		}
		std::printf("\n ------------------------- Done! -------------------------");

		fullscreen = false;
		width = window.GetWidth();
		height = window.GetHeight();
		
		std::printf("\n[Print] 1, if you want fullscreen mode, otherwise [Print] 0 (or any other symbol): ");
		char str{};
		std::cin >> str;
		if (str=='1')
			fullscreen = true;

		std::printf("\n[GUIDE] Press the LEFT / RIGHT arrow to control your platform. LEFT MOUSE BUTTON to launch a ball. \n Once the ball is launched, you can't to launch it again. \nIf you LOOSE a ball to the bottom of the screen, the game will restart\n");
		std::printf("\n Press ENTER, if you ready to play.\n");
			std::cin >> str;
		showCursor(true);

		
	}



	virtual bool Init() override
	{
		internalTextures_.BackgroundInit(window.GetWidth(), window.GetHeight(), BACKGROUNDTEXTUREPATH);
		if(!m_gameworld.init(&internalTextures_, &window));
			return true;
		return true;
	}

	virtual void Close() override
	{

	}

	virtual bool Tick() override
	{
		drawSprite(internalTextures_.GetTexture(NONE_ENTITY), 0, 0);

		double timestep = (double)(getTickCount() - LastTime);

		if (timestep < framerate)
		{
			m_gameworld.draw();

			return false;
		}

		m_gameworld.onKeyPressed((Key)HoveredKey_);
		m_gameworld.update(timestep);
		m_gameworld.draw();

		LastTime = getTickCount();

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) override
	{
		window.OnMouseMove(x, y, xrelative, yrelative);
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) override
	{
		m_gameworld.onMouseButtonClick((MouseButton)button, isReleased);
	}

	virtual void onKeyPressed(FRKey k) override
	{
		
		HoveredKey_ = k;
	}

	virtual void onKeyReleased(FRKey k) override
	{
		m_gameworld.onKeyReleased((Key)k);
		if(HoveredKey_==k)
			HoveredKey_ = FRKey::COUNT;
	}

	virtual const char* GetTitle() override
	{
		return Title;
	}
private:


	//
	uint32_t LastTime = 0;
	FRKey HoveredKey_ = FRKey::COUNT;
	TextureManager internalTextures_;
	Window window;
	GameWorld m_gameworld;
	const char* Title = "Arkanoid Techno-Tomato Edition";
};



int main(int argc, char* argv[])
{

	return run(new GameFramework);
}
